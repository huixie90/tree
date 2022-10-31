#ifndef TREE_TRAVERSER_BREADTH_FIRST_HPP
#define TREE_TRAVERSER_BREADTH_FIRST_HPP

#include "detail/movable_box.hpp"

#include <cassert>
#include <concepts>
#include <deque>
#include <ranges>

namespace tree {

template <class View, class Fn>
class breadth_first_view
    : public std::ranges::view_interface<breadth_first_view<View, Fn>> {

  class iterator;

  friend class iterator;

  movable_box<Fn> successor_fn_;
  std::deque<View> queue_;

public:
  constexpr breadth_first_view(View roots, Fn suuccesor_fn)
      : successor_fn_(std::in_place, std::move(suuccesor_fn)), queue_() {
    if (!std::ranges::empty(roots)) {
      queue_.push_back(std::move(roots));
    }
  }

  constexpr iterator begin() {
    return {*this, std::ranges::begin(queue_.front())};
  }

  constexpr std::default_sentinel_t end() const { return {}; }
};

template <class View, class Fn> class breadth_first_view<View, Fn>::iterator {

  using Parent = breadth_first_view<View, Fn>;
  using BaseIter = std::ranges::iterator_t<View>;

  Parent *parent_ = nullptr;
  BaseIter current_ = BaseIter();

  void enqueue_next_generation() {
    decltype(auto) next = std::invoke(*(parent_->successor_fn_), *current_);
    if (!std::ranges::empty(next)) {
      parent_->queue_.push_back(
          std::views::all(std::forward<decltype(next)>(next)));
    }
  }

  constexpr bool parent_empty() const { return parent_->queue_.empty(); }

public:
  using iterator_concept = std::input_iterator_tag;
  using iterator_category = std::input_iterator_tag; // TODO: not always present
  using value_type = std::ranges::range_value_t<View>;
  using difference_type = std::ranges::range_difference_t<View>;

  iterator()
    requires std::default_initializable<BaseIter>
  = default;

  constexpr iterator(Parent &parent, BaseIter iter)
      : parent_(std::addressof(parent)), current_(std::move(iter)) {}

  constexpr decltype(auto) operator*() const { return *current_; }

  iterator &operator++() {
    assert(!parent_empty());

    enqueue_next_generation();

    if (++current_ == std::ranges::end(parent_->queue_.front())) {
      parent_->queue_.pop_front();
      if (!parent_empty()) {
        current_ = std::ranges::begin(parent_->queue_.front());
      }
    }

    return *this;
  }

  void operator++(int) { ++*this; }

  friend constexpr bool operator==(const iterator &iter,
                                   std::default_sentinel_t) {
    return iter.parent_empty();
  }
};

template <class Range, class Fn>
breadth_first_view(Range &&, Fn)
    -> breadth_first_view<std::views::all_t<Range &&>, Fn>;

} // namespace tree

#endif // TREE_TRAVERSER_BREADTH_FIRST_HPP
