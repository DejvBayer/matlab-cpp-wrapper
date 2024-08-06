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

#ifndef MEX_CHAR_ARRAY_HPP
#define MEX_CHAR_ARRAY_HPP

#include "detail/include.hpp"

#include "CharArrayRef.hpp"
#include "TypedArray.hpp"

namespace mex
{
  /// @brief CharArray class
  class CharArray : public TypedArray<char16_t>
  {
    public:
      /// @brief Inherit constructors from TypedArray<char16_t>
      using TypedArray<char16_t>::TypedArray;

      /**
       * @brief Construct from a std::string_view
       * @param str The string view
       */
      explicit CharArray(std::string_view str);
      
      /**
       * @brief Construct from a std::u16string_view
       * @param str The string view
       */
      explicit CharArray(std::u16string_view str);

      /// @brief Default destructor
      ~CharArray() = default;

      /// @brief Use the TypedArray<char16_t>::operator=
      using TypedArray<char16_t>::operator=;

      /**
       * @brief Convert to std::string (ASCII)
       * @return std::string
       */
      std::string toAscii() const
      {
        return mex::toAscii(TypedArrayCref<char16_t>{*this});
      }

      /**
       * @brief Convert to std::u16string_view
       * @return std::u16string_view
       */
      [[nodiscard]] operator std::u16string_view() const
      {
        return std::u16string_view{getData()};
      }

      /// @brief Use the TypedArray<char16_t>::operator ArrayRef
      using TypedArray<char16_t>::operator ArrayRef;

      /// @brief Use the TypedArray<char16_t>::operator ArrayCref
      using TypedArray<char16_t>::operator ArrayCref;

      /// @brief Use the TypedArray<char16_t>::operator TypedArrayRef
      using TypedArray<char16_t>::operator TypedArrayRef<char16_t>;

      /// @brief Use the TypedArray<char16_t>::operator TypedArrayCref
      using TypedArray<char16_t>::operator TypedArrayCref<char16_t>;

      /**
       * @brief Conversion operator to CharArrayRef
       * @return Reference to the array
       */
      [[nodiscard]] operator CharArrayRef()
      {
        checkValid();
        return CharArrayRef{get()};
      }

      /**
       * @brief Conversion operator to CharArrayCref
       * @return Const reference to the array
       */
      [[nodiscard]] operator CharArrayCref() const
      {
        checkValid();
        return CharArrayCref{get()};
      }
  };

  /**
   * @brief Make a CharArray.
   * @param dims The dimensions of the array.
   * @return The CharArray.
   */
  [[nodiscard]] inline CharArray makeCharArray(View<std::size_t> dims)
  {
    mxArray* array = mxCreateCharArray(dims.size(), dims.data());

    if (array == nullptr)
    {
      throw Exception{"failed to create char array"};
    }

    mexMakeMemoryPersistent(array);

    return CharArray{std::move(array)};
  }

  /**
   * @brief Make a CharArray from a std::string_view.
   * @param str The string view.
   * @return The CharArray.
   */
  [[nodiscard]] inline CharArray makeCharArray(std::string_view str)
  {
    mxArray* array = mxCreateStringFromNChars(str.data(), str.size());

    if (array == nullptr)
    {
      throw Exception{"failed to create char array"};
    }

    mexMakeArrayPersistent(array);

    return CharArray{std::move(array)};
  }

  /**
   * @brief Make a CharArray from a std::u16string_view.
   * @param str The string view.
   * @return The CharArray.
   */
  [[nodiscard]] inline CharArray makeCharArray(std::u16string_view str)
  {
    CharArray array = makeCharArray({{str.size() + 1}});

    std::copy(str.begin(), str.end(), array.begin());

    return array;
  }

  /**
   * @brief Construct from a std::string_view
   * @param str The string view
   */
  inline CharArray::CharArray(std::string_view str)
  : TypedArray<char16_t>{makeCharArray(str)}
  {}

  /**
   * @brief Construct from a std::u16string_view
   * @param str The string view
   */
  inline CharArray::CharArray(std::u16string_view str)
  : TypedArray<char16_t>{makeCharArray(str)}
  {}
} // namespace mex

#endif /* MEX_CHAR_ARRAY_HPP */
