#include <stdio.h>  // #define BUFSIZ 1024
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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


int main() {
    int running = 1;
    key_t msqkey = 1234; // 0x4D2;
    // msqkey is userspace(outer) name of a message queue,
    // while msqid is kernel(inner) name of a message queue.
    // The kernel translates message queue key to message queue id.
    int msqid = msgget(msqkey, 0666 | IPC_CREAT);
    if (msqid == -1) {
        ERR_EXIT("msgget failed");
    }

    struct msg_s data;
    long msgtype = 0;
    while (running) {
        // get one message out of message identified by msqid, 
        // and store this message into a buffer whose size is MAX_TEXT.
        // If the buffer is too small, you may get an error, 
        // which depends on flag, the fifth argument(here is 0).
        if (msgrcv(msqid, (void*) &data, MAX_TEXT, msgtype, 0) == -1) {
            ERR_EXIT("msgrcv failed");
        }
        printf("recv: %s\n", data.text);
        if (strncmp(data.text, "end", 3) == 0) {
            running = 0;
        }
    }

    if (msgctl(msqid, IPC_RMID, 0) == -1) {
        ERR_EXIT("msgctl(IPC_RMID) failed");
    }

    exit(EXIT_SUCCESS);
}
