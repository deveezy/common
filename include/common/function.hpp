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

  alignas(StorageAlign) std::byte data[StorageSize];
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
    _function.manager(&data, &_function._data, Operation::Clone);
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
  static_assert((StorageAlign % alignof(function_type) == 0),
                "Function::StorageAlign must be adjusted");

  // Create the implementation inastance
  invoker = &Invoke<function_type>;
  manager = &Manage<function_type>;
}

template <class R, class... Args, size_t Capacity>
inline Function<R(Args...), Capacity>::~Function() noexcept {
  if (manager) manager(&data, nullptr, Operation::Destroy);
}

template <typename R, typename... Args, size_t Capacity>
inline Function<R(Args...), Capacity> &
Function<R(Args...), Capacity>::operator=(std::nullptr_t) noexcept {
  if (manager) {
    manager(&data, nullptr, Operation::Destroy);
    manager = nullptr;
    invoker = nullptr;
  }
  return *this;
}

template <typename R, typename... Args, size_t Capacity>
inline Function<R(Args...), Capacity> &
Function<R(Args...), Capacity>::operator=(const Function &_function) noexcept {
  Function(_function).swap(*this);
  return *this;
}

template <typename R, typename... Args, size_t Capacity>
inline Function<R(Args...), Capacity> &
Function<R(Args...), Capacity>::operator=(Function &&_function) noexcept {
  Function(std::move(_function)).swap(*this);
  return *this;
}

template <class R, class... Args, size_t Capacity>
template <typename TFunction>
inline Function<R(Args...), Capacity> &
Function<R(Args...), Capacity>::operator=(TFunction &&_function) noexcept {
  Function(std::forward<TFunction>(_function)).swap(*this);
  return *this;
}

template <class R, class... Args, size_t Capacity>
template <typename TFunction>
inline Function<R(Args...), Capacity> &
Function<R(Args...), Capacity>::operator=(std::reference_wrapper<TFunction> _function) noexcept {
  Function(_function).swap(*this);
  return *this;
}

template <typename R, typename... Args, size_t Capacity>
inline R Function<R(Args...), Capacity>::operator()(Args... _args) {
  if (!invoker) throw std::bad_function_call();
  return invoker(&data, std::forward<Args>(_args)...);
}

template <typename R, typename... Args, size_t Capacity>
template <typename TFunction>
inline R Function<R(Args...), Capacity>::Invoke(void *_data, Args &&..._args) noexcept {
  TFunction &function = *static_cast<TFunction *>(_data);
  return function(std::forward<Args>(_args)...);
}

template <typename R, typename... Args, size_t Capacity>
template <typename TFunction>
inline void Function<R(Args...), Capacity>::Manage(void *_dst, void *_src,
                                                   Operation _operation) noexcept {
  switch (_operation) {
    case Operation::Clone:
      new (_dst) TFunction(*static_cast<TFunction *>(_src));
      break;
    case Operation::Destroy:
      static_cast<TFunction *>(_dst)->~TFunction();
      break;
  }
}

template <typename R, typename... Args, size_t Capacity>
inline void Function<R(Args...), Capacity>::swap(Function &_function) noexcept {
  std::swap(data, _function.data);
  std::swap(manager, _function.manager);
  std::swap(invoker, _function.invoker);
}

template <typename R, typename... Args, size_t Capacity>
void swap(Function<R(Args...), Capacity> &_lhs, Function<R(Args...), Capacity> &_rhs) noexcept {
  _lhs.swap(_rhs);
}
} // namespace common
