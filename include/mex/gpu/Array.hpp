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

#ifndef MEX_GPU_ARRAY_HPP
#define MEX_GPU_ARRAY_HPP

#include <mex.h>
#include <gpu/mxGPUArray.h>

#include "ArrayRef.hpp"

namespace mex::gpu
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
       * @param array mxGPUArray pointer (rvalue reference)
       */
      explicit Array(mxGPUArray*&& array) noexcept
      : mArray{array}
      {}

      /**
       * @brief Constructor
       * @param array mxArray pointer
       */
      explicit Array(mxArray* array)
      : mArray{mxGPUCopyFromMxArray(array)}
      {
        if (mArray == nullptr)
        {
          throw Exception{"failed to create array from mxArray"};
        }
      }

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
        return mxGPUGetNumberOfDimensions(mArray);
      }

      /**
       * @brief Get the dimensions of the array
       * @return View of the dimensions
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        checkValid();
        return View<std::size_t>{mxGPUGetDimensions(mArray), getRank()};
      }

      /**
       * @brief Get the number of elements in the array
       * @return Number of elements
       */
      [[nodiscard]] std::size_t getNumElements() const
      {
        checkValid();
        return mxGPUGetNumberOfElements(mArray);
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
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {
        checkValid();
        
        switch (getClassId())
        {
          case ClassId::_double:
          case ClassId::single:
          case ClassId::int8:
          case ClassId::uint8:
          case ClassId::int16:
          case ClassId::uint16:
          case ClassId::int32:
          case ClassId::uint32:
          case ClassId::int64:
          case ClassId::uint64:
            return true;
          default:
            return false;
        }
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        checkValid();
        return getNumElements() == 1;
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        checkValid();
        return getNumElements() == 0;
      }

      /**
       * @brief Is the array element class complex?
       * @return True if the array element class is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        checkValid();
        return mxGPUGetComplexity(mArray) == mxCOMPLEX;
      }

      /**
       * @brief Get the class ID of the array
       * @return Class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        checkValid();
        return static_cast<ClassId>(mxGPUGetClassID(mArray));
      }

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] const void* getData() const
      {
        checkValid();
        return mxGPUGetDataReadOnly(mArray);
      }

      /**
       * @brief Get the array data
       * @return Pointer to the array data
       */
      [[nodiscard]] void* getData()
      {
        checkValid();
        return mxGPUGetData(mArray);
      }

      /**
       * @brief Get the mxGPUArray pointer
       * @return mxGPUArray pointer
       */
      [[nodiscard]] mxGPUArray* get() noexcept
      {
        return mArray;
      }

      /**
       * @brief Get the mxGPUArray pointer
       * @return mxGPUArray pointer
       */
      [[nodiscard]] const mxGPUArray* get() const noexcept
      {
        return mArray;
      }

      /**
       * @brief Release the array
       * @return mxArray pointer
       */
      [[nodiscard]] Array release() noexcept
      {
        mxArray* array = mxGPUCreateMxArrayOnGPU(mArray);

        destroy();

        return Array{std::move(array)};
      }

      /**
       * @brief Convert to ArrayRef
       * @return ArrayRef
       */
      [[nodiscard]] operator ArrayRef()
      {
        checkValid();
        return ArrayRef{mArray};
      }

      /**
       * @brief Convert to ArrayCref
       * @return ArrayCref
       */
      [[nodiscard]] operator ArrayCref() const
      {
        checkValid();
        return ArrayCref{mArray};
      }
    private:
      /**
       * @brief Duplicate the array
       * @param array mxGPUArray pointer
       * @return Duplicated mxGPUArray pointer
       */
      [[nodiscard]] static mxGPUArray* duplicateArray(const mxGPUArray* array)
      {
        if (array == nullptr)
        {
          throw Exception{"invalid array to duplicate"};
        }
        
        mxGPUArray* arrayDup = mxGPUCopyGPUArray(array);

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
        mxGPUDestroyGPUArray(std::move(mArray));
      }

      mxGPUArray* mArray{}; ///< mxArray pointer
  };
} // namespace mex::gpu


#endif /* MEX_GPU_ARRAY_HPP */
