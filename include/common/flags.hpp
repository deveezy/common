#pragma once

#include <bitset>
#include <type_traits>

namespace common
{
// Enum-based flags false checker
template <typename TEnum>
struct IsEnumFlags : public std::false_type
{
};

//! Register a new enum-based flags macro
#define ENUM_FLAGS(_type)                                                                          \
  using common::operator&;                                                                         \
  using common::operator|;                                                                         \
  using common::operator^;                                                                         \
  namespace common                                                                                 \
  {                                                                                                \
  template <>                                                                                      \
  struct IsEnumFlags<_type> : std::true_type                                                       \
  {                                                                                                \
  };                                                                                               \
  }

//! Enum-based flags
/*!
    Helper class for enum based flags which wraps particular enum as a template parameter
    and provides flags manipulation operators and methods.
    Not thread-safe.
*/

template <typename TEnum>
class Flags
{
  //! Enum underlying type
  using Type = std::make_unsigned_t<std::underlying_type_t<TEnum>>;

public:
  Flags() noexcept = default;
  Flags(Type _value) noexcept
    : value(_value) {}
  Flags(TEnum _value) noexcept
    : value(static_cast<Type>(_value)) {}
  Flags(const Flags &) noexcept = default;
  Flags(Flags &&) noexcept = default;
  ~Flags() noexcept = default;

  Flags &operator=(Type _value) noexcept {
    value = _value;
    return *this;
  }
  // enum class : uint8_t {EnumValue0, EnumValue1}
  // Flags example = EnumValue1;
  Flags &operator=(TEnum _value) noexcept {
    value = static_cast<Type>(_value);
    return *this;
  }
  Flags &operator=(const Flags &) noexcept = default;
  Flags &operator=(Flags &&) noexcept = default;

  //! Is any flag set?
  explicit operator bool() const noexcept { return IsSet(); }

  //! Is no flag set?
  bool operator!() const noexcept { return !IsSet(); }

  //! Reverse all flags
  Flags operator~() const noexcept { return Flags(~value); }

  //! Flags logical assign operators
  Flags &operator&=(const Flags &_flags) noexcept {
    value &= _flags.value;
    return *this;
  }
  Flags &operator|=(const Flags &_flags) noexcept {
    value |= _flags.value;
    return *this;
  }
  Flags &operator^=(const Flags &_flags) noexcept {
    value ^= _flags.value;
    return *this;
  }

  //! Flags logical friend operators
  friend Flags operator&(const Flags &_flags1, const Flags &_flags2) noexcept {
    return Flags(_flags1.value & _flags2.value);
  }
  friend Flags operator|(const Flags &_flags1, const Flags &_flags2) noexcept {
    return Flags(_flags1.value | _flags2.value);
  }
  friend Flags operator^(const Flags &_flags1, const Flags &_flags2) noexcept {
    return Flags(_flags1.value ^ _flags2.value);
  }

  // Flags comparison
  friend bool operator==(const Flags &_flags1, const Flags &_flags2) noexcept {
    return _flags1.value == _flags2.value;
  }
  friend bool operator!=(const Flags &_flags1, const Flags &_flags2) noexcept {
    return _flags1.value != _flags2.value;
  }

  //! Convert to the enum value
  operator TEnum() const noexcept { return static_cast<TEnum>(value); }

  //! Is any flag set?
  bool IsSet() const noexcept { return (value != 0); }
  //! Is the given flag set?
  bool IsSet(Type _value) const noexcept { return (value & _value) != 0; }
  //! Is the given flag set?
  bool IsSet(TEnum _value) const noexcept { return (value & static_cast<Type>(_value)) != 0; }

  //! Get the enum value
  TEnum Value() const noexcept { return static_cast<TEnum>(value); }

  //! Get the underlying enum value
  Type Underlying() const noexcept { return value; }
  //! Get the bitset value
  std::bitset<sizeof(Type) * 8> Bitset() const noexcept { return {value}; }

  //! Swap two instances
  void Swap(Flags &_flags) noexcept {
    using std::swap;
    swap(value, _flags.value);
  }

  template <typename UEnum>
  friend void Swap(Flags<UEnum> &_flags1, Flags<UEnum> &_flags2) noexcept;

private:
  Type value{0};
};

template <typename TEnum>
inline void Swap(Flags<TEnum> &_flags1, Flags<TEnum> &_flags2) noexcept {
  _flags1.swap(_flags2);
}

template <typename TEnum>
constexpr auto operator&(TEnum _value1, TEnum _value2) noexcept
  -> std::enable_if_t<IsEnumFlags<TEnum>::value, Flags<TEnum>> {
  return Flags<TEnum>(_value1) & _value2;
}

template <typename TEnum>
constexpr auto operator|(TEnum _value1, TEnum _value2) noexcept
  -> std::enable_if_t<IsEnumFlags<TEnum>::value, Flags<TEnum>> {
  return Flags<TEnum>(_value1) | _value2;
}

template <typename TEnum>
constexpr auto operator^(TEnum _value1, TEnum _value2) noexcept
  -> std::enable_if_t<IsEnumFlags<TEnum>::value, Flags<TEnum>> {
  return Flags<TEnum>(_value1) ^ _value2;
}

} // namespace common
