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

#ifndef MATLABW_MX_EXCEPTION_HPP
#define MATLABW_MX_EXCEPTION_HPP

#include "detail/include.hpp"

#include "memory.hpp"

namespace matlabw::mx
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
      explicit Exception(std::string message)
      : Exception{"mx:unidentified", std::move(message)}
      {}

      /**
       * @brief Constructor
       * @param message Error message
       */
      explicit Exception(std::string id, std::string message)
      : mId{std::move(id)}, mMessage{(message.empty()) ? "Unknown error" : std::move(message)}
      {}

      /**
       * @brief Get error message
       * @return Error message
       */
      [[nodiscard]] const char* what() const noexcept override
      {
        return mMessage.c_str();
      }

      /**
       * @brief Check if error has an ID
       * @return True if error has an ID
       */
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
      std::string mId{};      ///< Error ID
      std::string mMessage{}; ///< Error message
  };
} // namespace matlabw::mx

#endif /* MATLABW_MX_EXCEPTION_HPP */
