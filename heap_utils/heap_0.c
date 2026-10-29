#include "heap.h"

/*
 * 	Function that swap two integers
 */
void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
 *	Create Heap function givent the capacity
 */
Heap	*createHeap(int capacity)
{
	Heap	*heap;

	heap = (Heap *)malloc(sizeof(Heap));
	if (!heap)
		return NULL;
	heap->size = 0;
	heap->capacity = capacity;
	heap->array = (int *)malloc(capacity * sizeof(int));
	if (!heap->array)
	{
		free(heap);
		return NULL;
	}
	return heap;
}

/*
 *	Function that heapify the node at index i
 */
void	heapify(Heap *heap, int i)
{
	int	largest;
	int	left;
	int	right;

	largest = i;
	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		if (left < heap->size && heap->array[left] > heap->array[largest])
			largest = left;
		if (right < heap->size && heap->array[right] > heap->array[largest])
			largest = right;
		if (largest == i)
			break;
		swap(&heap->array[i], &heap->array[largest]);
		i = largest;
	}
}

/*
 * 	Function that build a maxheap from an existing array
 */
void	buildHeap(Heap *heap)
{
	int	n;
	int	i;

	n = heap->size;
	i = (n / 2) - 1;
	while (i >= 0)
	{
		heapify(heap, i);
		i--;
	}
}

/*
 *	Function to increase the valure at given index
 *
*/
void	increasekey(Heap *heap, int index, int new_value)
{
	if (index >= heap->size || heap->array[index] >= new_value)
		return ;
	heap->array[index] = new_value;
	while (index != 0 && heap->array[(index - 1) / 2] < heap->array[index])
	{
		swap(&heap->array[(index - 1) / 2], &heap->array[index]);
		index = (index - 1) / 2;
	}
}

