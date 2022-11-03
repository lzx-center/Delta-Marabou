/*********************                                                        */
/*! \file TableauRow.cpp
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

#include "MarabouError.h"
#include "TableauRow.h"

TableauRow::TableauRow( unsigned size )
    : _size( size )
{
    _row = new TableauRow::Entry[size];
    if ( !_row )
        throw MarabouError( MarabouError::ALLOCATION_FAILED, "TableauRow::row" );
}

TableauRow::~TableauRow()
{
    delete[] _row;
}

double TableauRow::operator[]( unsigned index ) const
{
    return _row[index]._coefficient;
}

void TableauRow::dump() const
{
    bool flag = true;
    for ( unsigned i = 0; i < _size; ++i )
    {
        if ( FloatUtils::isZero( _row[i]._coefficient ) )
            continue;
        if (FloatUtils::gt(_row[i]._coefficient, 0) and !flag) {
            printf("+");
        }
        printf( "%.3lfx_{%u}", _row[i]._coefficient, _row[i]._var );
        flag = false;
    }
    if (!FloatUtils::isZero(_scalar)) {
        if (FloatUtils::gt(_scalar, 0)) {
            printf("+%3lf",_scalar);
        } else {
            printf("%3lf",_scalar);
        }
    }
//    printf( "\n\tscalar = %.2lf\n", _scalar );
//    printf( "\tlhs = x%u\n", _lhs );
}

//
// Local Variables:
// compile-command: "make -C ../.. "
// tags-file-name: "../../TAGS"
// c-basic-offset: 4
// End:
//
