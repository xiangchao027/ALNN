//alnn.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Layer Structure
typedef struct T_LAYER {
    char    _type;
    int     _size;
    float   *_map;
} * layer;

#ifndef LAYER_TYPE
#define INPUT_LAYER             'i'
#define SELF_ORGANIZED_MAP      'm'
#define FULL_CONNECTED_LAYER    'f'
#define SPARSE_CONNECTED_LAYER  's'
#endif

// build layer
layer create_layer( char type, int size ) {
    layer _layer = (layer) malloc( sizeof(struct T_LAYER) );
    _layer->_type = type;
    _layer->_size = size;
    _layer->_map = (float*) malloc( sizeof(float) * size );
    memset( (char*)_layer, 0, sizeof(float) * size );
    return _layer;
}

// build self-organized-map layer
layer make_som_layer( int size ) {
    return create_layer( SELF_ORGANIZED_MAP, size );
}

// build fully-connected neural network
layer make_fully_connected_layer( int size ) {
    return create_layer( FULL_CONNECTED_LAYER, size );
}

// build sparse-connected neural network
layer make_sparse_connected_layer( int size ) {
    return create_layer( SPARSE_CONNECTED_LAYER, size );
}

// build input layer
layer make_input_layer( int size ) {
    return create_layer( INPUT_LAYER, size );
}
