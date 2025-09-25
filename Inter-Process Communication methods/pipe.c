#include <stdio.h>      // For printf()
#include <unistd.h>     // For pipe(), fork(), read(), write()
#include <stdlib.h>     // For exit()

int main() {
    int fd[2]; // Array to hold two ends of the pipe
    char buffer[50]; // Buffer to read data
    
    // Step 1: Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }
    
    // Step 2: Create a child process
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    
    if (pid == 0) {  
        // Child process
        
        // Close the write end (child only reads)
        close(fd[1]);
        
        // Read from the pipe
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        
        // Close the read end
        close(fd[0]);
        
    } else {  
        // Parent process
        
        // Close the read end (parent only writes)
        close(fd[0]);
        
        // Write to the pipe
        char msg[] = "Hello from parent!";
        write(fd[1], msg, sizeof(msg));
        
        // Close the write end
        close(fd[1]);
    }
    
    return 0;
}

