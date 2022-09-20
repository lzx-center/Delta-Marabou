//
// Created by center on 22-9-20.
//

#include "SearchTree.h"

size_t SearchTree::new_node() {
    auto size = _nodes.size();
    _nodes.emplace_back(SearchTreeNode(size));
    return size;
}

SearchTree::SearchTree() {
    _root = new_node();
    _current_node = _root;
    printf("In search tree");
}