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

#ifndef MEX_GPU_TYPED_ARRAY_REF_HPP
#define MEX_GPU_TYPED_ARRAY_REF_HPP

#include "../detail/include.hpp"

#include "Array.hpp"
#include "../ArrayRef.hpp"
#include "../common.hpp"

namespace mex::gpu
{
  /**
   * @brief Typed array reference class.
   * @tparam T Value type
   */
  template<typename T>
  class TypedArrayRef : public ArrayRef
  {
    static_assert(!std::is_const_v<T>, "T must be a non-const type");
    static_assert(!std::is_volatile_v<T>, "T must be a non-volatile type");
    static_assert(!std::is_reference_v<T>, "T must be a non-reference type");
    
    public:
      using value_type             = T;                                     ///< Value type
      using reference              = value_type&;                           ///< Reference type
      using const_reference        = const value_type&;                     ///< Const reference type
      using pointer                = value_type*;                           ///< Pointer type
      using const_pointer          = const T*;                              ///< Const pointer type
      using iterator               = pointer;                               ///< Iterator type
      using const_iterator         = const_pointer;                         ///< Const iterator type
      using reverse_iterator       = std::reverse_iterator<iterator>;       ///< Reverse iterator type
      using const_reverse_iterator = std::reverse_iterator<const_iterator>; ///< Const reverse iterator type

      /// @brief Class ID
      static constexpr ClassId classId = TypeProperties<T>::classId;

      /// @brief Explicitly deleted default constructor.
      TypedArrayRef() = delete;

      /**
       * @brief Constructor from an ArrayRef.
       * @param other ArrayRef
       */
      explicit TypedArrayRef(const ArrayRef& other)
      : ArrayRef{(checkArrayClass(other.getClassId()), other)}
      {}

      /**
       * @brief Constructor from a TypedArrayRef.
       * @param other TypedArrayRef
       */
      TypedArrayRef& operator=(const ArrayRef& other)
      {
        checkArrayClass(other.getClassId());
        return ArrayRef::operator=(other);
      }

      /**
       * @brief Gets a pointer to the data.
       * @return Pointer to the data
       */
      [[nodiscard]] pointer getData() const
      {
        return static_cast<pointer>(ArrayRef::getData());
      }

    private:
      /**
       * @brief Checks if the array is of the correct class.
       * @param otherClassId Class ID
       */
      void checkArrayClass(const ClassId otherClassId) const
      {
        if (otherClassId != classId)
        {
          throw Exception{"invalid class ID"};
        }
      }
  };

  /**
   * @brief Typed array const reference class.
   * @tparam T Value type
   */
  template<typename T>
  class TypedArrayCref : public ArrayCref
  {
    public:
      using value_type             = const T;                               ///< Value type
      using reference              = value_type&;                           ///< Reference type
      using const_reference        = const value_type&;                     ///< Const reference type
      using pointer                = value_type*;                           ///< Pointer type
      using const_pointer          = const T*;                              ///< Const pointer type
      using iterator               = pointer;                               ///< Iterator type
      using const_iterator         = const_pointer;                         ///< Const iterator type
      using reverse_iterator       = std::reverse_iterator<iterator>;       ///< Reverse iterator type
      using const_reverse_iterator = std::reverse_iterator<const_iterator>; ///< Const reverse iterator type

      /// @brief Class ID
      static constexpr ClassId classId = TypeProperties<T>::classId;

      /// @brief Explicitly deleted default constructor.
      TypedArrayCref() = delete;

      /**
       * @brief Constructor from an Array.
       * @param other Array
       */
      explicit TypedArrayCref(const Array& other)
      : ArrayCref{(checkArrayClass(other.getClassId()), other)}
      {}

      /**
       * @brief Constructor from an ArrayCref.
       * @param other ArrayCref
       */
      explicit TypedArrayCref(const ArrayCref& other)
      : ArrayCref{(checkArrayClass(other.getClassId()), other)}
      {}

      /**
       * @brief Constructor from an ArrayRef.
       * @param other ArrayRef
       */
      explicit TypedArrayCref(const ArrayRef& other)
      : ArrayCref{(checkArrayClass(other.getClassId()), other)}
      {}

      /**
       * @brief Constructor from a ArrayCref.
       * @param other ArrayCref
       */
      TypedArrayCref& operator=(const ArrayCref& other)
      {
        checkArrayClass(other.getClassId());
        return ArrayCref::operator=(other);
      }

      /**
       * @brief Constructor from a ArrayRef.
       * @param other ArrayRef
       */
      TypedArrayCref& operator=(const ArrayRef& other)
      {
        checkArrayClass(other.getClassId());
        return ArrayCref::operator=(other);
      }

      /**
       * @brief Gets a pointer to the data.
       * @return Pointer to the data
       */
      [[nodiscard]] const_pointer getData() const
      {
        return static_cast<const_pointer>(ArrayCref::getData());
      }
    private:
      /**
       * @brief Checks if the array is of the correct class.
       * @param otherClassId Class ID
       */
      void checkArrayClass(const ClassId otherClassId) const
      {
        if (otherClassId != classId)
        {
          throw Exception{"invalid class ID"};
        }
      }
  };
} // namespace mex::gpu

#endif /* MEX_GPU_TYPED_ARRAY_REF_HPP */
