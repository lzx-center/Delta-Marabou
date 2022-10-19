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
#include "Debug.h"
#include "TimeUtils.h"

#define TREE_LOG(f, x, ...) LOG(GlobalConfiguration::TREE_LOGGING, f, x)

struct SearchTreeNode {
public:
    enum NodeType {
        SAT = 0,
        UNSAT,
        PATH_NODE,
        LAZY_NODE //represent the subtree of this node is not stored
    };

    explicit SearchTreeNode(int id = 0) : _id(id), _nodeType(PATH_NODE), _conflictVariable(-1), _left(-1),
                                          _right(-1), _preNode(-1), _plLayer(-1), _plNode(-1), _plType(UNKNOWN),
                                          _start(TimeUtils::sampleMicro()), _end(TimeUtils::sampleMicro()),
                                          _back(TimeUtils::sampleMicro()), _preUnSAT(-1), _timeToBack(0.0), _timeToSplit(0.0)
                                          {}

    int _id;
    NodeType _nodeType;
    int _conflictVariable;
    // left represent:
    //     inactive in Relu
    //     lower part in Disjunction
    // right represent on the contrary
    int _left, _right;
    int _preNode, _plLayer, _plNode;
    std::vector<unsigned> _basicVariables;
    PiecewiseLinearFunctionType _plType;
    struct timespec _start, _end, _back;
    int _preUnSAT;
    double _timeToSplit, _timeToBack;

    PiecewiseLinearConstraint::Position getPosition();

    void setPosition(PiecewiseLinearConstraint::Position &position);

    void setType(PiecewiseLinearFunctionType type);

    PiecewiseLinearFunctionType getType();

    List<unsigned> getBasicVariableLists();

    bool isLeaf();

    String getStringPlType() const;

    String getStringNodeType() const;

    NodeType getNodeType();

    static String getTypeString(PiecewiseLinearFunctionType type);

    void print();
    Stringf getStringSummary();
    void printProcessTime();
    void calcTime();

private:
    friend class boost::serialization::access;

    friend class SearchTree;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // serialize base class information
        if (version >= 0) {
            ar & _plLayer & _plNode & _conflictVariable;
            ar & _left & _right & _preNode & _id & _nodeType & _basicVariables & _plType;
            ar & _timeToBack & _timeToSplit;
        }
    }
};

class SearchTree {
public:
    enum ResultTYpe {
        VERIFIED_SAT = 0,
        VERIFIED_UNSAT,
        NOT_VERIFIED
    };
    enum DirectionType {
        LEFT = 0,
        RIGHT,
        CANT_JUDGE
    };
    std::vector<unsigned> _satisfyPath;
private:
    int _root, _current;
    std::vector<SearchTreeNode> _nodes;
    std::map<PiecewiseLinearConstraint::Position, int> _mapPositionToNode;
    std::map<int, unsigned> _stackEntryToTreeNode;
    ResultTYpe _resultType;
    unsigned _nodeNumThreshold;


    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // serialize base class information
        if (version >= 0) {
            ar & _root & _current & _nodes & _resultType & _nodeNumThreshold & _satisfyPath;
        }
    }

public:
    int _numCannotJudgeUnSat = 0;
    int _totalUnSatInPreTree = 0;
    SearchTree();

    void setTreeNodeThreshold(unsigned num);

    void mapStackEntryToCurrentNode(int id) {
        _stackEntryToTreeNode[id] = _current;
    }

    int getNodeByStackEntry(int id) {
        if (_stackEntryToTreeNode.count(id))
            return _stackEntryToTreeNode[id];
        return -1;
    }

    SearchTreeNode &getNode(int index);

    size_t size();

    void adjustDirection(List<PiecewiseLinearCaseSplit> &list);

    void markUnsatLeaf(const Set<unsigned> &varSet, unsigned conflict);

    void setVerifiedResult(ResultTYpe resultTYpe);

    void markSatLeaf(const Set<unsigned> &varSet);

    SearchTreeNode &getCurrentNode();

    size_t newNode();

    void setCurrent(int index) {
        _current = index;
    }

    void saveToFile(const String &filePath);

    void loadFromFile(const String &filePath);

    int getCurrentIndex();

    void processCaseSplit(PiecewiseLinearCaseSplit *split);

    void gotoChildBySplit(PiecewiseLinearCaseSplit *split);

    void gotoChildByDirection(int current, DirectionType direction);

    /*
     * 0 : for left
     * 1 : for right
     */
    DirectionType getDirection(PiecewiseLinearCaseSplit::SplitType type);

    void setNodeInfo(PiecewiseLinearConstraint *pLConstraint);

    String getStringResultType();

    ResultTYpe getResultType() { return _resultType; }

    void print();
    void printPreUnSat();
    void printUnSAT();
    void printSummaryToFile(Stringf filePath="");
    void getSubTree(int current, std::vector<unsigned int> &numSubNode);
};

#endif //MARABOU_SEARCHTREE_H