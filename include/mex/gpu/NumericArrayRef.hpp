/*
  This file is part of mex-cpp-wrapper library.

  Copyright (c) 2024 David Bayer

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef MEX_GPU_NUMERIC_ARRAY_REF_HPP
#define MEX_GPU_NUMERIC_ARRAY_REF_HPP

#include "TypedArrayRef.hpp"

namespace mex::gpu
{
  /**
   * @brief Numeric typed array reference
   * @tparam T Element type
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  using NumericArrayRef = TypedArrayRef<T>;

  /**
   * @brief Numeric typed array const reference
   * @tparam T Element type
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  using NumericArrayCref = TypedArrayCref<T>;
} // namespace mex::gpu

#endif /* MEX_GPU_NUMERIC_ARRAY_REF_HPP */
