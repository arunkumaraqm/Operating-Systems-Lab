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

int main()
{
    int nf_processes;
    float burst_times[20], waiting_times[20], turnarounds[20];
    float average_waiting_time = 0, average_turnaround = 0;
    int i, j; 
    
    scanf("%d", &nf_processes); 
    read_array(nf_processes, burst_times);
 
    for (i = 0; i < nf_processes; i++)
    {
        waiting_times[i] = 0; 
        
        for (j = 0; j < i; j++)
        {
            waiting_times[i] = waiting_times[i] + burst_times[j]; 
        }

        turnarounds[i] = waiting_times[i] + burst_times[i]; 
    }

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
