#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 999

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char filename[100];
    if (rank == 0) {
        printf("Enter filename: ");
        scanf("%s", filename);
    }
    MPI_Bcast(filename, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    FILE *file = fopen(filename, "rb+");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        MPI_Finalize();
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long int file_size = ftell(file);
    rewind(file);

    int *data = (int *)malloc(file_size);
    if (!data) {
        printf("Error allocating memory\n");
        MPI_Finalize();
        return 1;
    }

    fread(data, sizeof(int), file_size / sizeof(int), file);

    // Local counter array
    int local_count[MAX_VALUE + 1];
    for (int i = 0; i <= MAX_VALUE; i++) {
        local_count[i] = 0;
    }

    // Count occurrences of each value
    for (int i = rank * (file_size / size); i < (rank + 1) * (file_size / size); i++) {
        local_count[data[i]]++;
    }

    // Global count array
    int global_count[MAX_VALUE + 1];
    if (rank == 0) {
        for (int i = 0; i <= MAX_VALUE; i++) {
            global_count[i] = 0;
        }
    }

    MPI_Reduce(local_count, global_count, MAX_VALUE + 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate prefixes for local displacement
    int displacement[MAX_VALUE + 1];
    if (rank == 0) {
        displacement[0] = 0;
        for (int i = 1; i <= MAX_VALUE; i++) {
            displacement[i] = displacement[i - 1] + global_count[i - 1];
        }
    }

    MPI_Bcast(displacement, MAX_VALUE + 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Sort data locally
    int *sorted_data = (int *)malloc(file_size / size);
    for (int i = rank * (file_size / size); i < (rank + 1) * (file_size / size); i++) {
        sorted_data[displacement[data[i]]++] = data[i];
    }

    // Gather sorted data from all processes
    int *global_sorted_data = NULL;
    if (rank == 0) {
        global_sorted_data = (int *)malloc(file_size);
    }
    MPI_Gather(sorted_data, file_size / size, MPI_INT, global_sorted_data, file_size / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        rewind(file);
        fwrite(global_sorted_data, sizeof(int), file_size / sizeof(int), file);
        fclose(file);
        free(global_sorted_data);
    }

    free(sorted_data);
    free(data);
    MPI_Finalize();

    return 0;
}
