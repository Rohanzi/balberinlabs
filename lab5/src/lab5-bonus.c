/* Работа двух нитей исполнения.
Каждая нить исполнения просто увеличивает на 1 разделяемую 
переменную a. */ 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int a = 0; 
/* 1. Переменная a является глобальной статической для всей 
программы, поэтому она будет разделяться обеими нитями 
исполнения.
   2. Ниже следует текст функции, которая будет 
ассоциирована со 2-ой thread'ой.
   3. Параметр dummy в нашей функции не используется и 
присутствует только для совместимости типов данных. По той
же причине функция возвращает значение void *, хотя
это никак не используется в программе.*/
void *mythread(void *dummy)
{
    pthread_t mythid; /* Для идентификатора нити исполнения */
                      /* Заметим, что переменная mythid является 
                         динамической локальной переменной функции mythread(), 
                         т.е. помещается в стеке и, следовательно, не разделяется
                         нитями исполнения. */
                      /* Запрашиваем идентификатор thread'а */
    mythid = pthread_self();
    a = a+1;
    printf("Thread %d, Calculation result = %d\n", (int)mythid, a);
    return NULL;
}
/* Функция main() – она же ассоциированная функция главного thread'а */
int main(int argc, const char * argv[], const char *envp[])
{
    printf("Enviroment variables\n");
    for (int i=0; envp[i]; i++) {
        printf("%d %s\n", i, envp[i]);
    }
    printf("CLI arguments \n");
    for (int i=0; i<argc; i++) {
        printf("%d %s\n", i, argv[i]);
    }
        //файловые дескрипторы
    int filedesc = open("lab5", O_RDONLY);
    int filedesccopy = open("lab5copy", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IXUSR | S_IWUSR | S_IRGRP | S_IXGRP | S_IXOTH);
        //размер файла
    struct stat st;
    fstat(filedesc, &st);
    size_t size = st.st_size;
    printf("Size: %d", (int)size);
    char *data;
    data = (char *)malloc(size);
        //копируем + напишем в стандартный вывод 16 байтов
    read(filedesc, data, size);
    write(filedesccopy, data, size);
    write(1, data, 16);
        //закрываем файловые дескрипторы
    close(filedesc);
    close(filedesccopy);
    
    pid_t childpid = fork();
    if(childpid == 0)
    {
        char *str1;
        pthread_t thid, mythid;
        int result;
        result = pthread_create( &thid,(pthread_attr_t *)NULL, mythread, NULL);
        /* Пытаемся создать новую нить исполнения,
         ассоциированную с функцией mythread(). Передаем ей
         в качестве параметра значение NULL. В случае удачи в
         переменную thid занесется идентификатор нового thread'а.
         Если возникнет ошибка, то прекратим работу. */
        if(result != 0){
            printf ("Error on thread create,return value = %d\n", result);
            exit(-1);
        }
        printf("Thread created, thid = %d\n", (int)thid);
        /* Запрашиваем идентификатор главного thread'а */
        mythid = pthread_self();
        a = a+1;
        printf("Thread %d, Calculation result = %d\n",(int)mythid, a);
        /* Ожидаем завершения порожденного thread'a, не
         интересуясь, какое значение он нам вернет. Если не
         выполнить вызов этой функции, то возможна ситуация,
         когда мы завершим функцию main() до того, как выполнится
         порожденный thread, что автоматически повлечет за
         собой его завершение, исказив результаты. */
        pthread_join(thid, (void **)NULL);
        sprintf(str1, "%d", a);
        //Проверяем что результаты не исказились
        execl("/bin/echo", "/bin/echo", "result: ", str1, (char *) 0);
        /* exec загружается в память вместо потока программы, 
         потому все что после него мы не увидим */
        printf("This won't be seen");
                }
                else
                {
                    /* но тем не менее простой fork позволяет
                     продолжать выполнение программы */
                    execl("/bin/sh", "sh", "-c", "date", (char *) 0);
                }
                return 0;
                }
