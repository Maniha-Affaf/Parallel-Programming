#include <iostream>
#include <mpi.h>
using namespace std;
#define array_size 10
#define isEven(n) (n % 2== 0)

//Initialize array with random values
void random_array(int arr[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        arr[i] = size - i;
    }
}

//Display the array
void displayArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        cout << arr[i] << "     ";
    }
    cout << endl;
}

//function to sort the array
void sort_array(int* arr, int starting_index, int elements_per_process) 
{
    int ending_index = (elements_per_process + starting_index); // it will be the last element of array
    for (int i = starting_index; i < ending_index && i < array_size; i = i + 2) 
    {
        if (arr[i] > arr[i + 1]) 
        {
            swap(arr[i], arr[i + 1]);
        }
    }
}

//function to merge the arrays
void merge_array(int recieved_array[][array_size], int* arr, int no_of_processes, int elements_per_process) 
{
    for (int j = 1; j < no_of_processes; ++j) 
    {
        int starting_index = elements_per_process * j;
        int end = starting_index + elements_per_process;

        for (int i = starting_index; i < end && i < array_size; i++) 
        {
            arr[i] = recieved_array[j - 1][i];
        }
    }
}

int main(int argc, char* argv[]) 
{
    int myrank, no_of_processes;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
    int arr[array_size]{ 0 };
    int elements_per_process = array_size / no_of_processes;
    random_values_array(arr, array_size);

    if (myrank == 0) 
    {
        int starting_index;
        int recieved_array[no_of_processes - 1][array_size];
        for (int i = 0; i < array_size; i++) 
        {
            sort_array(arr, isEven(i), elements_per_process);
            for (int j = 1; j < no_of_processes; j++) 
            {
                starting_index = (j * elements_per_process) + isEven(i);

                MPI_Send(&starting_index, 1, MPI_INT, j, j, MPI_COMM_WORLD);
                MPI_Recv(recieved_array[j - 1], array_size, MPI_INT, j, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


            }
            merge_array(recieved_array, arr, no_of_processes, elements_per_process);
        }
        displayArray(arr, array_size);
    }

    else 
    {
        int start;
        for (int i = 0; i < array_size; ++i) 
        {
            MPI_Recv(&start, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sort_array(arr, start, elements_per_process);
            MPI_Send(arr, array_size, MPI_INT, 0, myrank, MPI_COMM_WORLD);
        }
    }
    
    MPI_Finalize();
    return 0;
}