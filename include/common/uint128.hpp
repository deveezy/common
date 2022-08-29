#pragma once

#include <cstdint>

namespace common
{
class uint128_t
{
public:
  uint128_t() noexcept;
  uint128_t(int8_t) noexcept;
  uint128_t(uint8_t) noexcept;
  uint128_t(int16_t) noexcept;
  uint128_t(uint16_t) noexcept;
  uint128_t(int32_t) noexcept;
  uint128_t(uint32_t) noexcept;
  uint128_t(int64_t) noexcept;
  uint128_t(uint64_t) noexcept;

  template <typename T>
  explicit uint128_t(const T &_value) noexcept;

  template <typename TUpper, typename TLower>
  uint128_t(const TUpper &_upper, const TLower &_lower) noexcept;

  uint128_t(const uint128_t &_value) noexcept = default;
  uint128_t(uint128_t &&_value) noexcept = default;
  ~uint128_t() noexcept = default;

  template <typename T>
  uint128_t &operator=(const T &_value) noexcept;
  uint128_t &operator=(const uint128_t &_value) noexcept = default;
  uint128_t &operator=(uint128_t &&_value) noexcept = default;

  uint128_t operator+() const noexcept { return *this; }
  uint128_t operator-() const noexcept { return ~*this + 1; }

  uint128_t &operator++() noexcept { return *this += 1; }
  uint128_t operator++(int) noexcept {
    uint128_t tmp{*this};
    ++*this;
    return tmp;
  }
  uint128_t &operator--() noexcept { return *this -= 1; }
  uint128_t operator--(int) noexcept {
    uint128_t tmp{*this};
    --*this;
    return tmp;
  }

  uint128_t &operator+=(const uint128_t &_value) noexcept { return *this = *this + _value; }
  uint128_t &operator-=(const uint128_t &_value) noexcept { return *this = *this - _value; }
  uint128_t &operator*=(const uint128_t &_value) noexcept { return *this = *this * _value; }
  uint128_t &operator/=(const uint128_t &_value) noexcept { return *this = *this / _value; }
  uint128_t &operator%=(const uint128_t &_value) noexcept { return *this = *this % _value; }

  template <typename T>
  uint128_t &operator+=(const T &_value) noexcept {
    return *this = *this + uint128_t{_value};
  }
  template <typename T>
  uint128_t &operator-=(const T &_value) noexcept {
    return *this = *this - uint128_t{_value};
  }
  template <typename T>
  uint128_t &operator*=(const T &_value) noexcept {
    return *this = *this * uint128_t{_value};
  }
  template <typename T>
  uint128_t &operator/=(const T &_value) noexcept {
    return *this = *this / uint128_t{_value};
  }
  template <typename T>
  uint128_t &operator%=(const T &_value) noexcept {
    return *this = *this % uint128_t{_value};
  }

  template <typename T>
  friend T &operator+=(T &_value1, const uint128_t &_value2) noexcept {
    return _value1 = (T)(uint128_t(_value1) + _value2);
  }
  template <typename T>
  friend T &operator-=(T &_value1, const uint128_t &_value2) noexcept {
    return _value1 = (T)(uint128_t(_value1) - _value2);
  }
  template <typename T>
  friend T &operator*=(T &_value1, const uint128_t &_value2) noexcept {
    return _value1 = (T)(uint128_t(_value1) * _value2);
  }
  template <typename T>
  friend T &operator/=(T &_value1, const uint128_t &_value2) noexcept {
    return _value1 = (T)(uint128_t(_value1) / _value2);
  }
  template <typename T>
  friend T &operator%=(T &_value1, const uint128_t &_value2) noexcept {
    return _value1 = (T)(uint128_t(_value1) % _value2);
  }

  template <typename T>
  friend T operator+(T &_value1, const uint128_t &_value2) noexcept {
    return uint128_t{_value1} + _value2;
  }
  template <typename T>
  friend T operator+(const uint128_t &_value1, T &_value2) noexcept {
    return _value1 + uint128_t{_value2};
  }
  friend uint128_t operator+(const uint128_t &_value1, const uint128_t &_value2) noexcept;

  template <typename T>
  friend T operator-(T &_value1, const uint128_t &_value2) noexcept {
    return uint128_t{_value1} - _value2;
  }
  template <typename T>
  friend T operator-(const uint128_t &_value1, T &_value2) noexcept {
    return _value1 - uint128_t{_value2};
  }
  friend uint128_t operator-(const uint128_t &_value1, const uint128_t &_value2) noexcept;

  template <typename T>
  friend T operator*(T &_value1, const uint128_t &_value2) noexcept {
    return uint128_t{_value1} * _value2;
  }
  template <typename T>
  friend T operator*(const uint128_t &_value1, T &_value2) noexcept {
    return _value1 * uint128_t{_value2};
  }
  friend uint128_t operator*(const uint128_t &_value1, const uint128_t &_value2) noexcept;

  template <typename T>
  friend T operator/(T &_value1, const uint128_t &_value2) noexcept {
    return uint128_t{_value1} / _value2;
  }
  template <typename T>
  friend T operator/(const uint128_t &_value1, T &_value2) noexcept {
    return _value1 / uint128_t{_value2};
  }
  friend uint128_t operator/(const uint128_t &_value1, const uint128_t &_value2) noexcept;

  template <typename T>
  friend T operator%(T &_value1, const uint128_t &_value2) noexcept {
    return uint128_t{_value1} % _value2;
  }
  template <typename T>
  friend T operator%(const uint128_t &_value1, T &_value2) noexcept {
    return _value1 % uint128_t{_value2};
  }
  friend uint128_t operator%(const uint128_t &_value1, const uint128_t &_value2) noexcept;
};
} // namespace common

int main() {
  common::uint128_t val = 10;
  +val;
  return 0;
}
