#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

#define STAR "\x1b[36m*\x1b[0m"

extern char **environ;

int main() {
    pid_t pid;
    printf(STAR " Stage 3: tty & supervise loop\n");
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty1", "--noclear", "115200", "vt100", NULL}, environ);
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty2", "--noclear", "115200", "vt100", NULL}, environ);
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty3", "--noclear", "115200", "vt100", NULL}, environ);
    posix_spawn(&pid, "/sbin/agetty", 0, 0, (char*[]){"/sbin/agetty", "-L", "tty4", "--noclear", "115200", "vt100", NULL}, environ);
    posix_spawn(&pid, "/sbin/cat", 0, 0, (char*[]){"/sbin/cat", "/init/logo", NULL}, environ);
    printf("\n" STAR " Boot complete!\n--------------------------------------------------------\n");
    printf(STAR " oINIT v.1C\n");
    printf(STAR " No idea how many lines of code this has, but its probably a lot!\n");
    while (1) {
        sleep(1);
    }
}
