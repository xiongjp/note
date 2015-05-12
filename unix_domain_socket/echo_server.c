#include <stdio.h> // perror
#include <stdlib.h> // exit
#include <unistd.h> // fork
#include <errno.h> // EINTR
#include <sys/types.h> // historical reason, always with <sys/socket.h>
#include <sys/socket.h> // socket
// The <sys/socket.h> header shall define the following macro as the maximum 
// backlog queue length which may be specified by the backlog field
// of the listen() function:

// SOMAXCONN
// The maximum backlog queue length.
#include <string.h> // strcpy, memset
#include <sys/un.h> // definitions for UNIX domain sockets, struct sockaddr_un


#define SOCKET_FILE "/home/xiongjp/non-work/test/unix_domain_socket/test.sock"

#define ERR_EXIT(err_msg) \
    do { \
        perror(err_msg); \
        exit(EXIT_FAILURE); \
    } while (0)


void echo_server(int conn_fd) {
    char buf[1024];
    while (1) {
        memset(buf, 0, sizeof(buf));
        int n = read(conn_fd, buf, sizeof(buf));
        if (n == -1) {
            if (n == EINTR) continue;
            ERR_EXIT("read return -1");
        } else if (n == 0) {
            printf("read return 0");
            break;
        }
        printf("echo_server receives: %s\n", buf);
        // fputs(buf, stdout);
        write(conn_fd, buf, strlen(buf));
    }
    close(conn_fd);
}


int main() {
    int listen_fd;
    // create a socket for listening
    if ((listen_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
        ERR_EXIT("socket function return negative");
    }
    unlink(SOCKET_FILE);
    struct sockaddr_un server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_FILE);
    // bind a address to the listening socket for clients to connect
    if (bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        ERR_EXIT("bind error");
    }
    // start to listen for connecting request
    if (listen(listen_fd, SOMAXCONN) < 0) {
        ERR_EXIT("listen error");
    }

    while (1) {
        // create a new socket, which implies a new connection between server and client
        int conn_fd = accept(listen_fd, NULL, NULL);
        if (conn_fd == -1) {
            if (conn_fd == EINTR) continue;
            ERR_EXIT("acccept error");
        }

        pid_t pid = fork();
        if (pid == -1) {
            ERR_EXIT("fork error");
        }
        if (pid == 0) {
            close(listen_fd);
            echo_server(conn_fd);
            exit(EXIT_SUCCESS);
        }

        close(conn_fd);
    }

    return 0;
}
