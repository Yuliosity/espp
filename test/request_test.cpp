//
// Created by Yury on 18/04/15.
//

#include "gtest/gtest.h"
#include "request.hpp"

using namespace espp;

TEST(Test, RequestHasBodyAndSize) {
    auto req = Request().size(42);
    ASSERT_EQ(R"({"query":{"match_all":{}},"size":42})", req.toString());
}

TEST(Test, MakeTermRequest) {
    auto req = Request(TermQ("checked", false));
    const char *sample = R"({"query":{"term":{"checked":false}},"size":10})";
    ASSERT_EQ(sample, req.toString());
    Field<bool> checked("checked");
    ASSERT_EQ(sample, Request(TermQ(checked, false)).toString());
}

TEST(Test, MakeBoolRequest) {
    auto req = Request(BoolQ().must({TermQ("checked", false), TermQ("name", "kimchy")}));
    ASSERT_EQ(R"({"query":{"bool":{"must":[{"term":{"checked":false}},{"term":{"name":"kimchy"}}]}},"size":10})", req.toString());
}

TEST(Test, MakeBoolRequestWithOperators) {
    auto req = Request(TermQ("checked", false) && TermQ("name", "kimchy") && TermQ("age", 42));
    ASSERT_EQ(R"({"query":{"bool":{"must":[{"term":{"checked":false}},{"term":{"name":"kimchy"}},{"term":{"age":42}}]}},"size":10})", req.toString());
}