#include <stdio.h>
#include <sys/mount.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>  
#include <spawn.h>
#include <stdlib.h>

extern char **environ;

int main() {
    pid_t pid;
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty1", "--noclear", "115200", "vt100", NULL}, environ);
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty2", "--noclear", "115200", "vt100", NULL}, environ);
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty3", "--noclear", "115200", "vt100", NULL}, environ);
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty4", "--noclear", "115200", "vt100", NULL}, environ);
    printf("\nBoot complete!\n-----------------------------------------------------------------\n");
    printf("oINIT v.1C\n");
    printf("No idea how many lines of code this has!\n");
    while (1){sleep(1);}
}
