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

#include <exception>

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
      explicit Exception(const char* message)
      : mMessage{message}
      {}

      /**
       * @brief Get error message
       * @return Error message
       */
      [[nodiscard]] const char* what() const noexcept override
      {
        return mMessage;
      }

    private:
      const char* mMessage{"unknown error"}; ///< Error message
  };
} // namespace mex

#endif /* MEX_EXCEPTION_HPP */
