#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>


#define SOCKET_FILE "/home/xiongjp/non-work/test/unix_domain_socket/test.sock"

#define ERR_EXIT(err_msg) \
    do { \
        perror(err_msg); \
        exit(EXIT_FAILURE); \
    } while(0)


void echo_client(int conn_fd) {
    char send_buf[1024] = {0};
    char recv_buf[1024] = {0};
    while (fgets(send_buf, sizeof(send_buf), stdin) != NULL) {
        write(conn_fd, send_buf, strlen(send_buf));
        read(conn_fd, recv_buf, sizeof(recv_buf));
        // fputs(recv_buf, stdout);
        printf("echo_client receive back: %s\n", recv_buf);
        memset(recv_buf, 0, sizeof(recv_buf));
        memset(send_buf, 0, sizeof(send_buf));
    }
}


int main() {
    int conn_fd;
    // in <sys/socket.h>
    // #define  PF_UNIX     AF_UNIX
    /* create a socket, return a socket file descripter
     * argument 1: domain, address family, AF_INET, AF_INET6, AF_UNIX, AF_UNSPEC
     * argument 2: type, SOCK_DGRAM, SOCK_RAW, SOCK_SEQPACKET, SOCK_STREAM
     * argument 3: protocol, always 0, corresponding default protocol
     */   
    if ((conn_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
        ERR_EXIT("socket error");
    }

    struct sockaddr_un server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_FILE);

    // connect to server, whose address is specified by server_addr
    if (connect(conn_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        ERR_EXIT("connect error");
    }

    echo_client(conn_fd);
    close(conn_fd);

    return 0;
}
