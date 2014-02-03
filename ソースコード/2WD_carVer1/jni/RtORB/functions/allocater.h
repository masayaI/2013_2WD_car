/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  RtORB Allocater
 *
 *
 */
#ifndef __FUNC_ALLOCATER_H__
#define __FUNC_ALLOCATER_H__

void * RtORB__alloc(long size, const char *info);
void * RtORB__calloc(long size, long n, const char *info);
void * RtORB__realloc(void *ptr, long size, const char *info);
void * RtORB_alloc_by_typecode(CORBA_TypeCode tc, int len, const char *info);
void * RtORB_typecode_alloc(CORBA_TypeCode tc);
void * RtORB__allocbuf(CORBA_TypeCode tc, long length);
void * RtORB__reallocbuf(void * ptr, CORBA_TypeCode tc, long length);
void * RtORB_sequence_allocbuf(CORBA_TypeCode tc, long length);
char * RtORB__strdup(const char *str, const char *info);

void RtORB__free(void *val, const char *info);
void RtORB_free_by_typecode(CORBA_TypeCode tc, void *val, int flag);
void RtORB_free_by_typecode_cpp(CORBA_TypeCode tc, void *val, int flag);
void RtORB_Arguments_free(void **argv, int in_argc, CORBA_IArg *in_argv);
void RtORB__freekids(CORBA_TypeCode tc, void *p, void *d);

#endif

