#include <stdio.h>
#include <stdlib.h>


// basic data structures
// matrix.type :
//      b : unsigned char = binary, constrainted by 0/1 check
//      c : char = character, from 0 to 127
//      u : unsigned char = byte
//      s : short int = short integer
//      l : long int = long integer
//      f : float = float number
//      d : double = double
typedef struct T_MATRIX {
    int     col;        // column count
    int     row;        // row count
    char    type;       // element type
    void*   elem;       // element values
} matrix;

// declaration
void help_msg();
void read_mnist( matrix * m, const char * f );
void read_cifar10( matrix * m, const char * f );
void read_cifar100( matrix * m, const char * f );
void read_stl10( matrix * m, const char * f );
void read_svhn( matrix * m, const char * f );


// print help information
void help_msg() {
    fprintf( stdout, "USAGE: main.a [dataset id]\n");
    fprintf( stdout, "       dataset id is in [1, 5]\n");
    fprintf( stdout, "       1 - MNIST dataset\n");
    fprintf( stdout, "       2 - CIFAR-10\n");
    fprintf( stdout, "       3 - CIFAR-100\n");
    fprintf( stdout, "       4 - STL-10\n");
    fprintf( stdout, "       5 - SVHN\n");
    fflush( stdout );
    exit( 0 );
}

// read mnist dataset
void read_mnist( matrix * m, const char * f ) {
    // read the magic number

    // test if dataset is ready
}

// read CIFAR-10 dataset
void read_cifar10( matrix * m, const char * f ) {

}

// read CIFAR-100 dataset
void read_cifar100( matrix * m, const char * f ) {

}

// read STL-10 dataset
void read_stl10( matrix * m, const char * f ) {

}

// read SVHN dataset
void read_svhn( matrix * m, const char * f ) {

}


int main(int argc, const char ** argv ) {
    int data_id;
    // read MNIST dataset
    if ( argc < 2 ) {
        help_msg();
    } else {
        if ( !argv[1][1] ) {
            fprintf( stderr, "input invalid!\n" );
            help_msg();
        }
        data_id = atoi( argv[1] );
        if ( data_id < 1 || data_id > 5 ) {
            fprintf( stderr, "input dataset is invalid!\n" );
            help_msg();
        }
    }

    // begin to read dataset into memory
    matrix m;
    read_mnist( &m, "MNIST" );


    return 0;
}
