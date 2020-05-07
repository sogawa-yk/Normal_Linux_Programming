#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;

    if(argc < 2){
        fprintf(stderr, "%s: file name not given\n", argv[0])
    }
}