//
// Created by Yury on 18/04/15.
//

#ifndef ESPP_QUERY_HPP
#define ESPP_QUERY_HPP

#include "json.hpp"

namespace espp
{

class IQuery
{
public:
    virtual ~IQuery() {}
    virtual void toJSON(JsonBuffer &) = 0;
};

typedef Wrapper<IQuery> Query;

class MatchAllQ: public IQuery
{
public:
    void toJSON(JsonBuffer &buf)
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

    void toJSON(JsonBuffer &buf)
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
