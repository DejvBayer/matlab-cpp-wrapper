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

#ifndef MATLABW_MEX_MEMORY_HPP
#define MATLABW_MEX_MEMORY_HPP

#include "detail/include.hpp"

namespace matlabw::mex
{
  /**
   * @brief Makes the specified memory persistent between MEX function calls.
   * @param ptr A pointer to the memory to make persistent.
   */
  void makePersistent(const void* ptr)
  {
    mexMakeMemoryPersistent(const_cast<void*>(ptr));
  }

  /**
   * @brief Makes the specified memory persistent between MEX function calls.
   * @param array An array whose memory to make persistent.
   */
  void makePersistent(const mx::Array& array)
  {
    if (array.isValid())
    {
      mexMakeArrayPersistent(const_cast<mxArray*>(array.get()));
    }
  }
} // namespace matlabw::mex

#endif /* MATLABW_MEX_MEMORY_HPP */
