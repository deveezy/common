#include <utils/ip.hpp>

#include <arpa/inet.h>

#include <fmt/format.h>

#include <utils/from_string.hpp>
#include <utils/check_syscall.hpp>

namespace utils::ip {

namespace {

template <size_t N>
AddressBase<N> AddressFromString(const std::string &str) {
  typename AddressBase<N>::BytesType bytes;
  const auto compare = [](const int &ret, const int &err_mark) { return ret <= err_mark; };
  const auto family  = N == 4 ? AF_INET : AF_INET6;
  utils::CompareSyscallWithCustomException<AddressSystemError>(compare, ::inet_pton(family, str.data(), &bytes), 0,
      fmt::format("converting {} address from string", N == 4 ? "IPv4" : "IPv6"));
  return AddressBase<N>(bytes);
}

template <size_t N>
std::string AddressToString(const AddressBase<N> &address) {
  constexpr auto addr_len = N == 4 ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;
  char addr_str[addr_len];
  const auto bytes  = address.GetBytes();
  const auto family = N == 4 ? AF_INET : AF_INET6;
  return utils::CheckSyscallNotEqualsCustomException<AddressSystemError>(
      ::inet_ntop(family, &bytes, addr_str, addr_len), nullptr, "converting {} address to string",
      N == 4 ? "IPv4" : "IPv6");
}

template <typename Address>
NetworkBase<Address> NetworkFromString(const std::string &str)
  requires(kIsAddressType<Address>)
{
  const auto throw_exception = []() {
    throw std::invalid_argument(fmt::format(
        "Error while converting {} to string", std::is_same_v<Address, AddressV4> ? "NetworkV4" : "NetworkV6"));
  };
  auto pos = str.find_first_of('/');
  if ((pos == std::string::npos) || (pos == str.size() - 1)) { throw_exception(); }
  auto end = str.find_first_not_of("0123456789", pos + 1);
  if (end != std::string::npos) { throw_exception(); }
  const auto addr      = AddressFromString<Address::AddressSize>(str.substr(0, pos));
  const int prefix_len = utils::FromString<int>(str.substr(pos + 1));
  if (prefix_len < 0 || prefix_len > NetworkBase<Address>::kMaximumPrefixLength) { throw_exception(); }
  return NetworkBase<Address>(addr, static_cast<unsigned char>(prefix_len));
}

template <typename Address>
NetworkBase<Address> TransformToCidrNetwork(NetworkBase<Address> address) {
  auto bytes               = address.GetAddress().GetBytes();
  const auto prefix_length = address.GetPrefixLength();
  for (std::size_t i = 0; i < bytes.size(); ++i) {
    if (prefix_length <= i * 8) {
      bytes[i] = 0;
    } else if (prefix_length < (i + 1) * 8) {
      bytes[i] &= 0xFF00 >> (prefix_length % 8);
    }
  }
  return NetworkBase<Address>(typename NetworkBase<Address>::AddressType(bytes), prefix_length);
}

}  // namespace

AddressV4 AddressV4FromString(const std::string &str) { return AddressFromString<4>(str); }

std::string AddressV4ToString(const AddressV4 &address) { return AddressToString(address); }

AddressV6 AddressV6FromString(const std::string &str) { return AddressFromString<16>(str); }

std::string AddressV6ToString(const AddressV6 &address) { return AddressToString(address); }

std::string NetworkV4ToString(const NetworkV4 &network) {
  return fmt::format("{}/{}", AddressV4ToString(network.GetAddress()), network.GetPrefixLength());
}

NetworkV4 NetworkV4FromString(const std::string &str) { return NetworkFromString<AddressV4>(str); }

NetworkV4 TransformToCidrFormat(NetworkV4 network) { return TransformToCidrNetwork<AddressV4>(network); }

std::string NetworkV6ToString(const NetworkV6 &network) {
  return fmt::format("{}/{}", AddressV6ToString(network.GetAddress()), network.GetPrefixLength());
}

NetworkV6 NetworkV6FromString(const std::string &str) { return NetworkFromString<AddressV6>(str); }

NetworkV6 TransformToCidrFormat(NetworkV6 network) { return TransformToCidrNetwork<AddressV6>(network); }

}  // namespace utils::ip
