#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <type_traits>

namespace common
{
// Allocation free function stub
template <typename, size_t Capacity = 1024>
class Function;

/*
  Allocation free function uses internal stack-based buffer to keep
  the closure. This allows to avoid slow heap allocation in function
  constructor as it performed in std::function implementation.
*/
template <typename R, typename... Args, size_t Capacity>
class Function<R(Args...), Capacity>
{
public:
  Function() noexcept;
  Function(std::nullptr_t _function) noexcept;
  Function(const Function &_function) noexcept;
  Function(Function &&_function) noexcept;
  template <typename TFunction>
  Function(TFunction &&_function) noexcept;
  ~Function() noexcept;

  Function &operator=(std::nullptr_t) noexcept;
  Function &operator=(const Function &_function) noexcept;
  Function &operator=(Function &&_function) noexcept;
  template <typename TFunction>
  Function &operator=(TFunction &&_function) noexcept;
  template <typename TFunction>
  Function &operator=(std::reference_wrapper<TFunction> _function) noexcept;

  // Check if the function is valid
  explicit operator bool() const noexcept { return manager != nullptr; }

  // Invoke the function
  R operator()(Args... args);

  // Swap two instances
  void swap(Function &_function) noexcept;
  template <typename UR, typename... UArgs, size_t UCapacity>
  friend void swap(Function<UR(UArgs...), UCapacity> &_lhs,
                   Function<UR(UArgs...), UCapacity> &_rhs) noexcept;

private:
  enum class Operation { Clone, Destroy };

  using Invoker = R (*)(void *, Args &&...);
  using Manager = void (*)(void *, void *, Operation);

  static const size_t StorageSize = Capacity - sizeof(Invoker) - sizeof(Manager);
  static const size_t StorageAlign = 8;

  alignas(StorageAlign) std::byte _data[StorageSize];
  Invoker invoker;
  Manager manager;

  template <typename TFunction>
  static R Invoke(void *_data, Args &&...) noexcept;

  template <typename TFunction>
  static void Manage(void *dst, void *src, Operation _operation) noexcept;
};

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!  IMPLEMENTATION  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

template <typename R, typename... Args, size_t Capacity>
inline Function<R(Args...), Capacity>::Function() noexcept
  : invoker(nullptr)
  , manager(nullptr) {}

template <typename R, typename... Args, size_t Capacity>
inline Function<R(Args...), Capacity>::Function(std::nullptr_t) noexcept
  : Function<R(Args...), Capacity>() {}

template <typename R, typename... Args, size_t Capacity>
inline Function<R(Args...), Capacity>::Function(const Function &_function) noexcept
  : Function<R(Args...), Capacity>() {
  if (_function) {
    _function.manager(&_data, &_function._data, Operation::Clone);
    invoker = _function.invoker;
    manager = _function.manager;
  }
}

template <typename R, typename... Args, size_t Capacity>
inline Function<R(Args...), Capacity>::Function(Function &&_function) noexcept
  : Function<R(Args...), Capacity>() {
  _function.swap(*this);
}

template <typename R, typename... Args, size_t Capacity>
template <typename TFunction>
inline Function<R(Args...), Capacity>::Function(TFunction &&function) noexcept
  : Function<R(Args...), Capacity>() {
  using function_type = std::decay_t<TFunction>;

  // Check implementation storage parameters
  static_assert((StorageSize >= sizeof(function_type)), "Function::StorageSize must be increased");
  static_assert((StorageAlign >= alignof(function_type) == 0),
                "Function::StorageAlign must be adjusted");
}
} // namespace common
