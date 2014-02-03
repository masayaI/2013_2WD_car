/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */

/*

 Simple GIOP Implementation for x86 (Big Endian)
 

*/
#ifndef __POA_DEFS_H__
#define __POA_DEFS_H__

#if USE_THREAD
#include <pthread.h>
#endif
#include <RtORB/array.h>
#include <RtORB/list.h>
#include <RtORB/hashtable.h>
#include <RtORB/typecode.h>

#ifdef __cplusplus
extern "C"
{
#endif 
/////// POA
#define POA_HOLDING 	1 
#define POA_ACTIVE  	2
#define POA_DISCARDING 	3
#define POA_INACTIVE  	4

/// POA_Policy
typedef struct PortableServer_POA_Policy_struct{
  unsigned long  type;
  unsigned long  id;
} PortableServer_POA_Policy_struct;

typedef PortableServer_POA_Policy_struct * PortableServer_POA_Policy;

/// POAManagerFactory
typedef struct PortableServer_POAManagerFactory_struct{
  struct CORBA_ORB_struct *orb;
  char *id;
  PtrArray *poa_mgr;
} PortableServer_POAManagerFactory_struct;

typedef PortableServer_POAManagerFactory_struct * PortableServer_POAManagerFactory;

/// POAManager
typedef struct PortableServer_POAManager_struct{
  struct CORBA_ORB_struct *orb;
  char *id;
  PtrArray *poa;

  unsigned long status;
#if USE_THREAD
  pthread_t _thread[FD_SETSIZE];
#endif
} PortableServer_POAManager_struct;

typedef PortableServer_POAManager_struct * PortableServer_POAManager;

//// POA
typedef struct PortableServer_POA_struct{
  struct CORBA_ORB_struct *orb;
  char *id;

  struct GIOP_Connection *_server;

  PortableServer_POAManagerFactory mgr_factory;
  PortableServer_POAManager manager;

//  struct PortableServer_POA_struct *children;
  PtrArray *children;
  struct PortableServer_ServantManager_struct *servant_mgr;

//  PtrArray *servants;
  hashtable *object_map;

  PtrList *requests;

//  unsigned long status;

}PortableServer_POA_struct;

typedef PortableServer_POA_struct * PortableServer_POA;

/// ServantManager
typedef struct PortableServer_ServantManager_struct{
  char *id;

  PortableServer_POA poa;

  unsigned long status;
}PortableServer_ServantManager_struct;

typedef PortableServer_ServantManager_struct * PortableServer_ServantManager;


/// ObjectId
typedef struct PortableServer_ObjectId_struct{
  
  struct CORBA_Object_struct *_this;

}PortableServer_ObjectId_struct;

typedef PortableServer_ObjectId_struct * PortableServer_ObjectId;

/////////////// Servant
typedef void *PortableServer_Servant;

typedef struct {
  void *_private;

  void (*finalize)(PortableServer_Servant , CORBA_Environment *);
  PortableServer_POA (*default_POA)(PortableServer_Servant, CORBA_Environment *);
  void (*add_ref)(PortableServer_Servant, CORBA_Environment *);
  void (*remove_ref)(PortableServer_Servant, CORBA_Environment *);
  CORBA_InterfaceDef *(*get_interface)(PortableServer_Servant, CORBA_Environment *);
  CORBA_boolean (*is_a)(PortableServer_Servant, const char *, CORBA_Environment *);
  CORBA_boolean (*non_existent)(PortableServer_Servant, CORBA_Environment *);
} PortableServer_ServantBase__epv ;

typedef PortableServer_ServantBase__epv *PortableServer_ServantBase__vepv;

typedef struct {
  void *_private;
  PortableServer_ServantBase__vepv *vepv;
} PortableServer_ServantBase;


typedef struct{
  PortableServer_ServantBase servant;
  PortableServer_POA poa;
  void *_private;
}impl_POA_ServantBase;

typedef struct {
  void (*dummy)();
//  void *(*impl_finder)(void*, char*, CORBA_Class_Method**, void *(**)());
  void *(*impl_finder)();
  const char *class_name;
  unsigned long *class_id;
  CORBA_Class_Impl *class_impl;
}PortableServer_ClassInfo;

////// RtORB POA Object

typedef struct{

  void *_private;

  CORBA_Object obj;

  PortableServer_POA poa;
  PortableServer_Servant servant;
  PortableServer_ObjectId objectId;

  void *_reserve;
}RtORB_POA_Object;


PortableServer_POA PortableServer_POA__narrow(CORBA_Object);

#ifdef __cplusplus
}
#endif 
#endif

