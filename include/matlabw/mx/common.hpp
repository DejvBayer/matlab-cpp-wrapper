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

#ifndef MATLABW_MX_COMMON_HPP
#define MATLABW_MX_COMMON_HPP

#include "detail/include.hpp"

namespace matlabw::mx
{
  // Check types compatibility.
  static_assert(std::is_same_v<mwSize, std::size_t>, "mwSize must be std::size_t");
  static_assert(std::is_same_v<mwIndex, std::size_t>, "mwIndex must be std::size_t");
  static_assert(std::is_same_v<mwSignedIndex, std::ptrdiff_t>, "mwSignedIndex must be std::ptrdiff_t");
  static_assert(std::is_same_v<mxChar, char16_t>, "mxChar must be char16_t");
  static_assert(std::is_same_v<mxLogical, bool>, "mwLogical must be bool");

  /**
   * @brief A span of elements.
   * @tparam T The type of the elements.
   * @tparam ext The extent of the span.
   */
  template<typename T, std::size_t ext = std::dynamic_extent>
  using Span = std::span<T, ext>;

  /**
   * @brief A span of constant elements.
   * @tparam T The type of the elements.
   * @tparam ext The extent of the span.
   */
  template<typename T, std::size_t ext = std::dynamic_extent>
  using View = std::span<const T, ext>;

  /// @brief ClassId enumeration.
  enum class ClassId : std::underlying_type_t<mxClassID>
  {
    unknown  = mxUNKNOWN_CLASS,  ///< Unknown class.
    cell     = mxCELL_CLASS,     ///< Cell array.
    _struct  = mxSTRUCT_CLASS,   ///< Structure.
    logical  = mxLOGICAL_CLASS,  ///< Logical.
    _char    = mxCHAR_CLASS,     ///< Character.
    _void    = mxVOID_CLASS,     ///< Void.
    _double  = mxDOUBLE_CLASS,   ///< Double.
    single   = mxSINGLE_CLASS,   ///< Single.
    int8     = mxINT8_CLASS,     ///< 8-bit signed integer.
    uint8    = mxUINT8_CLASS,    ///< 8-bit unsigned integer.
    int16    = mxINT16_CLASS,    ///< 16-bit signed integer.
    uint16   = mxUINT16_CLASS,   ///< 16-bit unsigned integer.
    int32    = mxINT32_CLASS,    ///< 32-bit signed integer.
    uint32   = mxUINT32_CLASS,   ///< 32-bit unsigned integer.
    int64    = mxINT64_CLASS,    ///< 64-bit signed integer.
    uint64   = mxUINT64_CLASS,   ///< 64-bit unsigned integer.
    function = mxFUNCTION_CLASS, ///< Function.
    opaque   = mxOPAQUE_CLASS,   ///< Opaque.
    index    = mxINDEX_CLASS,    ///< Index. Alias for uint32 or uint64 depending on the platform.
  };

  /// @brief Complexity enumeration.
  enum class Complexity : std::underlying_type_t<mxComplexity>
  {
    real    = mxREAL,    ///< Real.
    complex = mxCOMPLEX, ///< Complex.
  };

  // Forward declarations.
  class Cell;
  class Object;
  class Struct;

  /// @brief Index type. Enable implicit conversion from/to std::size_t.
  enum Index : std::size_t {};

  /// @brief FieldIndex type.
  enum class FieldIndex : std::size_t {};

  /**
   * @brief Gets the `eps` variable value.
   * @return The `eps` variable value.
   */
  [[nodiscard]] inline double getEps()
  {
    return mxGetEps();
  }

  /**
   * @brief Gets the `inf` variable value.
   * @return The `inf` variable value.
   */
  [[nodiscard]] inline double getInf()
  {
    return mxGetInf();
  }

  /**
   * @brief Gets the `nan` variable value.
   * @return The `nan` variable value.
   */
  [[nodiscard]] inline double getNaN()
  {
    return mxGetNaN();
  }

  /**
   * @brief Checks if a value is finite.
   * @param value The value.
   * @return True if the value is finite, false otherwise.
   */
  [[nodiscard]] inline bool isFinite(double value)
  {
    return mxIsFinite(value);
  }

  /**
   * @brief Checks if a value is infinite.
   * @param value The value.
   * @return True if the value is infinite, false otherwise.
   */
  [[nodiscard]] inline bool isInf(double value)
  {
    return mxIsInf(value);
  }

  /**
   * @brief Checks if a value is NaN.
   * @param value The value.
   * @return True if the value is NaN, false otherwise.
   */
  [[nodiscard]] inline bool isNaN(double value)
  {
    return mxIsNaN(value);
  }

  /**
   * @brief Creates a scalar span.
   * @tparam T The type of the scalar.
   * @param scalar The scalar.
   * @return The scalar span.
   */
  template<typename T>
  [[nodiscard]] inline Span<T> makeScalarSpan(T& scalar)
  {
    return Span<T>{&scalar, 1};
  }

  /**
   * @brief Creates a scalar view.
   * @tparam T The type of the scalar.
   * @param scalar The scalar.
   * @return The scalar view.
   */
  template<typename T>
  [[nodiscard]] inline View<T> makeScalarView(const T& scalar)
  {
    return View<T>{&scalar, 1};
  }
} // namespace matlabw::mx

#endif /* MATLABW_MX_COMMON_HPP */
