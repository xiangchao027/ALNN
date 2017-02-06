// debugs.h
#ifndef DEBUGS_H
#define DEBUGS_H    1

// function declaration
#define DEBUG_CALL( func ) {\
    if( !(func) ) {\
        fprintf( stderr, "%s@%d : call failure!\n", \
        __FILE__, __LINE__ );\
        exit( 1 );\
    }\
}

#define DEBUG_ASSERT( expr ) {\
    if( !(expr) ) {\
        fprintf( stderr, "%s@%d : runtime check failed!\n", \
        __FILE__, __LINE__ );\
        exit( 1 );\
    }\
}

#endif
