/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *
 */
#ifndef __CORBA_H__
#define __CORBA_H__
#include <stdio.h>
#include <stdlib.h>
#include <endian.h>

#ifdef USE_THREAD
#include <pthread.h>
#endif
#include <RtORB/giop.h>
#include <RtORB/typecode.h>
#include <RtORB/hashtable.h>
#include <RtORB/corba-defs.h>
#include <RtORB/CDR-defs.h>
#include <RtORB/corba-object-defs.h>
#include <RtORB/poa-defs.h>

#ifdef __cplusplus
extern "C"
{
#endif 

#include <RtORB/list.h>
#include <RtORB/array.h>
#include <RtORB/functions/allocater.h>
#include <RtORB/functions/endian.h>
#include <RtORB/functions/corba-exception.h>
#include <RtORB/functions/corba-sequence.h>
#include <RtORB/functions/corba-typecode.h>
#include <RtORB/functions/orb.h>
#include <RtORB/functions/iop.h>
#include <RtORB/functions/giop.h>
#include <RtORB/functions/giop-marshal.h>
#include <RtORB/functions/giop-msg.h>
#include <RtORB/functions/socket.h>
#include <RtORB/functions/shmcport.h>
#include <RtORB/functions/poa.h>
#include <RtORB/functions/server_loop.h>
//#include <RtORB/functions/typecode.h>
#include <RtORB/functions/rtorb.h>
#include <RtORB/functions/pthread.h>
#include <RtORB/util.h>

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

#ifndef LE
#define LE	1
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define __CDR_ORDER__ 	1
#else 
#define __CDR_ORDER__ 	0
#endif

#ifdef DEBUG
#	define	ASSERT(c, info)		do_assert(c, info)
#else
#	define	ASSERT(c, info)
#endif

#define SKIP_ALIAS(tc) \
	while((tc)->kind == tk_alias) { (tc) = (tc)->member_type[0]; }

#ifdef DEBUG_MALLOC
#  define RtORB_alloc(s, info)		RtORB__alloc(s, info)
#  define RtORB_realloc(p, s, info)	RtORB__realloc(p, s, info)
#  define RtORB_calloc(s, n, info)	RtORB__calloc(s, n, info)
#  define RtORB_strdup(s, info)		RtORB__strdup(s, info)
#  define RtORB_strndup(s, n, info)	RtORB__strndup(s, n, info)
#  define RtORB_free(s, info)		RtORB__free(s, info)
#else
#  define RtORB_alloc(s, info)		calloc(1, s)
#  define RtORB_realloc(p, s, info)	realloc(p, s)
#  define RtORB_calloc(s, n, info)	calloc(n, s)
#  define RtORB_strdup(s, info)		strdup(s)
#  define RtORB_strndup(s, n, info)	strndup(s, n)
#  define RtORB_free(s, info)		free(s)
#endif

#define DEFAULT_HASH_SIZE 64

void do_assert(boolean c, const char* info);

extern CORBA_ORB _ORB_;

#ifdef USE_THREAD
extern pthread_mutex_t  CORBA_MUTEX;
#define CORBA_MUTEX_LOCK() pthread_mutex_lock(&CORBA_MUTEX)
#define CORBA_MUTEX_UNLOCK() pthread_mutex_unlock(&CORBA_MUTEX)
#else
#define CORBA_MUTEX_LOCK() 
#define CORBA_MUTEX_UNLOCK() 
#endif
//extern struct sockport_profile  *SocetProfile;

CORBA_TypeCode CORBA_TypeCode_get_dynamic(CORBA_TCKind kind, const char *repoid, const char *id);

#ifdef __cplusplus
}
#endif 

#endif
