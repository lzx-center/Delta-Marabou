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

void SearchTree::saveToFile(const String &filePath) {
    for (auto &node: _nodes) {
        node.calcTime();
//        node.printProcessTime();
    }
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
    if (_resultType == VERIFIED_SAT) {
        printf("Satisfy path: ");
        for (size_t i = 0; i < _satisfyPath.size(); ++i) {
            printf(i == _satisfyPath.size() - 1 ? "%d\n" : "%d <- ", _satisfyPath[i]);
        }
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
    node._preNode = _current;
    auto &preNode = _nodes[node._preNode];
    auto direction = getDirection(split->getType());
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
    node._end = TimeUtils::sampleMicro();
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
    node._end = TimeUtils::sampleMicro();
    node._back = node._end;
    assert(node._plType == UNKNOWN);
    _resultType = VERIFIED_UNSAT;
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
    node._end = TimeUtils::sampleMicro();
    node._back = node._end;
    node._nodeType = SearchTreeNode::SAT;
    for (auto var: varSet) {
        node._basicVariables.push_back(var);
    }
    _resultType = VERIFIED_SAT;
    std::vector<unsigned> stack;
    int current = node._id;
    while (current != -1) {
        stack.push_back(current);
        _satisfyPath.push_back(current);
        current = _nodes[current]._preNode;
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
SearchTree::getDirection(PiecewiseLinearCaseSplit::SplitType type) {
    if (type == PiecewiseLinearCaseSplit::RELU_INACTIVE || type == PiecewiseLinearCaseSplit::DISJUNCTION_LOWER) {
        return LEFT;
    } else if (type == PiecewiseLinearCaseSplit::RELU_ACTIVE || type == PiecewiseLinearCaseSplit::DISJUNCTION_UPPER) {
        return RIGHT;
    }
    return CANT_JUDGE;
}


void SearchTree::gotoChildBySplit(PiecewiseLinearCaseSplit *split) {
    if (_nodes[_current].isLeaf()) {
        return;
    }
    auto direction = getDirection(split->getType());
    gotoChildByDirection(_current, direction);
    TREE_LOG("Current node is [%d]\n", _current);
//    _nodes[_current].print();
}

void SearchTree::setTreeNodeThreshold(unsigned num) {
    _nodeNumThreshold = num;
}

void SearchTree::gotoChildByDirection(int current, SearchTree::DirectionType direction) {
    if (direction == RIGHT) {
        TREE_LOG("Current id [%d], now go to right node [%d]\n", _current, _nodes[current]._right);
        _current = _nodes[current]._right;
    } else if (direction == LEFT) {
        TREE_LOG("Current id [%d], now go to left node [%d]\n", _current, _nodes[current]._left);
        _current = _nodes[current]._left;
    } else {
        assert(false && "Unknown direction");
    }
    // Means that there's no son node in first verification
    if (_current == -1) {
        _current = current;
        _nodes[current]._nodeType = SearchTreeNode::LAZY_NODE;
    }
}

void SearchTree::adjustDirection(List<PiecewiseLinearCaseSplit> &list) {
    if (_satisfyPath.empty()) {
        return;
    }
    auto direction = getDirection(list.front().getType());
    if (_nodes[_current]._left == (int) _satisfyPath.back()) {
        TREE_LOG("Go to left node [%d] first\n", _satisfyPath.back());
        if (direction == RIGHT) {
            std::reverse(list.begin(), list.end());
        }
    } else if (_nodes[_current]._right == (int) _satisfyPath.back()) {
        TREE_LOG("Go to right node [%d] first\n", _satisfyPath.back());
        if (direction == LEFT) {
            std::reverse(list.begin(), list.end());
        }
    }
}

void SearchTree::printPreUnSat() {
    for (auto &node: _nodes) {
        if (node._preUnSAT != -1) {
            node.print();
        }
    }
}

void SearchTree::printUnSAT() {
    for (auto &node: _nodes) {
        if (node._nodeType == SearchTreeNode::UNSAT) {
            node.print();
        }
    }
}

void SearchTree::printSummaryToFile(Stringf filePath) {
    std::ofstream outfile;
    outfile.open(filePath.ascii());
    std::vector<unsigned> numSubNodes(_nodes.size(), 0);
    getSubTree(0, numSubNodes);
    outfile << "Tree info:\n";
    outfile << Stringf("\tSearch tree size: %d\n",
                       _nodes.size()).ascii();
    if (_resultType == VERIFIED_UNSAT) {
        outfile << Stringf("Total unsat: %d, can not judge: %d, success rate: %f\n", _totalUnSatInPreTree,
                           _numCannotJudgeUnSat, 1.0 - 1.0 * _numCannotJudgeUnSat / _totalUnSatInPreTree).ascii();
    }
    for (auto &node: _nodes) {
        outfile << node.getStringSummary().ascii();
        outfile << "SubTree size: " << numSubNodes[node._id] << "\n";
        outfile << "\n";
    }

    outfile << "\nCompare tree info:\n";
    for (auto &node : _nodes) {
        if (node._preUnSAT != -1) {
            outfile << Stringf("Current node is : %d, pre search tree node: %d\n", node._id, node._preUnSAT).ascii();
            outfile << "SubTree size: " << numSubNodes[node._id] << "\n";
        }
    }
    outfile.close();
}

void SearchTree::getSubTree(int current, std::vector<unsigned int> &numSubNode) {
    numSubNode[current] = 1;
    auto left = _nodes[current]._left, right = _nodes[current]._right;
    if (left != -1) {
        getSubTree(left, numSubNode);
        numSubNode[current] += numSubNode[left];
    }
    if (right != -1) {
        getSubTree(right, numSubNode);
        numSubNode[current] += numSubNode[right];
    }
}


void SearchTreeNode::print() {
    printf(
            "Tree node id: %d, node type: %s\n",
            _id, getStringNodeType().ascii()
    );
    if (_nodeType == PATH_NODE) {
        if (_preNode == -1)
            printf("Constraint position is (%d, %d), PLConstraint type: %s\nleft node: %d, right node: %d\n",
                   _plLayer, _plNode, getStringPlType().ascii(), _left, _right
            );
        else
            printf("Constraint position is (%d, %d), PLConstraint type: %s\nleft node: %d, right node: %d, pre-node: %d\n",
                   _plLayer, _plNode, getStringPlType().ascii(), _left, _right, _preNode
            );
    } else {
        printf("Previous node: %d\n", _preNode);
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
    if (_preUnSAT != -1) {
        printf("Pre unsat node: %d\n", _preUnSAT);
    }
    printProcessTime();
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
    for (auto &v: _basicVariables) {
        ret.append(v);
    }
    return ret;
}

void SearchTreeNode::printProcessTime() {
    printf("Time to perform next split %f, Time to back to current node: %f\n",
           _timeToSplit, _timeToBack);
    printf("\n");
}

void SearchTreeNode::calcTime() {
    _timeToSplit = 1.0 * TimeUtils::timePassed(_start, _end) / 1000000;
    _timeToBack = 1.0 * TimeUtils::timePassed(_start, _back) / 1000000;
}

Stringf SearchTreeNode::getStringSummary() {
    Stringf ret("");
    ret += Stringf(
            "Tree node id: %d, node type: %s\n",
            _id, getStringNodeType().ascii()
    );
    if (_nodeType == PATH_NODE) {
        if (_preNode == -1)
            ret += Stringf("Constraint position is (%d, %d), PLConstraint type: %s\nleft node: %d, right node: %d\n",
                           _plLayer, _plNode, getStringPlType().ascii(), _left, _right
            );
        else
            ret += Stringf(
                    "Constraint position is (%d, %d), PLConstraint type: %s\nleft node: %d, right node: %d, pre-node: %d\n",
                    _plLayer, _plNode, getStringPlType().ascii(), _left, _right, _preNode
            );
    } else {
        ret += Stringf("Previous node: %d\n", _preNode);
    }
    if (_nodeType == UNSAT) {
        ret += Stringf("Conflict variable: %d\n", _conflictVariable);
    }
    if (_preUnSAT != -1) {
        ret += Stringf("Pre unsat node: %d\n", _preUnSAT);
    }
    ret += Stringf("Time to perform next split %f, Time to back to current node: %f\n",
                   _timeToSplit, _timeToBack);
    return ret;
}
