#include <utils/uuid4.hpp>

#include <utils/boost_uuid4.hpp>
#include <utils/encoding/hex.hpp>

namespace utils::generators {

std::string GenerateUuidV4() {
  const auto val = GenerateBoostUuid();
  return encoding::ToHex(val.begin(), val.size());
}

}  // namespace utils::generators
