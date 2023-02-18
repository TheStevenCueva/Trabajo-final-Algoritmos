#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

//EJERCICIO 2
int main(int argc, char** argv) {
    int num_procs, proc_id;
    long RECTAS = 20000000;
    double mid, height, width, area_local, area_total = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    // Se envía el valor de RECTAS a todos los procesos
    MPI_Bcast(&RECTAS, 1, MPI_LONG, 0, MPI_COMM_WORLD);

    width = 1.0 / (double) RECTAS;
    long start, end;

    // Se divide el cálculo del área en cuatro partes
    if (proc_id == 0) {
        start = 0;
        end = RECTAS / 4;
        //printf("Proceso %d\n",proc_id);
    }
    else if (proc_id == 1) {
        start = RECTAS / 4;
        end = RECTAS / 2;
        //printf("Proceso %d\n",proc_id);
    }
    else if (proc_id == 2) {
        start = RECTAS / 2;
        end = 3 * RECTAS / 4;
        //printf("Proceso %d\n",proc_id);
    }
    else if (proc_id == 3) {
        start = 3 * RECTAS / 4;
        //printf("Proceso %d\n",proc_id);
        end = RECTAS;
    }
    else {
        start = 0;
        end = 0;
    }

    area_local = 0.0;
    for (long i = start; i < end; i++) {
        mid = (i + 0.5) * width;
        height = 4.0 / (1.0 + mid * mid);
        area_local += height;
    }
    area_local *= width;

    // Se realiza una reducción de suma en el proceso 0
    MPI_Reduce(&area_local, &area_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Se muestra el resultado en el proceso 0
    if (proc_id == 0) {
        printf("Resultado = %f\n", area_total);
    }

    MPI_Finalize();

    return 0;
}
