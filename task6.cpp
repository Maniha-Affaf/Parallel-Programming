#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
//mpi scatter call
MPI_Init(&argc,&argv);
int size,rank;
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
int num_arr[20];
for(int i=0;i<20;i++){
num_arr[i]=i+1;
}
int noof-elements=20/size;
int array[noof-elements];
MPI_Scatter(&num_arr,noof-elements,MPI_INT,&array,noof-elements,MPI_INT,0,MPI_COMM_WORLD);
cout<<"process id"<<rank<<endl;
for(int i=0;i<size;i++){
cout<<array[i]<<",";
}
cout<<endl;
MPI_Finalize();
return 0;
}
