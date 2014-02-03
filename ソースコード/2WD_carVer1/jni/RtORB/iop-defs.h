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

#ifndef __IOP_DEFS_H__
#define __IOP_DEFS_H__

#include <RtORB/corba-defs.h>

#ifdef __cplusplus
extern "C"
{
#endif 
/*
 * Standaer Service Contexts
 */
enum IOP_ServiceId {
  IOP_TransactionService,
  IOP_CodeSets,
  IOP_ChainBypassChunk,
  IOP_ChainBypassInfo,
  IOP_LogicalThreadId,
  IOP_BI_DIR_IIOP,
  IOP_SendingContextRunTime,
  IOP_INVOCATION_POLICIES,
  IOP_FORWARDED_IDENTITY,
  IOP_UnknownExceptionInfo,
  IOP_RTCorbaPriority,
  IOP_RTCorbaPriorityRange,
  IOP_FT_GROUP_VERSION,
  IOP_FT_REQUEST,
  IOP_ExceptionDetailMessage,
  IOP_SecurityAttributeService,
  IOP_ActivityService,
  IOP_ServiceId_END
};

enum IOP_Profile_ID {
  IOP_TAG_INTERNET_IOP,
  IOP_TAG_MULTIPLE_COMPONENTS,
  IOP_TAG_SCCP_IOP,
  IOP_TAG_PROFILE_END
};

enum IOP_Component_ID {
  IOP_TAG_ORB_TYPE,
  IOP_TAG_CODE_SETS,
  IOP_TAG_POLICIES,
  IOP_TAG_ALTERNATE_IIOP_ADDRESS,
  IOP_TAG_COMPLETE_OBJECT_KEY,
  IOP_TAG_ENDPOINT_ID_POSITION,
  IOP_TAG_LOCATION_POLICY = 12,
  IOP_TAG_ASSOCIATION_OPTIONS,
  IOP_TAG_SPKM_1_SEC_MECH,
  IOP_TAG_SPKM_2_SEC_MECH,
  IOP_TAG_KERBEROSV5_SEC_MACH,
  IOP_TAG_CSI_ECMA_SECRET_SEC_MECH,
  IOP_TAG_CSI_ECMA_HYBRID_SEC_MECH,
  IOP_TAG_SSL_SEC_TRANS,
  IOP_TAG_CSI_ECMA_PUBLIC_SEC_MECH,
  IOP_TAG_GENERIC_SEC_MECH,
  IOP_TAG_FIREWALL_TRANS,
  IOP_TAG_SCCP_CONTACT_INFO,
  IOP_TAG_JAVA_CODEBSE,
  IOP_TAG_DCE_STRING_BINDING=100,
  IOP_TAG_DCE_BINDING_NAME,
  IOP_TAG_DCE_NO_PIPES,
  IOP_TAG_DCE_SEC_MECH,
  IOP_TAG_INET_SEC_MECH=123,
  IOP_TAG_GROUP=90001,
  IOP_TAG_PRIMARY,
  IOP_TAG_HEARTBEAT_ENABLED,

  IOP_TAG_COMPONENT_END
};


/******* IOP ************/
typedef struct {
  unsigned long  context_id;
  CORBA_Sequence_Octet context_data;
} IOP_ServiceContext;

typedef  struct{
  unsigned long num;
  IOP_ServiceContext *data;
} IOP_ServiceContextList;

typedef struct {
  unsigned long tag;
  CORBA_Sequence_Octet profile_data;
} IOP_TaggedProfile;

typedef struct {
   unsigned long size;
   IOP_TaggedProfile *profile;
} CORBA_Sequence_IOP_TaggedProfile;

typedef struct{
  CORBA_String type_id;
  CORBA_Sequence_IOP_TaggedProfile profiles;
} IOP_IOR;

typedef struct{
  unsigned long selected_profile_index;
  IOP_IOR ior;
} IORAddressingInfo;

typedef unsigned long IOP_ComponentId;

typedef struct {
  IOP_ComponentId tag;
  CORBA_Sequence_Octet component_data;
} IOP_TaggedComponent;

typedef struct {
  unsigned long size;
  IOP_TaggedComponent **data;
} CORBA_Sequence_IOP_TaggedComponent;


/**
 *  IIOP
 *
 */
typedef struct {
  octet  major;
  octet  minor;
} IIOP_Version;

typedef struct {
  IIOP_Version version;
  octet dummy[2];
  CORBA_String host;
  unsigned short port;
  CORBA_Sequence_Octet object_key;
} IIOP_ProfileBody_1_0;

typedef struct {
  IIOP_Version version;
  octet dummy[2];
  CORBA_String host;
  unsigned short port;
  CORBA_Sequence_Octet object_key;
  CORBA_Sequence_IOP_TaggedComponent components;
} IIOP_ProfileBody_1_1;

typedef union {
  IIOP_ProfileBody_1_0 _1_0;
  IIOP_ProfileBody_1_1 _1_1;
} IIOP_ProfileBody;

typedef struct {
  CORBA_String host;
  unsigned short port;
} IIOP_ListenPoint;

typedef struct {
  unsigned long size;
  IIOP_ListenPoint *data;
} CORBA_Sequence_IIOP_ListenPoint;

typedef CORBA_Sequence_IIOP_ListenPoint IIOP_ListenPointList;

typedef struct {
  IIOP_ListenPointList  listen_points;
} BiDir_IIOP_ServiceContext;


//////////////////////
//
//
#define MAX_URLS        10
enum{
	  PROTO_RIR, PROTO_IIOP, PROTO_OTHER
};

typedef struct {
  int protocol;
  int byte_order;
  int version_major;
  int version_minor;
  char *type_id;
  char *hostname;
  unsigned short port;
  char *object_key;
  char *naming_context;
  unsigned long object_key_len;
  unsigned long flags;
  unsigned long location_flags;
  char *_ior_string;
  int _ior_string_len;
} CORBA_URL;


#ifdef __cplusplus
}
#endif 
#endif
