/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  rtorb.h
 *
 *
 */

#ifndef __FUNC_RTORB_H__
#define __FUNC_RTORB_H__

int Marshal_Args(octet *buf, void **argv, int i_args, CORBA_IArg *i_argv);
void actionReply(octet *buf, CORBA_Sequence_Octet *body,
		CORBA_Class_Method *method,
		CORBA_Environment *env);
void invokeMethod_via_GIOP(CORBA_Object obj, CORBA_Class_Method *method,
		void **retval, void **args, CORBA_Environment *env);

int CORBA_ORB_find_object(PortableServer_POA poa, CORBA_Object obj, CORBA_Environment *env);
void invokeMethod(CORBA_Object obj, CORBA_Class_Method *method,
		void **retval, void **args, CORBA_Environment *env);
#endif
