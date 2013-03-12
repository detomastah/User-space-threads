#include "threads.h"

void thread_finished();

static  ThreadPtr *threads;
static int current_thread;
static int thread_count;

static Thread  main_thread;

int in_scheduler = 0;

void thread_pool_add(ThreadPtr t);

void thread_init(Thread *t, int (*thread_fn)())
{
  t->state = THREAD_NEW;
  t->stack_size = 8192;
  t->stack_bottom = mmap (NULL, t->stack_size + THREAD_STACK_MARGIN, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
  if (t->stack_bottom == MAP_FAILED)
  {
    puts("Cannot allocate stack");
    exit(0);
  }
  memset (t->stack_bottom, '\0', t->stack_size);
  memset (t->regs, '\0', sizeof(long long int) * 16);

  t->stack = (int64*) (t->stack_bottom + t->stack_size);

  if (thread_fn)
  {
    // Return immediately to thread function
    t->stack[0] = (int64) thread_fn;
    // When thread function finishes return to handler
    t->stack[+1] = (int64) &thread_finished;
    // Set stack registers
    t->regs[4] = t->regs[5] = (int64) t->stack;
  }

  thread_pool_add(t);
}

void thread_finished() {
  threads[current_thread]->state = THREAD_FINISHED;
  thread_yield();
}

void thread_pool_init()
{
  current_thread = 0;
  threads = NULL;
}

void thread_pool_add(ThreadPtr t)
{
  thread_count++;
  current_thread++;
  threads = realloc(threads, sizeof(ThreadPtr) * (thread_count - 1));
  threads[thread_count - 1] = t;
}

void thread_pool_wait()
{
  current_thread = 0;
  context_switch(&main_thread.regs,
       threads[current_thread]->regs);
  puts("All threads finished");
}

int find_next_thread(int current_thread)
{
  int next_thread = current_thread + 1;
  int counter = thread_count;

  while (counter)
  {
    if (next_thread >= thread_count)
      next_thread = 0;

    if (threads[next_thread]->state != THREAD_FINISHED)
      return next_thread;

    next_thread++;
    counter--;
  }

  return -1;
}

void thread_yield()
{
  int next_thread = find_next_thread(current_thread);
  int previous_thread = current_thread;

  //printf("PREV: %d NEXT THREAD: %d\n", previous_thread, next_thread);

  current_thread = next_thread;

  if (next_thread == -1)
  {
    context_switch(threads[previous_thread]->regs,
        &main_thread.regs);
  }
  else if (next_thread == previous_thread)
  {
  }
  else
  {
    context_switch(threads[previous_thread]->regs,
        threads[next_thread]->regs);
  }
}


