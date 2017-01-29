#ifndef ALNN_H
#define ALNN_H  1

//alnn.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

// the limit of depth of neural network
enum { MAX_NEURAL_NETWORK_DEPTH = 100 };

// Layer Structure
typedef struct T_LAYER {
    char    _type;
    matrix  _map;
} layer;

// conections
typedef struct T_CONNECTION {
    matrix  _last;  // last state matrix
    matrix  _now;   // current state matrix
} connection;

// neural network
typedef struct T_NEURAL_NETWORK {
    layer*          _layers;
    connection *    _connections;
    int             _depth;
} neural_network;

#ifndef LAYER_TYPE
#define INPUT_LAYER             'i'
#define SELF_ORGANIZED_MAP      'm'
#define FULL_CONNECTED_LAYER    'f'
#define SPARSE_CONNECTED_LAYER  's'
#endif

// build layer
int create_layer( layer * _layer, char type, int row, int col ) {
    _layer->_type = type;
    _layer->_map.num = 1;
    _layer->_map.row = row;
    _layer->_map.col = col;
    return matrix_alloc( &(_layer->_map) );
}

// destroy a layer
void destroy_layer( layer * _layer ) {
    matrix_free( &(_layer->_map) );
}

// refers to a layer: copy a layer without matrix reallocation
int ref_layer( layer * new_layer, layer * ref_layer ) {
    if ( !ref_layer || !new_layer ) {
        return R_FALSE;
    }
    memcpy( new_layer, ref_layer, sizeof(layer) );
    return R_TRUE;
}

// copy a layer with matrix reallocation
int copy_layer( layer * new_layer, layer * template_layer ) {
    if ( !new_layer || !template_layer ) {
        return R_FALSE;
    }
    memcpy( new_layer, template_layer, sizeof(layer) );
    return matrix_alloc( &(new_layer->_map) );
}

// build self-organized-map layer
int make_som_layer( layer * som_layer, int row, int col ) {
    return create_layer( som_layer, SELF_ORGANIZED_MAP, row, col );
}

// build fully-connected neural network
int make_fully_connected_layer( layer * full_layer, int row, int col ) {
    return create_layer( full_layer, FULL_CONNECTED_LAYER, row, col );
}

// build sparse-connected neural network
int make_sparse_connected_layer( layer * sparse_layer, int row, int col ) {
    return create_layer( sparse_layer, SPARSE_CONNECTED_LAYER, row, col );
}

// build input layer
int make_input_layer( layer * input_layer, int row, int col ) {
    return create_layer( input_layer, INPUT_LAYER, row, col );
}


// linking layers from input layer to output layer
// input layer is not necessarily the input layer for entire network
// output layer is not necessarily the output layer for entire network
int link_layers(
    connection * new_connection,
    layer * input_layer,
    layer * output_layer
) {
    if ( !input_layer || !output_layer ) {
        return R_FALSE;
    }
    if (output_layer->_type == FULL_CONNECTED_LAYER ) {
        // last
        new_connection->_last.num = output_layer->_map.row * output_layer->_map.col;
        new_connection->_last.col = input_layer->_map.col;
        new_connection->_last.row = input_layer->_map.row;
        // now is the same
        new_connection->_now.num = output_layer->_map.row * output_layer->_map.col;
        new_connection->_now.col = input_layer->_map.col;
        new_connection->_now.row = input_layer->_map.row;
        // reset matrix
        matrix_alloc( &new_connection->_last );
        matrix_alloc( &new_connection->_now );
        matrix_set_zero( &new_connection->_last );
        matrix_set_zero( &new_connection->_now );
        // done
    } else if ( output_layer->_type == SELF_ORGANIZED_MAP ) {
    } else if ( output_layer->_type == SPARSE_CONNECTED_LAYER ) {
    } else {
        return R_FALSE;
    }
    return R_TRUE;
}


// create a neural network with given layer number( depth )
int create_neural_network( neural_network * network ) {
    if ( !network ) {
        return R_FALSE;
    }
    network->_layers = (layer *) malloc(
        sizeof(layer) * MAX_NEURAL_NETWORK_DEPTH
    );
    network->_connections = (connection *) malloc(
        sizeof(connection) * (MAX_NEURAL_NETWORK_DEPTH - 1)
    );
    network->_depth = 0;
    return R_TRUE;
}

// add new layer to network
// notice: do not call destroy_layer() outside this function, this will crash
// application, because this function refers layers without reallocation.
int neural_network_append_layer( neural_network * network, layer * new_layer ) {
    if ( (!network) || (!new_layer) ) {
        return R_FALSE;
    }
    if ( network->_depth >= MAX_NEURAL_NETWORK_DEPTH ) {
        return R_FALSE;
    }
    if ( !ref_layer( network->_layers + network->_depth, new_layer ) ) {
        return R_FALSE;
    }
    network->_depth ++;

    // add connections to neural neural network
    if ( network->_depth == 1 ) { // if only input layer, then exit;
        return R_TRUE;
    }
    if( !link_layers(
        network->_connections + (network->_depth - 2),
        network->_layers + (network->_depth - 2),
        network->_layers + (network->_depth - 1)
    ) ) {
        return R_FALSE;
    }


    return R_TRUE;
}

// compute forward
void compute_forward( neural_network * network );

// compute backward
void compute_backward( neural_network * network );

// add new instance to neural network input layer
void neural_network_train( neural_network * network, matrix * input );

// test model
void neural_network_test( neural_network * network, matrix * input );


#endif
