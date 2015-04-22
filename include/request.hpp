//
// Created by Yury on 18/04/15.
//

#ifndef ESPP_REQUEST_HPP
#define ESPP_REQUEST_HPP

#include <memory>
#include "json.hpp"
#include "query.hpp"

namespace espp {

class Request {
    Query _query;
    std::size_t _size = 10;

public:

    Request(Query &&query = MatchAllQ()):
        _query(std::move(query))
    {}


    /*JsonValue toJSON()
    {
        JsonValue res(rapidjson::kObjectType);
        res["size"] = (unsigned)_size;
        return res;
    }*/

    void toJSON(JsonBuffer &buf) const
    {
        buf.StartObject();
        buf.String("query");
        _query.toJSON(buf);
        buf.String("size");
        buf.Uint(_size);
        buf.EndObject();
    }

    Request && size(std::size_t size)
    {
        _size = size;
        return std::move(*this);
    }

    std::string toString() const
    {
        using namespace rapidjson;
        StringBuffer buf;
        Writer<StringBuffer> writer(buf);
        //toJSON().Accept(writer);
        toJSON(writer);
        return std::string(buf.GetString());
    }
};

}

#endif //ESPP_REQUEST_HPP
