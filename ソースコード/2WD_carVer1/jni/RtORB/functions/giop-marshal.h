/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 * RtORB: giop-marshal.h
 *   IIOP-GIOP
 *
 *  Copyright(C) 2006, Isao Hara, AIST
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2008/01/08 07:56:06 $
 *  $Id: giop-marshal.h,v 1.1.1.1 2008/01/08 07:56:06 yoshi Exp $
 */

#ifndef __FUNC_GIOP_MARSHAL_H__
#define __FUNC_GIOP_MARSHAL_H__

void Address_Alignment(int *current, int base);
void *Align_Pointer_Address(void *val, unsigned long base);
unsigned long size_of_typecode(CORBA_TypeCode tc);
unsigned long align_of_typecode(CORBA_TypeCode tc);
void copy_octet(void *dist, octet *buf, int size, int *current);

////////////////////////////////////////////////////////////////
//
//  marshal
//
void marshalOctet(octet *buf, int *pos, octet val);
void marshalShort(octet *buf, int *pos, short val);
void marshalLong(octet *buf, int *pos, long val);
void marshalFloat(octet *buf, int *pos, float val);
void marshalDouble(octet *buf, int *pos, double val);
int marshalString(octet *dist, int *pos, char *str);
int marshalString2(octet *dist, int *pos, char *str, int len);
int marshal_CORBA_String(octet *dist, int *pos, CORBA_String *str);
void marshal_Octet_Sequence(octet *buf, int *pos, octet *data, int size);
void marshal_CORBA_Sequence(octet *buf, int *pos, CORBA_Sequence *seq);
void marshal_IOP_SerivceContextList(IOP_ServiceContextList *service_context,
		octet *buf, int *current);

////////////// demarshal
octet demarshalOctet(char *buf, int *pos);
short demarshalShort(octet *buf, int *pos, int order);
long demarshalLong(octet *buf, int *pos, int order);
float demarshalFloat(octet *buf, int *pos, int order);
double demarshalDouble(octet *buf, int *pos, int order);
char *deMarshalString(char *src, int *pos, int byte_order, int *size);
int demarshal_CORBA_String(CORBA_String *str, octet *src, int *pos, int order);
void demarshal_IOP_SerivceContext(IOP_ServiceContext *context,
		octet *buf, int *current, int order);
void demarshal_IOP_SerivceContextList(IOP_ServiceContextList *service_context,
		octet *buf, int *current, int order);

////////////////////////////
unsigned long demarshal_by_typecode(void **dist, CORBA_TypeCode tc, octet *buf, int *current, int order);
void ** deMarshal_Arg(octet *buf, int i_args, CORBA_IArg *i_argv, int order);
void deMarshal_Arguments(void **retval, void **args, octet *buf, CORBA_Class_Method *method, int order);

////////////////////////////
int marshal_by_typecode(octet *buf, void *argv, CORBA_TypeCode tc, int *current);
int Marshal_Arg(octet *buf, void * *argv, int i_args, CORBA_IArg *i_argv);
void Marshal_Result(char *reply_buf, void * *result, CORBA_TypeCode tc, int *size);
void Marshal_Reply_Arguments(GIOP_ReplyBody *reply, void * *result,
			void * *argv, CORBA_Class_Method *m);



#endif
