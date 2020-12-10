#include "macros.h"
#include "utils.h"
#include <stdio.h>
#include <stdbool.h>



void solve()
{
	int n; // size of the page array
	scan(n);
	int nf_occupied = 0;
	int nf_hits = 0;

	int arr[n];
	fill(arr, n, -1);
	int last_used_times[n];

	int reference_string_size;
	scan(reference_string_size);
	int reference_string[reference_string_size];
	read_array(reference_string, reference_string_size);

	for(int t = 0; t < reference_string_size; ++t)
	{
		int key = reference_string[t];

		int pos = find(arr, n, key);
		if (pos != -1)
		{
			nf_hits ++;
			last_used_times[pos] = t;
		}
		else if (nf_occupied != n)
		{
			arr[nf_occupied] = key;
			last_used_times[nf_occupied] = t;
			nf_occupied ++;

		}
		else
		{
			int loc = location_of_min(last_used_times, n);
			arr[loc] = key;
			last_used_times[loc] = t;
		}
		ps(key); 
		(pos != -1)? printf("Hit\t"): printf("Miss\t");
		print_array(arr, n);
	}

	int nf_faults = reference_string_size - nf_hits;
	printf("No. of hits 	= %d\n", nf_hits);
	printf("No. of faults 	= %d\n", nf_faults);
	printf("Fault rate	 	= %.2f %%\n", (nf_faults * 100.0) / reference_string_size); 

}

void main(int argc, char const *argv[])
{
	solve();
}

/*
In:
3
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

Out:
7 Miss	7 -1 -1 
0 Miss	7 0 -1 
1 Miss	7 0 1 
2 Miss	2 0 1 
0 Hit	2 0 1 
3 Miss	2 0 3 
0 Hit	2 0 3 
4 Miss	4 0 3 
2 Miss	4 0 2 
3 Miss	4 3 2 
0 Miss	0 3 2 
3 Hit	0 3 2 
2 Hit	0 3 2 
1 Miss	1 3 2 
2 Hit	1 3 2 
0 Miss	1 0 2 
1 Hit	1 0 2 
7 Miss	1 0 7 
0 Hit	1 0 7 
1 Hit	1 0 7 
No. of hits 	= 8
No. of faults 	= 12
Fault rate	 	= 60.00 %
*/





















