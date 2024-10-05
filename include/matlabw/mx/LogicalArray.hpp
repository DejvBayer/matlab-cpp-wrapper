/*
  This file is part of matlab-cpp-wrapper library.

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

#ifndef MATLABW_MX_LOGICAL_ARRAY_HPP
#define MATLABW_MX_LOGICAL_ARRAY_HPP

#include "detail/include.hpp"

#include "TypedArray.hpp"

namespace matlabw::mx
{
  /// @brief LogicalArrayRef class
  using LogicalArrayRef = TypedArrayRef<bool>;

  /// @brief LogicalArrayCref class
  using LogicalArrayCref = TypedArrayCref<bool>;

  /// @brief LogicalArray class
  using LogicalArray = TypedArray<bool>;

  /**
   * @brief Create a logical array
   * @param dims Dimensions of the logical array
   * @return LogicalArray
   */
  [[nodiscard]] inline LogicalArray makeLogicalArray(View<std::size_t> dims)
  {
    mxArray* array = mxCreateLogicalArray(dims.size(), dims.data());

    if (array == nullptr)
    {
      throw Exception{"failed to create logical array"};
    }

    return LogicalArray{std::move(array)};
  }

  /**
   * @brief Create a logical array
   * @param m Number of rows
   * @param n Number of columns
   * @return LogicalArray
   */
  [[nodiscard]] inline LogicalArray makeLogicalArray(std::size_t m, std::size_t n)
  {
    return makeLogicalArray({{m, n}});
  }

  /**
   * @brief Create a logical scalar array
   * @param value Logical value
   * @return LogicalArray
   */
  [[nodiscard]] inline LogicalArray makeLogicalScalar(bool value)
  {
    mxArray* array = mxCreateLogicalScalar(value);

    if (array == nullptr)
    {
      throw Exception{"failed to create logical scalar array"};
    }

    return LogicalArray{std::move(array)};
  }
}

#endif /* MATLABW_MX_LOGICAL_ARRAY_HPP */
