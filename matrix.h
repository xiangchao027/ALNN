#ifndef MATRIX_H
#define MATRIX_H    1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// basic data structures
// matrix.type :
//      b : unsigned char = binary, constrainted by 0/1 check
//      c : char = character, from 0 to 127
//      u : unsigned char = byte
//      s : short int = short integer
//      l : long int = long integer
//      f : float = float number
//      d : double = double
enum {
    T_BINARY = 'b',
    T_CHAR = 'c',
    T_BYTE = 'u',
    T_SHORT = 's',
    T_LONG = 'l',
    T_FLOAT = 'f',
    T_DOUBLE = 'd'
};

enum { R_FALSE = 0 , R_TRUE = 1 };


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
int matrix_set_zero( matrix * m );  // set all elements to zero

// definitions of declared functions
int matrix_alloc( matrix * m ) {
    size_t n;
    if ( !m ) {
        return R_FALSE;
    }
    if ( m->num <= 0 || m->row <= 0 || m->col <= 0 ) {
        return R_FALSE;
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
    } else {
        return R_FALSE;
    }
    return R_TRUE;
}

// deallocation of matrix
int matrix_free( matrix * m ) {
    if ( !m ) {
        return R_FALSE;
    }
    free( m->elem );
    m->num = 0;
    m->col = 0;
    m->row = 0;
    m->elem = 0;
    return R_TRUE;
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
        return R_FALSE;
    }
    if ( num < 0 || num >= m->num ) {
        return R_FALSE;
    }
    if ( row < 0 || row >= m->row ) {
        return R_FALSE;
    }
    if ( col < 0 || col >= m->col ) {
        return R_FALSE;
    }
    if ( m->type == T_BINARY ) {
        i = num * m->row * m->col + row * m->col + col;
        binary_elem = ((unsigned char *)m->elem)[i/8];
        i = i % 8;
        if ( i == 0 ) {
            *((char *)elem) =  binary_elem & 0x01;
        } else if ( i == 1 ) {
            *((char *)elem) = binary_elem & 0x02;
        } else if ( i == 2 ) {
            *((char *)elem) = binary_elem & 0x04;
        } else if ( i == 3 ) {
            *((char *)elem) = binary_elem & 0x08;
        } else if ( i == 4 ) {
            *((char *)elem) = binary_elem & 0x010;
        } else if ( i == 5 ) {
            *((char *)elem) = binary_elem & 0x020;
        } else if ( i == 6 ) {
            *((char *)elem) = binary_elem & 0x040;
        } else if ( i == 7 ) {
            *((char *)elem) = binary_elem & 0x080;
        }
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
    }
    return R_TRUE;
}
//
int matrix_set_zero( matrix * m ) {
    int i, n, u;
    if ( !m ) {
        return R_FALSE;
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
    } else {
        return R_FALSE;
    }
    memset( m->elem, 0, n * u );
    return R_TRUE;
}


#endif
