#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

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
  if (!is_user_vaddr(esp) || !pagedir_get_page(thread_current()->pagedir, esp)) {
    thread_current()->exit_block->exit_status = -1;
    thread_exit();
  }
  int sys_no = *((int*)esp);
  switch (sys_no) {
    // void halt (void) NO_RETURN;
    case SYS_HALT: {
      thread_exit();
    }
  
    // void exit (int status) NO_RETURN;
    case SYS_EXIT: {
      struct thread* t = thread_current();
      t->exit_block->exit_status = *((int*)(esp + 4));
      thread_exit();
    }

    // pid_t exec (const char *file);
    case SYS_EXEC: {
      char * file = *((char**)(esp + 4));
      break;
    }
    
    // int wait (pid_t);
    case SYS_WAIT: {
      break;
    }

    // bool create (const char *file, unsigned initial_size);
    case SYS_CREATE: {
      break;
    }

    // bool remove (const char *file);
    case SYS_REMOVE: {
      break;
    }

    // int open (const char *file);
    case SYS_OPEN: {

    }

    // int filesize (int fd);
    case SYS_FILESIZE: {
      break;
    }

    // int read (int fd, void *buffer, unsigned length);
    case SYS_READ: {
      break;
    }

    // int write (int fd, const void *buffer, unsigned length);
    case SYS_WRITE: {
      int fd = *((int*)(esp + 4));
      if (fd == 1) {
        char * buffer = *((char**)(esp + 8));
        int length = *((int*)(esp + 12));
        putbuf(buffer, length);
      }
      break;
    }

    // void seek (int fd, unsigned position);
    case SYS_SEEK: {
      break;
    }

    // unsigned tell (int fd);
    case SYS_TELL: {
      break;
    }

    // void close (int fd);
    case SYS_CLOSE: {break;}

    /** Project 3 and optionally project 4. */
    // mapid_t mmap (int fd, void *addr);
    case SYS_MMAP: {break;}
    // void munmap (mapid_t);
    case SYS_MUNMAP: {break;}

    /** Project 4 only. */
    // bool chdir (const char *dir);
    case SYS_CHDIR: {break;}
    // bool mkdir (const char *dir);
    case SYS_MKDIR: {break;}
    // bool readdir (int fd, char name[READDIR_MAX_LEN + 1]);
    case SYS_READDIR: {break;}
    // bool isdir (int fd);
    case SYS_ISDIR: {break;}
    // int inumber (int fd);
    case SYS_INUMBER: {break;}

    // unknown bad sys_no
    default:{
      thread_current()->exit_block->exit_status = -1;
      thread_exit();
    }
  }
}
