#ifndef _REDIS_H
#define _REDIS_H

#include <stdio.h>

#define REDIS_TRUE 1
#define REDIS_FALSE 0
#define REDIS_VERSION "0.1"

#define REDIS_FLAG_FREE  (1<<0)
#define REDIS_FLAG_DEBUG (1<<1)
#define REDIS_FLAG_ANY   0

typedef struct _redis_data_t {
	char c;
	int sz;
	union {
		long int              l;
		char*                 str; // c => $,-,+
		struct _redis_data_t* data; // c => *
	};
} redis_data_t;

typedef struct _redis_t {
	FILE*        fp;
	int          fd;
	int          flag;
	char         ip[32];
 
	char         buf[256];

	redis_data_t data;
} redis_t;

redis_t *redis_init(redis_t *redis, int flag);

    int  redis_debug(redis_t *redis);

    int  redis_connect(redis_t *redis, const char *host, int port);

    int  redis_send(redis_t *redis, const char *format, ...);
    int  redis_senda(redis_t *redis, int argc, const char *argv[]);

    int  redis_dgets(redis_t *redis);
    int  redis_recv(redis_t *redis, char flag);

    int  redis_auth(redis_t *redis, const char *password);
    int  redis_ping(redis_t *redis);
    int  redis_echo(redis_t *redis, const char *str);
    int  redis_select(redis_t *redis, int database);
    int  redis_dbsize(redis_t *redis, long int *size);
    int  redis_keys(redis_t *redis, const char *pattern, char ***keys);
    int  redis_quit(redis_t *redis);

    int  redis_type(redis_t *redis, const char *key, char **rtype);
    int  redis_set(redis_t *redis, const char *key, const char *value);
    int  redis_get(redis_t *redis, const char *key, char **value);

    int  redis_multi(redis_t *redis);
    int  redis_exec(redis_t *redis);
    int  redis_scan(redis_t *redis, int cursor, const char *match, int count);

   void  _redis_clean(redis_data_t *data);
#define  redis_clean(redis)                  _redis_clean(&(redis)->data)
    int  redis_close(redis_t *redis);
   void  redis_destory(redis_t *redis);

#endif
