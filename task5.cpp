#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
//mpi all reduce call


MPI_Init(&argc,&argv);
int size,rank;
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
int num=rank;
int sum=0;


MPI_Allreduce(&num,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
cout<<"sum in process "<<rank<<" is "<<sum<<endl;
MPI_Finalize();
return 0;
}
