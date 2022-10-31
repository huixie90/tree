#include "tree/pre_order.hpp"

#include <catch2/catch_all.hpp>
#include <vector>

#include <iostream>

#define TEST_POINT(x) TEST_CASE(x, "[pre_order]")

struct Node {
  int i;
  std::vector<Node> children;
};

TEST_POINT("simple") {
  std::vector<Node> tree{
      {0,
       {
           {1,
            {
                {3, {}},
                {4, {}},
            }},
           {2,
            {
                {5, {}},
                {6, {}},
            }},
       }},
  };

  tree::pre_order_view v(tree, &Node::children);

  auto expected = {0, 1, 3, 4, 2, 5, 6};
  REQUIRE(std::ranges::equal(v | std::views::transform(&Node::i), expected));
}

TEST_POINT("forest") {
  std::vector<Node> tree{
      {0,
       {
           {1,
            {
                {3, {}},
                {4, {}},
            }},
           {2,
            {
                {5, {}},
                {6, {}},
            }},
       }},
      {7, {}},
  };

  tree::pre_order_view v(tree, &Node::children);

  auto expected = {0, 1, 3, 4, 2, 5, 6, 7};
  REQUIRE(std::ranges::equal(v | std::views::transform(&Node::i), expected));
}

TEST_POINT("generator") {
  auto getChildren = [](int i) {
    if (i > 6) {
      return std::vector<int>{};
    }
    return std::vector{2 * i + 1, 2 * i + 2};
  };

  tree::pre_order_view v(std::vector{0}, getChildren);
  auto expected = {0, 1, 3, 7, 8, 4, 9, 10, 2, 5, 11, 12, 6, 13, 14};
  REQUIRE(std::ranges::equal(std::move(v), expected));
}

TEST_POINT("empty") {
  std::vector<Node> tree{};

  tree::pre_order_view v(tree, &Node::children);
  REQUIRE(std::ranges::empty(v));
}
