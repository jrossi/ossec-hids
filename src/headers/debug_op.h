/* @(#) $Id: ./src/headers/debug_op.h, 2011/09/08 dcid Exp $
 */

/* Copyright (C) 2009 Trend Micro Inc.
 * All right reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */


/* Part of the OSSEC HIDS
 * Available at http://www.ossec.net
 */

/* Functions to generate debug/verbose/err reports.
 * Right now, we have two debug levels: 1,2,
 * a verbose mode and a error (merror) function.
 * To see these messages, use the "-d","-v" options
 * (or "-d" twice to see debug2). The merror is printed
 * by default when an important error occur.
 * */

#ifndef __DEBUG_H

#define __DEBUG_H

#ifndef __GNUC__
#define __attribute__(x)
#endif

void debug1(const char *msg,...) __attribute__((format(printf, 1, 2))) __attribute__((nonnull));

void debug2(const char *msg,...) __attribute__((format(printf, 1, 2))) __attribute__((nonnull));

void merror(const char *msg,...) __attribute__((format(printf, 1, 2))) __attribute__((nonnull));

void verbose(const char *msg,...) __attribute__((format(printf, 1, 2))) __attribute__((nonnull));

void print_out(const char *msg,...) __attribute__((format(printf, 1, 2))) __attribute__((nonnull));

void log2file(const char * msg,... ) __attribute__((format(printf, 1, 2))) __attribute__((nonnull));

void ErrorExit(const char *msg,...) __attribute__((format(printf, 1, 2))) __attribute__((nonnull)) __attribute__ ((noreturn));

#ifdef DEV_DEBUG 
#define d(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define d(M, ...) // fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/* Use these three functions to set when you
 * enter in debug, chroot or daemon mode
 */
void nowDebug(void);

void nowChroot(void);

void nowDaemon(void);

int isChroot(void);

/* Debug analysisd */
#ifdef DEBUGAD
    #define DEBUG_MSG(x,y,z) verbose(x,y,z)
#else
    #define DEBUG_MSG(x,y,z)
#endif /* end debug analysisd */

#endif
