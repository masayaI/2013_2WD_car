/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  Common Data Representation
 *
 *
 */
#ifndef __CDR_H__
#define __CDR_H__

#ifdef __cplusplus
extern "C"
{
#endif
#define MAX(A,B)	(A>B ? A:B)

#define Order_BE	0
#define Order_LE	1


//// Alignment requirements for OMG IDL primitive data types
#define Align_char 	1
#define Align_octet 	1
#define Align_short 	2
#define Align_ushort 	2
#define Align_long 	4
#define Align_ulong 	4
#define Align_longlong 	8
#define Align_ulonglong	8
#define Align_float	4
#define Align_double	8
#define Align_longdouble	8
#define Align_boolean	1
#define Align_enum	4
#define Align_wchar 	1 	// for GIOP 1.2 or 1.3
				// for GIOP 1.1 wchar alignment is 1, 2 or 4

#define Align_pointer	4
#define Align_union	4
#define Align_sequence	4
#define Align_any	4

/// Datat Length for each data type
#define DataLen_char 	1
#define DataLen_octet 	1
#define DataLen_short 	2
#define DataLen_ushort 	2
#define DataLen_long 	4
#define DataLen_ulong 	4
#define DataLen_longlong 	8
#define DataLen_ulonglong	8
#define DataLen_float	4
#define DataLen_double	8
#define DataLen_longdouble	16
#define DataLen_boolean	1
#define DataLen_enum	4
#define DataLen_wchar	2

///

#ifdef __cplusplus
}
#endif                          /* __cplusplus */


#endif
