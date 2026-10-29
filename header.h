# ifndef FT_CODEXION
# define FT_CODEXION

#include<limits.h>
#include<stdlib.h>
#include<pthreads.h>

typedef	enum	e_scheduler
{
	FIFO,
	EDF
}		t_scheduler;

typedef	struct	s_simulation
{
	int		n_coders;
	long long 	time_to_burnout;
	long long	time_to_compile;
	long long	time_to_debug;
	long long	time_to_refactor;
	int		n_compiles_required;
	long long	dongle_cooldown;
	t_scheduler	scheduler;

	long long	start_time;
	long long	next_sequence;
	int		stopped;

	t_heap		heap;

	pthread_mutex_t	sequence_mutext;
	pthread_mutex_t	heap_mutext;
	pthread_mutex_t	print_mutext;
	pthread_mutex_t	state_mutext;

	pthread_t	monitor;
	struct s_coder	*coders;
	struct s_dongle	*dongle;

}		t_simulation;

typedef struct		s_request
{
	int		coder;
	long long	priority;
	long long	sequence;
}			t_request;

typedef struct		s_heap
{
	t_request	*data;
	int		size;
	int		capacity;
}			t_heap;

typedef struct		s_coder
{
	int		id;
	pthread_t	thread;
	long long	last_compile_start;
	int		compile_count;
}			t_coder;

void	swap(int *a, int *b);
t_heap	*create_heap(int capacity);
void	heapify(t_heap *heap, int i);
void	build_heap(t_heap *heap);
void	increasekey(t_heap *heap, int index, int new_value);
void	insertHeap(t_heap *heap, int value);
int	extract_root(t_heap *heap);
void	deletekey(t_heap *heap, int index);

# endif
