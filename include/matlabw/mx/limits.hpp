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

#ifndef MATLABW_MX_LIMITS_HPP
#define MATLABW_MX_LIMITS_HPP

#include "detail/include.hpp"

namespace matlabw::mx
{
  /// @brief Maximum size.
  inline constexpr std::size_t maxSize{MWSIZE_MAX};

  /// @brief Maximum index.
  inline constexpr std::size_t maxIndex{MWINDEX_MAX};

  /// @brief Maximum signed index.
  inline constexpr std::ptrdiff_t maxSignedIndex{MWSINDEX_MAX};

  /// @brief Minimum size.
  inline constexpr std::size_t minSize{MWSIZE_MIN};

  /// @brief Minimum index.
  inline constexpr std::size_t minIndex{MWINDEX_MIN};

  /// @brief Minimum signed index.
  inline constexpr std::ptrdiff_t minSignedIndex{MWSINDEX_MIN};

  /// @brief Maximum MATLAB identifier size.
  inline constexpr std::size_t maxNameSize{mxMAXNAM};
} // namespace matlabw::mx

#endif /* MATLABW_MX_LIMITS_HPP */
