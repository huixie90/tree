#include "tree/breadth_first.hpp"

#include <catch2/catch_all.hpp>
#include <vector>

#include <iostream>

#define TEST_POINT(x) TEST_CASE(x, "[breadth_first]")

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

  tree::breadth_first_view v(tree, &Node::children);

  auto expected = {0, 1, 2, 3, 4, 5, 6};
  REQUIRE(std::ranges::equal(v | std::views::transform(&Node::i), expected));
}

TEST_POINT("generator") {
  auto getChildren = [](int i) { return std::vector{2 * i + 1, 2 * i + 2}; };

  tree::breadth_first_view v(std::vector{0}, getChildren);
  auto expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  REQUIRE(std::ranges::equal(std::move(v) | std::views::take(15), expected));
}
