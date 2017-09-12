#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, const char * argv[], const char *envp[])
{
    char data[8000];
    strcat(data, "CLI arguments\n" );
    for (int i=0; i<argc; i++) {
        strcat(data, argv[i]);
        strcat(data, "\n");
    }
    strcat(data, "Enviroment variables\n" );
    for (int i=0; envp[i]; i++) {
        strcat(data, envp[i]);
        strcat(data, "\n");
        
    }
        //файловые дескрипторы
    int filedesc = open("lab5.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IXUSR | S_IWUSR | S_IRGRP | S_IXGRP | S_IXOTH);
    write(filedesc, data, strlen(data));
    close(filedesc);
    
}
