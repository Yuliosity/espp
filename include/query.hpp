//
// Created by Yury on 18/04/15.
//

#ifndef ESPP_QUERY_HPP
#define ESPP_QUERY_HPP

#include <initializer_list>
#include <vector>
#include "json.hpp"

namespace espp
{

class IQuery
{
public:
    virtual ~IQuery() {}
    virtual void toJSON(JsonBuffer &) const = 0;
};

typedef Wrapper<IQuery> Query;


class BoolQ: public IQuery
{
    std::vector<Query> _must,
                       _should,
                       _mustNot;

    std::size_t _minimumShouldMatch = 0;

    static void printNonemptyArray(const char *name, const std::vector<Query> &v, JsonBuffer &buf)
    {
        if (v.size()) {
            buf.String(name);
            buf.StartArray();
            for (const auto &e: v)
                e.toJSON(buf);
            buf.EndArray();
        }
    }

public:
    BoolQ()
    {}

    BoolQ && must(std::initializer_list<Query> queries) &&
    {
        _must.insert(_must.end(), queries);
        return std::move(*this);
    }

    BoolQ && should(std::initializer_list<Query> queries) &&
    {
        _should.insert(_must.end(), queries);
        return std::move(*this);
    }

    BoolQ && minimumShouldMatch(std::size_t m) &&
    {
        _minimumShouldMatch = m;
        return std::move(*this);
    }

    void toJSON(JsonBuffer &buf) const
    {
        buf.String("bool");
        buf.StartObject();
        printNonemptyArray("must", _must, buf);
        printNonemptyArray("should", _should, buf);
        printNonemptyArray("mustNot", _mustNot, buf);
        if (_minimumShouldMatch != 0) {
            buf.String("minimum_should_match");
            buf.Uint(_minimumShouldMatch);
        }
        buf.EndObject();
    }

    BoolQ && operator &&(Query &&q1) &&
    {
        _must.push_back(q1);
        return std::move(*this);
    }

    BoolQ && operator ||(Query &&q1) &&
    {
        _should.push_back(q1);
        return std::move(*this);
    }
};

BoolQ operator&&(Query &&q1, Query &&q2)
{
    return BoolQ().must({q1, q2});
}

BoolQ && operator||(Query &&q1, Query &&q2)
{
    return BoolQ().should({q1, q2});
}


class MatchAllQ: public IQuery
{
public:
    void toJSON(JsonBuffer &buf) const
    {
        buf.String("match_all");
        buf.StartObject();
        buf.EndObject();
    }
};

class TermQ: public IQuery
{
    std::string _field;
    Value _val;
public:
    /* Typesafe variant when the field type is known */
    template<typename T>
    TermQ(const Field<T> &field, T &&val):
        _field(field.name()),
        _val(std::move(val))
    {}
    /* Dynamic variant where a field is accessed by name */
    template<typename T>
    TermQ(std::string &&field, T &&val):
        _field(std::move(field)),
        _val(std::move(val))
    {}

    void toJSON(JsonBuffer &buf) const
    {
        buf.String("term");
        buf.StartObject();
        buf.String(_field);
        _val.Accept(buf);
        buf.EndObject();
    }

};
/* TODO
Match Query
Multi Match Query
Bool Query
Boosting Query
Common Terms Query
Constant Score Query
Dis Max Query
Filtered Query
Fuzzy Like This Query
Fuzzy Like This Field Query
Function Score Query
Fuzzy Query
GeoShape Query
Has Child Query
Has Parent Query
Ids Query
Indices Query
Match All Query
More Like This Query
Nested Query
Prefix Query
Query String Query
Simple Query String Query
Range Query
Regexp Query
Span First Query
Span Multi Term Query
Span Near Query
Span Not Query
Span Or Query
Span Term Query
Term Query
Terms Query
Top Children Query
Wildcard Query
Minimum Should Match
Multi Term Query Rewrite
Template Query
*/

}

#endif //ESPP_QUERY_HPP
