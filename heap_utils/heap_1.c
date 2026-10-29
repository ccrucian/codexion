#include "heap.h"

/*
 * 	Insert a new valueinto the heap. Added at first at the end,
 * 	then put it in the right place.
 */
void	insertHeap(Heap *heap, int value)
{
	int	i;

	if (heap->size == heap->capacity)
		return ;
	i = heap->size;
	heap->array[i] = value;
	heap->size++;
	while (i && heap->array[(i - 1) / 2] < heap->array[i])
	{
		swap(&heap->array[(i - 1) / 2], &heap->array[i]);
		i = (i - 1) / 2;
	}
}

/*
 *	Function to extract the root (maximum value) from the heap and
 *	return it.
 *
 */

int	extract_root(Heap *heap)
{
	int	root;

	if (heap->size <= 0)
		return INT_MIN;
	if (heap->size == 1)
	{
		heap->size--;
		return heap->array[0];
	}
	root = heap->array[0];
	heap->array[0] = heap->array[heap->size - 1];
	heap->size--;
	heapify(heap, 0);
	return root;
}

/*
 * 	Function to delete a value at given index
 */
void	deletekey(Heap *heap, int index)
{
	int	i;

	if (index >= heap->size)
		return ;
	if (index == heap->size - 1)
	{
		heap->size--;
		return ;
	}
	heap->array[index] = heap->array[heap->size - 1];
	heap->size--;
	i = index;
	if (i > 0 && heap->array[(i - 1) / 2] < heap->array[i])
	{
		while (i && heap->array[(i - 1) / 2] < heap->array[i])
		{
			swap(&heap->array[(i - 1) / 2], &heap->array[i]);
			i = (i - 1) / 2;
		}
	}
	else
		heapify(heap, index);
}
