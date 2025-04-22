#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void simulate_grep(char* str, char* source){
    pid_t p = fork();
    pid_t cpid;

    if(p < 0){
        printf("Unsuccessful fork\n");
        exit(1);
    } else if(p == 0){
        printf("Child process (GREP) created with PID: %d, PPID: %d\n", getpid(), getppid());
        execlp("./grepNew", "./grepNew", str, source, NULL);
        perror("execlp failed"); // show error if execlp fails
        exit(1);
    } else {
        cpid = wait(NULL);
        printf("Parent process (GREP finished)\n");
    }
}

void simulate_cp(char* source, char* destination){
    pid_t p = fork();
    pid_t cpid;

    if(p < 0){
        printf("Unsuccessful fork\n");
        exit(1);
    } else if(p == 0){
        printf("Child process (COPY) created with PID: %d, PPID: %d\n", getpid(), getppid());
        execlp("./copyCommand", "./copyCommand", source, destination, NULL);
        perror("execlp failed"); // show error if execlp fails
        exit(1);
    } else {
        cpid = wait(NULL);
        printf("Parent process (COPY finished)\n");
    }
}

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Usage:\n");
        printf("For copy: ./a.out cp source.txt destination.txt\n");
        printf("For grep: ./a.out grep word_to_search filename.txt\n");
        return 1;
    }

    char *command = argv[1];

    if(strcmp(command, "cp") == 0){
        simulate_cp(argv[2], argv[3]);
    }
    else if(strcmp(command, "grep") == 0){
        simulate_grep(argv[2], argv[3]);
    }
    else {
        printf("Invalid command. Use 'cp' or 'grep'.\n");
    }

    return 0;
}
