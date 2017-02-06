// t_main.c
// test app entry point
#include "t_matrix.h"
#include "t_alnn.h"

int main( int argc, const char ** agrv ) {
    // test in order of dependency
    // test matrix tool functions
    if ( !t_matrix() ) {
        return 1;
    }
    // test neural network tool functions
    if ( !t_alnn() ) {
        return 1;
    }
    fprintf( stdout, "All tests passed!\n" );
    fflush( stdout );
    return 0;
}
