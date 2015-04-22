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
