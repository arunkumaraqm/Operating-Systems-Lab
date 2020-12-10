#include <stdio.h> 
#include <stdbool.h>
#include <limits.h>

#define max(one, two) ((one < two) ? two: one)
typedef struct Process
{
	int process_number;
	float burst;
	float arrival;
	float waiting;
	float turnaround;
} Process;

void print_process(Process* proc)
{
	printf("(%d, %f, %f, %f, %f)\n",
			proc->process_number, 
			proc->burst,
			proc->arrival,
			proc->waiting,
			proc->turnaround);
}

void print_process_array(int nf, Process* arr)
{
	for (int i = 0; i < nf; ++i)
	{
		print_process(&arr[i]);
	}
	printf("\n");
}

void read_process(Process* proc)
{
	scanf("%f %f",
			&proc->burst,
			&proc->arrival);
}

void read_process_array(int nf, Process* arr)
{
	for (int i = 0; i < nf; ++i)
	{
		arr[i].process_number = i + 1;
		read_process(&arr[i]);
	}
}

bool cmp_by_arrival_then_burst(Process* proc_one, Process* proc_two)
{
	return proc_one->arrival < proc_two->arrival ||
		(proc_one->arrival == proc_two->arrival &&
		 proc_one->burst < proc_two->burst);
}

bool cmp_by_process_no(Process* proc_one, Process* proc_two)
{
	return proc_one->process_number < proc_two->process_number;
}

void swap(Process *xp, Process *yp) 
{ 
	Process temp = *xp; 
	*xp = *yp; 
	*yp = temp; 
} 

void bubble_sort(int nf, Process* arr, bool (*lt)(Process*, Process*))
{ 
	int i, j; 
	for (i = 0; i < nf - 1; i++)       
	{
		for (j = 0; j < nf - i - 1; j++)  
		{
			if (lt(&arr[j + 1], &arr[j])) 
			{
				swap(&arr[j], &arr[j + 1]); 
			}
		}
	}
} 

void sjf(int nf, Process* arr, float* avg_waiting, float* avg_turnaround)
{
	float time_elapsed = 0, sum_waiting, sum_turnaround;
	int left = 0, right = 0;

	for (int i = 0; i < nf; ++i)
	{
		float minn = FLOAT_MAX;
		int pos = -1;

		for (int j = left; j <= right; ++j)
		{
			if (arr[j].burst < minn)
			{
				minn = arr[j].burst;
				pos = j;
			}
		}

		if (pos != -1) //INCOMPLETE
		{
			swap(&arr[pos], &arr[left]);
			left++;
		}
	}
	for (int i = 0; i < nf; ++i)
	{
		time_elapsed = max(time_elapsed, arr[i].arrival);
		arr[i].waiting = time_elapsed;
		time_elapsed += arr[i].burst;
		arr[i].turnaround = time_elapsed;

		sum_waiting += arr[i].waiting;
		sum_turnaround += arr[i].turnaround;
	}

	*avg_waiting = sum_waiting / nf;
	*avg_turnaround = sum_turnaround / nf;
}

void main()
{
	int nf;
	scanf("%d", &nf);

	Process arr[nf];
	read_process_array(nf, arr);
	
	bubble_sort(nf, arr, cmp_by_arrival_then_burst);
	
	float avg_waiting, avg_turnaround;
	sjf(nf, arr, &avg_waiting, &avg_turnaround);

	bubble_sort(nf, arr, cmp_by_process_no);
	print_process_array(nf, arr);
	printf("=> (%f, %f)",
			avg_waiting, avg_turnaround);N
}
