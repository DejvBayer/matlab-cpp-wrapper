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

#ifndef MATLABW_MX_MX_HPP
#define MATLABW_MX_MX_HPP

#include "detail/include.hpp"

#if MATLAB_TARGET_API_VERSION < R2018a
# error "This library requires MATLAB R2018a or later."
#endif

#include "Array.hpp"
#include "ArrayRef.hpp"
#include "CellArray.hpp"
#include "CellArrayRef.hpp"
#include "CharArray.hpp"
#include "CharArrayRef.hpp"
#include "common.hpp"
#include "Exception.hpp"
#include "limits.hpp"
#include "LogicalArray.hpp"
#include "memory.hpp"
#include "NumericArray.hpp"
#include "NumericArrayRef.hpp"
#include "ObjectArray.hpp"
#include "propery.hpp"
#include "StructArray.hpp"
#include "StructArrayRef.hpp"
#include "TypedArray.hpp"
#include "TypedArrayRef.hpp"
#include "typeTraits.hpp"
#include "visit.hpp"

#ifdef MATLABW_ENABLE_GPU
# include "gpu/Array.hpp"
# include "gpu/init.hpp"
# include "gpu/NumericArray.hpp"
# include "gpu/TypedArray.hpp"
#endif

#endif /* MATLABW_MX_MX_HPP */
