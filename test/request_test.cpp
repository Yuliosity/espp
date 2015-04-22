//
// Created by Yury on 18/04/15.
//

#include "gtest/gtest.h"
#include "request.hpp"

using namespace espp;

TEST(Test, HelloWorld) {
    ASSERT_EQ(2 + 2, 4);
}

TEST(Test, RequestHasSize) {
    auto req = Request().size(42);
    ASSERT_EQ(R"({"size":42})", req.toString());
}