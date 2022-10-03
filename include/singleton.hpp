#pragma once

#include <memory>

template <typename T>
struct wrapper
{
  /* If this isn't here, the issue doesn't exist. Also, if it's a trivial type, the issue
   * doesn't exist. Also, if it's shared_ptr, it doesn't exist. */
  std::unique_ptr<T> a;
  /* This is 0x0 outside of cling and 0x1 inside of Cling. */
  T *b{};
};

template <typename C>
wrapper<C>& singleton()
{
  static wrapper<C> p{};
  return p;
}
