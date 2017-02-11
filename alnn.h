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

enum LAYER_TYPE {
    LT_INPUT    =   'i',
    LT_SOM      =   'm',
    LT_FULL     =   'f',
    LT_SPARSE   =   's'
};

#define CHECK_LAYER_TYPE( _t ) (\
    _t == LT_INPUT  ||\
    _t == LT_SOM    ||\
    _t == LT_FULL   ||\
    _t == LT_SPARSE\
)

// ********************* tool functions *********************** //
// build layer
int create_layer(
    layer * _l,
    enum LAYER_TYPE _lt,
    enum ELEMENT_TYPE _et,
    int row,
    int col
) {
    // check type validality
    if ( !CHECK_LAYER_TYPE( _lt ) ) {
        return false;
    }
    if ( !CHECK_ELEM_TYPE( _et ) ) {
        return false;
    }
    _l->_type = _lt;
    _l->_map.type = _et;
    _l->_map.num = 1;
    _l->_map.row = row;
    _l->_map.col = col;

    return matrix_alloc( &(_l->_map) );
}

// destroy a layer
int destroy_layer( layer * _layer ) {
    return matrix_free( &(_layer->_map) );
}

// refers to a layer: copy a layer without matrix reallocation
int ref_layer( layer * new_layer, layer * ref_layer ) {
    if ( !ref_layer || !new_layer ) {
        return false;
    }
    memcpy( new_layer, ref_layer, sizeof(layer) );
    return true;
}

// copy a layer with matrix reallocation
int copy_layer( layer * _nl, layer * _l ) {
    if ( !_nl || !_l ) {
        return false;
    }
    memcpy( _nl, _l, sizeof(layer) );
    return matrix_alloc( &(_nl->_map) );
}

// linking layers from input layer to output layer
// input layer is not necessarily the input layer for entire network
// output layer is not necessarily the output layer for entire network
int link_layers(
    connection * _c,
    layer * _i,
    layer * _o
) {
    if ( !_c || !_i || !_o ) {
        _debug_();
        return false;
    }
    if (_o->_type == LT_FULL ) {
        // last
        _c->_last.num = _o->_map.row * _o->_map.col;
        _c->_last.col = _i->_map.col;
        _c->_last.row = _i->_map.row;
        _c->_last.type = T_FLOAT;
        // reset matrix
        if ( !matrix_alloc( &_c->_last ) ) {
            _debug_();
            return false;
        }
        if ( !matrix_set_zero( &_c->_last ) ) {
            _debug_();
            return false;
        }
        // copy to current state map
        if ( !matrix_copy( &_c->_now, &_c->_last ) ) {
            _debug_();
            return false;
        }
    } else if ( _o->_type == LT_SOM ) {
        // last
        _c->_last.num = _o->_map.row * _o->_map.col;
        _c->_last.col = _i->_map.col;
        _c->_last.row = _i->_map.row;
        _c->_last.type = _i->_map.type;
        // reset matrix
        if ( !matrix_alloc( &_c->_last ) ) {
            _debug_();
            return false;
        }
        if ( !matrix_set_zero( &_c->_last ) ) {
            _debug_();
            return false;
        }
        // copy to current state map
        if ( !matrix_copy( &_c->_now, &_c->_last ) ) {
            _debug_();
            return false;
        }
    } else if ( _o->_type == LT_SPARSE ) {
        // last
        _c->_last.num = _o->_map.row * _o->_map.col;
        _c->_last.col = _i->_map.col;
        _c->_last.row = _i->_map.row;
        _c->_last.type = T_FLOAT;
        // reset matrix
        if ( !matrix_alloc( &_c->_last ) ) {
            _debug_();
            return false;
        }
        if ( !matrix_set_zero( &_c->_last ) ) {
            _debug_();
            return false;
        }
        // copy to current state map
        if ( !matrix_copy( &_c->_now, &_c->_last ) ) {
            _debug_();
            return false;
        }
    } else {
        return false;
    }
    return true;
}

// destroy connection
int destroy_connection( connection * conn ) {
    if ( conn ) {
        if ( !matrix_free( &conn->_last ) || !matrix_free( &conn->_now ) ) {
            return false;
        }
    }
    return true;
}


// create a neural network with given layer number( depth )
int create_neural_network( neural_network * network ) {
    if ( !network ) {
        return false;
    }
    network->_layers = (layer *) malloc(
        sizeof(layer) * MAX_NEURAL_NETWORK_DEPTH
    );
    network->_connections = (connection *) malloc(
        sizeof(connection) * (MAX_NEURAL_NETWORK_DEPTH - 1)
    );
    network->_depth = 0;
    return true;
}

// add new layer to network
// notice: do not call destroy_layer() outside this function, this will crash
// application, because this function refers layers without reallocation.
int neural_network_append_layer( neural_network * network, layer * new_layer ) {
    if ( (!network) || (!new_layer) ) {
        return false;
    }
    if ( network->_depth >= MAX_NEURAL_NETWORK_DEPTH ) {
        return false;
    }
    if ( !ref_layer( network->_layers + network->_depth, new_layer ) ) {
        return false;
    }
    network->_depth ++;

    // add connections to neural neural network
    if ( network->_depth == 1 ) { // if only input layer, then exit;
        return true;
    }
    if( !link_layers(
        network->_connections + (network->_depth - 2),
        network->_layers + (network->_depth - 2),
        network->_layers + (network->_depth - 1)
    ) ) {
        return false;
    }


    return true;
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
