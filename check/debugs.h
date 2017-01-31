// debugs.h
#ifndef DEBUGS_H
#define DEBUGS_H    1

// function declaration
#define DEBUG_CALL( func ) {\
    if( !(func) ) {\
        fprintf( stderr, "@%d : call failure!\n", __LINE__ );\
        exit( 1 );\
    }\
}

#define DEBUG_ASSERT( expr ) {\
    if( !(expr) ) {\
        fprintf( stderr, "@%d : runtime check failed!\n", __LINE__ );\
        exit( 1 );\
    }\
}

#endif
