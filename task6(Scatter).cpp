#include<mpi.h>
#include<iostream>
using namespace std;

//main function
int main(int argc,char *argv[]){


// no of process and id of process
int num_pp,myrank;

MPI_Init(&argc,&argv);

MPI_Comm_size(MPI_COMM_WORLD,&num_pp);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

// Initializing array
int array[20];
for(int i=0;i<20;i++){
array[i]=i+1;
}


int element_per_process=20/num_pp;

int array[element_per_process];

//mpi scatter call

MPI_Scatter(&array,element_per_process,MPI_INT,&array,element_per_process,MPI_INT,0,MPI_COMM_WORLD);

cout<<"process id"<<myrank<<endl;

//Printing array

for(int i=0;i<num_pp;i++){
cout<<array[i]<<",";
}
cout<<endl;
MPI_Finalize();
return 0;
}
