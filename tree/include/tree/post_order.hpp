#ifndef TREE_TRAVERSER_POST_ORDER_HPP
#define TREE_TRAVERSER_POST_ORDER_HPP

#include "detail/movable_box.hpp"

#include <cassert>
#include <concepts>
#include <ranges>
#include <stack>

namespace tree {

template <class View, class Fn>
class post_order_view
    : public std::ranges::view_interface<post_order_view<View, Fn>> {

  struct view_and_iter {
    using BaseIter = std::ranges::iterator_t<View>;
    View view_;
    BaseIter iter_;

    constexpr view_and_iter(View view)
        : view_(std::move(view)), iter_(std::ranges::begin(view_)) {}
  };

  class iterator;

  friend class iterator;

  movable_box<Fn> successor_fn_;
  std::stack<view_and_iter> stack_;

  constexpr void search() {
    while (stack_.top().iter_ != std::ranges::end(stack_.top().view_)) {
      stack_.emplace(
          std::views::all(std::invoke(*successor_fn_, *stack_.top().iter_)));
    }
    stack_.pop();
  }

public:
  constexpr post_order_view(View roots, Fn suuccesor_fn)
      : successor_fn_(std::in_place, std::move(suuccesor_fn)), stack_() {
    if (!std::ranges::empty(roots)) {
      stack_.emplace(std::move(roots));
    }
  }

  constexpr iterator begin() {
    search();
    return {*this};
  }

  constexpr std::default_sentinel_t end() const { return {}; }

  constexpr bool empty() const { return stack_.empty(); }
};

template <class View, class Fn> class post_order_view<View, Fn>::iterator {

  using Parent = post_order_view<View, Fn>;

  Parent *parent_ = nullptr;

  constexpr bool parent_empty() const { return parent_->stack_.empty(); }

public:
  using iterator_concept = std::input_iterator_tag;
  using iterator_category = std::input_iterator_tag; // TODO: not always present
  using value_type = std::ranges::range_value_t<View>;
  using difference_type = std::ranges::range_difference_t<View>;

  iterator() = default;

  constexpr iterator(Parent &parent) : parent_(std::addressof(parent)) {}

  constexpr decltype(auto) operator*() const {
    return *parent_->stack_.top().iter_;
  }

  constexpr iterator &operator++() {
    assert(!parent_empty());

    ++parent_->stack_.top().iter_;
    parent_->search();

    return *this;
  }

  constexpr void operator++(int) { ++*this; }

  friend constexpr bool operator==(const iterator &iter,
                                   std::default_sentinel_t) {
    return iter.parent_empty();
  }
};

template <class Range, class Fn>
post_order_view(Range &&, Fn)
    -> post_order_view<std::views::all_t<Range &&>, Fn>;

} // namespace tree

#endif // TREE_TRAVERSER_POST_ORDER_HPP
