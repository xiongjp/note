# socket��ַ��ʽ


### ��׼

sus��posix���ڻ�����һ�������ˣ��������׼ֻ��Ҫһ��������������Դ��opengroup��վ�ϵ����˵����

sys/socket.hͷ�ļ���Ӧ�ö���struct sockaddr, ������Ӧ�ð������³�Ա��

```c
struct sockaddr {
    sa_family_t  sa_family;  /* Address family */
    char         sa_data[]   /* Socket address (variable-length data) */
};
```

netinet/in.hͷ�ļ���Ӧ�ö���struct in_addr, struct sockaddr_in, ��������Ӧ�ð������³�Ա��

```c
struct in_addr {
    in_addr_t s_addr; /* ipv4 address */
};

struct sockaddr_in {
    sa_family_t    sin_family;  /* address family */
    in_port_t      sin_port;    /* port number */
    struct in_addr sin_addr;    /* ipv4 address */
};
```

netinet/in.hͷ�ļ���Ӧ�ö���struct in6_addr, struct sockaddr_in6, ��������Ӧ�ð������³�Ա��

```c
struct in6_addr {
    uint8_t s6_addr[16]  /* ipv6 address */
};

struct sockaddr_in6 {
    sa_family_t     sin_family;     /* address family */
    in_port_t       sin_port;       /* port number */
    uint32_t        sin_flowinfo;   /* traffic class and flow info */
    struct in6_addr sin6_addr;      /* ipv4 address */
    uint32_t        sin6_scope_id;  /* set of interfaces for scope */
};
```

sys/un.hͷ�ļ���Ӧ�ö���struct sockaddr_un, ������Ӧ�ð������³�Ա��

```c
struct sockaddr_un {
    sa_family_t  sun_family;  /* AF_UNIX */
    char         sun_path[]   /* pathname */
};
```

### Linuxʵ��

```c
struct sockaddr { // sizeof: 16
    sa_family_t  sa_family;  /* Address family, 2B*/
    char         sa_data[14]   /* Socket address (variable-length data) */
};

struct in_addr {
    in_addr_t s_addr; /* ipv4 address, uint32_t */
};

struct sockaddr_in { // sizeof: 16
    sa_family_t    sin_family;  /* address family, 2B, uint16_t */
    in_port_t      sin_port;    /* port number, 2B, uint16_t */
    struct in_addr sin_addr;    /* ipv4 address, 4B */
    unsigned char  sin_zero[8]; /* filler, 8B */
};

struct in6_addr {
    uint8_t s6_addr[16]  /* ipv6 address */
};

struct sockaddr_in6 { // sizeof: 28
    sa_family_t     sin_family;     /* address family, 2B */ 
    in_port_t       sin_port;       /* port number, 2B */
    uint32_t        sin_flowinfo;   /* traffic class and flow info, 4B */
    struct in6_addr sin6_addr;      /* ipv4 address, 16B */
    uint32_t        sin6_scope_id;  /* set of interfaces for scope, 4B */
};

struct sockaddr_un { // sizeof: 110
    sa_family_t  sun_family;  /* AF_UNIX, 2B */
    char         sun_path[108]   /* pathname, 108B */
};
```

### BSDʵ��

```c
struct sockaddr { // size: 16
    unsigned char  sa_len;         /* total length */
    sa_family_t    sa_family;      /* address family */
    char           sa_data[14];    /* actually longer; address value */
};

struct in_addr {
    in_addr_t s_addr;
};

struct sockaddr_in { // size: 16
    uint8_t         sin_len;
    sa_family_t     sin_family;
    in_port_t       sin_port;
    struct in_addr  sin_addr;
    char            sin_zero[8];
};

struct in6_addr {
    uint8_t s6_addr[16]  /* ipv6 address */
};

struct sockaddr_in6 { // size: 28
    uint8_t         sin6_len;       /* length of this struct */
    sa_family_t     sin6_family;    /* AF_INET6 */
    in_port_t       sin6_port;      /* Transport layer port # */
    uint32_t        sin6_flowinfo;  /* IP6 flow information */
    struct in6_addr sin6_addr;      /* IP6 address */
    uint32_t        sin6_scope_id;  /* scope zone index */
};

struct sockaddr_un { // size: 106
    unsigned char sun_len;        /* length including null */
    sa_family_t   sun_family;     /* AF_UNIX, 2B */
    char          sun_path[104]   /* pathname, 108B */
};

```