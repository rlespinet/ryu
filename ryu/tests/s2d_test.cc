// Copyright 2019 Ulf Adams
//
// The contents of this file may be used under the terms of the Apache License,
// Version 2.0.
//
//    (See accompanying file LICENSE-Apache or copy at
//     http://www.apache.org/licenses/LICENSE-2.0)
//
// Alternatively, the contents of this file may be used under the terms of
// the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE-Boost or copy at
//     https://www.boost.org/LICENSE_1_0.txt)
//
// Unless required by applicable law or agreed to in writing, this software
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.

#include <math.h>

#include "ryu/ryu_parse.h"
#include "third_party/gtest/gtest.h"

#define EXPECT_S2D(a, b, r) { double value; EXPECT_EQ(r, s2d(b, &value)); EXPECT_EQ(a, value); } while (0);

TEST(S2dTest, BadInput) {
  double value;
  EXPECT_S2D(0.0, "x", 0u);
  EXPECT_S2D(1.0, "1..1", 2u);
  EXPECT_S2D(0.0, "..", 1u);
  EXPECT_S2D(1.0, "1..1", 2u);
  EXPECT_S2D(1.0, "1ee1", 2u);
  EXPECT_S2D(1.0, "1e.1", 2u);
  EXPECT_S2D(0.0, "", 0u);
  // The following tests now trigger an assert.
  // EXPECT_S2D(0.0, "123456789012345678", 0u);
  // EXPECT_S2D(0.0, "1e12345", 0u);
}

TEST(S2dTest, Basic) {
  EXPECT_S2D(0.0, "0", 1u);
  EXPECT_S2D(-0.0, "-0", 2u);
  EXPECT_S2D(1.0, "1", 1u);
  EXPECT_S2D(2.0, "2", 1u);
  EXPECT_S2D(123456789.0, "123456789", 9u);
  EXPECT_S2D(123.456, "123.456", 7u);
  EXPECT_S2D(123.456, "123456e-3", 9u);
  EXPECT_S2D(123.456, "1234.56e-1", 10u);
  EXPECT_S2D(1.453, "1.453", 5u);
  EXPECT_S2D(1453.0, "1.453e+3", 8u);
  EXPECT_S2D(0.0, ".0", 2u);
  EXPECT_S2D(1.0, "1e0", 3u);
  EXPECT_S2D(1.0, "1E0", 3u);
  EXPECT_S2D(1.0, "000001.000000", 13u);
  EXPECT_S2D(0.2316419, "0.2316419", 9u);
}

TEST(S2dTest, MinMax) {
  EXPECT_S2D(1.7976931348623157e308, "1.7976931348623157e308", 22u);
  EXPECT_S2D(5E-324, "5E-324", 6u);
}

TEST(S2dTest, MantissaRoundingOverflow) {
  // This results in binary mantissa that is all ones and requires rounding up
  // because it is closer to 1 than to the next smaller float. This is a
  // regression test that the mantissa overflow is handled correctly by
  // increasing the exponent.
  EXPECT_S2D(1.0, "0.99999999999999999", 19u);
  // This number overflows the mantissa *and* the IEEE exponent.
  EXPECT_S2D(INFINITY, "1.7976931348623159e308", 22u);
}

TEST(S2dTest, Underflow) {
  EXPECT_S2D(0.0, "2.4e-324", 8u);
  EXPECT_S2D(0.0, "1e-324", 6u);
  EXPECT_S2D(0.0, "9.99999e-325", 12u);
  // These are just about halfway between 0 and the smallest float.
  // The first is just below the halfway point, the second just above.
  EXPECT_S2D(0.0, "2.4703282292062327e-324", 23u);
  EXPECT_S2D(5e-324, "2.4703282292062328e-324", 23u);
}

TEST(S2dTest, Overflow) {
  EXPECT_S2D(INFINITY, "2e308", 5u);
  EXPECT_S2D(INFINITY, "1e309", 5u);
}

TEST(S2dTest, TableSizeDenormal) {
  EXPECT_S2D(5e-324, "4.9406564584124654e-324", 23u);
}

TEST(S2dTest, Issue157) {
  EXPECT_S2D(1.2999999999999999E+154, "1.2999999999999999E+154", 23u);
}
