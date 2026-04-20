#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mount.h>

#define SOCKET_PATH "/tmp/engine_socket"
#define STACK_SIZE (1024 * 1024)

char child_stack[STACK_SIZE];

typedef struct {
    char id[32];
    pid_t pid;
} container_t;

container_t containers[100];
int count = 0;

/******** CONTAINER FUNCTION ********/
int container_func(void *arg) {
    char **args = (char **)arg;

    chroot(args[1]);
    chdir("/");

    mkdir("/proc", 0555);
    mount("proc", "/proc", "proc", 0, NULL);

    execvp(args[2], &args[2]);
    perror("exec failed");
    return 1;
}

/******** START CONTAINER ********/
void start_container(char *id, char *rootfs, char *cmd) {

    char *args[] = {"container", rootfs, cmd, NULL};

    pid_t pid = clone(container_func,
                      child_stack + STACK_SIZE,
                      CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD,
                      args);

    if (pid > 0) {
        containers[count].pid = pid;
        strcpy(containers[count].id, id);
        count++;

        printf("Started %s (PID %d)\n", id, pid);
        printf("DEBUG: count = %d\n", count);  // debug
    } else {
        perror("clone failed");
    }
}

/******** SUPERVISOR ********/
void run_supervisor() {
    int server_fd, client_fd;
    struct sockaddr_un addr;

    unlink(SOCKET_PATH);

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    printf("Supervisor running...\n");

    signal(SIGCHLD, SIG_IGN);

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);

        char buffer[256] = {0};
        read(client_fd, buffer, sizeof(buffer));

        printf("Command: %s\n", buffer);

        char cmd[20] = {0}, id[20] = {0}, rootfs[100] = {0}, prog[50] = {0};

        int args = sscanf(buffer, "%s %s %s %s", cmd, id, rootfs, prog);

        if (args >= 1 && strcmp(cmd, "start") == 0) {
            start_container(id, rootfs, prog);
        }
        else if (args >= 1 && strcmp(cmd, "ps") == 0) {
            printf("Running containers:\n");
            for (int i = 0; i < count; i++) {
                printf("%s : %d\n", containers[i].id, containers[i].pid);
            }
        }
        else if (args >= 2 && strcmp(cmd, "stop") == 0) {
            for (int i = 0; i < count; i++) {
                if (strcmp(containers[i].id, id) == 0) {
                    kill(containers[i].pid, SIGKILL);
                    printf("Stopped %s\n", id);
                }
            }
        }

        close(client_fd);
    }
}

/******** CLIENT ********/
void send_cmd(char *cmd) {
    int sock;
    struct sockaddr_un addr;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    write(sock, cmd, strlen(cmd));
    close(sock);
}

/******** MAIN ********/
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: ./engine <command>\n");
        return 1;
    }

    if (strcmp(argv[1], "supervisor") == 0) {
        run_supervisor();
    }
    else if (strcmp(argv[1], "start") == 0) {
        char cmd[256];
        sprintf(cmd, "start %s %s %s", argv[2], argv[3], argv[4]);
        send_cmd(cmd);
    }
    else if (strcmp(argv[1], "ps") == 0) {
        send_cmd("ps");
    }
    else if (strcmp(argv[1], "stop") == 0) {
        char cmd[256];
        sprintf(cmd, "stop %s", argv[2]);
        send_cmd(cmd);
    }

    return 0;
}
