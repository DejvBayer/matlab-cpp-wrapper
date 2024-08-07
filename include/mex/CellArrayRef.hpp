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

#ifndef MEX_CELL_ARRAY_REF_HPP
#define MEX_CELL_ARRAY_REF_HPP

#include "detail/include.hpp"

#include "Array.hpp"
#include "CellArrayRef.hpp"
#include "TypedArray.hpp"

namespace mex
{
  /// @brief Cell class (alias of Array)
  class Cell : public Array {};

  // Check that the size of Cell is equal to the size of Array
  static_assert(sizeof(Cell) == sizeof(Array), "Cell size must be equal to Array size");

  /// @brief CellArrayRef class
  class CellArrayRef : public TypedArrayRef<Cell>
  {
    public:
      /// @brief Inherit constructors from TypedArrayRef<Cell>
      using TypedArrayRef<Cell>::TypedArrayRef;

      /// @brief Default destructor
      ~CellArrayRef() = default;

      /// @brief Use the TypedArrayRef<Cell>::operator=
      using TypedArrayRef<Cell>::operator=;
  };

  /// @brief CellArrayCref class
  class CellArrayCref : public TypedArrayCref<Cell>
  {
    public:
      /// @brief Inherit constructors from TypedArrayRef<Cell>
      using TypedArrayCref<Cell>::TypedArrayCref;

      /// @brief Default destructor
      ~CellArrayCref() = default;

      /// @brief Use the TypedArrayCref<Cell>::operator=
      using TypedArrayCref<Cell>::operator=;
  };
} // namespace mex

#endif /* MEX_CELL_ARRAY_REF_HPP */
