#include <stdio.h> 
#include <stdbool.h>

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

typedef struct Queue
{
	Process* list;
	int size;
	int begin;
	int end;
} Queue;

void q_make(Queue* qu, int length)
{
	qu->list = calloc(length, sizeof Process);
	qu->begin = 0; qu->end = -1;
}
void q_destroy(Queue* qu)
{
	free(qu->list);
}
void q_isempty(Queue* qu)
{
	return qu->begin == qu->end + 1;
}
void q_enqu(Queue* qu, Process ele)
{
	qu->end ++;
	qu->list[qu->end] = ele;
}
void q_dequ(Queue* qu)
{
	qu->begin ++;
}
void round_robin(int nf, Process* arr, float* avg_waiting, float* avg_turnaround)
{
	Process queue[2 * nf];
	int qbegin = 0, qend = nf - 1;

	float time_elapsed = 0, sum_waiting, sum_turnaround;
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
	round_robin(nf, arr, &avg_waiting, &avg_turnaround);

	bubble_sort(nf, arr, cmp_by_process_no);
	print_process_array(nf, arr);
	printf("=> (%f, %f)",
			avg_waiting, avg_turnaround);
}
