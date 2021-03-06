#include "threads.h"

Thread t1, t2;

int gn()
{
  int j;
  while(1)
  for (j = 0; j < 5; j++)
  {
    printf("GN -> %d\n", j);
    sleep(1);
    //thread_yield();
  }
}

int fn() {

  int i;
  while(1)
  for (i = 15; i > 0; i--)
  {
    printf("FN -> %d\n", i);
    sleep(1);
    //thread_yield();
  }
}

int main(int argc) {
  thread_pool_init();

  thread_init(&t1, &fn);
  thread_init(&t2, &gn);

  thread_pool_wait();

  //context_switch(t3.regs, t2.regs);

  //switch_control();

  //store_regs(&t1);
  //restore_regs(&t1);
  //pop_stack(&a, &b);
  //test_store_regs();

  return 0;
}