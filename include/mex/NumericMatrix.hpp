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

#ifndef MEX_NUMERIC_MATRIX_HPP
#define MEX_NUMERIC_MATRIX_HPP

#include "detail/include.hpp"

#include "Exception.hpp"
#include "NumericMatrixRef.hpp"
#include "TypedArray.hpp"
#include "typeTraits.hpp"

namespace mex
{
  /**
   * @brief Numeric typed array
   * @tparam T Element type
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  using NumericArray = TypedArray<T>;

  /**
   * @brief Creates a numeric array
   * @tparam T Element type
   * @param dims Dimensions
   * @return Numeric array
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  [[nodiscard]] NumericArray<T> makeNumericArray(View<std::size_t> dims)
  {
    mxArray* array = mxCreateNumericArray(dims.size(),
                                          const_cast<std::size_t*>(dims.data()),
                                          static_cast<mxClassID>(TypeProperties<T>::classId),
                                          static_cast<mxComplexity>(TypeProperties<T>::complexity));

    if (array == nullptr)
    {
      throw Exception{"failed to create numeric array"};
    }

    return NumericArray<T>{std::move(array)};
  }

  /**
   * @brief Creates an uninitialized numeric array
   * @tparam T Element type
   * @param dims Dimensions
   * @return Uninitialized numeric array
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  [[nodiscard]] NumericArray<T> makeUninitNumericArray(View<std::size_t> dims)
  {
    mxArray* array = mxCreateUninitNumericArray(dims.size(),
                                                const_cast<std::size_t*>(dims.data()),
                                                static_cast<mxClassID>(TypeProperties<T>::classId),
                                                static_cast<mxComplexity>(TypeProperties<T>::complexity));

    if (array == nullptr)
    {
      throw Exception{"failed to create uninitialized numeric array"};
    }

    return NumericArray<T>{std::move(array)};
  }

  /**
   * @brief Creates a numeric array of size 1 with the specified value
   * @tparam T Element type
   * @param value Value
   * @return Numeric array
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  [[nodiscard]] NumericArray<T> makeNumericScalar(const T& value)
  {
    auto array = makeUninitNumericArray<T>({{1}});

    numArray[0] = value;

    return numArray;
  }
} // namespace mex

#endif /* MEX_NUMERIC_MATRIX_HPP */

