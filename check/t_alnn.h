// t_alnn.h
// test alnn data Structure and its supporting functions

#ifndef T_ALNN_H
#define T_ALNN_H    1

#include "../alnn.h"

int t_alnn() {
    layer _l, _nl;
    connection _c;
    // test create layer
    DEBUG_CALL( create_layer( &_l, LT_INPUT, T_BYTE, 32, 32 ) );
    // test refer layer
    DEBUG_CALL( ref_layer( &_nl , &_l ) );
    // test copy layer
    DEBUG_CALL( copy_layer( &_nl, &_l ) );
    // test link layer
    DEBUG_CALL( destroy_layer( &_nl ) );
    DEBUG_CALL( create_layer( &_nl, LT_FULL, T_FLOAT, 16, 16 ) );
    DEBUG_CALL( link_layers( &_c, &_l, &_nl ) );
    DEBUG_ASSERT(
        _c._last.num == 16*16 &&
        _c._last.row == 32 &&
        _c._last.col == 32 &&
        _c._now.num == 16*16 &&
        _c._now.row == 32 &&
        _c._now.col == 32 &&
        _c._last.elem != 0 &&
        _c._now.elem != 0 &&
        ((float*)_c._now.elem)[16*15+3] == 0
    );

    // test som layer
    DEBUG_CALL( destroy_connection( &_c ) );
    DEBUG_CALL( destroy_layer( &_nl ) );
    DEBUG_CALL( create_layer( &_nl, LT_SOM, T_FLOAT, 16, 16) );
    DEBUG_CALL( link_layers( &_c, &_l, &_nl ) );
    DEBUG_ASSERT(
        _c._last.num == 16*16 &&
        _c._last.row == 32 &&
        _c._last.col == 32 &&
        _c._now.num == 16*16 &&
        _c._now.row == 32 &&
        _c._now.col == 32 &&
        _c._last.elem != 0 &&
        _c._now.elem != 0 &&
        ((unsigned char*)_c._now.elem)[16*15+3] == 0
    );

    // must remember to RELEASE the connections
    DEBUG_CALL( destroy_connection( &_c ) );
    // test destroy layer
    DEBUG_CALL( destroy_layer( &_nl ) );
    DEBUG_CALL( destroy_layer( &_l ) );

    return true;
}


#endif
