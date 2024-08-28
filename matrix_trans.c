#include <time.h>
#include <sys/time.h>

void transposeInPlace(float *matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float temp = matrix[i * n + j];
            matrix[i * n + j] = matrix[j * n + i];
            matrix[j * n + i] = temp;
        }
    }
}

void transposeWithArray(float *matrix, float *result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[j * n + i] = matrix[i * n + j];
        }
    }
}


int main( int argc, char **argv ) {

    for (int n = 200; n <= 1800; n += 200){

        struct timeval start, end;

        float *A = (float*)malloc( n*n*sizeof(float) );
        float *B = (float*)malloc( n*n*sizeof(float) );
        float *C = (float*)malloc( n*n*sizeof(float) );

        for( int i = 0; i < n*n; i++ ){
                A[i] = drand48()*2-1;
                C[i] = drand48()*2-1;
        }

        for( int i = 0; i < n*n; i++ ){
            B[i] = 0;
        }

        gettimeofday( &start, NULL );
        transposeInPlace(A, n);
        gettimeofday( &end, NULL );

        double seconds1 = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
        printf( "in_place %g milliseconds\n", seconds1*1e3 );

        gettimeofday( &start, NULL );
        transposeWithArray(C, B, n);
        gettimeofday( &end, NULL );

        double seconds2 = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
        printf( "new_array %g milliseconds\n", seconds2*1e3 );
    }
   
    return 0;
}


