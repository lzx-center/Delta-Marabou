/*********************                                                        */
/*! \file PiecewiseLinearCaseSplit.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Guy Katz, Duligur Ibeling
 ** This file is part of the Marabou project.
 ** Copyright (c) 2017-2019 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved. See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** [[ Add lengthier description here ]]

**/

#ifndef __PiecewiseLinearCaseSplit_h__
#define __PiecewiseLinearCaseSplit_h__

#include "Equation.h"
#include "IEngine.h"
#include "MString.h"
#include "Pair.h"
#include "Tightening.h"
#include "PiecewiseLinearCaseSplit.h"
class PiecewiseLinearCaseSplit
{
public:
    enum SplitType {
        RELU_INACTIVE = 0,
        RELU_ACTIVE,
        DISJUNCTION_LOWER,
        DISJUNCTION_UPPER,
        UNKNOWN
    };
    int _layer = -1;
    int _node = -1;
    SplitType _type = UNKNOWN;
    /*
      Store information regarding a bound tightening.
    */
    void storeBoundTightening( const Tightening &tightening );
    const List<Tightening> &getBoundTightenings() const;

    SplitType getType() {return _type;}

    void setType(PiecewiseLinearCaseSplit::SplitType type) { _type = type;}
    /*
      Store information regarding a new equation to be added.
    */
    void addEquation( const Equation &equation );
  	const List<Equation> &getEquations() const;

    /*
      Dump the case split - for debugging purposes.
    */
    void dump() const;
    void dump( String &output ) const;

    /*
      Equality operator.
    */
    bool operator==( const PiecewiseLinearCaseSplit &other ) const;

    /*
      Change the index of a variable that appears in this case split
    */
    void updateVariableIndex( unsigned oldIndex, unsigned newIndex );

    void setPosition(int layer, int node) {
        _layer = layer;
        _node = node;
    }

private:
    /*
      Bound tightening information.
    */
    List<Tightening> _bounds;

    /*
      The equation that needs to be added.
    */
    List<Equation> _equations;
};

#endif // __PiecewiseLinearCaseSplit_h__

//
// Local Variables:
// compile-command: "make -C ../.. "
// tags-file-name: "../../TAGS"
// c-basic-offset: 4
// End:
//
