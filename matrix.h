#ifndef MATRIX_H
#define MATRIX_H    1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// show debug information
#ifdef __DEBUG__
#define _debug_() {\
    fprintf( stdout, "%s:\t%d\n", __FILE__, __LINE__ );\
}
#else
#define _debug_() {}
#endif


// basic data structures
// matrix.type :
//      b : unsigned char = binary, constrainted by 0/1 check
//      c : char = character, from 0 to 127
//      u : unsigned char = byte
//      s : short int = short integer
//      l : long int = long integer
//      f : float = float number
//      d : double = double
enum ELEMENT_TYPE {
    T_BINARY,
    T_CHAR,
    T_BYTE,
    T_SHORT,
    T_LONG,
    T_FLOAT,
    T_DOUBLE,
    T_RGB
};

#define CHECK_ELEM_TYPE( _t ) (\
    _t == T_BINARY  ||\
    _t == T_CHAR    ||\
    _t == T_BYTE    ||\
    _t == T_SHORT   ||\
    _t == T_LONG    ||\
    _t == T_FLOAT   ||\
    _t == T_DOUBLE  ||\
    _t == T_RGB\
)

enum { false = 0 , true = 1 };

typedef struct T_RGB{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb;

typedef struct T_MATRIX {
    int     num;        // number of instances
    int     col;        // column count
    int     row;        // row count
    char    type;       // element type
    void*   elem;       // element values
} matrix;

// declaration of tool functions
int matrix_alloc( matrix * m );     // allocation of matrix elements
int matrix_free( matrix * m );      // deallocation of matrix elements
int matrix_get_elem(                // get matrix element by coordinate
    void * elem,
    matrix * m,
    int num,
    int row,
    int col
);
int matrix_set_elem(
    void * elem,
    matrix * m,
    int num,
    int row,
    int col
);
int matrix_set_zero( matrix * m );  // set all elements to zero
int matrix_direct_copy( matrix * nm, matrix * m ); // directly copy elements
int matrix_copy( matrix * nm, matrix * m ); // deep copy

// definitions of declared functions
int matrix_alloc( matrix * m ) {
    size_t n;
    if ( !m ) {
        _debug_();
        return false;
    }
    if ( m->num <= 0 || m->row <= 0 || m->col <= 0 ) {
        _debug_();
        return false;
    }
    if ( m->type == T_BINARY ) {
        n = ( m->num * m->row * m->col + 8 ) / 8;
        m->elem = (unsigned char *)malloc( n );
    } else if ( m->type == T_CHAR ) {
        n = m->num * m->row * m->col * sizeof(char);
        m->elem = (char*)malloc( n );
    } else if ( m->type == T_BYTE ) {
        n = m->num * m->row * m->col * sizeof(unsigned char);
        m->elem = (unsigned char *)malloc( n );
    } else if ( m->type == T_SHORT ) {
        n = m->num * m->row * m->col * sizeof(short int);
        m->elem = (short int *)malloc( n );
    } else if ( m->type == T_LONG ) {
        n = m->num * m->row * m->col * sizeof(long int);
        m->elem = (long int *)malloc( n );
    } else if ( m->type == T_FLOAT ) {
        n = m->num * m->row * m->col * sizeof(float);
        m->elem = (float *)malloc( n );
    } else if ( m->type == T_DOUBLE ) {
        n = m->num * m->row * m->col * sizeof(double);
        m->elem = (double *)malloc( n );
    } else if ( m->type == T_RGB ) {
        n = m->num * m->row * m->col * sizeof(rgb);
        m->elem = (rgb *)malloc( n );
    } else {
        _debug_();
        return false;
    }
    return true;
}

// deallocation of matrix
int matrix_free( matrix * m ) {
    if ( !m ) {
        return false;
    }
    free( m->elem );
    m->num = 0;
    m->col = 0;
    m->row = 0;
    m->elem = 0;
    return true;
}

int matrix_get_elem(
    void * elem,
    matrix * m,
    int num,
    int row,
    int col
) {
    size_t i;
    unsigned char binary_elem;

    if ( !m || !elem) {
        return false;
    }
    if ( num < 0 || num >= m->num ) {
        return false;
    }
    if ( row < 0 || row >= m->row ) {
        return false;
    }
    if ( col < 0 || col >= m->col ) {
        return false;
    }
    if ( m->type == T_BINARY ) {
        i = num * m->row * m->col + row * m->col + col;
        binary_elem = ((unsigned char *)m->elem)[i/8];
        i = i % 8;
        *((unsigned char *)elem) = !!(binary_elem & (0x01<<i));
    } else if ( m->type == T_CHAR ) {
        i = num * m->row * m->col + row * m->col + col;
        *((char *)elem) = ((char *)(m->elem))[i];
    } else if ( m->type == T_BYTE ) {
        i = num * m->row * m->col + row * m->col + col;
        *((unsigned char *)elem) = ((unsigned char *)(m->elem))[i];
    } else if ( m->type == T_SHORT ) {
        i = num * m->row * m->col + row * m->col + col;
        *((short int *)elem) = ((short int *)(m->elem))[i];
    } else if ( m->type == T_LONG ) {
        i = num * m->row * m->col + row * m->col + col;
        *((long int *)elem) = ((long int *)(m->elem))[i];
    } else if ( m->type == T_FLOAT ) {
        i = num * m->row * m->col + row * m->col + col;
        *((float *)elem) = ((float *)(m->elem))[i];
    } else if ( m->type == T_DOUBLE ) {
        i = num * m->row * m->col + row * m->col + col;
        *((double *)elem) = ((double *)(m->elem))[i];
    } else if ( m->type == T_RGB ) {
        i = num * m->row * m->col + row * m->col + col;
        *((rgb *)elem) = ((rgb *)(m->elem))[i];
    } else {
        return false;
    }
    return true;
}

int matrix_set_zero( matrix * m ) {
    size_t i, n, u;
    if ( !m ) {
        return false;
    }
    if ( m->type == T_BINARY ) {
        u = 1;
        n = ( m->num * m->row * m->col + 8 ) / 8;
    } else if ( m->type == T_CHAR ) {
        u  = 1;
        n = m->num * m->row * m->col;
    } else if ( m->type == T_BYTE ) {
        u = 1;
        n = m->num * m->row * m->col;
    } else if ( m->type == T_SHORT ) {
        u = sizeof( short int );
        n = m->num * m->row * m->col;
    } else if ( m->type == T_LONG ) {
        u = sizeof( long int );
        n = m->num * m->row * m->col;
    } else if ( m->type == T_FLOAT ) {
        u = sizeof( float );
        n = m->num * m->row * m->col;
    } else if ( m->type == T_DOUBLE ) {
        u = sizeof( double );
        n = m->num * m->row * m->col;
    } else if ( m->type == T_RGB ) {
        u = sizeof( rgb );
        n = m->num * m->row * m->col;
    } else {
        return false;
    }
    memset( m->elem, 0, n * u );
    return true;
}

int matrix_set_elem(
    void * elem,
    matrix * m,
    int num,
    int row,
    int col
) {
    size_t i;
    unsigned char binary_elem;

    if ( !m || !elem) {
        return false;
    }
    if ( num < 0 || num >= m->num ) {
        return false;
    }
    if ( row < 0 || row >= m->row ) {
        return false;
    }
    if ( col < 0 || col >= m->col ) {
        return false;
    }
    if ( m->type == T_BINARY ) {
        i = num * m->row * m->col + row * m->col + col;
        binary_elem = ((unsigned char *)m->elem)[i/8];
        i = i % 8;
        if ( *((unsigned char *)elem) == 0 ) {
            binary_elem &= (~(0x01<<i));
        } else {
            binary_elem |= (0x01<<i);
        }
        i = num * m->row * m->col + row * m->col + col;
        ((unsigned char *)m->elem)[i/8] = binary_elem;
    } else if ( m->type == T_CHAR ) {
        i = num * m->row * m->col + row * m->col + col;
        ((char *)(m->elem))[i] = *((char *)elem);
    } else if ( m->type == T_BYTE ) {
        i = num * m->row * m->col + row * m->col + col;
        ((unsigned char *)(m->elem))[i] = *((unsigned char *)elem);
    } else if ( m->type == T_SHORT ) {
        i = num * m->row * m->col + row * m->col + col;
        ((short int *)(m->elem))[i] = *((short int *)elem);
    } else if ( m->type == T_LONG ) {
        i = num * m->row * m->col + row * m->col + col;
        ((long int *)(m->elem))[i] = *((long int *)elem);
    } else if ( m->type == T_FLOAT ) {
        i = num * m->row * m->col + row * m->col + col;
        ((float *)(m->elem))[i] = *((float *)elem);
    } else if ( m->type == T_DOUBLE ) {
        i = num * m->row * m->col + row * m->col + col;
        ((double *)(m->elem))[i] = *((double *)elem);
    } else if ( m->type == T_RGB ) {
        i = num * m->row * m->col + row * m->col + col;
        ((rgb *)(m->elem))[i] = *((rgb *)elem);
    } else {
        return false;
    }
    return true;
}


// copy everything including elements from m to nm without reallocation
// NOTE : matrix [nm] requires the same size as matrix [m]
int matrix_direct_copy( matrix * nm, matrix * m ) {
    size_t n;
    if ( !nm || !m ) {
        return false;
    }
    // check dimension
    if (
        nm->type != m->type ||
        nm->num != m->num ||
        nm->row != m->row ||
        nm->col != m->col
    ) {
        return false;
    }
    // deep copy
    if ( m->type == T_BINARY ) {
        n = ( m->num * m->row * m->col + 8 ) / 8;
    } else if ( m->type == T_CHAR ) {
        n = m->num * m->row * m->col * sizeof(char);
    } else if ( m->type == T_BYTE ) {
        n = m->num * m->row * m->col * sizeof(unsigned char);
    } else if ( m->type == T_SHORT ) {
        n = m->num * m->row * m->col * sizeof(short int);
    } else if ( m->type == T_LONG ) {
        n = m->num * m->row * m->col * sizeof(long int);
    } else if ( m->type == T_FLOAT ) {
        n = m->num * m->row * m->col * sizeof(float);
    } else if ( m->type == T_DOUBLE ) {
        n = m->num * m->row * m->col * sizeof(double);
    } else if ( m->type == T_RGB ) {
        n = m->num * m->row * m->col * sizeof(rgb);
    } else {
        return false;
    }
    memcpy( (char*)(nm->elem), (char*)(m->elem), n );
    return true;
}

// copy everything including elements from m to nm
// NOTE : matrix [nm] will be covered, existing memory requires deallocation
// outside this function
int matrix_copy( matrix * nm, matrix * m ) {
    size_t n;
    if ( !nm || !m ) {
        return false;
    }
    // deep copy
    *nm = *m;
    if ( !matrix_alloc( nm ) ) {
        return false;
    }
    if ( !matrix_direct_copy( nm , m ) ) {
        return false;
    }
    return true;
}


#endif
