#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

// need to add something here to extract from the stack (esp) of the intr_frame
static void
syscall_handler (struct intr_frame *f) 
{
  // retrieve the syscall number
  void * esp = f->esp;
  // how to I know the sys_no(arg_0) is at the top of esp
  int sys_no = *((int*)esp);
  switch (sys_no) {
    case 0: {
      break;
    }
    // void exit (int status) NO_RETURN;
    case 1: {
      struct thread* t = thread_current();
      t->exit_block->exit_status = *((int*)(esp + 4));
      thread_exit();
    }

    // int write (int fd, const void *buffer, unsigned length);
    case 9: {
      int fd = *((int*)(esp + 4));
      char * buffer = *((char**)(esp + 8));
      int length = *((int*)(esp + 12));
      putbuf(buffer, length);
    }
  }
}
