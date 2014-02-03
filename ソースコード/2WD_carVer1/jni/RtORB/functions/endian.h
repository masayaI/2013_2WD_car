/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  RtORB: endian.h
 *    Simple GIOP Implementation for x86 (Little Endian)
 *
 *  Copyright(C) 2006, Isao Hara, AIST
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2008/01/08 07:56:06 $
 *  $Id: endian.h,v 1.1.1.1 2008/01/08 07:56:06 yoshi Exp $
 *  
 */
//#include <RtORB/corba.h>
#ifndef __FUNC_ENDIAN_H__
#define __FUNC_ENDIAN_H__

/******* ByteOrder ************/
void swapByteOrderInOctet(char *buf, int size);
void swapByteOrder(unsigned char *dist, unsigned char *source, int size);
short reverseOrderShort(short v);
long reverseOrderLong(long v);
long long  reverseOrderLongLong(long long  v);
float reverseOrderFloat(float v);
double reverseOrderDouble(double v);
long double reverseOrderLongDouble(long double v);

/*********************************/

#endif
