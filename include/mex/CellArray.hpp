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

#ifndef MEX_CELL_ARRAY_HPP
#define MEX_CELL_ARRAY_HPP

#include "detail/include.hpp"

#include "CellArrayRef.hpp"
#include "TypedArray.hpp"

namespace mex
{
  /// @brief CellArray class
  using CellArray = TypedArray<Cell>;

  /**
   * @brief Create a cell array
   * @param dims Dimensions of the cell array
   * @return CellArray
   */
  [[nodiscard]] inline CellArray makeCellArray(View<std::size_t> dims)
  {
    mxArray* array = mxCreateCellArray(dims.size(), dims.data());

    if (array == nullptr)
    {
      throw Exception{"failed to create cell array"};
    }

    mexMakeArrayPersistent(array);

    return CellArray{std::move(array)};
  }

  /**
   * @brief Create a cell array
   * @param m Number of rows
   * @param n Number of columns
   * @return CellArray
   */
  [[nodiscard]] inline CellArray makeCellArray(std::size_t m, std::size_t n)
  {
    return makeCellArray({{m, n}});
  }
} // namespace mex

#endif /* MEX_CELL_ARRAY_HPP */
