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

#ifndef MEX_ARRAY_HPP
#define MEX_ARRAY_HPP

#include <mex.h>

#include "ArrayRef.hpp"
#include "common.hpp"
#include "Exception.hpp"
#include "typeTraits.hpp"

namespace mex
{
  /// @brief Array class
  class Array
  {
    public:
      /// @brief Default constructor
      Array() noexcept = default;

      /// @brief Explicitly deleted constructor from nullptr.
      Array(nullptr_t) = delete;

      /**
       * @brief Constructor
       * @param array mxArray pointer (rvalue reference)
       */
      explicit Array(mxArray*&& array) noexcept
      : mArray{array}
      {}

      /**
       * @brief Copy constructor
       * @param other Other array
       */
      explicit Array(const Array& other)
      : Array{duplicateArray(other.get())}
      {}

      /**
       * @brief Copy constructor from reference
       * @param other Reference to other array
       */
      explicit Array(const ArrayRef& other)
      : Array{duplicateArray(other.get())}
      {}

      /**
       * @brief Copy constructor from reference
       * @param other Reference to other array
       */
      explicit Array(const ArrayCref& other)
      : Array{duplicateArray(other.get())}
      {}

      /**
       * @brief Move constructor
       * @param other Other array
       */
      Array(Array&& other) noexcept = default;

      /// @brief Destructor
      ~Array() noexcept
      {
        destroy();
      }

      /**
       * @brief Copy assignment operator
       * @param other Other array
       * @return Reference to this array
       */
      Array& operator=(const Array& other)
      {
        if (this != &other)
        {
          destroy();
          mArray = duplicateArray(other.get());
        }

        return *this;
      }

      /**
       * @brief Copy assignment operator from reference
       * @param other Reference to other array
       * @return Reference to this array
       */
      Array& operator=(const ArrayRef& other)
      {
        if (other.get() != get())
        {
          destroy();
          mArray = duplicateArray(other.get());
        }

        return *this;
      }

      /**
       * @brief Copy assignment operator from const reference
       * @param other Const reference to other array
       * @return Reference to this array
       */
      Array& operator=(const ArrayCref& other)
      {
        if (other.get() != get())
        {
          destroy();
          mArray = duplicateArray(other.get());
        }

        return *this;
      }

      /**
       * @brief Move assignment operator
       * @param other Other array
       * @return Reference to this array
       */
      Array& operator=(Array&& other) noexcept = default;

      /**
       * @brief Get the rank of the array
       * @return Rank of the array
       */
      [[nodiscard]] std::size_t getRank() const
      {
        checkValid();
        return mxGetNumberOfDimensions(mArray);
      }

      /**
       * @brief Get the dimensions of the array
       * @return View of the dimensions
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        checkValid();
        return View<std::size_t>{mxGetDimensions(mArray), getRank()};
      }

      /**
       * @brief Get the number of elements in the array
       * @return Number of elements
       */
      [[nodiscard]] std::size_t getNumElements() const
      {
        checkValid();
        return mxGetNumberOfElements(mArray);
      }

      /**
       * @brief Is the array valid?
       * @return True if the array is valid, false otherwise
       */
      [[nodiscard]] bool isValid() const
      {
        return mArray != nullptr;
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        checkValid();
        return mxIsScalar(mArray);
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        checkValid();
        return mxIsEmpty(mArray);
      }

      /**
       * @brief Is the array element class complex?
       * @return True if the array element class is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        checkValid();
        return mxIsComplex(mArray);
      }

      /**
       * @brief Get the class ID of the array
       * @return Class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        checkValid();
        return static_cast<ClassId>(mxGetClassID(mArray));
      }

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] const void* getData() const
      {
        checkValid();
        return mxGetData(mArray);
      }

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] void* getData()
      {
        checkValid();
        return mxGetData(mArray);
      }

      /**
       * @brief Get a reference to the array
       * @return Reference to the array
       */
      [[nodiscard]] ArrayRef ref()
      {
        checkValid();
        return ArrayRef{mArray};
      }

      /**
       * @brief Get a reference to the array
       * @return Reference to the array
       */
      [[nodiscard]] ArrayCref ref() const
      {
        return cref();
      }

      /**
       * @brief Get a const reference to the array
       * @return Const reference to the array
       */
      [[nodiscard]] ArrayCref cref() const
      {
        checkValid();
        return ArrayCref{mArray};
      }

      /**
       * @brief Get the mxArray pointer
       * @return mxArray pointer
       */
      [[nodiscard]] mxArray* get() noexcept
      {
        return mArray;
      }

      /**
       * @brief Get the mxArray pointer
       * @return mxArray pointer
       */
      [[nodiscard]] const mxArray* get() const noexcept
      {
        return mArray;
      }
    private:
      /**
       * @brief Duplicate the array
       * @param array mxArray pointer
       * @return Duplicated mxArray pointer
       */
      [[nodiscard]] static mxArray* duplicateArray(const mxArray* array)
      {
        if (array == nullptr)
        {
          throw Exception{"invalid array to duplicate"};
        }
        
        mxArray* arrayDup = mxDuplicateArray(array);

        if (arrayDup == nullptr)
        {
          throw Exception{"failed to duplicate array"};
        }

        return arrayDup;
      }

      /// @brief Check if the array is valid
      void checkValid() const
      {
        if (!isValid())
        {
          throw Exception{"accessing invalid array"};
        }
      }

      /// @brief Destroy the array
      void destroy() noexcept
      {
        mxDestroyArray(get());
      }

      mxArray* mArray{}; ///< mxArray pointer
  };
} // namespace mex

#endif /* MEX_ARRAY_HPP */
