//
// Created by center on 22-9-20.
//

#include "SearchTree.h"
#include "fstream"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

size_t SearchTree::new_node() {
    auto size = _nodes.size();
    _nodes.emplace_back(SearchTreeNode(size));
    return size;
}

SearchTree::SearchTree() : _root(-1), _current_node(-1) {}

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


void SearchTreeNode::print() {
    printf(
            "Tree node id: %d, is leaf node: %s\nConstraint is (%d, %d)\nInactive constraint node at:%d, active constraint node at:%d\n",
            _id, _isLeaf ? "true" : "false", _plLayer, _plNode, _inactivePhase, _activePhase
    );
    if (_basicVariables.size()) {
        printf("Basic variables: ");
        for (auto v : _basicVariables) {
            printf("%d ",v);
        }
        printf("\n");
    }
}
