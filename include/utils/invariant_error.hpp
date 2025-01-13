#pragma once

/// @brief @copybrief utils::InvariantError

#include <utils/traceful_exception.hpp>

namespace utils {

///
/// @brief Exception that is thrown on INVARIANT violation
class InvariantError : public TracefulException {
  using TracefulException::TracefulException;
};

}  // namespace utils
