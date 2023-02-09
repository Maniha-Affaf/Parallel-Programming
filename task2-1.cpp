#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
//mpi all reduce call
MPI_Init(&argc,&argv);
int num_pp,myrank,n,element_pp,start,end;
MPI_Comm_size(MPI_COMM_WORLD,&num_pp);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
int array[n];
cout<<"enter array size";
cin>>n;
//array initialization
for(int i=0;i<n;i++){
array[i]=i+2;
}
int b_buff[5];
for(int i=0;i<5;i++){
b_buff[i]=array[i];
}

//every process take its elements of array by these formulas
element_pp=n/num_pp;
start=element_pp*myrank;
end=start+element_pp;
 
//broadcast first 5 elements of array
MPI_Bcast(&b_buff,5,MPI_INT,0,MPI_COMM_WORLD);

//reduce size of array and delete the multiples
for(int j=0;j<5;j++){
for(int i=start;i<end;i++){
if(array[i]%b_buff[j]==0){
	for(int k=i;k<n;k++){
		array[k]=array[k+1];
	}
	n--;
}
}
}
for(int i=0;i<n;i++){
cout<<array[i];
}
cout<<endl;
MPI_Finalize();
return 0;
}
