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

#ifndef MEX_OBJECT_ARRAY_HPP
#define MEX_OBJECT_ARRAY_HPP

#include "detail/include.hpp"

#include "TypedArray.hpp"
#include "StructArray.hpp"

namespace mex
{
  /// @brief ObjectArray class
  class ObjectArray : public TypedArray<Object>
  {
    public:
      /// @brief Inherit constructors
      using TypedArray<Object>::TypedArray;

      /**
       * @brief Construct an object array from a struct array
       * @param src Source struct array
       * @param name Class name
       */
      ObjectArray(StructArray src, const char* name)
      {
        if (name == nullptr)
        {
          throw Exception{"class name must not be null"};
        }

        Array array{src.release()};

        if (mxSetClassName(array.get(), name))
        {
          throw Exception{"failed to set class name"};
        }

        *this = std::move(array);
      }

      /// @brief Default destructor
      ~ObjectArray() = default;

      /// @brief Use inherited assignment operators
      using TypedArray<Object>::operator=;

      /**
       * @brief Get the class name of the object
       * @return Class name
       */
      [[nodiscard]] const char* getClassName() const
      {
        checkValid();
        return mxGetClassName(get());
      }

      /**
       * @brief Gets the property of the object
       * @param i Index
       * @param propName Property name
       * @return Property value
       */
      [[nodiscard]] std::optional<ArrayCref> getProperty(std::size_t i, const char* propName) const
      {
        checkValid();

        if (propName == nullptr)
        {
          throw Exception{"property name must not be null"};
        }

        mxArray* array = mxGetProperty(get(), i, propName);

        if (array == nullptr)
        {
          return std::nullopt;
        }

        mexMakeArrayPersistent(array);

        return ArrayCref{array};
      }

      /**
       * @brief Sets the property of the object
       * @param i Index
       * @param propName Property name
       * @param value Property value
       */
      void setProperty(std::size_t i, const char* propName, ArrayCref value)
      {
        checkValid();

        if (propName == nullptr)
        {
          throw Exception{"property name must not be null"};
        }

        mxSetProperty(get(), i, propName, value.get());
      }
  };
} // namespace mex

#endif /* MEX_OBJECT_ARRAY_HPP */
