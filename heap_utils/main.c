#include "heap.h"
#include<stdio.h>


void	printheap(Heap *heap)
{
	int	i;

	i = 0;
	if (heap->size == 0)
	{
		printf("No heap.\n");
		return ;
	}
	while (i < heap->size)
	{
		printf("%d ", heap->array[i]);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	Heap	*heap;

	heap = createHeap(10);
	insertHeap(heap, 900);
	insertHeap(heap, 1020);
	insertHeap(heap, 1150);
	//insertHeap(heap, 3);
	//insertHeap(heap, 1);
	//insertHeap(heap, 8);
	//insertHeap(heap, 7);
	printheap(heap);
	printf("Deleting 4: \n");
	deletekey(heap, 4);
	printheap(heap);
	printf("Extracting max: %d\n", extract_root(heap));
	printf("Heap after extraction:\n");
	printheap(heap);
	free(heap->array);
	free(heap);
	return (0);
}
