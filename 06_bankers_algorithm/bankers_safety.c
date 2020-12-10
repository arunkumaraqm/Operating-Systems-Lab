#include <stdio.h> 
#include <stdbool.h> // for bool datatype
#include <assert.h> // for assert
#include <string.h> // for memset

void read_data(
	int nf_processes, 
	int nf_resources,
	int max_mat[nf_processes][nf_resources],
	int allocated_mat[nf_processes][nf_resources],
	int need_mat[nf_processes][nf_resources],
	int total_nf_instances[nf_resources], 
	int nf_free_instances[nf_resources]
	)
{
	for (int rs = 0; rs < nf_resources; ++rs)
	{
		scanf("%d", &total_nf_instances[rs]);
		nf_free_instances[rs] = total_nf_instances[rs];
	}

	// reading max_mat and allocated_mat
	for (int pr = 0; pr < nf_processes; ++pr)
	{
		for (int rs = 0; rs < nf_resources; ++rs)
		{
			scanf("%d", &max_mat[pr][rs]);
			assert(max_mat[pr][rs] <= total_nf_instances[rs]);
		}
		for (int rs = 0; rs < nf_resources; ++rs)
		{
			scanf("%d", &allocated_mat[pr][rs]);
			assert(allocated_mat[pr][rs] <= max_mat[pr][rs]);
			
			need_mat[pr][rs] = max_mat[pr][rs] - allocated_mat[pr][rs];
		}
	}

	// make sure sum of allocated instances per resource doesn't exceed total available
	// also calculate nf_free_instances
	for (int rs = 0; rs < nf_resources; ++rs)	
	{
		int cumulative = 0;
		for (int pr = 0; pr < nf_processes; ++pr)
		{
			cumulative += allocated_mat[pr][rs];
		}
		assert(cumulative <= total_nf_instances[rs]);
		nf_free_instances[rs] = total_nf_instances[rs] - cumulative;
	}
}

bool bankers_safety(
	int nf_processes, 
	int nf_resources,
	int max_mat[nf_processes][nf_resources],
	int allocated_mat[nf_processes][nf_resources],
	int need_mat[nf_processes][nf_resources],
	int total_nf_instances[nf_resources], 
	int nf_free_instances[nf_resources],
	int safe_sequence[nf_processes]
	)
{
	bool done[nf_processes];
	memset(done, 0, nf_processes * sizeof(*done));
	int nf_done_processes = 0;
	bool is_safe_state = true;
	int idx_safe_sequence = 0;

	while (nf_done_processes < nf_processes)
	{
		int pr;
		for (pr = 0; pr < nf_processes; ++pr)
		{
			if (done[pr]) continue;

			bool sufficient = true;
			for (int rs = 0; rs < nf_resources; ++rs)
			{
				sufficient = sufficient && (nf_free_instances[rs] >= need_mat[pr][rs]);
			}
			if (sufficient)
			{
				done[pr] = true;
				nf_done_processes ++;
				safe_sequence[idx_safe_sequence++] = pr;
				break;
			}
		}
		// if loop runs fully
		// ie if nf_free_instances is not sufficient to satisy need of any process
		if (pr == nf_processes)
		{
			is_safe_state = false;
			break;
		}

		for (int rs = 0; rs < nf_resources; ++rs)
		{
			nf_free_instances[rs] += allocated_mat[pr][rs];
		}
	}

	return is_safe_state;
}
int main(int argc, char const *argv[])
{
	int nf_processes, nf_resources;
	scanf("%d %d", &nf_processes, &nf_resources);

	int max_mat[nf_processes][nf_resources];
	int allocated_mat[nf_processes][nf_resources];
	int need_mat[nf_processes][nf_resources];
	int total_nf_instances[nf_resources], nf_free_instances[nf_resources];
	memset(total_nf_instances, 0, nf_resources * sizeof(*total_nf_instances));
	memset(nf_free_instances, 0, nf_resources * sizeof(*nf_free_instances));
	
	int safe_sequence[nf_processes]; 

	read_data(
		nf_processes, 
		nf_resources,
		max_mat,
		allocated_mat,
		need_mat,
		total_nf_instances, 
		nf_free_instances
		);

	bool is_safe_state = bankers_safety(
		nf_processes, 
		nf_resources,
		max_mat,
		allocated_mat,
		need_mat,
		total_nf_instances, 
		nf_free_instances,
		safe_sequence
		);

	if (is_safe_state)
	{
		for (int pr = 0; pr < nf_processes; ++pr)
		{
			printf("%d, ", safe_sequence[pr]);
		}
		printf("\n");
	}
	else
	{
		printf("Unsafe state.\n");
	}


	return 0;
}