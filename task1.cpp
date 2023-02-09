#include <mpi.h> 
#include <iostream>
 using namespace std;
 int main(int argc, char *argv[])
  {
   int num_process, myrank;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_process);
   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
   int N=10;
   int arr[N]={1,2,3,4,5,6,7,4,9,22};
   int elemnt_per_process=N/num_process;
   int start_index=myrank* elemnt_per_process;
   int end_index=start_index+elemnt_per_process;
   int count=0;
   int key=4;
   for(int i=start_index; i<end_index; i++){
   	if(arr[i]==key){
   	
   		count++;
   	}
   
   }
   
   cout << "process : " << myrank << " found : " << count << " : element \n"<<endl;
   
   if (myrank!=0){
   	MPI_Send(&count, 1, MPI_INT, 0, 999, MPI_COMM_WORLD);
   }
   else {
   	for(int i=1; i<num_process; i++){
   		MPI_Status status;
   		int count_rcv;
   		MPI_Recv(&count_rcv, 1, MPI_INT,1,999, MPI_COMM_WORLD, &status);
   		count+=count_rcv;
   		
   	}
   	cout<<"Total : "<<count<<" : vlaue"<<endl;
   }

   
    MPI_Finalize();
 
    
     return 0;
  }
