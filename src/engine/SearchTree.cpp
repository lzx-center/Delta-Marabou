//
// Created by center on 22-9-20.
//

#include "SearchTree.h"
#include "fstream"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

size_t SearchTree::newNode() {
    auto size = _nodes.size();
    if (size == _nodeNumThreshold) {
        return -1;
    }
    _nodes.emplace_back(SearchTreeNode(size));
    if (size == _nodeNumThreshold - 1) {
        _nodes.back()._nodeType = SearchTreeNode::LAZY_NODE;
    }
    return size;
}

SearchTree::SearchTree() : _root(-1), _current(-1), _resultType(NOT_VERIFIED), _nodeNumThreshold(1000000000) {
    auto index = newNode();
    _root = _current = index;
}

SearchTreeNode &SearchTree::getNode(int index) {
    return _nodes[index];
}

void SearchTree::saveToFile(const String &filePath) const {
    std::ofstream ofs(filePath.ascii());
    {
        boost::archive::text_oarchive oa(ofs);
        oa << *this;
    }
}

void SearchTree::loadFromFile(const String &filePath) {
    // create and open an archive for input
    std::ifstream ifs(filePath.ascii());
    {
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> (*this);
        // archive and stream closed when destructors are called
    }
}

void SearchTree::print() {
    for (auto n: _nodes) {
        n.print();
    }
    printf("Verified result: %s\n", getStringResultType().ascii());
}


void SearchTree::processCaseSplit(PiecewiseLinearCaseSplit *split) {
    int nodeIndex = newNode();
    if (nodeIndex == -1) {
        _current = -1;
        return;
    }
    auto &node = _nodes[nodeIndex];
    node._preNode = _mapPositionToNode[PiecewiseLinearConstraint::Position(split->_layer, split->_node)];
    auto &preNode = _nodes[node._preNode];
    auto direction = getDirection(preNode.getType(), split->getBoundTightenings());
    if (direction == LEFT) {
        preNode._left = nodeIndex;
    } else if (direction == RIGHT) {
        preNode._right = nodeIndex;
    } else {
        printf("current node:%d, type: %s\n", _current, preNode.getStringPlType().ascii());
        assert(false && "can not handle such constraint type");
    }
    setCurrent(nodeIndex);
}

void SearchTree::setNodeInfo(PiecewiseLinearConstraint *pLConstraint) {
    if (_current == -1) return;
    auto &node = _nodes[_current];
    node.setPosition(pLConstraint->_position);
    node.setType(pLConstraint->getType());
    _mapPositionToNode[pLConstraint->getPosition()] = _current;
}

int SearchTree::getCurrentIndex() {
    return _current;
}

void SearchTree::markUnsatLeaf(const Set<unsigned> &varSet, unsigned conflict) {
    if (_current == -1) {
        return;
    }
    auto &node = _nodes[_current];
    assert(node._plType == UNKNOWN);
    _resultType = VERIFIED_SAT;
    node._nodeType = SearchTreeNode::UNSAT;
    node._basicVariables.reserve(varSet.size());
    for (auto var: varSet) {
        node._basicVariables.push_back(var);
    }
    node._conflictVariable = conflict;
}

size_t SearchTree::size() {
    return _nodes.size();
}

void SearchTree::markSatLeaf(const Set<unsigned int> &varSet) {
    auto &node = _nodes[_current];
    node._nodeType = SearchTreeNode::SAT;
    for (auto var: varSet) {
        node._basicVariables.push_back(var);
    }
    std::vector<unsigned> stack;
    int current = node._id;
    while (current != -1) {
        stack.push_back(current);
        current = _nodes[current]._preNode;
    }
    node._satisfyPath.reserve(stack.size());
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        node._satisfyPath.push_back(*it);
    }
}

void SearchTree::setVerifiedResult(SearchTree::ResultTYpe resultTYpe) {
    _resultType = resultTYpe;
}

String SearchTree::getStringResultType() {
    String s;
    switch (_resultType) {

        case VERIFIED_SAT:
            s = "sat";
            break;
        case VERIFIED_UNSAT:
            s = "unsat";
            break;
        case NOT_VERIFIED:
            s = "not verified";
            break;
    }
    return s;
}

SearchTreeNode &SearchTree::getCurrentNode() {
    return _nodes[_current];
}

SearchTree::DirectionType
SearchTree::getDirection(PiecewiseLinearFunctionType type, const List<Tightening> &tightenLists) {
    if (type == RELU) {
        bool inActive = true;
        for (auto tighten: tightenLists) {
            if (tighten._type != Tightening::UB) {
                inActive = false;
                break;
            }
        }
        if (inActive) {
            return LEFT; // left
        }
        return RIGHT; //right
    } else if (type == DISJUNCTION) {
        assert(tightenLists.size() == 1 && "tighten size is not equal to 1");
        if (tightenLists.begin()->_type == Tightening::UB) {
            return LEFT; // left
        }
        return RIGHT; // right
    }
    return CANT_JUDGE;
}

void SearchTree::gotoChildBySplit(PiecewiseLinearFunctionType type, PiecewiseLinearCaseSplit *split) {
    if (_nodes[_current].isLeaf()) return;
    auto direction = getDirection(type, split->getBoundTightenings());
    if (direction == RIGHT) {
        _current = _nodes[_current]._right;
    } else if (direction == LEFT) {
        _current = _nodes[_current]._left;
    } else {
        assert(false && "Unknown direction");
    }
    printf("Now go to node: %d\n", _current);
}

void SearchTree::setTreeNodeThreshold(unsigned num) {
    _nodeNumThreshold = num;
}


void SearchTreeNode::print() {
    printf(
            "Tree node id: %d, node type: %s\n",
            _id, getStringNodeType().ascii()
    );
    if (_nodeType == PATH_NODE) {
        printf("Constraint position is (%d, %d), PLConstraint type: %s\nleft node: %d, right node: %d, pre-node: %d\n",
               _plLayer, _plNode, getStringPlType().ascii(), _left, _right, _preNode
        );
    }
    if (_nodeType == UNSAT) {
        printf("Conflict variable: %d\n", _conflictVariable);
    }
    if (!_basicVariables.empty()) {
        printf("Basic variables: ");
        for (auto v: _basicVariables) {
            printf("%d ", v);
        }
        printf("\n");
    }
    if (_nodeType == SAT) {
        printf("Satisfy path: ");
        for (size_t i = 0; i < _satisfyPath.size(); ++i) {
            printf(i == _satisfyPath.size() - 1 ? "%d\n" : "%d -> ", _satisfyPath[i]);
        }
    }
    printf("\n");
}

PiecewiseLinearConstraint::Position SearchTreeNode::getPosition() {
    return PiecewiseLinearConstraint::Position(_plLayer, _plNode);
}

void SearchTreeNode::setPosition(PiecewiseLinearConstraint::Position &position) {
    _plLayer = position._layer;
    _plNode = position._node;
}


bool SearchTreeNode::isLeaf() {
    return _nodeType == SAT or _nodeType == UNSAT or _nodeType == LAZY_NODE;
}

void SearchTreeNode::setType(PiecewiseLinearFunctionType type) {
    _plType = type;
}

PiecewiseLinearFunctionType SearchTreeNode::getType() {
    return _plType;
}

String SearchTreeNode::getStringPlType() const {
    return getTypeString(_plType);
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

String SearchTreeNode::getStringNodeType() const {
    String s;
    switch (_nodeType) {
        case SAT:
            s = "sat";
            break;
        case UNSAT:
            s = "unsat";
            break;
        case PATH_NODE:
            s = "path_node";
            break;
        case LAZY_NODE:
            s = "lazy_node";
            break;
    }
    return s;
}

SearchTreeNode::NodeType SearchTreeNode::getNodeType() {
    return _nodeType;
}

List<unsigned> SearchTreeNode::getBasicVariableLists() {
    List<unsigned> ret;
    for (auto &v : _basicVariables) {
        ret.append(v);
    }
    return ret;
}
