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
    explicit SearchTreeNode(int id = 0, bool isLeaf = false) : _id(id), _isLeaf(isLeaf), _conflictVariable(-1), _left(-1),
                                                      _right(-1), _preNode(-1), _plLayer(-1), _plNode(-1),_type(UNKNOWN) {}

    int _id;
    bool _isLeaf;
    int _conflictVariable;
    // left represent:
    //     inactive in Relu
    //     lower part in Disjunction
    // right represent on the contrary
    int _left, _right;
    int _preNode, _plLayer, _plNode;
    std::vector<unsigned> _basicVariables;
    PiecewiseLinearFunctionType _type;

    void setPosition(PiecewiseLinearConstraint::Position &position);
    void setType(PiecewiseLinearFunctionType type);
    PiecewiseLinearFunctionType getType();
    void markAsLeaf();
    bool isLeaf();
    String getStringType() const;
    static String getTypeString(PiecewiseLinearFunctionType type);
    void print();
private:
    friend class boost::serialization::access;
    friend class SearchTree;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // serialize base class information
        if (version >= 0) {
            ar & _plLayer & _plNode & _conflictVariable;
            ar & _left & _right & _preNode  & _id  & _isLeaf & _basicVariables & _type;
        }
    }
};

class SearchTree {
private:
    int _root, _current;
    std::vector<SearchTreeNode> _nodes;
    std::map<std::pair<int, int>, int> _mapSplitToNode;


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // serialize base class information
        if (version >= 0) {
            ar & _root & _current & _nodes;
        }
    }

public:
    SearchTree();
    SearchTreeNode& getNode(int index);

    size_t size();

    void markLeaf(const Set<unsigned>& varSet, unsigned conflict);

    size_t newNode();

    void setCurrent(int index) {
        _current = index;
    }

    void saveToFile(std::string filePath);

    void loadFromFile(std::string filePath);

    int getCurrentIndex();

    void processCaseSplit(PiecewiseLinearCaseSplit* split);

    void setNodeInfo(PiecewiseLinearConstraint* pLConstraint);

    void print();
};

#endif //MARABOU_SEARCHTREE_H