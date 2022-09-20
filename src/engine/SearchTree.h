//
// Created by center on 22-9-20.
//
#pragma once
#ifndef MARABOU_SEARCHTREE_H
#define MARABOU_SEARCHTREE_H
#include "vector"
#include "PiecewiseLinearConstraint.h"
struct SearchTreeNode {
public:
    SearchTreeNode(size_t id = 0) : _id(id) {}
    unsigned _plLayer, _plNode;
    int _conflictVariable;
    size_t _activePhase, _inactivePhase, _preNode, _id;
};

class SearchTree {
private:
    size_t _root, _current_node;
    std::vector<SearchTreeNode> _nodes;
public:
    SearchTree();
    size_t new_node();
};


#endif //MARABOU_SEARCHTREE_H