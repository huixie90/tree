#ifndef TREE_TRAVERSER_DETAIL_MAYBE_CONST_HPP
#define TREE_TRAVERSER_DETAIL_MAYBE_CONST_HPP

#include <version>

#if defined(_LIBCPP_VERSION)

#include <__type_traits/maybe_const.h>

_LIBCPP_BEGIN_NAMESPACE_STD

namespace ranges {

template <bool _Const, class _Tp>
using maybe_const = __maybe_const<_Const, _Tp>;

}

_LIBCPP_END_NAMESPACE_STD

#endif

#endif // TREE_TRAVERSER_DETAIL_MAYBE_CONST_HPP
