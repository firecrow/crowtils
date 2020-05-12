/* copyright 2020 firecrow silvernight, licensed under the wtfpl see LICENSE file */
char xerrmsg[1024];

#ifndef ctl_xerrlog
    #define ctl_xerrlog(XARG) do {\
        fprintf(stderr, "%s", (XARG)); \
        fflush(stderr); \
        exit(errno || 1); \
      } while(0)
#endif

#define ctl_x(XARG) \
    if(XARG) do {\
        snprintf(xerrmsg, 1024, "NOT OK %s:%d:%s %d\n", __FILE__, __LINE__, __func__, XARG); \
        ctl_xerrlog(xerrmsg); \
    } while(0)

#define ctl_xgt(XARG) \
    if((XARG) < 0) do { \
        snprintf(xerrmsg, 1024, "GT NOT OK %s:%d:%s %d\n", __FILE__, __LINE__, __func__, XARG); \
        ctl_xerrlog(xerrmsg); \
    } while(0)

#define ctl_xptr(XARG) \
    if((XARG) == NULL) do { \
        snprintf(xerrmsg, 1024, "PTR NOT OK %s:%d:%s\n", __FILE__, __LINE__, __func__); \
        ctl_xerrlog(xerrmsg); \
    } while(0)

