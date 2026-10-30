#include "header.h"

void	swap_nodes(t_request *a, t_request *b)
{
	t_request	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	heap_push(t_heap *heap, t_request req)
{
	int	i;

	if (heap->size == heap->capacity)
		return ;
	i = heap->size;
	heap->data[i] = req;
	heap->size++;
	while (i > 0 && compare_requests(heap->data[i], heap->data[(i - 1) / 2]))
	{
		swap_nodes(&heap->data[(i - 1) / 2], &heap->data[i]);
		i = (i - 1) / 2;
	}

}

void	heapify_down(t_heap *heap, int i)
{
	int	smallest;
	int	left;
	int	right;

	while (1)
	{
		smallest = i;
		left = (2 * i) + 1;
		right = (2 * i) + 2;
		if (left < heap->size &&
			compare_requests(heap->data[left], heap->data[smallest]))
			smallest = left;
		if (right < heap->size &&
			compare_requests(heap->data[right], heap->data[smallest]))
			smallest = right;
		if (smallest == i)
			break;
		swap_nodes(&heap->data[smallest], &heap->data[i]);
		i = smallest;
	}

}

int	compare_requests(t_request a, t_request b)
{
	if (a.priority < b.priority 
		|| (a.priority == b.priority
			&& a.sequence < b.sequence))
		return (1);
	return (0);
}

void	set_priority(t_request *req, t_coder *coder, t_simulation *sim)
{
	if (sim->scheduler == EDF)
		req->priority = coder->last_compile_start
			+ sim->time_to_burnout;
	else
		req->priority = req->sequence;
}

void	enqueue_request(t_simulation *sim, t_coder *coder)
{
	t_request	req;

	pthread_mutex_lock(&sim->heap_mutex);

	req.coder_id = coder->id;
	req.sequence = sim->next_sequence;
	sim->next_sequence++;
	set_priority(&req, coder, sim);
	heap_push(&sim->heap, req);

	pthread_mutex_unlock(&sim->heap_mutex);
}

t_request	pop_root(t_heap *heap)
{
	t_request	root;

	root = heap->data[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->data[0] = heap->data[heap->size]:
		heapify_down(heap, 0);
	}
	return root;
}
