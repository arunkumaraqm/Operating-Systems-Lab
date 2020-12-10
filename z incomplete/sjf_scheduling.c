#include <stdio.h>

float average(int size, float* arr)
{
    float summ;
    for (int i = 0; i < size; i++)
    {
        summ += arr[i];
    }    

    return summ / size;
}

void read_array(int size, float* arr)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%f", &arr[i]); 
    }    
}

typedef struct IndexedValues
{
    int idx;
    float value;
} IndexedValues;

int main()
{
    int nf_processes;
    float burst_times[20], waiting_times[20] = {}, turnarounds[20] = {};
    float average_waiting_time = 0, average_turnaround = 0;
    int i, j; 
    
    scanf("%d", &nf_processes); 
    read_array(nf_processes, burst_times);

    IndexedValues burst_times_w_idx[20];
    for (int i = 0; i < nf_processes; ++i)
    {
        burst_times_w_idx.idx = i;
        burst_times_w_idx.value = burst_times[i];
    }
    qsort(burst_times_w_idx, nf_processes, sizeof IndexedValues, cmpfunc);
 


    average_waiting_time = average(nf_processes, waiting_times);
    average_turnaround = average(nf_processes, turnarounds);

    printf("(Process no., Burst time, Waiting time, Turnaround time)\n");
    for (i = 0; i < nf_processes; ++i)
    {
        printf("(%d, %f, %f, %f), \n",
            i + 1,
            burst_times[i],
            waiting_times[i],
            turnarounds[i]
            );
    }
    printf("Average Waiting Time = %f\n", average_waiting_time);
    printf("Average Turnaround Time = %f\n", average_turnaround);
    return 0; 
}
