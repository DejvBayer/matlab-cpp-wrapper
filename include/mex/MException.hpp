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

#ifndef MEX_MEXCEPTION_HPP
#define MEX_MEXCEPTION_HPP

#include "detail/include.hpp"

#include "ObjectArray.hpp"
#include "ObjectArrayRef.hpp"

namespace mex
{
  class MException : public ObjectArray
  {
    public:
      /// @brief Inherited constructors.
      using ObjectArray::ObjectArray;

      /// @brief Default destructor.
      ~MException() = default;

      /// @brief Inherit assignment operator.
      using ObjectArray::operator=;

      /// @brief Inherit conversion to ArrayRef
      using ObjectArray::operator ArrayRef;

      /// @brief Inherit conversion to ArrayCref
      using ObjectArray::operator ArrayCref;

      /// @brief Inherit conversion to ObjectArrayRef
      using ObjectArray::operator ObjectArrayRef;

      /// @brief Inherit conversion to ObjectArrayCref
      using ObjectArray::operator ObjectArrayCref;
  };
} // namespace mex

#endif /* MEX_MEXCEPTION_HPP */
