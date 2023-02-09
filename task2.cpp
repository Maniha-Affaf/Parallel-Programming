#include <mpi.h> 
#include <iostream>
 using namespace std;
 int main(int argc, char *argv[])
  {
   
   int size, rank;
    int N=10;
   int arr[N];
    int count=0;
   int key=4;
   for(int i=0; i<N; i++)
   {
   	cout<<"Enter : "<<i<<"Number"<<endl;
   	cin>>arr[i];
   }
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
   //int arr[N]={1,2,3,4,5,6,7,4,9,22};
   int element_per_process=N/size;
   int start_index=rank* element_per_process;
   int end_index=start_index+element_per_process;
  
   for(int i=start_index; i<end_index; i++){
   	if(arr[i]==key){
   	
   		count++;
   	}
   
   }
   
   cout << "process : " << rank << " found : " << count << " : element \n"<<endl;
   
   if (rank!=0){
   	MPI_Send(&count, 1, MPI_INT, 0, 999, MPI_COMM_WORLD);
   }
   else {
   	for(int i=1; i<size; i++){
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
