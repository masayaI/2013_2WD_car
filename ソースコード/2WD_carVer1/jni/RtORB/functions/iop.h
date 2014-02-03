/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  RtORB:
 *  	iop.h
 *  Copyright(C) 2006, Isao Hara, AIST
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2008/01/08 07:56:06 $
 *  $Id: iop.h,v 1.1.1.1 2008/01/08 07:56:06 yoshi Exp $
 */

#ifndef __FUNC_IOP_H__
#define __FUNC_IOP_H__

int Create_Tag_Internet_IOP(char *dist, int sock, char *object_key);
int Create_Default_IOR(char *buf, int sock, char *typedId, char *object_key);
//int deMarshal_IOR(IIOP_IOR *ior_data, octet *ior, int len, int byte_order);
int Sequence_Octet_to_String(char *dist, char *src, int size);
int Long_to_String(char *dist, long val);
int CORBA_Sequence_Octet_to_String(char *dist, char *src, int size);
int createIOR(char *buf, int sock, char *typedId, char *object_key);
//int parseIOR_From_String(IIOP_IOR *ior_data, char *ior);

CORBA_URL * CORBA_URL__alloc(long n);
void CORBA_URL__delete(CORBA_URL *url, long n);
int parseIOR(CORBA_URL **data, octet *ior, int *pos, int byte_order);
char *nextToken(char **dist, char *str, const char *seed);
void parseURL(CORBA_URL *target, char *str);
char * extractURL(char **dist, char *str, int *num, const char *delim);
int parseCorbalocURL(CORBA_URL **data, char *str);
int parseCorbanameURL(CORBA_URL **data, char *str);
int parseCorbaURL(CORBA_URL **data, char *str);

#endif
