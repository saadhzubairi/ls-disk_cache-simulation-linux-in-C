#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <dirent.h>

#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"

void ls()
{

    DIR *folder;
    struct dirent *entry;
    int files = 0;

    char *path = ".";
    folder = opendir(path);
    if (folder == NULL)
    {
        puts("Unable to read directory");
        return (1);
    }
    else
    {
        while (entry = readdir(folder))
        {
            files++;
            if (entry->d_type == 8)
            {
                printf(WHITE "%s ", entry->d_name);
            }
            else
            {
                if (strncmp(entry->d_name, ".", 1) != 0)
                {
                    printf(BLUE "%s ", entry->d_name);
                }
            }
        }
    }
    closedir(folder);
}
void ls_a()
{

    DIR *folder;
    struct dirent *entry;
    int files = 0;

    char *path = ".";
    folder = opendir(path);
    if (folder == NULL)
    {
        puts("Unable to read directory");
        return (1);
    }
    else
    {
        while (entry = readdir(folder))
        {
            files++;
            if (entry->d_type == 8)
            {
                printf(WHITE "%s ", entry->d_name);
            }
            else
            {
                printf(BLUE "%s ", entry->d_name);
            }
        }
    }
    closedir(folder);
    printf("\n");
}
void ls_l()
{

    DIR *folder;
    struct dirent *entry;
    int files = 0;

    char *path = ".";
    folder = opendir(path);
    printf("no.\tino\t\ttype\toffest\t\t\treclen\tname\n");
    if (folder == NULL)
    {
        puts("Unable to read directory");
        return (1);
    }
    else
    {
        while (entry = readdir(folder))
        {
            files++;
            printf("%d\t%lu\t\t%d\t%ld\t%d\t%s \n",
                   files,
                   entry->d_ino,
                   entry->d_type,
                   entry->d_off,
                   entry->d_reclen,
                   entry->d_name);
        }
    }
    closedir(folder);
    printf("\n");
}
void ls_r()
{
    DIR *folder;
    struct dirent *entry;
    int files = 0;
    char *path = ".";

    folder = opendir(path);
    if (folder == NULL)
    {
        puts("Unable to read directory");
        return (1);
    }
    else
    {
        while (entry = readdir(folder))
        {
            files++;
        }
    }
    closedir(folder);
    char array[files][30];
    files = 0;

    folder = opendir(path);
    if (folder == NULL)
    {
        puts("Unable to read directory");
        return (1);
    }
    else
    {
        while (entry = readdir(folder))
        {
            files++;
            strcpy(array[files], entry->d_name);
        }
    }
    closedir(folder);

    char temp[30];

    for (int i = 0; i < files; i++)
    {
        for (int j = 0; j < files - 1 - i; j++)
        {
            if (strcmp(array[j], array[j + 1]) > 0)
            {
                strcpy(temp, array[j]);
                strcpy(array[j], array[j + 1]);
                strcpy(array[j + 1], temp);
            }
        }
    }

    for (int i = 0; i < files; i++)
    {
        printf("%s ", array[i]);
    }
    printf("\n");

    return array;
}
void ls_T(char * path)
{
    DIR * dp = opendir(path);
    struct dirent * ep;
    char newdir[512];
    printf(BLUE "\n%s :\n" WHITE, path);
    while((ep = readdir(dp)))
        if(strncmp(ep->d_name, ".", 1))
            printf("\t%s\n" WHITE, ep->d_name);
    closedir(dp);
    
    dp = opendir(path);
    while((ep = readdir(dp))) if(strncmp(ep->d_name, ".", 1)) {
        if(ep->d_type == 4) {
            sprintf(newdir, "%s/%s", path, ep->d_name);
            ls_T(newdir);
        }
    }
    closedir(dp);
}

void find(char *str_in){
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    char *path = ".";
    folder = opendir(path);
    if (folder == NULL)
    {
        puts("Unable to read directory");
        return (1);
    }
    else
    {
        while (entry = readdir(folder))
        {
            files++;
            char *m = entry->d_name;
            if(strcmp(m,str_in)==0){
                printf("File found! (%s)\n",m);
                return NULL;
            } 
        }
            printf("No file with the name %s found in the directory '%s'\n",str_in,path);
    }
    closedir(folder);
}


void list_dir(char c)
{
    if (c=='x')
    {
        ls();
    }
    else if (c == 'a')
    {
        ls_a();
    }
    else if (c == 'l')
    {
        ls_l();
    }
    else if (c == 'r')
    {
        ls_r();
    }
    else if (c == 'T'){
        ls_T(".");
    }
}


int main(int argc, char **argv)
{
    switch (argc)
    {
    case 2:
        if (strcmp(argv[1], "ls") == 0)
            list_dir('x');
        else{
            find(argv[1]);
        }
    case 3:
        if (strcmp(argv[1],"ls")==0){
            if(strcmp(argv[2],"-a")==0) list_dir('a');
            if(strcmp(argv[2],"-l")==0) list_dir('l');
            if(strcmp(argv[2],"-r")==0) list_dir('r');
            if(strcmp(argv[2],"-T")==0) list_dir('T');
        }
    }
}