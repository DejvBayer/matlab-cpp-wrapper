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

#include "ArrayRef.hpp"
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

      /// @brief Explicitly deleted constructor from nullptr.
      TypedArrayRef(std::nullptr_t) = delete;

      /**
       * @brief Constructor from a mxArray pointer.
       * @param array mxArray pointer
       */
      explicit TypedArrayRef(mxArray* array)
      : ArrayRef{(checkArrayClass(array), array)}
      {}

      /**
       * @brief Constructor from an ArrayRef.
       * @param other ArrayRef
       */
      explicit TypedArrayRef(const ArrayRef& other)
      : ArrayRef{(checkArrayClass(other.get()), other)}
      {}

      /**
       * @brief Constructor from a TypedArrayRef.
       * @param other TypedArrayRef
       */
      TypedArrayRef& operator=(const ArrayRef& other)
      {
        checkArrayClass(other.get());
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

      /**
       * @brief Accesses an element with bounds checking.
       * @param i Index
       * @return Reference to the element
       */
      [[nodiscard]] reference at(std::size_t i) const
      {
        if (i >= getSize())
        {
          throw Exception{"index out of range"};
        }

        return getData()[i];
      }

      /**
       * @brief Accesses an element without bounds checking.
       * @param i Index
       * @return Reference to the element
       */
      [[nodiscard]] reference operator[](std::size_t i) const
      {
        return getData()[i];
      }

      /**
       * @brief Gets an iterator to the beginning.
       * @return Iterator to the beginning
       */
      [[nodiscard]] iterator begin() const
      {
        return getData();
      }

      /**
       * @brief Gets a const iterator to the beginning.
       * @return Const iterator to the beginning
       */
      [[nodiscard]] const_iterator cbegin() const
      {
        return getData();
      }

      /**
       * @brief Gets an iterator to the end.
       * @return Iterator to the end
       */
      [[nodiscard]] iterator end() const
      {
        return getData() + getSize();
      }

      /**
       * @brief Gets a const iterator to the end.
       * @return Const iterator to the end
       */
      [[nodiscard]] const_iterator cend() const
      {
        return getData() + getSize();
      }

      /**
       * @brief Gets a reverse iterator to the beginning.
       * @return Reverse iterator to the beginning
       */
      [[nodiscard]] reverse_iterator rbegin() const
      {
        return reverse_iterator{end()};
      }

      /**
       * @brief Gets a const reverse iterator to the beginning.
       * @return Const reverse iterator to the beginning
       */
      [[nodiscard]] const_reverse_iterator crbegin() const
      {
        return const_reverse_iterator{end()};
      }

      /**
       * @brief Gets a reverse iterator to the end.
       * @return Reverse iterator to the end
       */
      [[nodiscard]] reverse_iterator rend() const
      {
        return reverse_iterator{begin()};
      }

      /**
       * @brief Gets a const reverse iterator to the end.
       * @return Const reverse iterator to the end
       */
      [[nodiscard]] const_reverse_iterator crend() const
      {
        return const_reverse_iterator{begin()};
      }
    private:
      /// @brief Checks if the array is of the correct class
      void checkArrayClass(const mxArray* array) const
      {
        return detail::checkArrayClass<classId>(array);
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

      /// @brief Explicitly deleted constructor from nullptr.
      TypedArrayCref(std::nullptr_t) = delete;

      /**
       * @brief Constructor from a mxArray pointer.
       * @param array mxArray pointer
       */
      explicit TypedArrayCref(const mxArray* array)
      : ArrayCref{(checkArrayClass(array), array)}
      {}

      /**
       * @brief Constructor from an ArrayCref.
       * @param other ArrayCref
       */
      explicit TypedArrayCref(const ArrayCref& other)
      : ArrayCref{(checkArrayClass(other.get()), other)}
      {}

      /**
       * @brief Constructor from an ArrayRef.
       * @param other ArrayRef
       */
      explicit TypedArrayCref(const ArrayRef& other)
      : ArrayCref{(checkArrayClass(other.get()), other)}
      {}

      /**
       * @brief Constructor from a ArrayCref.
       * @param other ArrayCref
       */
      TypedArrayCref& operator=(const ArrayCref& other)
      {
        checkArrayClass(other.get());
        return ArrayCref::operator=(other);
      }

      /**
       * @brief Constructor from a ArrayRef.
       * @param other ArrayRef
       */
      TypedArrayCref& operator=(const ArrayRef& other)
      {
        checkArrayClass(other.get());
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

      /**
       * @brief Accesses an element with bounds checking.
       * @param i Index
       * @return Reference to the element
       */
      [[nodiscard]] reference at(std::size_t i) const
      {
        if (i >= getSize())
        {
          throw Exception{"index out of range"};
        }

        return getData()[i];
      }

      /**
       * @brief Accesses an element without bounds checking.
       * @param i Index
       * @return Reference to the element
       */
      [[nodiscard]] reference operator[](std::size_t i) const
      {
        return getData()[i];
      }

      /**
       * @brief Gets an iterator to the beginning.
       * @return Iterator to the beginning
       */
      [[nodiscard]] iterator begin() const
      {
        return getData();
      }

      /**
       * @brief Gets a const iterator to the beginning.
       * @return Const iterator to the beginning
       */
      [[nodiscard]] const_iterator cbegin() const
      {
        return begin();
      }

      /**
       * @brief Gets an iterator to the end.
       * @return Iterator to the end
       */
      [[nodiscard]] iterator end() const
      {
        return getData() + getSize();
      }

      /**
       * @brief Gets a const iterator to the end.
       * @return Const iterator to the end
       */
      [[nodiscard]] const_iterator cend() const
      {
        return end();
      }

      /**
       * @brief Gets a reverse iterator to the beginning.
       * @return Reverse iterator to the beginning
       */
      [[nodiscard]] reverse_iterator rbegin() const
      {
        return reverse_iterator{end()};
      }

      /**
       * @brief Gets a const reverse iterator to the beginning.
       * @return Const reverse iterator to the beginning
       */
      [[nodiscard]] const_reverse_iterator crbegin() const
      {
        return rbegin();
      }

      /**
       * @brief Gets a reverse iterator to the end.
       * @return Reverse iterator to the end
       */
      [[nodiscard]] reverse_iterator rend() const
      {
        return reverse_iterator{begin()};
      }

      /**
       * @brief Gets a const reverse iterator to the end.
       * @return Const reverse iterator to the end
       */
      [[nodiscard]] const_reverse_iterator crend() const
      {
        return rend();
      }
    private:
      /// @brief Checks if the array is of the correct class
      void checkArrayClass(const mxArray* array) const
      {
        return detail::checkArrayClass<classId>(array);
      }
  };
} // namespace mex::gpu

#endif /* MEX_GPU_TYPED_ARRAY_REF_HPP */
