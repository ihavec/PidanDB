#include <gtest/gtest.h>

#include <string>

#include "container/bplustree/node.h"
#include "container/bplustree/tree.h"

namespace pidan {

using Key = std::string;
using KeyComparator = std::less<Key>;

TEST(BPlusTreeNodeTest, InnerNodeAndFind) {
  const KeyComparator comparator;
  Key key = "2";
  InnerNode<Key> node(1, reinterpret_cast<Node *>(1), reinterpret_cast<Node *>(2), key);
  ASSERT_EQ(node.FindChild("1", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("3", comparator), reinterpret_cast<Node *>(2));

  ASSERT_TRUE(node.Insert("4", reinterpret_cast<Node *>(3), comparator));
  ASSERT_EQ(node.FindChild("1", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("2", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("3", comparator), reinterpret_cast<Node *>(2));
  ASSERT_EQ(node.FindChild("4", comparator), reinterpret_cast<Node *>(2));
  ASSERT_EQ(node.FindChild("5", comparator), reinterpret_cast<Node *>(3));

  ASSERT_TRUE(node.Insert("3", reinterpret_cast<Node *>(4), comparator));
  ASSERT_EQ(node.FindChild("1", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("2", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("3", comparator), reinterpret_cast<Node *>(2));
  ASSERT_EQ(node.FindChild("4", comparator), reinterpret_cast<Node *>(4));
  ASSERT_EQ(node.FindChild("5", comparator), reinterpret_cast<Node *>(3));

  ASSERT_TRUE(node.Insert("1", reinterpret_cast<Node *>(5), comparator));
  ASSERT_EQ(node.FindChild("0", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("1", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("2", comparator), reinterpret_cast<Node *>(5));
  ASSERT_EQ(node.FindChild("3", comparator), reinterpret_cast<Node *>(2));
  ASSERT_EQ(node.FindChild("4", comparator), reinterpret_cast<Node *>(4));
  ASSERT_EQ(node.FindChild("5", comparator), reinterpret_cast<Node *>(3));

  ASSERT_TRUE(node.Insert("5", reinterpret_cast<Node *>(6), comparator));
  ASSERT_EQ(node.FindChild("0", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("1", comparator), reinterpret_cast<Node *>(1));
  ASSERT_EQ(node.FindChild("2", comparator), reinterpret_cast<Node *>(5));
  ASSERT_EQ(node.FindChild("3", comparator), reinterpret_cast<Node *>(2));
  ASSERT_EQ(node.FindChild("4", comparator), reinterpret_cast<Node *>(4));
  ASSERT_EQ(node.FindChild("5", comparator), reinterpret_cast<Node *>(3));
  ASSERT_EQ(node.FindChild("6", comparator), reinterpret_cast<Node *>(6));
}

}  // namespace pidan