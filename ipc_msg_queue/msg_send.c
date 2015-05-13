#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>


#define BUF_SIZE 512

#define MAX_TEXT 512

#define ERR_EXIT(err_msg) \
    do { \
        perror(err_msg); \
        exit(EXIT_FAILURE); \
    } while(0)


struct msg_s {
    long type;
    char text[MAX_TEXT];
};


int main(int argc, char const *argv[]) {
    int running = 1;
    struct msg_s data;
    char buf[BUF_SIZE];
    key_t msqkey = 1234;
    int msqid = msgget(msqkey, 0666 | IPC_CREAT);
    if (msqid == -1) {
        ERR_EXIT("msgget failed");
    }

    while (running) {
        printf("Input some data: ");
        fgets(buf, BUF_SIZE, stdin);
        data.type = 1;
        strcpy(data.text, buf);
        // send one MAX_TEXT bytes message to message queue identified by msqid
        if (msgsnd(msqid, (void*) &data, MAX_TEXT, 0) == -1) {
            ERR_EXIT("msgsnd failed");
        }

        if (strncmp(buf, "end", 3) == 0) {
            running = 0;
        }
        sleep(1);
    }
    return 0;
}
