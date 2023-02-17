#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 20000

void generate_random_numbers(int* arr, int size);
void merge_sort(int* arr, int start, int end);
void merge(int* arr, int start, int mid, int end);

int main(int argc, char** argv) {
    int arr[ARRAY_SIZE];
    int sum = 0, local_sum = 0, nprocs, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        generate_random_numbers(arr, ARRAY_SIZE);
        merge_sort(arr, 0, ARRAY_SIZE - 1);
    }

    int chunk_size = ARRAY_SIZE / nprocs;
    int local_arr[chunk_size];

    MPI_Scatter(arr, chunk_size, MPI_INT, local_arr, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_arr[i];
    }

    if (rank == 0) {
        MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    } else {
        MPI_Reduce(&local_sum, NULL, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printf("La suma de los %d numeros aleatorios es: %d\n", ARRAY_SIZE, sum);
    }

    MPI_Finalize();
    return 0;
}

void generate_random_numbers(int* arr, int size) {
    srand(0);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 11;
    }
}

void merge_sort(int* arr, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void merge(int* arr, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int left[n1], right[n2];

    for (int i = 0; i < n1; i++) {
        left[i] = arr[start + i];
    }

    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = start;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}
