#ifndef ESPP_JSON_HPP
#define ESPP_JSON_HPP

#include "../deps/rapidjson/include/rapidjson/document.h"

namespace espp
{

typedef rapidjson::Value JsonValue;

typedef rapidjson::Writer<rapidjson::StringBuffer> JsonBuffer;

}

#endif //ESPP_JSON_HPP
