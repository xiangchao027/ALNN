// t_main.c
// test app entry point
#include "t_matrix.h"

int main( int argc, const char ** agrv ) {
    // test in order of dependency
    // test matrix tool functions
    if( !t_matrix() ) {
        return 1;
    }
    // test neural network tool functions
    fprintf( stdout, "All tests passed!\n" );
    fflush( stdout );
    return 0;
}
