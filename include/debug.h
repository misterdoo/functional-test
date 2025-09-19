/*
* file name   : Debug.h
* created     : 21.Mar.25
* Author      : dookyoon.kim
* description : dk git hub
*/
#ifndef DEBUG_H
#define DEBUG_H

#define INFO(fmt, arg...)   		fprintf(stderr, "\033[1;35;45m[I]\033[0;39;49m.. " fmt, ##arg)

#define mgh_info(fmt, arg...)   	fprintf(stderr, "[INFO] " fmt, ##arg)
#define mgh_debug(fmt, arg...)     	fprintf(stderr, "[DBG:%4d] " fmt, __LINE__, ##arg)
#define mgh_trace(fmt, arg...)      fprintf(stderr, "[TRACE:%-15.15s:%4d] " fmt, __func__, __LINE__, ##arg)

#define mgh_warn(fmt, arg...)     	fprintf(stderr, "\033[1;36;47m[WARN:%-15.15s]\033[0;39;49m " fmt, __func__, ##arg)
#define mgh_error(fmt, arg...)      fprintf(stderr, "\033[1;33;41m[ERR:%-15.15s:%4d]\033[0;39;49m " fmt, __func__, __LINE__, ##arg)
#define mgh_printf(fmt, arg...)     fprintf(stderr, "" fmt, ##arg)

#define mgh_none(fmt, arg...)		{ }

#endif
