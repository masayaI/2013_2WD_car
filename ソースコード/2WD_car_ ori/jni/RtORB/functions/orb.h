/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *   RtORB:
 *     orb.h
 *
 *   Copyright(C) 2006, Isao Hara, AIST
 *
 *   $Revision: 1.1.1.1 $
 *   $Date: 2008/01/08 07:56:06 $
 *   $Id: orb.h,v 1.1.1.1 2008/01/08 07:56:06 yoshi Exp $
 *
 */

#ifndef __FUNC_ORB_H__
#define __FUNC_ORB_H__

/*
#ifndef CORBA_POLICY_ERROR_CODE
#define CORBA_POLICY_ERROR_CODE	1
const CORBA_PolicyErrorCode BAD_POLICY = 0;
const CORBA_PolicyErrorCode UNSUPPORTED_POLICY = 1;
const CORBA_PolicyErrorCode BAD_POLICY_TYPE = 2;
const CORBA_PolicyErrorCode BAD_POLICY_VALUE = 3;
const CORBA_PolicyErrorCode UNSUPPORTED_POLICY_VALUE = 4;
#endif
hashtable *CORBA_Object_Table;
*/

void CORBA_exception_init(CORBA_Environment *env);
char * CORBA_exception_id(CORBA_Environment *ev);
CORBA_any  CORBA_exception_value(CORBA_Environment *ev);
void CORBA_exception_free(CORBA_Environment *ev);
void set_CORBA_exception(CORBA_Environment *ev, unsigned long id, char *report);

/////////////////////////////////////////////////////////////
void setServiceID(CORBA_Config *cfg, char *argv[]);
void setORBid(CORBA_Config *cfg, char *argv[]);
void setListenEndpoints(CORBA_Config *cfg, char *argv[]);
void setProprietaryActivation(CORBA_Config *cfg, char *argv[]);
void setInitRef(CORBA_Config *cfg, char *argv[]);
void setDefaultInitRef(CORBA_Config *cfg, char *argv[]);
void setServerPort(CORBA_Config *cfg, char *argv[]);
int checkArgParams(char *argv[], int n);
int checkArgs(CORBA_Config *cfg, int *argc, char *argv[], int i,
		char *arg_name, void (*func)(), int requires);

CORBA_ORB CORBA_ORB_init(int *argc, char **argv, char orb_id, CORBA_Environment *env);
CORBA_Object CORBA_ORB_resolve_initial_references(CORBA_ORB orb, char *id,  CORBA_Environment *env);
CORBA_Object new_CORBA_Object(char *obj_key);
int CORBA_Object_free(CORBA_Object obj);
void delete_CORBA_Object(CORBA_Object obj);
CORBA_Object CORBA_Object_dup(CORBA_Object obj);
void CORBA_Object__set_object_key(CORBA_Object obj, char *key, CORBA_Environment *env);
void CORBA_Object__narrow(CORBA_Object obj, CORBA_TypeCode tc, CORBA_Environment *env);
unsigned char * CORBA_ORB_id(CORBA_ORB orb, CORBA_Environment *env);
char *CORBA_Object__to_string(CORBA_Object obj, CORBA_Environment *env);
unsigned char * CORBA_ORB_object_to_string(CORBA_ORB orb, CORBA_Object obj,  CORBA_Environment *env);
CORBA_Object CORBA_ORB_string_to_object(CORBA_ORB orb, unsigned char *str,  CORBA_Environment *env);
boolean CORBA_ORB_get_service_information(CORBA_ORB orb, unsigned short service_type,
		CORBA_ServiceInforamtion *service_information, CORBA_Environment *env) ;
void CORBA_ORB_get_default_context(CORBA_ORB orb, CORBA_Context *ctx, CORBA_Environment *env) ;
boolean CORBA_ORB_work_pending(CORBA_ORB orb, CORBA_Environment *env);
void CORBA_ORB_perform_work(CORBA_ORB orb, CORBA_Environment *env);
void CORBA_ORB_run(CORBA_ORB orb,  CORBA_Environment *env) ;
void CORBA_ORB_shutdown(CORBA_ORB orb, boolean wait_for_completion, CORBA_Environment *env) ;
void CORBA_ORB_destroy(CORBA_ORB orb, CORBA_Environment *env);
unsigned long CORBA_ORB_get_next_request_id(CORBA_ORB orb, CORBA_Environment *env);

CORBA_InterfaceDef * CORBA_Object_get_interface(CORBA_Object object, CORBA_Environment *env);
unsigned long * CORBA_Object_repository_id(CORBA_Object object, CORBA_Environment *env);
CORBA_Object CORBA_Object_duplicate(CORBA_Object object, CORBA_Environment *env);
void CORBA_Object_release(CORBA_Object object, CORBA_Environment *env);
boolean CORBA_Object_is_nil(CORBA_Object object, CORBA_Environment *env);
boolean CORBA_Object_is_a(CORBA_Object object, unsigned char *logical_type_id,
		CORBA_Environment *env);
boolean CORBA_Object_non_existent(CORBA_Object object, CORBA_Environment *env);
unsigned long CORBA_Object_hash(CORBA_Object object, unsigned long maximum, CORBA_Environment *env);
boolean CORBA_Object_is_equivalent(CORBA_Object object, CORBA_Object other_object,
		CORBA_Environment *env);

CORBA_Policy * CORBA_Object_get_policy(CORBA_Object object, CORBA_PolicyType policy_type,
		CORBA_Environment *env);
CORBA_Policy * CORBA_Object_get_client_policy(CORBA_Object object, CORBA_PolicyType type,
		CORBA_Environment *env);
CORBA_PolicyList * CORBA_Object_get_policy_overrides(CORBA_Object object,
		CORBA_PolicyTypeSeq types, CORBA_Environment *env);
CORBA_Object CORBA_Object_set_policy_overrides(CORBA_Object object, CORBA_PolicyList policies,
		unsigned long set_add, CORBA_Environment *env);
boolean CORBA_Object_validate_connection(CORBA_Object object,
		CORBA_PolicyList inconsistent_policies, CORBA_Environment *env);
CORBA_DomainManagerList * CORBA_Object_get_domain_managers(CORBA_Object object,
		CORBA_Environment *env);
CORBA_Object CORBA_Object_get_component( CORBA_Object object, CORBA_Environment *env);
CORBA_ORB CORBA_Object_get_orb( CORBA_Object object, CORBA_Environment *env);
CORBA_Policy new_CORBA_Policy();
CORBA_Policy CORBA_Policy_copy(CORBA_Policy policy, CORBA_Environment *env);
void CORBA_Policy_destroy(CORBA_Policy policy, CORBA_Environment *env);
CORBA_Policy CORBA_ORB_create_policy(CORBA_ORB orb, CORBA_PolicyType type,
		CORBA_any val, CORBA_Environment *env);

#endif
