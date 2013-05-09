#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/mman.h>

#define TICS_PER_SEC  500
#define uS_INTERVAL 1000000/TICS_PER_SEC

#define THREAD_STACK_MARGIN 128

typedef struct Thread Thread;
typedef Thread* ThreadPtr;
typedef struct ThreadPool ThreadPool;
typedef long long int int64;

enum ThreadState { THREAD_NEW, THREAD_RUNNING, THREAD_FINISHED };

struct Thread {
  int64 regs[16];

  int64 *stack;
  int stack_size;

  enum ThreadState state;
  // Keep stack bottom in order to free stack memory when thread is destroyed
  char *stack_bottom;
};

void thread_pool_init();
void thread_pool_wait();

int context_switch(long long int *regs_to_save, long long int *regs_to_restore);

void thread_init(Thread *t, int (*thread_fn)());
void thread_yield();
