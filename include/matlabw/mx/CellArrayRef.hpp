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

#ifndef MATLABW_MX_CELL_ARRAY_REF_HPP
#define MATLABW_MX_CELL_ARRAY_REF_HPP

#include "detail/include.hpp"

#include "Array.hpp"
#include "CellArrayRef.hpp"
#include "TypedArray.hpp"

namespace matlabw::mx
{
  /// @brief Cell class (alias of Array)
  class Cell : public Array
  {
    public:
      /// @brief Inherit constructors
      using Array::Array;

      /// @brief Destructor
      ~Cell() = default;

      /// @brief Inherit assignment operators
      using Array::operator=;

      /// @brief Inherit conversion operator to reference
      using Array::operator ArrayRef;

      /// @brief Inherit conversion operator to const reference
      using Array::operator ArrayCref;
  };

  // Check that the size of Cell is equal to the size of Array
  static_assert(sizeof(Cell) == sizeof(Array), "Cell size must be equal to Array size");

  /// @brief CellArrayRef class
  using CellArrayRef = TypedArrayRef<Cell>;

  /// @brief CellArrayCref class
  using CellArrayCref = TypedArrayCref<Cell>;
} // namespace matlabw::mx

#endif /* MATLABW_MX_CELL_ARRAY_REF_HPP */
