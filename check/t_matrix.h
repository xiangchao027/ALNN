// t_matrix.h
// testmony of matrix data structure
#ifndef T_MATRIX_H
#define T_MATRIX_H  1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// custom headers
#include "../matrix.h"
#include "debugs.h"

int t_matrix() {
    matrix m;
    m.type = T_BINARY;
    m.num = 3;
    m.row = 32;
    m.col = 32;
    DEBUG_CALL( matrix_alloc( &m ) );
    DEBUG_ASSERT( m.elem != 0 );

    char elem;
    elem = 1;
    matrix_set_elem( &elem, &m, 0, 31, 25);
    elem = 0;
    matrix_get_elem( &elem, &m, 0, 31, 25);
    fprintf( stdout, "[0x%x] ", elem );

    DEBUG_CALL( matrix_free( &m ) );
    DEBUG_ASSERT( m.elem == 0 );

    return R_TRUE;
}



#endif
