#pragma once

/// @brief @copybrief utils::NotNull

#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

#include <utils/assert.hpp>

namespace utils {

///
/// @brief Restricts a pointer or smart pointer to only hold non-null values.
template <typename T>
class NotNull {
  static_assert(!std::is_reference_v<T>, "NotNull does not work with references");
  static_assert(!std::is_const_v<T>);

public:
  constexpr explicit NotNull() = delete;

  constexpr explicit NotNull(const T &u) : ptr_(u) { ASSERT_MSG(ptr_, "Trying to construct NotNull from null"); }

  constexpr explicit NotNull(T &&u) : ptr_(std::move(u)) { ASSERT_MSG(ptr_, "Trying to construct NotNull from null"); }

  template <typename U>
  constexpr explicit NotNull(U &&u)
    requires(std::is_convertible_v<U, T>)
      : ptr_(std::forward<U>(u)) {
    ASSERT_MSG(ptr_, "Trying to construct NotNull from null");
  }

  template <typename U>
  constexpr /*implicit*/ NotNull(U &u)
    requires(std::is_convertible_v<U *, T>)
      : ptr_(std::addressof(u)) {}

  template <typename U>
  constexpr NotNull(const NotNull<U> &other)
    requires(std::is_convertible_v<U, T>)
      : ptr_(other.GetBase()) {
    ASSERT_MSG(ptr_, "Trying to construct NotNull from null (moved-from) NotNull");
  }

  template <typename U>
  constexpr NotNull(NotNull<U> &&other)
    requires(std::is_convertible_v<U, T>)
      : ptr_(std::move(other).GetBase()) {
    ASSERT_MSG(ptr_, "Trying to construct NotNull from null (moved-from) NotNull");
  }

  constexpr NotNull(std::nullptr_t) = delete;

  NotNull(const NotNull &other) noexcept = default;
  NotNull(NotNull &&other) noexcept      = default;

  NotNull &operator=(const NotNull &other) noexcept = default;
  NotNull &operator=(NotNull &&other) noexcept      = default;

  constexpr NotNull &operator=(std::nullptr_t) = delete;

  constexpr const T &GetBase() const & {
    ASSERT_MSG(ptr_, "Trying to access a null (moved-from) NotNull");
    return ptr_;
  }

  constexpr T &&GetBase() && {
    ASSERT_MSG(ptr_, "Trying to access a null (moved-from) NotNull");
    return std::move(ptr_);
  }

  constexpr /*implicit*/ operator const T &() const & { return GetBase(); }

  constexpr /*implicit*/ operator bool() = delete;

  constexpr decltype(auto) operator->() const & { return GetBase(); }

  constexpr decltype(auto) operator*() const & { return *GetBase(); }

  template <typename U>
  constexpr bool operator==(const NotNull<U> &other) const & {
    return GetBase() == other.GetBase();
  }

  template <typename U>
  constexpr bool operator!=(const NotNull<U> &other) const & {
    return GetBase() != other.GetBase();
  }

private:
  T ptr_;
};

/// @brief A `std::shared_ptr` that is guaranteed to be not-null.
/// @see MakeSharedRef
template <typename U>
using SharedRef = NotNull<std::shared_ptr<U>>;

/// @brief A `std::unique_ptr` that is guaranteed to be not-null.
/// @see MakeUniqueRef
template <typename U>
using UniqueRef = NotNull<std::unique_ptr<U>>;

/// @brief An equivalent of `std::make_shared` for SharedRef.
template <typename U, typename... Args>
SharedRef<U> MakeSharedRef(Args &&...args) {
  return SharedRef<U> {std::make_shared<U>(std::forward<Args>(args)...)};
}

/// @brief An equivalent of `std::make_unique` for UniqueRef.
template <typename U, typename... Args>
UniqueRef<U> MakeUniqueRef(Args &&...args) {
  return UniqueRef<U> {std::make_unique<U>(std::forward<Args>(args)...)};
}

}  // namespace utils

template <typename T>
// NOLINTNEXTLINE(cert-dcl58-cpp)
struct std::hash<utils::NotNull<T>> : public std::hash<T> {
  using std::hash<T>::hash;

  auto operator()(const utils::NotNull<T> &value) const
      noexcept(std::is_nothrow_invocable_v<const std::hash<T> &, const T &>) {
    return this->std::hash<T>::operator()(value.GetBase());
  }
};
