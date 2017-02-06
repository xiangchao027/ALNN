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

typedef union T_UNIT {
    char _char;
    unsigned char _byte;
    short int _short;
    rgb _rgb;
    long int _long;
    float _float;
    double _double;
} unit;

int t_matrix() {
    matrix m, nm;
    unit elem;
    m.type = T_BINARY;
    m.num = 3;
    m.row = 32;
    m.col = 32;
    // test matrix allocation
    DEBUG_CALL( matrix_alloc( &m ) );
    DEBUG_ASSERT( m.elem != 0 );
    // test matrix initialization
    DEBUG_CALL( matrix_set_zero( &m ) );
    DEBUG_CALL( matrix_get_elem( &elem._byte, &m, 1, 31, 25) );
    DEBUG_ASSERT( elem._byte == 0 );
    // test matrix element setter
    elem._byte = 1;
    DEBUG_CALL( matrix_set_elem( &elem._byte, &m, 1, 31, 25) );
    elem._byte = 0;
    DEBUG_CALL( matrix_get_elem( &elem._byte, &m, 1, 31, 25) );
    DEBUG_ASSERT( elem._byte == 1 );
    // test matrix deallocation
    DEBUG_CALL( matrix_free( &m ) );
    DEBUG_ASSERT( m.elem == 0 );

    // test with type [byte]
    m.type = T_BYTE;
    m.num = 3;
    m.row = 32;
    m.col = 32;
    DEBUG_CALL( matrix_alloc( &m ) );
    DEBUG_ASSERT( m.elem != 0 );
    DEBUG_CALL( matrix_set_zero( &m ) );
    DEBUG_CALL( matrix_get_elem( &elem._byte, &m, 1, 31, 25) );
    DEBUG_ASSERT( elem._byte == 0 );
    elem._byte = 83;
    DEBUG_CALL( matrix_set_elem( &elem._byte, &m, 1, 31, 25) );
    elem._byte = 0;
    DEBUG_CALL( matrix_get_elem( &elem._byte, &m, 1, 31, 25) );
    DEBUG_ASSERT( elem._byte == 83 );
    // test matrix deallocation
    DEBUG_CALL( matrix_free( &m ) );
    DEBUG_ASSERT( m.elem == 0 );

    // test with color type [rgb] : standard image input format
    m.type = T_RGB;
    m.num = 1;
    m.row = 32;
    m.col = 32;
    DEBUG_CALL( matrix_alloc( &m ) );
    DEBUG_ASSERT( m.elem != 0 );
    DEBUG_CALL( matrix_set_zero( &m ) );
    DEBUG_CALL( matrix_get_elem( &elem._rgb, &m, 0, 31, 25) );
    DEBUG_ASSERT( elem._rgb.r == 0 && elem._rgb.g==0 && elem._rgb.b==0 );
    elem._rgb.r = 12;
    elem._rgb.g = 28;
    elem._rgb.b = 217;
    DEBUG_CALL( matrix_set_elem( &elem._rgb, &m, 0, 31, 25) );
    elem._rgb.r = 0;
    elem._rgb.g = 0;
    elem._rgb.b = 0;
    DEBUG_CALL( matrix_get_elem( &elem._rgb, &m, 0, 31, 25) );
    DEBUG_ASSERT( elem._rgb.r == 12 && elem._rgb.g==28 && elem._rgb.b==217 );
    // test matrix copy
    DEBUG_CALL( matrix_copy( &nm, &m ) );
    elem._rgb.r = 0;
    elem._rgb.g = 0;
    elem._rgb.b = 0;
    DEBUG_CALL( matrix_get_elem( &elem._rgb, &nm, 0, 31, 25) );
    DEBUG_ASSERT( elem._rgb.r == 12 && elem._rgb.g==28 && elem._rgb.b==217 );
    // test matrix deallocation
    DEBUG_CALL( matrix_free( &m ) );
    DEBUG_CALL( matrix_free( &nm ) );
    DEBUG_ASSERT( m.elem == 0 );
    DEBUG_ASSERT( nm.elem == 0 );

    return true;
}



#endif
