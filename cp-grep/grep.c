#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grepFun(char *source, char *str) {
    FILE *src = fopen(source, "r");
    if (src == NULL) {
        printf("Input file is not accessible.\n");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;
    int cnt = 0;

    while ((read = getline(&line, &len, src)) != -1) {
        // Check if the line contains the string 'str'
        if (strstr(line, str) != NULL) {
            cnt++;
        }
    }

    printf("Number of matching lines: %d\n", cnt);

    free(line);  
    fclose(src);
}

int main(int argc, char *argv[]) {
    // if (argc != 5) {
    //     printf("Insufficient number of arguments\n");
    //     return 1;
    // }
    char *str = argv[1];
    
    grepFun(argv[2], str);

    return 0;
}
