// DIA
#ifndef _DIA_UNISTD_H_
#define _DIA_UNISTD_H_
/* ws2tcpip.h */

typedef struct addrinfo {
    int ai_flags;              /* AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST */
    int ai_family;             /* PF_xxx */
    int ai_socktype;           /* SOCK_xxx */
    int ai_protocol;           /* 0 or IPPROTO_xxx for IPv4 and IPv6 */
    size_t ai_addrlen;         /* Length of ai_addr */
    char *ai_canonname;        /* Canonical name for nodename */
    struct sockaddr *ai_addr;  /* Binary address */
    struct addrinfo *ai_next;  /* Next structure in linked list */
} ADDRINFO, *LPADDRINFO;

/* Flags used in "hints" argument to getaddrinfo() */

#define AI_PASSIVE     0x1  /* Socket address will be used in bind() call */
#define AI_CANONNAME   0x2  /* Return canonical name in first ai_canonname */
#define AI_NUMERICHOST 0x4  /* Nodename must be a numeric address string */

#define IN
//#define FAR
#define OUT


typedef int ( __stdcall getaddrinfo_t( IN const char * nodename,
                                       IN const char * servname,
                                       IN const struct addrinfo * hints,
                                       OUT struct addrinfo * * res ) ); // ws2_32.dll

typedef void ( __stdcall freeaddrinfo_t( IN struct addrinfo * ai ) ); // ws2_32.dll

typedef int socklen_t;

#endif /* _DIA_UNISTD_H_ */


