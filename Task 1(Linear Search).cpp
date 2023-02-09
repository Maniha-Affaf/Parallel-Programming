
//adding libraries
#include <iostream>
#include<mpi.h>

using namespace std;
int main(int argc , char argv[]){

  const int X = 20;
  int arr[X] = {4,78,54,32,67,24,33,57,150,42,159,4,13,9,5,72,45,51,3,4}
  int key = 4;
  int size,myrank,count =0;

  MPI_Init(&argc ,&argv);
  MPI_Comm_size(MPI_COMM_WORLD ,&size); // size = no of processes 
  MPI_Comm_rank(MPI_COMM_WORLD ,&myrank); // id of the process

  int elements_per_process = X/size;
  int starting_index = myrank * elements_per_process; 
  int ending_index = starting_index + elements_per_process; 

  for(int starting_index; starting_index<ending_index; starting_index++){

    if(arr[starting_index] ==key){ //if key is found or matches in the array
        count++;
    }

  }

  if(myrank ==0){
    int sum_of_count = 0;
    for(int i =0; i<size; i++){
        MPI_Recv(&sum_of_count, i, MPI_INT, i, 1000, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			count = count + sum_of_count; // will add the occurunces of key in the to count
    }
    cout <<"count value of key "<<key<<" is "<<count;
  }
  else{
    MPI_Send(&count, 1, MPI_INT, 0, 1000, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;




}

