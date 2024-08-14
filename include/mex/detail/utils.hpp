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

#ifndef MEX_DETAIL_UTILS_HPP
#define MEX_DETAIL_UTILS_HPP

#include "include.hpp"
#include "../Exception.hpp"
#include "../memory.hpp"

namespace mex::detail
{
  /**
   * @brief Duplicate array (non-persistent)
   * @param array Array
   * @param nonPersistent Non-persistent flag
   * @return Duplicated array
   */
  [[nodiscard]] inline mxArray* duplicateArray(const mxArray* array, NonPersistent)
  {
    if (array == nullptr)
    {
      throw Exception{"invalid array to duplicate"};
    }
    
    mxArray* arrayDup = mxDuplicateArray(array);

    if (arrayDup == nullptr)
    {
      throw Exception{"failed to duplicate array"};
    }

    return arrayDup;
  }

  /**
   * @brief Duplicate array (persistent)
   * @param array Array
   * @return Duplicated array
   */
  [[nodiscard]] inline mxArray* duplicateArray(const mxArray* array)
  {
    mxArray* arrayDup = duplicateArray(array, nonPersistent);

    mexMakeArrayPersistent(arrayDup);

    return arrayDup;
  }
} // namespace mex::detail

#endif /* MEX_DETAIL_UTILS_HPP */
