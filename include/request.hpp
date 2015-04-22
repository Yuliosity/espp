//
// Created by Yury on 18/04/15.
//

#ifndef ESPP_REQUEST_HPP
#define ESPP_REQUEST_HPP

#include <memory>
#include "../deps/rapidjson/include/rapidjson/writer.h"
#include "json.hpp"
#include "query.hpp"

namespace espp {

class Request {
    Query _query;
    std::size_t _size = 0;

public:
    /*JsonValue toJSON()
    {
        JsonValue res(rapidjson::kObjectType);
        res["size"] = (unsigned)_size;
        return res;
    }*/

    void toJSON(JsonBuffer &buf)
    {
        buf.StartObject();
        buf.String("size");
        buf.Uint(_size);
        buf.EndObject();
    }

    Request && size(std::size_t size)
    {
        _size = size;
        return std::move(*this);
    }

    std::string toString()
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
