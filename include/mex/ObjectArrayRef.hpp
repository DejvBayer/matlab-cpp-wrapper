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

#ifndef MEX_OBJECT_ARRAY_REF_HPP
#define MEX_OBJECT_ARRAY_REF_HPP

#include "detail/include.hpp"

#include "TypedArrayRef.hpp"

namespace mex
{
  /// @brief ObjectArrayRef class
  class ObjectArrayRef : public TypedArrayRef<Object>
  {
    public:
      /// @brief Inherit constructors
      using TypedArrayRef<Object>::TypedArrayRef;

      /// @brief Default destructor
      ~ObjectArrayRef() = default;

      /// @brief Inherit assignment operators
      using TypedArrayRef<Object>::operator=;

      /**
       * @brief Get the class name of the object
       * @return Class name
       */
      [[nodiscard]] const char* getClassName() const
      {
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
      void setProperty(std::size_t i, const char* propName, ArrayCref value) const
      {
        if (propName == nullptr)
        {
          throw Exception{"property name must not be null"};
        }

        mxSetProperty(get(), i, propName, value.get());
      }
  };

  /// @brief ObjectArrayCref type alias
  class ObjectArrayCref : public ObjectArrayRef
  {
    public:
      /// @brief Inherit constructors
      using ObjectArrayRef::ObjectArrayRef;

      /// @brief Default destructor
      ~ObjectArrayCref() = default;

      /// @brief Inherit assignment operators
      using ObjectArrayRef::operator=;

      /**
       * @brief Get the class name of the object
       * @return Class name
       */
      [[nodiscard]] const char* getClassName() const
      {
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
  };
}