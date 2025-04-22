#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Enter the correct number of arguments\n");
        return 1;
    }

    int pipe_fd[2];
    int fork_result;
    char* source_file = argv[1];
    char* destination_file = argv[2];
    int source_fd;
    int dest_fd;

    // Open the source file for reading
    FILE* source_fp = fopen(source_file, "r");
    if(source_fd == -1) {
        printf("Unable to open source file: %s\n", source_file);
        return 1;
    } else {
        dup2(source_fd, STDIN_FILENO); // Redirect stdin to the source file
        close(source_fd);
    }

    // Create a pipe
    pipe(pipe_fd);
    
    // Fork the process
    fork_result = fork();
    if(fork_result > 0) { // Parent process
        // Redirect stdout to the pipe's write end
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        
        // Execute the 'sort' command
        execl("/usr/bin/sort", "sort", NULL);
        perror("execl failed for sort");
    }
    else if(fork_result == 0) { // Child process
        // Redirect stdin to the pipe's read end
        dup2(pipe_fd[0], STDIN_FILENO);
        
        // Open the destination file for writing
        dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(dest_fd == -1) {
            printf("Unable to open destination file: %s\n", destination_file);
            return 1;
        } else {
            // Redirect stdout to the destination file
            dup2(dest_fd, STDOUT_FILENO);
            close(dest_fd);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            
            // Execute the 'uniq' command
            execl("/usr/bin/uniq", "uniq", NULL);
            perror("execl failed for uniq");
        }
    } else {
        perror("Fork failed!!!");
        return 1;
    }

    return 0;
}