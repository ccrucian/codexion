# ifndef FT_HEAP
# define FT_HEAP

#include<limits.h>
#include<stdlib.h>

typedef struct	s_request
{
	int		coder;
	long long	priority;
	long long	sequence;
}		t_request;

typedef struct	Heap
{
	int	*array;
	int	size;
	int	capacity;
}		Heap;

void	swap(int *a, int *b);
Heap	*createHeap(int capacity);
void	heapify(Heap *heap, int i);
void	buildHeap(Heap *heap);
void	increasekey(Heap *heap, int index, int new_value);
void	insertHeap(Heap *heap, int value);
int	extract_root(Heap *heap);
void	deletekey(Heap *heap, int index);

# endif
