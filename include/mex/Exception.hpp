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

#ifndef MEX_EXCEPTION_HPP
#define MEX_EXCEPTION_HPP

#include "detail/include.hpp"

#include "memory.hpp"

namespace mex
{
  /// @brief Exception class
  class Exception : public std::exception
  {
    public:
      /// @brief Default constructor
      Exception() = default;

      /**
       * @brief Constructor
       * @param message Error message
       */
      explicit Exception(std::string_view message)
      : mMessage{message}
      {}

      /**
       * @brief Constructor
       * @param message Error message
       */
      explicit Exception(std::string_view id, std::string_view message)
      : mId{id}, mMessage{message}
      {}

      /**
       * @brief Get error message
       * @return Error message
       */
      [[nodiscard]] const char* what() const noexcept override
      {
        return mMessage.c_str();
      }

      [[nodiscard]] bool hasId() const noexcept
      {
        return !mId.empty();
      }

      /**
       * @brief Get error ID
       * @return Error ID
       */
      [[nodiscard]] const char* id() const noexcept
      {
        return mId.c_str();
      }

    private:
      /// @brief String type using mex allocator
      using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;

      String mId{};                     ///< Error ID
      String mMessage{"unknown error"}; ///< Error message
  };
} // namespace mex

#endif /* MEX_EXCEPTION_HPP */
