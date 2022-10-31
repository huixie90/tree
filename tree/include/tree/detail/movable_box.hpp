#ifndef TREE_TRAVERSER_DETAIL_MOVABLE_BOX_HPP
#define TREE_TRAVERSER_DETAIL_MOVABLE_BOX_HPP

#include <version>

#if defined(_LIBCPP_VERSION)

#include <__ranges/copyable_box.h>
#include <concepts>

namespace tree {

template <class T>
  requires(std::copy_constructible<T> && std::is_object_v<T>)
using movable_box = std::ranges::__copyable_box<T>;

}

#endif

#endif // TREE_TRAVERSER_DETAIL_MOVABLE_BOX_HPP
