#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "alnn.h"


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
    int     num;        // number of instances
    int     col;        // column count
    int     row;        // row count
    char    type;       // element type
    void*   elem;       // element values
} matrix;

// declarations
void help_msg();
void fread_h2l( void * target, int size, FILE * fp );
void read_mnist(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_output,
    const char * f );
void read_cifar10(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f );
void read_cifar100(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f );
void read_stl10(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f );
void read_svhn(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f );



// definitions
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

// read bytes from file and fill into memory in a high to low bit flow way
void fread_h2l( void * target, int size, FILE * fp ) {
    int i;
    if ( size < 1 ) {
        return;
    }
    for ( i = size - 1; i >= 0; i -- ) {
        if ( feof( fp ) ) {
            break;
        }
        fread( target + i, 1, 1, fp );
    }
}

// read mnist dataset
//      default path is:
//          {$MNIST}/train_input
//          {$MNIST}/train_label
//          {$MNIST}/test_input
//          {$MNIST}/test_label
void read_mnist(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_output,
    const char * f
) {
    // read the magic number
    char train_input_path[256];
    char train_label_path[256];
    char test_input_path[256];
    char test_label_path[256];

    int magic_number;
    FILE * fp;

    // memory reset
    memset( train_input_path, 0, sizeof train_input_path );
    memset( train_label_path, 0, sizeof train_label_path );
    memset( test_input_path, 0, sizeof test_input_path );
    memset( test_label_path, 0, sizeof test_label_path );

    strcat( train_input_path, f );
    strcat( train_input_path, "/" );
    strcat( train_input_path, "train_input" );
    strcat( train_label_path, f );
    strcat( train_label_path, "/" );
    strcat( train_label_path, "train_label" );
    strcat( test_input_path, f );
    strcat( test_input_path, "/" );
    strcat( test_input_path, "test_input" );
    strcat( test_label_path, f );
    strcat( test_label_path, "/" );
    strcat( test_label_path, "test_label" );

    // read train input matrix
    fp = fopen( train_input_path, "rb" );
    if ( !fp ) {
        fprintf( stdout, "file open error:[%s]!\n", train_input_path );
        exit( 1 );
    }

    // weirdly, the MNIST dataset use a high to low bit flow file presentation
    fread_h2l( &magic_number, sizeof magic_number, fp );

    // check magic code
    if ( magic_number != 0x0803 ) {
        fprintf( stdout, "magic number invalid:[%s]!\n", train_input_path );
        exit( 1 );
    }

    // read how many images to read
    fread_h2l( &(train_input->num), sizeof train_input->num, fp );
    fread_h2l( &(train_input->row), sizeof train_input->row, fp );
    fread_h2l( &(train_input->col), sizeof train_input->col, fp );


}

void read_cifar10(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f
) {
}

void read_cifar100(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f
){
}

void read_stl10(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f
){
}

void read_svhn(
    matrix * train_input,
    matrix * train_label,
    matrix * test_input,
    matrix * test_label,
    const char * f
) {
}



int main(int argc, const char ** argv ) {
    int data_id;
    // read MNIST dataset
    if ( argc < 2 ) {
        help_msg();
    } else {
        if ( argv[1][1] ) { // in case string not closed
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
    if ( data_id == 1 ) { // MNIST
        matrix train_input, train_label, test_input, test_label;
        read_mnist(
            &train_input,
            &train_label,
            &test_input,
            &test_label,
            "./MNIST"
        );
    }



    return 0;
}
