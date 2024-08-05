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

#ifndef MEX_ARRAY_REF_HPP
#define MEX_ARRAY_REF_HPP

#include <mex.h>

#include "common.hpp"
#include "typeTraits.hpp"

namespace mex
{
  /// @brief Alias for a mutable reference to an array.
  using ArrayRef = Ref<Array>;

  /// @brief Alias for a constant reference to an array.
  using ArrayCref = Cref<Array>;

  /**
   * @brief Implements a reference to an array.
   * @tparam T The const or non-const type of the array.
   */
  template<typename T>
    requires isArray<T>
  class Ref<T>
  {
    private:
      /// @brief The constness of the referenced array.
      static constexpr bool isConst = std::is_const_v<T>;
    public:
      /// @brief Explicitly deleted default constructor.
      Ref() = delete;

      /// @brief Explicitly deleted constructor from nullptr.
      Ref(nullptr_t) = delete;

      /**
       * @brief Constructor from a mxArray pointer.
       * @param array mxArray pointer
       */
      explicit Ref(AddConstIfT<isConst, mxArray>* array)
      : mArray{array}
      {}

      /**
       * @brief Copy constructor from another reference.
       * @param other Another reference
       */
      template<typename U>
        requires isArray<U>
      Ref(const Ref<U>& other)
      : mArray{other.get()}
      {
        static_assert(isConst || !other.isConst);
      }

      ~Ref() = default;

      /**
       * @brief Copy assignment operator from another reference.
       * @param other Another reference
       * @return Reference to the assigned array
       */
      template<typename U>
        requires isArray<U>
      Ref& operator=(const Ref<U>& other)
      {
        static_assert(isConst || !other.isConst);

        mArray = other.get();
        return *this;
      }

      /**
       * @brief Gets the rank of the array.
       * @return The rank of the array
       */
      [[nodiscard]] std::size_t getRank() const
      {
        return mxGetNumberOfDimensions(mArray);
      }

      /**
       * @brief Gets the dimensions of the array.
       * @return The dimensions of the array
       */
      [[nodiscard]] View<std::size_t> getDims() const
      {
        return View<std::size_t>{mxGetDimensions(mArray), getRank()};
      }

      /**
       * @brief Gets the number of elements in the array.
       * @return The number of elements in the array
       */
      [[nodiscard]] std::size_t getNumElements() const
      {
        return mxGetNumberOfElements(mArray);
      }

      /**
       * @brief Is the array a scalar?
       * @return True if the array is a scalar, false otherwise
       */
      [[nodiscard]] bool isScalar() const
      {
        return mxIsScalar(mArray);
      }

      /**
       * @brief Is the array empty?
       * @return True if the array is empty, false otherwise
       */
      [[nodiscard]] bool isEmpty() const
      {
        return mxIsEmpty(mArray);
      }

      /**
       * @brief Is the array complex?
       * @return True if the array is complex, false otherwise
       */
      [[nodiscard]] bool isComplex() const
      {
        return mxIsComplex(mArray);
      }

      /**
       * @brief Gets the class ID of the array.
       * @return The class ID of the array
       */
      [[nodiscard]] ClassId getClassId() const
      {
        return static_cast<ClassId>(mxGetClassID(mArray));
      }

      /**
       * @brief Gets the data pointer.
       * @return The data pointer
       */
      [[nodiscard]] AddConstIfT<isConst, void>* getData() const
      {
        return mxGetData(mArray);
      }

      /**
       * @brief Gets the mxArray pointer.
       * @return The mxArray pointer
       */
      [[nodiscard]] AddConstIfT<isConst, mxArray>* get() const noexcept
      {
        return mArray;
      }
    protected:
      AddConstIfT<isConst, mxArray>* mArray{}; ///< The mxArray pointer
  };
} // namespace mex

#endif /* MEX_ARRAY_REF_HPP */
