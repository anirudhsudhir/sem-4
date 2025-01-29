#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_process_lineage(pid_t pid) {
  pid_t ppid = getppid(); // Get parent PID
  printf("Process Lineage (from child process to root):\n");

  // Print the lineage of the child process
  printf("PID: %d\n", pid);

  while (ppid != pid && ppid != 1) { // Traverse until the root (init/systemd)
    printf("Parent PID: %d\n", ppid);
    pid = ppid;       // Move to the parent
    ppid = getppid(); // Get the parent's parent
  }

  if (ppid == 1) { // If we reached root (init/systemd)
    printf("Root process PID (init/systemd): %d\n", ppid);
  }
}

int main() {
  pid_t pid = getpid();     // Get current process PID
  pid_t child_pid = fork(); // Create a child process

  if (child_pid == 0) {
    // In the child process
    printf("Child process started\n");
    print_process_lineage(getpid()); // Trace child's lineage
    exit(0);                         // Exit child process
  } else if (child_pid > 0) {
    // In the parent process
    printf("Parent process started\n");
    // Optionally print parent lineage too (e.g., trace the parent of the child)
    print_process_lineage(getpid()); // Trace parent process lineage
  } else {
    // If fork fails
    perror("fork failed");
    exit(1);
  }

  return 0;
}
