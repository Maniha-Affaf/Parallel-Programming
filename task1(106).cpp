//komal tanveer khan
//rollno 106-bscs-19
//section A1
//task1


#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
int npes,myrank;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&npes);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
int array[12]={1,2,10,3,2,2,4,5,6,3,2,5};
int key=2;
int elem_pp=12/npes;
int start_index=elem_pp*myrank;
int ending_index=start_index+elem_pp;

//for rank 0
if(rank==0){
count=0;
for(int i=start_index;i<=ending_index;i++){
if(array[i]==key){
count++;
}
}
MPI_Status status;
int sum;
for(int i=1;i<npes;i++){
count+=MPI_Recv(sum,1,MPI_INT,i,100,MPI_COMM_WORLD,&status);
}
cout<<"the key element"<<key<<"comes"<<count<<""times in the array";
}
//for other processes
else{
arr[elem_pp];
count=0;
for(int i=start_index;i<ending_index;i++){
if(arr[i]==key){
count++;
}
MPI_Send(count,1,MPI_INT,0,100,&MPI_COMM_WORLD);
}
MPI_Finalize();
return 0;
}