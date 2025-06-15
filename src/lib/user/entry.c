#include <syscall.h>

// This is compiled into the final user program
int main (int, char *[]);
void _start (int argc, char *argv[]);

void
_start (int argc, char *argv[]) 
{
  exit (main (argc, argv));
}
