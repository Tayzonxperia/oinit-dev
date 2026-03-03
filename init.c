#include <stdio.h>
#include <sys/mount.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <spawn.h>

#define STAR "\x1b[36m*\x1b[0m"

extern char **environ;

void boot_msg(void) {
    printf(STAR " Stage 1: boot\n");
}

void mounts(void) {
    pid_t pid;
    printf(STAR " Mounting pseudo-filesystems\n");
    mkdir("/proc", 0555);
    mkdir("/sys", 0555);
    mkdir("/dev", 0755);
    mkdir("/run", 0755);

    mount("proc", "/proc", "proc", 0, NULL);
    printf(STAR " Mounted /proc\n");

    mount("sysfs", "/sys", "sysfs", 0, NULL);
    printf(STAR " Mounted /sys\n");

    mount("devtmpfs", "/dev", "devtmpfs", 0, NULL);
    printf(STAR " Mounted /dev\n");

    mount("tmpfs", "/run", "tmpfs", 0, NULL);
    printf(STAR " Mounted /run\n");

    printf(STAR " Mounting other filesystems\n");
    posix_spawn(&pid, "/sbin/mount", 0, 0, (char*[]){"/sbin/mount", "-a", NULL}, environ);
    printf(STAR " Remounting / as rw\n");
    mount("/", "/", NULL, MS_REMOUNT, NULL);

}

void udev(void) {
    pid_t pid;
    printf(STAR " Starting udev\n");
    posix_spawn(&pid, "/sbin/udevd", 0, 0, (char*[]){"/sbin/udevd", "--daemon", NULL}, environ);
    printf(STAR " Triggering devices\n");
    posix_spawn(&pid, "/sbin/udevadm", 0, 0, (char*[]){"/sbin/udevadm", "trigger", NULL}, environ);
    printf(STAR " Settling devices\n");
    posix_spawn(&pid, "/sbin/udevadm", 0, 0, (char*[]){"/sbin/udevadm", "settle", NULL}, environ);
    printf(STAR " udev complete\n");
}

int main(void) {
    pid_t pid;
    boot_msg();
    mounts();
    udev();
    printf(STAR " Init complete\n");
    printf(STAR " Starting service management\n");
    posix_spawn(&pid, "/sbin/oinit-service", 0, 0, (char*[]){"/sbin/oinit-service", NULL}, environ);
    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0);
        sleep(1);
    }
}
