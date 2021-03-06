
#ifndef _NGX_FILTER_SESSION_H_INCLUDED_
#define _NGX_FILTER_SESSION_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <ngx_event_connect.h>
#include <ngx_filter.h>


#define NGX_REDIRECT_TO          1
#define NGX_REDIRECT_PASS        2
#define NGX_REDIRECT_TO_DEFAULT  3

#define NGX_BUF_SIZE               10240



typedef struct ngx_filter_session_s {
    uint32_t                signature;         /* "FILTER" */

    ngx_pool_t             *pool;

    ngx_connection_t       *connection;

    ngx_str_t               out;
    ngx_buf_t              *buffer;

    void                  **ctx;
    void                  **main_conf;
    void                  **srv_conf;

    ngx_resolver_ctx_t     *resolver_ctx;

    ngx_filter_cleanup_t  *cleanup;

    time_t                  start_sec;
    ngx_msec_t              start_msec;

    off_t                   bytes_read;
    off_t                   bytes_write;

    unsigned                quit:1;
    ngx_str_t              *addr_text;
    ngx_str_t               host;

} ngx_filter_session_t;


typedef void (*ngx_filter_cleanup_pt)(void *data);


struct ngx_filter_cleanup_s {
    ngx_filter_cleanup_pt      handler;
    void                       *data;
    ngx_filter_cleanup_t      *next;
};

void ngx_filter_init_connection(ngx_connection_t *c);

void ngx_filter_close_connection(ngx_connection_t *c);

u_char *ngx_filter_log_error(ngx_log_t *log, u_char *buf, size_t len);

void ngx_filter_finalize_session(ngx_filter_session_t *s);


ngx_int_t ngx_filter_log_handler(ngx_filter_session_t *s);

#endif
