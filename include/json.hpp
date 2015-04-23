#ifndef ESPP_JSON_HPP
#define ESPP_JSON_HPP

#define RAPIDJSON_HAS_STDSTRING 1
#include "../deps/rapidjson/include/rapidjson/document.h"
#include "../deps/rapidjson/include/rapidjson/writer.h"

#include <memory>
#include <type_traits>

namespace espp
{

typedef rapidjson::Value JsonValue;

typedef rapidjson::Writer<rapidjson::StringBuffer> JsonBuffer;

template<typename I>
class Wrapper: public I
{
    std::shared_ptr<I> _ptr;
public:
    template<typename T>
    Wrapper(T val):
        _ptr(std::make_shared<typename std::remove_reference<T>::type>(std::forward<T>(val)))
        //_ptr(new T(std::forward<T>(val)))
    {}
    /*Wrapper(I &&val):
        _ptr(std::make_shared(std::move(val))
    {}*/

    virtual void toJSON(JsonBuffer &buf) const
    {
        buf.StartObject();
        _ptr->toJSON(buf);
        buf.EndObject();
    }
};

template<typename T>
class Field
{
    std::string _name;
public:
    Field(std::string &&name):
        _name(name)
    {}
    const std::string &name() const
    {
        return _name;
    }
};

typedef JsonValue Value;
/*class Value
{
    JsonValue _val;
};*/

}

#endif //ESPP_JSON_HPP
