#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define DEMO 
typedef char String[32];
#define TOTAL_SIZE_KiB (64)
#define BLOCK_SIZE_KiB (1)
#define MAX_FILES (64) // (TOTAL_SIZE_KiB / BLOCK_SIZE_KiB) // 64 index blocks; each file 0 KiB
#define MAX_BLOCKS (64) // (TOTAL_SIZE_KiB / BLOCK_SIZE_KiB) 

#ifdef DEMO
    #define prompt printf
#else
    #define prompt
#endif

typedef struct Block
{
	bool occupied;
	int* arr; 
	int arr_size;
	// occupied = true and arr = NULL means block is used for storage
	// occupied = true and arr != NULL means block is used as index block
}Block;

Block disk[MAX_BLOCKS];
int nf_occupied_blocks = 0;

void print_disk()
{
	if (!nf_occupied_blocks)
	{
		printf("Out of %d blocks, none are occupied. \n", MAX_BLOCKS);
		return;
	}
	printf("Out of %d blocks, these are occupied: \n", MAX_BLOCKS);
	for (int i = 0; i < MAX_BLOCKS; ++i)
	{
		if (disk[i].occupied)
			printf("%d ", i);
	}
	printf("\n");
}

int find_first_unoccupied_block(int start)
{
	for (int i = start; i < MAX_BLOCKS; ++i)
	{
		if (disk[i].occupied == false)
		{
			return i;
		}
	}
	for (int i = 0; i < start; ++i)
	{
		if (disk[i].occupied == false)
		{
			return i;
		}
	}
	return -1;
}

typedef struct File
{
	String name;
	int size_KiB;
	Block* index_block;
}File;

typedef struct Directory
{
	File* files;
	int nf_files;
}Directory;

void initialize_dir(Directory* dir)
{
	dir->files = calloc(sizeof(File), MAX_FILES);
	dir->nf_files = 0;
}

void destroy_dir(Directory* dir)
{
	free(dir->files);
}

void add_file(Directory* dir)
{
	File new_file;
	prompt("File name and file size: ");
	scanf("%s %d", new_file.name, &new_file.size_KiB);
	int nf_storage_blocks = ceil(new_file.size_KiB / (BLOCK_SIZE_KiB * 1.0));
	if (nf_storage_blocks + 1 > MAX_BLOCKS - nf_occupied_blocks)
	{
		printf("Not enough disk space.\n");
		return;
	}

	int index_block_no = find_first_unoccupied_block(rand() % MAX_BLOCKS);
	printf("Index block at position %d.\n", index_block_no);
	if (index_block_no == -1) // Shouldn't reach here
	{
		printf("No unoccupied blocks for index.\n");
		return;
	}

	new_file.index_block = &disk[index_block_no];
	new_file.index_block->occupied = true;
	nf_occupied_blocks ++;
	
	new_file.index_block->arr = calloc(sizeof(int), MAX_BLOCKS);
	new_file.index_block->arr_size = 0;

	for (int i = 0; i < nf_storage_blocks; ++i)
	{
		int block_no = find_first_unoccupied_block(rand() % MAX_BLOCKS);
		if (block_no == -1) // Shouldn't reach here
		{
			printf("No unoccupied blocks for storage.\n");
			return;
		}
		printf("Block %d at position %d.\n", i, block_no);

		disk[block_no].occupied = true;
		nf_occupied_blocks ++;
		new_file.index_block->arr[new_file.index_block->arr_size ++] = block_no;
	}


	dir->files[dir->nf_files++] = new_file;
}

void seek_file(Directory* dir)
{
	String item; int block_no;
	// prompt("File name; block no. to seek: ")
	scanf("%s %d", item, &block_no);

	int position = -1;
	for (int i = 0; i < dir->nf_files; ++i)
	{
		if (strcmp(dir->files[i].name, item) == 0)
		{
			position = i;
			break;
		}
	}
	if (position == -1)
	{
		printf("File not found.\n");
		return;
	}

	File* file = &dir->files[position];
	if (block_no < file->index_block->arr_size)
	{
		int block_no_on_disk = file->index_block->arr[block_no];
		printf("The block no. on disk is %d.\n", block_no_on_disk);
	}
	else
	{
		printf("File does not have block %d.\n", block_no);
	}
}

void delete_file(Directory* dir)
{
	String item;
	// prompt("File name: ");
	scanf("%s", item);

	int position = -1;
	for (int i = 0; i < dir->nf_files; ++i)
	{
		if (strcmp(dir->files[i].name, item) == 0)
		{
			position = i;
			break;
		}
	}
	if (position == -1)
	{
		printf("File not found.\n");
		return;
	}

	File* file = &dir->files[position];
	for (int i = 0; i < file->index_block->arr_size; ++i)
	{
		disk[file->index_block->arr[i]].occupied = false;
		nf_occupied_blocks --;
	}

	file->index_block->occupied = false;
	nf_occupied_blocks --;
	file->index_block->arr = NULL;
	file->index_block->arr_size = 0;

	for (int i = position; i < MAX_FILES - 1; ++i)
	{
		dir->files[i] = dir->files[i + 1];
	}
	dir->nf_files --;
}

void list_files(Directory* dir)
{
	bool nonempty = false;
	for(int i = 0; i < dir->nf_files; ++i)
	{
		nonempty = true;
		printf("%s\n", dir->files[i].name);
	}
	if (!nonempty)
	{
		printf("Empty Directory.\n");
	}
}

int main(int argc, char const *argv[])
{
	Directory dir;
	initialize_dir(&dir);
	String command;
	do
	{
		prompt(">>> ");
		scanf("%s", command);
		
		if (strcmp(command, "add") == 0) add_file(&dir);
		else if (strcmp(command, "del") == 0) delete_file(&dir);
		else if (strcmp(command, "list") == 0) list_files(&dir);
		else if (strcmp(command, "seek") == 0) seek_file(&dir);
		else if (strcmp(command, "disk") == 0) print_disk();
		else break;

		printf("\n");
	}
	while(true);

	destroy_dir(&dir);

	return 0;
}

