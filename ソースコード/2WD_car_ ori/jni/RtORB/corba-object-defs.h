/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */

/*
 *
 *
 */

#ifndef __CORBA_OBJECT_DEFS__
#define __CORBA_OBJECT_DEFS__

#include <RtORB/corba-defs.h>
#include <RtORB/iop-defs.h>
#include <RtORB/list.h>
#include <RtORB/array.h>
#include <RtORB/hashtable.h>
#ifdef USE_SHMC
#include <RtORB/shmc.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif 
////////////////////
typedef struct GIOP_Connection{
  int sock;
  boolean activate;
  unsigned short port;
  unsigned char *hostname;
#ifdef USE_SHMC
  Shmc *shmc;
#endif
//  unsigned long type;
//  void *parent;
#if USE_THREAD
  pthread_t thread;
#endif
} GIOP_Connection;

//////// Object
typedef struct CORBA_Object_struct{
  void *servant;
  struct PortableServer_POA_struct *poa;
  CORBA_ORB orb;
  unsigned char *typedId;
  unsigned char *object_key;
  CORBA_URL *_url;
  unsigned char num_urls;
//  unsigned long _length_ior_string;
  unsigned char *_ior_string;
//  GIOP_Connection connection;
  GIOP_Connection *connection;
  CORBA_InterfaceDef *interface;
  unsigned long *repository_id;
  unsigned long ref;
  CORBA_Policy *policy;
  CORBA_PolicyList *_policies;
  void *impl;
  void *impl_obj;
  int release;
#ifdef __cplusplus
  CORBA_boolean _is_equivalent(CORBA_Object_struct*);
  CORBA_Object_struct & operator=(const CORBA_Object_struct &o);
#endif

}CORBA_Object_struct;

typedef CORBA_Object_struct * CORBA_Object;

typedef struct {
}CORBA_ServiceInforamtion;

typedef struct {
}CORBA_Context;

#ifdef __cplusplus
}
#endif 
#endif
