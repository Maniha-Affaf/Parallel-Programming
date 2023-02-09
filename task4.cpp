#include<mpi.h>
#include<iostream>
using namespace std;
int main( int argc,char *argv[]){
//mpi reduce call
int size,rank;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
int num=rank;
int sum=0;
MPI_Reduce(&num,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
cout<<"number sum is "<<sum<<"from process"<<rank<<endl;
MPI_Finalize();
return 0;
}
