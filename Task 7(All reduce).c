
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);


int num=0;
int arr[5]={1,2,6,4,5};

float local_sum = 0;
int i,numbersofArray;


// Print the random numbers on each process


 for (i = 0; i <= rank; i++) {
  printf("Values %d \n",arr[i]);

 
 }


for (i = 0; i < size; i++) {
  local_sum += arr[i];
}
// Print the random numbers on each process
printf("Local sum of process %d , %f, avg = %f\n",
       rank, local_sum, local_sum / size);

// Reduce all of the local sums into the global sum
float global_sum;
MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
           MPI_COMM_WORLD);

// Print the result
if (rank== 0) {
  printf("Total sum on each node = %f, avg = %f\n", global_sum,
         global_sum / (size));
}
}