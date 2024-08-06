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

#ifndef MEX_MEMORY_HPP
#define MEX_MEMORY_HPP

#include "detail/include.hpp"

namespace mex
{
  /// @brief A tag for allocating memory that is freed automatically when the MEX function terminates.
  inline constexpr struct NonPersistent {} nonPersistent;

  /**
   * @brief Allocates memory that is freed automatically when the MEX function terminates.
   * @param sizeInBytes The size of the memory to allocate in bytes.
   * @return A pointer to the allocated memory.
   */
  [[nodiscard]] inline void* malloc(std::size_t sizeInBytes, NonPersistent)
  {
    return mxMalloc(sizeInBytes);
  }

  /**
   * @brief Allocates memory.
   * @param sizeInBytes The size of the memory to allocate in bytes.
   * @return A pointer to the allocated memory.
   */
  [[nodiscard]] inline void* malloc(std::size_t sizeInBytes)
  {
    void* ptr = malloc(sizeInBytes, nonPersistent);

    mexMakeMemoryPersistent(ptr);

    return ptr;
  }

  /**
   * @brief Allocates memory and initializes it to zero. The memory is freed automatically when the MEX function terminates.
   * @param n The number of elements to allocate.
   * @return A pointer to the allocated memory.
   */
  template<typename T>
  [[nodiscard]] inline T* calloc(std::size_t n, NonPersistent)
  {
    return static_cast<T*>(mxCalloc(n, sizeof(T)));
  }

  /**
   * @brief Allocates memory and initializes it to zero.
   * @param n The number of elements to allocate.
   * @return A pointer to the allocated memory.
   */
  template<typename T>
  [[nodiscard]] inline T* calloc(std::size_t n)
  {
    T* ptr = calloc<T>(n, nonPersistent);

    mexMakeMemoryPersistent(ptr);

    return ptr;
  }

  /**
   * @brief Frees memory allocated with mxMalloc or mxCalloc.
   * @param ptr A pointer to the allocated memory.
   */
  inline void free(void* ptr)
  {
    mxFree(ptr);
  }

  /**
   * @brief A deleter for freeing memory allocated with mxMalloc or mxCalloc.
   * @tparam T The type of the allocated memory.
   */
  template<typename T>
  struct Deleter
  {
    /**
     * @brief Frees the allocated memory.
     * @param ptr A pointer to the allocated memory.
     */
    void operator()(T* ptr) const
    {
      mxFree(ptr);
    }
  };

  /**
   * @brief Allocator for use with std containers.
   * @tparam T The type of the allocated memory.
   */
  template<typename T>
  class Allocator
  {
  public:
    using value_type = T; ///< The type of the allocated memory.

    /// @brief Default constructor.
    Allocator() noexcept = default;

    /**
     * @brief Copy constructor.
     * @tparam U The type of the allocated memory.
     * @param other The allocator to copy.
     */
    template<typename U>
    Allocator(const Allocator<U>&) noexcept {}

    /**
     * @brief Allocates memory.
     * @param n The number of elements to allocate.
     * @return A pointer to the allocated memory.
     */
    T* allocate(std::size_t n)
    {
      if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
      {
        throw std::bad_alloc();
      }

      T* ptr = static_cast<T*>(malloc(n * sizeof(T)));

      if (!ptr)
      {
        throw std::bad_alloc();
      }

      return ptr;
    }

    /**
     * @brief Deallocates memory.
     * @param ptr A pointer to the allocated memory.
     * @param n The number of elements to deallocate.
     */
    void deallocate(T* ptr, std::size_t) noexcept
    {
      free(ptr);
    }
  };
} // namespace mex

#endif /* MEX_MEMORY_HPP */
