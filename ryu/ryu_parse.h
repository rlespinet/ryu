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
#ifndef RYU_PARSE_H
#define RYU_PARSE_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

// This is an experimental implementation of parsing strings to 64-bit floats
// using a Ryu-like algorithm. At this time, it only support up to 17 non-zero
// digits in the input, and also does not support all formats. Use at your own
// risk.
//
// This implementation does not currently support -DRYU_OPTIMIZE_SIZE and always
// compiles against the large lookup tables.

// Parse the characters from buffer, converting it into a double in
// the result output parameter. Return the number of character read
// from the buffer.
uint32_t s2d(const char * buffer, double * result);

// Parse the characters from buffer, converting it into a float in
// the result output parameter. Return the number of character read
// from the buffer.
uint32_t s2f(const char * buffer, float * result);

#ifdef __cplusplus
}
#endif

#endif // RYU_PARSE_H
