# espp
An API for working with Elasticsearch in a convenient and type-safe way. Can be used both as a standalone tool and in chain with [cpp-elasticsearch API](https://github.com/QHedgeTech/cpp-elasticsearch). Currently C++11 only.

The main goal is to provide eDSL which directly represents Elasticsearch query DSL. For example, a query
```
{
    "query": {
        "filtered" : {
            "query" : {
                "query_string" : {
                    "query" : "some query string here",
                    "default_operator": "AND"
                }
            },
            "filter" : {
                "term" : { "user" : "kimchy" }
            }
        }
    },
    "size": 10
}
```
can be built this way:
```
Search(FilteredQ(QueryString("some query string here").defaultOperator(And),
                 TermF("user", "kimchy"))).size(10);
```
Other features may be implemented in the future:

1. eDSL for mappings and indexes which can also be used to provide some additional compile-time information about specific fields.
2. Tools for semi-automatic mapping of C++ structures onto Elasticsearch documents.
