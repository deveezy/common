#pragma once

/// @file userver/utils/invariant_error.hpp
/// @brief @copybrief utils::InvariantError

#include <utils/traceful_exception.hpp>

namespace utils {

/// @ingroup userver_universal
///
/// @brief Exception that is thrown on UINVARIANT violation
class InvariantError : public TracefulException {
  using TracefulException::TracefulException;
};

}  // namespace utils
