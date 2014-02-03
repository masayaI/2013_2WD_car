/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/**
 * RtORB:
 *     poa.h
 *
 * Copyright(C) 2006, Isao Hara, AIST
 *
 * $Revision: 1.3 $
 * $Date: 2008/05/29 04:54:57 $
 * $Id: poa.h,v 1.3 2008/05/29 04:54:57 yoshi Exp $
 *
 */

#ifndef __FUNC_POA_H__
#define __FUNC_POA_H__


PortableServer_POAManagerFactory PortableServer_POAManagerFactory_new(CORBA_ORB orb);

PortableServer_POAManager
PortableServer_POAManagerFactory_find(PortableServer_POAManagerFactory factory, char *id,
		CORBA_Environment *env);

PtrArray * PortableServer_POAManagerFactory_list(PortableServer_POAManagerFactory factory,
		CORBA_Environment *env);

PortableServer_POAManager
PortableServer_POAManagerFactory_create_POAManager(PortableServer_POAManagerFactory factory,
		char *id, CORBA_Environment *env);

PortableServer_POAManager PortableServer_POAManager_new(char *id);

void PortableServer_POAManager_activate(PortableServer_POAManager poa_mgr,
		CORBA_Environment *env) ;

void PortableServer_POAManager_deactivate(PortableServer_POAManager poa_mgr,
		CORBA_boolean etherealize_objects, CORBA_boolean wait_for_complation,
		CORBA_Environment *env) ;

void PortableServer_POAManager_discars_requests(PortableServer_POAManager poa_mgr,
		CORBA_boolean wait_for_complation, CORBA_Environment *env) ;

void PortableServer_POAManager_hold_requests(PortableServer_POAManager poa_mgr,
		CORBA_boolean wait_for_complation, CORBA_Environment *env) ;

void PortableServer_POAManager_shutdown(PortableServer_POAManager poa_mgr, CORBA_Environment *env) ;

void PortableServer_POAManager_destory(PortableServer_POAManager poa_mgr, CORBA_Environment *env);

unsigned long
PortableServer_POAManager_get_state(PortableServer_POAManager poa_mgr, CORBA_Environment *env);

char * PortableServer_POAManager_get_id(PortableServer_POAManager poa_mgr, CORBA_Environment *env);

PortableServer_POA PortableServer_POA_new(char *id, unsigned short port);

PortableServer_POA PortableServer_POA_createPOA(PortableServer_POA ppoa, char *id, 
		PortableServer_POAManager mgr, PortableServer_POA_Policy *policies, 
		CORBA_Environment *env);

int CORBA_ORB_enqueue_request(CORBA_ORB orb, int sock);
int PortableServer_POA_enqueue_request(PortableServer_POA poa, int sock);

void PortableServer_POA_activate(PortableServer_POA poa, CORBA_Environment *env) ;
void PortableServer_POA_destory(PortableServer_POA poa, CORBA_Environment *env) ;

PortableServer_POAManager PortableServer_POA__get_the_POAManager(PortableServer_POA poa,
		CORBA_Environment *env);

int PortableServer_enqueue_request(GIOP_ConnectionHandler *h);
void PortableServer_execute_request(void *arg);
void POA_main_loop(PortableServer_POA rootPOA);
int POA_select_server_sockets(PortableServer_POA poa, fd_set *sockbits, int server_port,
		struct timeval *time_out);

void POA_server_socket_loop(PortableServer_POA poa, float time_out_float);

PortableServer_ObjectId PortableServer_POA_activate_object(PortableServer_POA poa, 
		PortableServer_Servant servant, CORBA_Environment *env);

void register_PortableServer_Servant(PortableServer_POA poa,
		PortableServer_Servant servant, CORBA_Environment *env);

CORBA_Object impl_POA_ServantBase_to_Object(impl_POA_ServantBase *poa_servant);

void RtORB_POA_Object__create(PortableServer_ClassInfo *info, PortableServer_Servant servant,
		void (*finalize)(), void *vepv);

void PortableServer_POA_deactivate_object(PortableServer_POA poa, 
		PortableServer_ObjectId id, CORBA_Environment *env);

void PortableServer_POA_reinstall_object(PortableServer_POA poa,
                CORBA_Object obj, char *object_key, CORBA_Environment *env);

CORBA_Object PortableServer_POA_servant_to_reference(PortableServer_POA poa,
		PortableServer_Servant servant, CORBA_Environment *env);

PortableServer_POA PortableServer_ServantBase__default_POA(PortableServer_Servant servant,
		CORBA_Environment *env);

CORBA_InterfaceDef * PortableServer_ServantBase__get_interface(PortableServer_Servant servant, 
		CORBA_Environment *env);

CORBA_boolean PortableServer_ServantBase__is_a(PortableServer_Servant servant, const char *id,
		CORBA_Environment *env);

CORBA_boolean PortableServer_ServantBase__non_existent(PortableServer_Servant servant,
		CORBA_Environment *env);
void PortableServer_ServantBase__add_ref(PortableServer_Servant servant,  CORBA_Environment *env);
void PortableServer_ServantBase__remove_ref(PortableServer_Servant servant,  CORBA_Environment *env);
void PortableServer_ServantBase__fini(PortableServer_Servant servant, CORBA_Environment *env);
void PortableServer_ServantBase__init(PortableServer_ServantBase *servant, CORBA_Environment *env);

PortableServer_POA PortableServer_root_POA(CORBA_Environment *ev);

#endif
