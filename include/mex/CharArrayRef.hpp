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

#ifndef MEX_CHAR_ARRAY_REF_HPP
#define MEX_CHAR_ARRAY_REF_HPP

#include "detail/include.hpp"

#include "TypedArrayRef.hpp"

namespace mex
{
  /**
   * @brief Convert a char16_t array to a std::string
   * @param array TypedArrayCref<char16_t>
   * @return std::string
   */
  [[nodiscard]] inline std::string toAscii(TypedArrayCref<char16_t> array)
  {
    const std::size_t size = std::char_traits<char16_t>::length(array.getData());

    std::string str(size + 1, '\0');

    mxGetString(array.get(), str.data(), size);

    return str;
  }

  /**
   * @brief Convert a char array to a std::string
   * @param array ArrayCref
   * @return std::string
   */
  [[nodiscard]] inline std::string toAscii(ArrayCref array)
  {
    if (array.getClassId() != ClassId::_char)
    {
      throw Exception{"MATLAB:toAscii:invalidInput", "Input must be of type string.\n"};
    }

    return toAscii(TypedArrayCref<char16_t>{array});
  }

  /// @brief CharArray class
  class CharArrayRef : public TypedArrayRef<char16_t>
  {
    public:
      /// @brief Inherit constructors from TypedArrayRef<char16_t>
      using TypedArrayRef<char16_t>::TypedArrayRef;

      /// @brief Default destructor
      ~CharArrayRef() = default;

      /// @brief Use the TypedArrayRef<char16_t>::operator=
      using TypedArrayRef<char16_t>::operator=;

      /**
       * @brief Convert to std::string (ASCII)
       * @return std::string
       */
      std::string toAscii() const
      {
        return mex::toAscii(*this);
      }
      
      /**
       * @brief Convert to std::u16string_view
       * @return std::u16string_view
       */
      [[nodiscard]] operator std::u16string_view() const
      {
        return std::u16string_view{getData()};
      }
  };

  /// @brief CharArrayCref class
  class CharArrayCref : public TypedArrayCref<char16_t>
  {
    public:
      /// @brief Inherit constructors from TypedArrayCref<char16_t>
      using TypedArrayCref<char16_t>::TypedArrayCref;

      /// @brief Default destructor
      ~CharArrayCref() = default;

      /// @brief Use the TypedArrayCref<char16_t>::operator=
      using TypedArrayCref<char16_t>::operator=;

      /**
       * @brief Convert to std::string (ASCII)
       * @return std::string
       */
      std::string toAscii() const
      {
        return mex::toAscii(*this);
      }
      
      /**
       * @brief Convert to std::u16string_view
       * @return std::u16string_view
       */
      [[nodiscard]] operator std::u16string_view() const
      {
        return std::u16string_view{getData()};
      }
  };
} // namespace mex

#endif /* MEX_CHAR_ARRAY_REF_HPP */
