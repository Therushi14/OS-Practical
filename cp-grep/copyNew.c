#include <stdio.h>
#include<stdlib.h>

void copy_file(char* source,char* destination){
    FILE *src = fopen(source,"r");
    if(src == NULL){
        printf("No content in source file\n");
        fclose(src);
        return;
    }
    FILE *dest = fopen(destination,"w");

    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);  // Write the character to destination file
    }
    fclose(src);
    fclose(dest);
    return;
}   

int main(int argc, char *argv[]){
    //return argc;
    // if(argc!=3){
    //     printf("Inappropriate number of arguments");
    // }
    copy_file(argv[1],argv[2]);
    printf("source to destination copying done\n");
    return 0;
}
