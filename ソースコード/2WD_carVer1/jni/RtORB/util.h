/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 * RtORB: util.h
 *
 * Copyright(C) 2006, Isao Hara, AIST
 *
 * $Revision: 1.1.1.1 $
 * $Date: 2008/01/08 07:56:06 $
 * $Id: util.h,v 1.1.1.1 2008/01/08 07:56:06 yoshi Exp $
 *
 */

#ifndef __UTIL_H__
#define __UTIL_H__

#ifdef __cplusplus
extern "C"
{
#endif 
/******* GIOP ************/
int readBytes(int fd, char *buf, int len);
int writeBytes(int fd, char *buf, int len);

///////////// Object ID ////
char *new_ObjectID();
/////////////////////////////////////////////////////////////////////////////
// DEBUG
void  dumpMessage(unsigned char *buf, int size);
void dump_value_by_typecode(void *val, CORBA_TypeCode tc);
////////////////////////////////////////////////////////////
//
char ixdigit(char a);
char hexdigit(char c);
octet *String2Octet(char *str);

void String__delete(char *str, char *info);
long RtORB_strlen(char *str);
char *Get_IP_Address();
#ifdef __cplusplus
}
#endif 
#endif
