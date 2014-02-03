/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *   RtORB: TypeCode.h
 *
 *   Copyright(C) 2006, Isao Hara, AIST
 *
 *   $Revision: 1.1.1.1 $
 *   $Date: 2008/01/08 07:56:06 $
 *   $Id: typecode.h,v 1.1.1.1 2008/01/08 07:56:06 yoshi Exp $
 */

#ifndef __FUNC__TYPECODE_H__
#define __FUNC__TYPECODE_H__

void
raises(CORBA_Environment *ev,char *msg );

boolean
CORBA_TypeCode_equal(CORBA_TypeCode code, CORBA_TypeCode tc, CORBA_Environment *ev);

boolean
CORBA_TypeCode_equivalent(CORBA_TypeCode code, CORBA_TypeCode tc, CORBA_Environment *ev);

CORBA_TCKind
CORBA_TypeCode_kind(CORBA_TypeCode code, CORBA_Environment *ev);

CORBA_RepositoryId
CORBA_TypeCode_id(CORBA_TypeCode code, CORBA_Environment *ev);

CORBA_Identifier
CORBA_TypeCode_name(CORBA_TypeCode code, CORBA_Environment *ev);

unsigned long
CORBA_TypeCode_member_count(CORBA_TypeCode code, CORBA_Environment *ev);

CORBA_Identifier
CORBA_TypeCode_member_name(CORBA_TypeCode code,unsigned long index,  CORBA_Environment *ev);

CORBA_TypeCode
CORBA_TypeCode_member_type(CORBA_TypeCode code,unsigned long index,  CORBA_Environment *ev);

void * *
CORBA_TypeCode_member_label(CORBA_TypeCode code,unsigned long index,  CORBA_Environment *ev);

CORBA_TypeCode
CORBA_TypeCode_discriminator_type(CORBA_TypeCode code,  CORBA_Environment *ev);

long 
CORBA_TypeCode_default_index(CORBA_TypeCode code,  CORBA_Environment *ev);

unsigned long 
CORBA_TypeCode_length(CORBA_TypeCode code,  CORBA_Environment *ev);

CORBA_TypeCode
CORBA_TypeCode_content_type(CORBA_TypeCode code,  CORBA_Environment *ev);

unsigned short
CORBA_TypeCode_fixed_digits(CORBA_TypeCode code,  CORBA_Environment *ev);

short
CORBA_TypeCode_fixed_scale(CORBA_TypeCode code,  CORBA_Environment *ev);

CORBA_Visibility
CORBA_TypeCode_member_visibility(CORBA_TypeCode code, unsigned long index,  CORBA_Environment *ev);

CORBA_ValueModifier
CORBA_TypeCode_type_modifier(CORBA_TypeCode code, CORBA_Environment *ev);

CORBA_TypeCode
CORBA_TypeCode_concrete_base_type(CORBA_TypeCode code, CORBA_Environment *ev);

CORBA_TypeCode
CORBA_TypeCode_get_dynamic(CORBA_TCKind, const char*, const char*);

int
CORBA_TypeCode_add_dynamic(CORBA_TypeCode tc);

#endif
