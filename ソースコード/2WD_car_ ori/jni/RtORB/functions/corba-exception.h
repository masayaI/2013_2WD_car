/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *   RtORB: corba-exception.h
 *
 *   Copyright(C) 2006, Isao Hara, AIST
 *
 *   $Revision: 1.2 $
 *   $Date: 2008/05/19 06:09:41 $
 *   $Id: corba-exception.h,v 1.2 2008/05/19 06:09:41 yoshi Exp $
 *
 */


#ifndef __FUNC_CORBA_EXCEPTION_H__
#define __FUNC_CORBA_EXCEPTION_H__


void
CORBA_exception_set(CORBA_Environment *ev, unsigned long major,
		char *repo_id, CORBA_any *params);

void 
CORBA_user_exception_set(CORBA_Environment *ev, char *repo_id, CORBA_TypeCode tc, void *value);
void CORBA_system_exception(CORBA_Environment *ev, char *msg);

int catchDefaultException(CORBA_Environment *env);
int catchException(CORBA_Environment *env, char *repo_id);
void clearException(CORBA_Environment *env);

void * CORBA_exception_get_value(CORBA_Environment *ev);

#endif
