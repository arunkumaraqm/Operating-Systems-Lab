#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
using namespace std;


template <typename T>
void print_container(vector<T> v)
{
	for(auto& ele: v)
	{
		cout << ele << ' ';
	}
	cout << endl;
}

void read_data(uint& nf, vector<uint>& arr)
{
	cin >> nf;
	arr.resize(nf);
	for(auto& ele: arr) cin >> ele;
}

struct ContiguousMemoryManagement
{
	uint nf_partitions, nf_processes;
	vector<uint> partition_sizes, memory_reqs_of_processes, hole_sizes;
//	vector<size_t> cannot_be_allocated;

	void read()
	{
		read_data(nf_partitions, partition_sizes);
		read_data(nf_processes, memory_reqs_of_processes);
	}

	void first_fit();

};

void ContiguousMemoryManagement:: first_fit()
{
	// setup
	hole_sizes = partition_sizes;

	for (auto i_memory_req: memory_reqs_of_processes)
	{
		bool allocated = false;

		auto idx = 0;
		for (auto& j_hole_size: hole_sizes)
		{
			if (i_memory_req <= j_hole_size)
			{
				j_hole_size -= i_memory_req;
				allocated = true;
				break;
			}
			idx++;
		}
		if (not allocated)
		{
			cout << i_memory_req << " process cannot be placed into main memory" << endl;
		}
		else
		{
			cout << i_memory_req << " process is placed in "<< partition_sizes[idx] << endl;
		}
	}
}


int main()
{
	Test();
}