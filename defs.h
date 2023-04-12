#ifndef DEFS_H
#define DEFS_H

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 60002

#define C_OK 0
#define C_NOK -1
#define C_BOOK_NOT_FOUND -2
#define C_BAD_STATUS -3

#define MAX_BUFF 2048
#define MAX_ARR 128
#define MAX_STR 64

typedef enum { CHECKED_IN,
               CHECKED_OUT,
               UNDER_REPAIR,
               LOST
} BookStatusType;

typedef enum { REQ_RET_BOOKS,
               REQ_CHECK_IN,
               REQ_CHECK_OUT,
               REQ_CLOSE
} RequestType;

#endif