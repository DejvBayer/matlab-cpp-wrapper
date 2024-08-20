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

#ifndef MATLABW_MEX_IO_HPP
#define MATLABW_MEX_IO_HPP

#include "detail/include.hpp"

namespace matlabw::mex
{
  /**
   * @brief Print formatted output to MATLAB command window.
   * @tparam Args Argument types.
   * @param format Format string.
   * @param args Arguments.
   */
  template<typename... Args>
  void printf(const char* format, Args&&... args)
  {
    if constexpr (sizeof...(Args) > 0)
    {
      mexPrintf(format, std::forward<Args>(args)...);
    }
    else
    {
      mexPrintf("%s", format);
    }
  }

  /**
   * @brief Print formatted output to MATLAB command window.
   * @tparam Args Argument types.
   * @param format Format string. Must be null-terminated.
   * @param args Arguments.
   */
  template<typename... Args>
  void printf(std::string_view format, Args&&... args)
  {
    printf(format.data(), std::forward<Args>(args)...);
  }

  /**
   * @brief Warns the user with a message.
   * @param message The message.
   */
  inline void warn(const char* message)
  {
    mexWarnMsgTxt(message);
  }

  /**
   * @brief Warns the user with a message.
   * @param message The message. Must be null-terminated.
   */
  inline void warn(std::string_view message)
  {
    warn(message.data());
  }

  /**
   * @brief Warns the user with a message.
   * @tparam Args Argument types.
   * @param id Message identifier.
   * @param format Format string.
   * @param args Arguments.
   */
  template<typename... Args>
  void warn(const char* id, const char* format, Args&&... args)
  {
    if constexpr (sizeof...(Args) > 0)
    {
      mexWarnMsgIdAndTxt(id, format, std::forward<Args>(args)...);
    }
    else
    {
      mexWarnMsgIdAndTxt(id, "%s", format);
    }
  }

  /**
   * @brief Warns the user with a message.
   * @tparam Args Argument types.
   * @param id Message identifier. Must be null-terminated.
   * @param format Format string. Must be null-terminated.
   * @param args Arguments.
   */
  template<typename... Args>
  void warn(std::string_view id, std::string_view format, Args&&... args)
  {
    warn(id.data(), format.data(), std::forward<Args>(args)...);
  }
} // namespace matlabw::mex

#endif /* MATLABW_MEX_IO_HPP */
