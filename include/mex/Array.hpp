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

#include "detail/include.hpp"

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
      {
        if (mArray != nullptr)
        {
          mexMakeArrayPersistent(mArray);
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
      Array(Array&& other) noexcept
      : mArray{std::exchange(other.mArray, nullptr)}
      {}

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
      Array& operator=(Array&& other) noexcept
      {
        if (this != &other)
        {
          destroy();
          mArray = std::exchange(other.mArray, nullptr);
        }

        return *this;
      }

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
       * @brief Get the number of rows
       * @return Number of rows
       */
      [[nodiscard]] std::size_t getM() const
      {
        checkValid();
        return mxGetM(mArray);
      }

      /**
       * @brief Get the number of columns
       * @return Number of columns
       */
      [[nodiscard]] std::size_t getN() const
      {
        checkValid();
        return mxGetN(mArray);
      }

      /**
       * @brief Get the number of elements in the array
       * @return Number of elements
       */
      [[nodiscard]] std::size_t getSize() const
      {
        checkValid();
        return mxGetNumberOfElements(mArray);
      }

      /**
       * @brief Gets the size of the element in bytes
       * @return Size of the element in bytes
       */
      [[nodiscard]] std::size_t getSizeOfElement() const
      {
        checkValid();
        return mxGetElementSize(mArray);
      }

      /**
       * @brief Resize the array
       * @param dims Dimensions
       */
      void resize(View<std::size_t> dims)
      {
        checkValid();

        if (mxSetDimensions(mArray, dims.data(), dims.size()))
        {
          throw Exception{"failed to resize array"};
        }

        mexMakeArrayPersistent(mArray);
      }

      /**
       * @brief Resize the array
       * @param m Number of rows
       * @param n Number of columns
       */
      void resize(std::size_t m, std::size_t n)
      {
        resize({{m, n}});
      }

      /**
       * @brief Is the array valid?
       * @return True if the array is valid, false otherwise
       */
      [[nodiscard]] bool isValid() const
      {
        return mArray != nullptr;
      }

#   ifdef MEX_ENABLE_GPU
      /**
       * @brief Is the array a GPU array?
       * @return True if the array is a GPU array, false otherwise
       */
      [[nodiscard]] bool isGpuArray() const
      {
        checkValid();
        return mxIsGPUArray(mArray);
      }
#   endif

      /**
       * @brief Is the array a numeric array?
       * @return True if the array is a numeric array, false otherwise
       */
      [[nodiscard]] bool isNumeric() const
      {
        checkValid();
        return mxIsNumeric(mArray);
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
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        checkValid();
        return mxIsEmpty(mArray);
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
       * @brief Is the array a double?
       * @return True if the array is a double, false otherwise
       */
      [[nodiscard]] bool isDouble() const
      {
        checkValid();
        return mxIsDouble(mArray);
      }

      /**
       * @brief Is the array a single?
       * @return True if the array is a single, false otherwise
       */
      [[nodiscard]] bool isSingle() const
      {
        checkValid();
        return mxIsSingle(mArray);
      }

      /**
       * @brief Is the array an int8?
       * @return True if the array is an int8, false otherwise
       */
      [[nodiscard]] bool isInt8() const
      {
        checkValid();
        return mxIsInt8(mArray);
      }

      /**
       * @brief Is the array a uint8?
       * @return True if the array is a uint8, false otherwise
       */
      [[nodiscard]] bool isUint8() const
      {
        checkValid();
        return mxIsUint8(mArray);
      }

      /**
       * @brief Is the array an int16?
       * @return True if the array is an int16, false otherwise
       */
      [[nodiscard]] bool isInt16() const
      {
        checkValid();
        return mxIsInt16(mArray);
      }

      /**
       * @brief Is the array a uint16?
       * @return True if the array is a uint16, false otherwise
       */
      [[nodiscard]] bool isUint16() const
      {
        checkValid();
        return mxIsUint16(mArray);
      }

      /**
       * @brief Is the array an int32?
       * @return True if the array is an int32, false otherwise
       */
      [[nodiscard]] bool isInt32() const
      {
        checkValid();
        return mxIsInt32(mArray);
      }

      /**
       * @brief Is the array a uint32?
       * @return True if the array is a uint32, false otherwise
       */
      [[nodiscard]] bool isUint32() const
      {
        checkValid();
        return mxIsUint32(mArray);
      }

      /**
       * @brief Is the array an int64?
       * @return True if the array is an int64, false otherwise
       */
      [[nodiscard]] bool isInt64() const
      {
        checkValid();
        return mxIsInt64(mArray);
      }

      /**
       * @brief Is the array a uint64?
       * @return True if the array is a uint64, false otherwise
       */
      [[nodiscard]] bool isUint64() const
      {
        checkValid();
        return mxIsUint64(mArray);
      }

      /**
       * @brief Is the array sparse?
       * @return True if the array is sparse, false otherwise
       */
      [[nodiscard]] bool isSparse() const
      {
        checkValid();
        return mxIsSparse(mArray);
      }

      /**
       * @brief Is the array char?
       * @return True if the array is char, false otherwise
       */
      [[nodiscard]] bool isChar() const
      {
        checkValid();
        return mxIsChar(mArray);
      }

      /**
       * @brief Is the array a logical?
       * @return True if the array is a logical, false otherwise
       */
      [[nodiscard]] bool isLogical() const
      {
        checkValid();
        return mxIsLogical(mArray);
      }

      /**
       * @brief Is the array a logical scalar?
       * @return True if the array is a logical scalar, false otherwise
       */
      [[nodiscard]] bool isLogicalScalar() const
      {
        checkValid();
        return mxIsLogicalScalar(mArray);
      }

      /**
       * @brief Is the array a true logical scalar?
       * @return True if the array is a true logical scalar, false otherwise
       */
      [[nodiscard]] bool isLogicalScalarTrue() const
      {
        checkValid();
        return mxIsLogicalScalarTrue(mArray);
      }

      /**
       * @brief Is the array a class?
       * @param name Class name
       * @return True if the array is a class, false otherwise
       */
      [[nodiscard]] bool isClass(const char* name) const
      {
        checkValid();

        if (name == nullptr)
        {
          throw Exception{"invalid class name"};
        }

        return mxIsClass(mArray, name);
      }

      /**
       * @brief Is the array a struct?
       * @return True if the array is a struct, false otherwise
       */
      [[nodiscard]] bool isStruct() const
      {
        checkValid();
        return mxIsStruct(mArray);
      }

      /**
       * @brief Is the array a cell?
       * @return True if the array is a cell, false otherwise
       */
      [[nodiscard]] bool isCell() const
      {
        checkValid();
        return mxIsCell(mArray);
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
       * @brief Get the class name of the array
       * @return Class name of the array
       */
      [[nodiscard]] const char* getClassName() const
      {
        checkValid();
        return mxGetClassName(mArray);
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
    protected:
      /// @brief Check if the array is valid
      void checkValid() const
      {
        if (!isValid())
        {
          throw Exception{"accessing invalid array"};
        }
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

        mexMakeArrayPersistent(arrayDup);

        return arrayDup;
      }

      /// @brief Destroy the array
      void destroy() noexcept
      {
        mxDestroyArray(std::exchange(mArray, nullptr));
      }

      mxArray* mArray{}; ///< mxArray pointer
  };
} // namespace mex

#endif /* MEX_ARRAY_HPP */
