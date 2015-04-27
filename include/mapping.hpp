
namespace espp
{

//Types which are mapped into Elasticsearch core types.
//http://www.elastic.co/guide/en/elasticsearch/reference/1.5/mapping-core-types.html
typedef std::string EsString;
typedef int EsInteger;
typedef double EsDouble;
typedef bool EsBoolean;
typedef void EsNull;

template<typename T>
const char * typeName();

template<>
const char * typeName<EsInteger> { return "integer"; }

template<>
const char * typeName<EsString> { return "string"; }

template<>
const char * typeName<EsBoolean> { return "boolean"; }

template<>
const char * typeName<EsDouble> { return "double"; }

//Composite types.
template<typename T>
typedef std::vector<T> EsArray<T>;

struct EsGeoPoint
{
    double lat, lon;
};

enum IndexEProp
{
    Analyzed,
    NotAnalyzed,
    NoIndex
};

//enum class?
enum TermVectorProp
{
    NoTV,
    YesTV,
    WithOffsets,
    WithPositions,
    WithPositionsOffsets
};

enum IndexOptionsProp
{
    Positions,
    Docs,
    Freqs
};

template<typename T>
class FieldInfo
{
    
};

template<>
class FieldInfo<EsInteger>
{
    unsigned char _precision_step;
};

template<typename T>
class Field
{
    std::string _name;
    EsDouble _boost = 1.0;
    T _null_value;
    FieldInfo<T> _info;
public:
    Field(std::string &&name):
        _name(name)
    {}
    const std::string &name() const
    {
        return _name;
    }
};

class Mapping
{
    std::string _name;
    struct FieldProp
    {
        std::string name;
        std::string type;
        IndexOption index_options;
        bool store;
        void toJSON(JsonBuffer &buf) const
        {
            buf.String(name);
            buf.StartObject(); {
                buf.String("type");
                buf.String(type);
                buf.String("store");
                buf.Bool(store);
            }
        }
    };
    std::vector<FieldProp> _fields;

public:
    template<typename T>
    void addField(const Field<T> &field)
    {
        field.emplace_back(field.name(), typeName<T>(), field.store());
    }
    void toJSON(JsonBuffer &buf) const
    {
        buf.String(_name);
        buf.StartObject(); {
            buf.String("properties");
            buf.StartObject(); {
                foreach (const auto &f: _fields)
                    f.toJSON(buf);
            }
        }
    }
};

}
