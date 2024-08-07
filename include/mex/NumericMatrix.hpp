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
   * @brief Creates a numeric array
   * @tparam T Element type
   * @param m Number of rows
   * @param n Number of columns
   * @return Numeric array
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  [[nodiscard]] NumericArray<T> makeNumericArray(std::size_t m, std::size_t n)
  {
    return makeNumericArray<T>({{m, n}});
  }

  /**
   * @brief Creates a numeric array
   * @param dims Dimensions
   * @param classId Class ID
   * @param complexity Complexity
   * @return Numeric array
   */
  [[nodiscard]] inline Array makeNumericArray(View<std::size_t> dims,
                                              const ClassId     classId,
                                              const Complexity  complexity = Complexity::real)
  {
    mxArray* array = mxCreateNumericArray(dims.size(),
                                          const_cast<std::size_t*>(dims.data()),
                                          static_cast<mxClassID>(classId),
                                          static_cast<mxComplexity>(complexity));

    if (array == nullptr)
    {
      throw Exception{"failed to create numeric array"};
    }

    return Array{std::move(array)};
  }

  /**
   * @brief Creates a numeric array
   * @param m Number of rows
   * @param n Number of columns
   * @param classId Class ID
   * @param complexity Complexity
   * @return Numeric array
   */
  [[nodiscard]] inline Array makeNumericArray(const std::size_t m,
                                              const std::size_t n,
                                              const ClassId     classId,
                                              const Complexity  complexity = Complexity::real)
  {
    return makeNumericArray({{m, n}}, classId, complexity);
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
   * @brief Creates an uninitialized numeric array
   * @tparam T Element type
   * @param m Number of rows
   * @param n Number of columns
   * @return Uninitialized numeric array
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  [[nodiscard]] NumericArray<T> makeUninitNumericArray(std::size_t m, std::size_t n)
  {
    return makeUninitNumericArray<T>({{m, n}});
  }

  /**
   * @brief Creates an unitiliazed numeric array
   * @param dims Dimensions
   * @param classId Class ID
   * @param complexity Complexity
   * @return Uninitialized numeric array
   */
  [[nodiscard]] inline Array makeUninitNumericArray(View<std::size_t> dims,
                                                    const ClassId     classId,
                                                    const Complexity  complexity = Complexity::real)
  {
    mxArray* array = mxCreateUninitNumericArray(dims.size(),
                                                const_cast<std::size_t*>(dims.data()),
                                                static_cast<mxClassID>(classId),
                                                static_cast<mxComplexity>(complexity));

    if (array == nullptr)
    {
      throw Exception{"failed to create uninitialized numeric array"};
    }

    return Array{std::move(array)};
  }

  /**
   * @brief Creates an uninitialized numeric array
   * @param m Number of rows
   * @param n Number of columns
   * @param classId Class ID
   * @param complexity Complexity
   * @return Uninitialized numeric array
   */
  [[nodiscard]] inline Array makeUninitNumericArray(const std::size_t m,
                                                    const std::size_t n,
                                                    const ClassId     classId,
                                                    const Complexity  complexity = Complexity::real)
  {
    return makeUninitNumericArray({{m, n}}, classId, complexity);
  }

  /**
   * @brief Creates a numeric array of size 1 with the specified value
   * @tparam T Element type
   * @param value Value
   * @return Numeric array
   */
  template<typename T, std::enable_if_t<isNumeric<T>, int> = 0>
  [[nodiscard]] NumericArray<T> makeNumericScalar(const T& value = {})
  {
    auto array = makeUninitNumericArray<T>({{1, 1}});

    array[0] = value;

    return array;
  }

  /**
   * @brief Creates a zeroed numeric array of size 1.
   * @param classId Class ID
   * @param complexity Complexity
   * @return Numeric array
   */
  [[nodiscard]] Array makeNumericScalar(const ClassId classId, const Complexity complexity = Complexity::real)
  {
    auto array = makeNumericArray({{1, 1}}, classId, complexity);

    return array;
  }
} // namespace mex

#endif /* MEX_NUMERIC_MATRIX_HPP */

