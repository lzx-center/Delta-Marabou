//
// Created by center on 22-9-20.
//
#pragma once
#ifndef MARABOU_SEARCHTREE_H
#define MARABOU_SEARCHTREE_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include "vector"
#include "PiecewiseLinearConstraint.h"
#include "string"

struct SearchTreeNode {
public:
    SearchTreeNode(int id = 0, bool isLeaf = false) : _id(id), _isLeaf(isLeaf), _conflictVariable(-1), _activePhase(-1),
                                                      _inactivePhase(-1), _preNode(-1), _plLayer(-1), _plNode(-1) {}

    int _id;
    bool _isLeaf;
    int _conflictVariable, _activePhase, _inactivePhase, _preNode, _plLayer, _plNode;
    std::set<unsigned> _basicVariables;

    void print();
private:
    friend class boost::serialization::access;
    friend class SearchTree;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // serialize base class information
        if (version >= 0) {
            ar & _plLayer;
            ar & _plNode;
            ar & _conflictVariable;
            ar & _activePhase;
            ar & _inactivePhase;
            ar & _preNode;
            ar & _id;
            ar & _isLeaf;
            ar & _basicVariables;
        }
    }
};

class SearchTree {
private:
    int _root, _current_node;
    std::vector<SearchTreeNode> _nodes;


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // serialize base class information
        if (version >= 0) {
            ar & _root;
            ar & _current_node;
            ar & _nodes;
        }
    }

public:
    SearchTree();
    SearchTreeNode& getNode(int index);

    size_t new_node();

    void saveToFile(std::string filePath);

    void loadFromFile(std::string filePath);

    void print();
};

#endif //MARABOU_SEARCHTREE_H