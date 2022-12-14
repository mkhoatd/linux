#include <iostream>
#include <pthread.h>
#include <vector>
#include <sstream>

using namespace std;

const int NUM_THREADS = 2; // Number of threads to create
const int PT_SIZE = 1024;      // Size of the page table

// Function to initialize a page table with the given size
void initializePageTable(vector<double> &pt)
{
    for (int i = 0; i < PT_SIZE; i++)
    {
        pt[i] = i * 1.0;
    }
}

struct thread_res
{
    double threadSum;
    string message;
};

// Function to be executed by each thread
void *threadFunction(void *args)
{
    // Get the thread number and the page table
    int threadNum = *(int *)args;
    vector<double> pt(PT_SIZE);
    initializePageTable(pt);

    // Calculate the range of page table indices that this thread will process
    int start = threadNum * PT_SIZE;
    int end = PT_SIZE+start-1;

    // Print the thread number and the range of indices that it will process
    stringstream ss;
    ss<< "Thread " << threadNum << ": " << start << "-" << end << endl;

    // Calculate the sum of the page table elements in the given range
    double threadSum = 0;
    thread_res* result = (thread_res*) malloc(sizeof(thread_res));
    for (int i = start; i < end; i++)
    {
        threadSum += pt[i];
    }
    string message = ss.str();
    result->threadSum = threadSum;
    result->message = message;
    return result;
}

int main()
{
    // Create the page table and initialize it
    vector<double> pt(PT_SIZE);
    initializePageTable(pt);

    // Create the threads
    pthread_t threads[NUM_THREADS];
    double threadSum;
    double totalSum = 0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        int *args = new int[sizeof(int) + sizeof(vector<double> *)];
        // Set the thread number and page table pointer in the argument array
        *(int *)args = i;
        *(vector<double> **)(args + sizeof(int)) = &pt;

        // Create the thread and pass the argument array as the thread function's parameter
        pthread_create(&threads[i], NULL, threadFunction, args);
    }

    // Wait for each thread to finish and get its return value (the thread sum)
    for (int i = 0; i < NUM_THREADS; i++)
    {
        void* threadResultVoid;
        pthread_join(threads[i], &threadResultVoid);
        // Add the thread sum to the total sum
        thread_res threadResult= *(thread_res*) threadResultVoid;
        cout<<threadResult.message;
        totalSum += threadResult.threadSum;
    }

    // Print the total sum of all the elements in the page table
    cout << "Total sum: "<<totalSum;
    return 0;
}

