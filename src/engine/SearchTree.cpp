//
// Created by center on 22-9-20.
//

#include "SearchTree.h"
#include "fstream"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

size_t SearchTree::newNode() {
    auto size = _nodes.size();
    _nodes.emplace_back(SearchTreeNode(size));
    return size;
}

SearchTree::SearchTree() : _root(-1), _current(-1) {
    auto index = newNode();
    _root = _current = index;
}

SearchTreeNode &SearchTree::getNode(int index) {
    return _nodes[index];
}

void SearchTree::saveToFile(std::string filePath) {
    std::ofstream ofs(filePath);
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
}

void SearchTree::loadFromFile(std::string filePath) {
    // create and open an archive for input
    std::ifstream ifs(filePath);
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> (*this);
    // archive and stream closed when destructors are called
}

void SearchTree::print() {
    for (auto n : _nodes) {
        n.print();
    }
}


void SearchTree::processCaseSplit(PiecewiseLinearCaseSplit *split) {
    int nodeIndex = newNode();
    auto &node  = _nodes[nodeIndex];
    node._preNode = _mapSplitToNode[{split->_layer, split->_node}];
    auto &preNode = _nodes[node._preNode];
    auto& tightenLists = split->getBoundTightenings();
    if (preNode.getType() == RELU) {
        bool inActive = true;
        for (auto tighten : tightenLists) {
            if (tighten._type != Tightening::UB) {
                inActive = false;
                break;
            }
        }
        if (inActive) {
            preNode._left = nodeIndex;
        } else {
            preNode._right = nodeIndex;
        }
    } else if (preNode.getType() == DISJUNCTION) {
        assert(tightenLists.size() == 1 && "tighten size is not equal to 1");
        if (tightenLists.begin()->_type == Tightening::UB) {
            preNode._left = nodeIndex;
        } else {
            preNode._right = nodeIndex;
        }
    } else {
        printf("current node:%d, type: %s\n", _current, preNode.getStringType().ascii());
        assert(false && "can not handle such constraint type");
    }
    setCurrent(nodeIndex);
}

void SearchTree::setNodeInfo(PiecewiseLinearConstraint *pLConstraint) {
    auto& node = _nodes[_current];
    node.setPosition(pLConstraint->_position);
    node.setType(pLConstraint->getType());
    _mapSplitToNode[{node._plLayer, node._plNode}] = _current;
}

int SearchTree::getCurrentIndex() {
    return _current;
}

void SearchTree::markLeaf(const Set<unsigned>& varSet, unsigned conflict) {
    auto &node = _nodes[_current];
    assert(node._type == UNKNOWN);
    node._isLeaf = true;
    for (auto var : varSet) {
        node._basicVariables.insert(var);
    }
    node._conflictVariable = conflict;
}


void SearchTreeNode::print() {
    printf(
            "Tree node id: %d, is leaf node: %s\nConstraint position is (%d, %d)\nleft node: %d, right node: %d, pre-node: %d\n",
            _id, _isLeaf ? "true" : "false", _plLayer, _plNode, _right, _left, _preNode
    );
    String s = getStringType();
    printf("Node type: %s\n", s.ascii());
    printf("Conflict variable: %d\n", _conflictVariable);
    if (!_basicVariables.empty()) {
        printf("Basic variables: ");
        for (auto v : _basicVariables) {
            printf("%d ",v);
        }
        printf("\n");
    }
    printf("\n");
}

void SearchTreeNode::setPosition(PiecewiseLinearConstraint::Position &position) {
    _plLayer = position._layer;
    _plNode = position._node;
}

void SearchTreeNode::markAsLeaf() {
    _isLeaf = true;
}

bool SearchTreeNode::isLeaf() {
    return _isLeaf;
}

void SearchTreeNode::setType(PiecewiseLinearFunctionType type) {
    _type = type;
}

PiecewiseLinearFunctionType SearchTreeNode::getType() {
    return _type;
}

String SearchTreeNode::getStringType() const {
    return getTypeString(_type);
}

String SearchTreeNode::getTypeString(PiecewiseLinearFunctionType type) {
    String s;
    switch (type) {
        case RELU:
            s = "Relu";
            break;
        case ABSOLUTE_VALUE:
            s = "Absolute value";
            break;
        case MAX:
            s = "Max";
            break;
        case DISJUNCTION:
            s = "Disjunction";
            break;
        case SIGN:
            s = "Sign";
            break;
        case UNKNOWN:
            s = "Unknown";
            break;
    }
    return s;
}
