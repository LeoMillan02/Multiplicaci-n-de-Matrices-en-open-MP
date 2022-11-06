#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define FB (3)
#define CB (4)
#define FA (4)
#define CA (3)

int main(int argc, char** argv){

    int matrixA[FA][CA] = {
            {3, 7, 1},
            {2, 11, 3},
            {9, 5, 8},
            {7, 6, 9},
    };
    int matrixB[FB][CB] = {
            {8, 3, 11, 3},
            {4, 8, 4, 3},
            {1, 6, 3, 7},
    };
    int threadcnt = 1;

    if (CA != FB) {
        printf("Columna A debe ser igual a fila B");
        return 0;
    }

    if (argc > 1) {
        threadcnt = atoi(argv[1]);
    }

    #ifdef _OPENMP
        omp_set_num_threads( threadcnt );
        printf("OMP defined, threadct = %d\n", threadcnt);
    #else
        printf("OMP not defined \n");
    #endif
    
    int C[FB][CB];
    int a,i,j,suma; 

    #pragma omp parallel for private(a,i,j,suma) shared (C)
    for (a = 0; a < CB; a++) {
        for (i = 0; i < FA; i++) {
            int suma = 0;
            for (j = 0; j < CA; j++) {
                suma += matrixA[i][j] * matrixB[j][a];
            }
            C[i][a] = suma;
        }
    }

    printf("Resultado: \n");
    for (int i = 0; i < FB; i++) {
        for (int j = 0; j < CB; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
return 0;
}