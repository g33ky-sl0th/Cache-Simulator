#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>


/* To save you time, we are including all 6 variants of the loop ordering 
   as separate functions and then calling them using function pointers. 
   The reason for having separate functions that are nearly identical is
   to avoid counting any extraneous processing towards the computation
   time.  This includes I/O accesses (printf) and conditionals (if/switch).
   I/O accesses are slow and conditional/branching statements could
   unfairly bias results (lower cases in switches must run through more
   case statements on each iteration).
*/
void matirx_mul1( int n, float *A, float *B, float *C ) {
    int i,j,k;

    for( i = 0; i < n; i++ ) {
        for( j = 0; j < n; j++ ) {
            for( k = 0; k < n; k++ ) {
                C[i+j*n] += A[i+k*n]*B[k+j*n];
            }
        }
    }
}

void matirx_mul2( int n, float *A, float *B, float *C ) {
    int i,j,k;

    for( i = 0; i < n; i++ ) {
        for( k = 0; k < n; k++ ) {
            for( j = 0; j < n; j++ ) {
                C[i+j*n] += A[i+k*n]*B[k+j*n];
            }
        }
    }
}

void matirx_mul3( int n, float *A, float *B, float *C ) {
    int i,j,k;

    for( j = 0; j < n; j++ ) {
        for( k = 0; k < n; k++ ) {
            for( i = 0; i < n; i++ ) {
                C[i+j*n] += A[i+k*n]*B[k+j*n];
            }
        }
    }
}

void matirx_mul4( int n, float *A, float *B, float *C ) {
    int i,j,k;

    for( j = 0; j < n; j++ ) {
        for( i = 0; i < n; i++ ) {
            for( k = 0; k < n; k++ ) {
                C[i+j*n] += A[i+k*n]*B[k+j*n];
            }
        }
    }
}

void matirx_mul5( int n, float *A, float *B, float *C ) {
    int i,j,k;

    for( k = 0; k < n; k++ ) {
        for( i = 0; i < n; i++ ) {
            for( j = 0; j < n; j++ ) {
                C[i+j*n] += A[i+k*n]*B[k+j*n];
            }
        }
    }
}

void matirx_mul6( int n, float *A, float *B, float *C ) {
    int i,j,k;

    for( k = 0; k < n; k++ ) {
        for( j = 0; j < n; j++ ) {
            for( i = 0; i < n; i++ ) {
                C[i+j*n] += A[i+k*n]*B[k+j*n];
            }
        }
    }
}



int main( int argc, char **argv ) {

    
    for (int n = 200; n <= 2000; n += 200){

        float *A = (float *)malloc( n*n * sizeof(float));
        float *B = (float *)malloc( n*n * sizeof(float));
        float *C = (float *)malloc( n*n * sizeof(float));
                    
        for( int i = 0; i < n*n; i++ ){
            A[i] = drand48()*2-1;
        };

        for( int i = 0; i < n*n; i++ ){
            B[i] = drand48()*2-1;
        };

        for( int i = 0; i < n*n; i++ ){
            C[i] = drand48()*2-1;
        };

        for( int i = 0; i < 6; i++) {

            struct timeval strat, finish;

            if (i == 0){                

                gettimeofday( &strat, NULL );
                matirx_mul1(n, A, B, C);
                gettimeofday( &finish, NULL );

                double seconds = (finish.tv_sec - strat.tv_sec) + 1.0e-6 * (finish.tv_usec - strat.tv_usec);
                printf( "%s:\tn = %d, %.3f time \n", "i-j-k", n, seconds );
            }

            else if (i == 1){

                gettimeofday( &strat, NULL );
                matirx_mul2(n, A, B, C);
                gettimeofday( &finish, NULL );

                double seconds = (finish.tv_sec - strat.tv_sec) + 1.0e-6 * (finish.tv_usec - strat.tv_usec);
                printf( "%s:\tn = %d, %.3f time \n", "i-k-j", n, seconds );
            }

            else if (i == 2){

                gettimeofday( &strat, NULL );
                matirx_mul3(n, A, B, C);
                gettimeofday( &finish, NULL );

                double seconds = (finish.tv_sec - strat.tv_sec) + 1.0e-6 * (finish.tv_usec - strat.tv_usec);
                printf( "%s:\tn = %d, %.3f time \n", "j-k-i", n, seconds );
            }

            else if (i == 3){

                gettimeofday( &strat, NULL );
                matirx_mul4(n, A, B, C);
                gettimeofday( &finish, NULL );

                double seconds = (finish.tv_sec - strat.tv_sec) + 1.0e-6 * (finish.tv_usec - strat.tv_usec);
                printf( "%s:\tn = %d, %.3f time \n", "j-i-k", n, seconds );
            }

            else if (i == 4){

                gettimeofday( &strat, NULL );
                matirx_mul5(n, A, B, C);
                gettimeofday( &finish, NULL );

                double seconds = (finish.tv_sec - strat.tv_sec) + 1.0e-6 * (finish.tv_usec - strat.tv_usec);
                printf( "%s:\tn = %d, %.3f time \n", "k-i-j", n, seconds );
            }

            else if (i == 5){

                gettimeofday( &strat, NULL );
                matirx_mul6(n, A, B, C);
                gettimeofday( &finish, NULL );

                double seconds = (finish.tv_sec - strat.tv_sec) + 1.0e-6 * (finish.tv_usec - strat.tv_usec);
                printf( "%s:\tn = %d, %.3f time \n", "k-j-i", n, seconds );
            }
            
        }

        printf("\n\n");
    }

    // free( A );
    // free( B );
    // free( C );

    printf("\n\n");

    return 0;
}
