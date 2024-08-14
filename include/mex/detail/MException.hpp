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

#ifndef MEX_DETAIL_MEXCEPTION_HPP
#define MEX_DETAIL_MEXCEPTION_HPP

#include "include.hpp"

#include "../CharArray.hpp"
#include "../ObjectArray.hpp"
#include "../propery.hpp"

namespace mex::detail
{
  /**
   * @brief Handle a MATLAB exception
   * @param me The MException object
   * @return The exception
   */
  inline void handleMException(mxArray* me)
  {
    if (me == nullptr)
    {
      return;
    }

    ArrayRef meObj{me};

    if (meObj.isEmpty())
    {
      throw Exception{"failed to get MException object"};
    }

    std::string id{};
    std::string message{};

    auto idArray = getProperty(meObj, "identifier");

    if (idArray.has_value() && idArray->isChar())
    {
      id = toAscii(*idArray);
    }

    auto messageArray = getProperty(meObj, "message");

    if (messageArray.has_value() && messageArray->isChar())
    {
      message = toAscii(*messageArray);
    }

    throw Exception{std::move(id), std::move(message)};
  }
} // namespace mex::detail

#endif /* MEX_DETAIL_MEXCEPTION_HPP */
