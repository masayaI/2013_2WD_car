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

#ifndef __GIOP_DEFS_H__
#define __GIOP_DEFS_H__

#include <RtORB/corba-defs.h>
#include <RtORB/corba-object-defs.h>
#include <RtORB/iop-defs.h>

#ifdef __cplusplus
extern "C"
{
#endif 
#define SIZEOF_GIOP_HEADER 12
//#define MaxMessageSize 262144
#define MaxMessageSize 4096

/*
 * GIOP Message Type
 */
enum GIOP_MsgType{
  GIOP_Request,
  GIOP_Reply,
  GIOP_CancelRequest,
  GIOP_LocateRequest,
  GIOP_LocateReply, 
  GIOP_CloseConnection,
  GIOP_MessageError,
  GIOP_Fragment,
  GIOP_MsgType_END
};

/*
 * GIOP Message Type
 */
enum GIOP_TargetAddress_Type{
  GIOP_KeyAddr, GIOP_ProfileAddr, GIOP_ReferenceAddr
};

/*
 * GIOP ReplyStatus
 */

enum ReplyStatusType{
  GIOP_NO_EXCEPTION,
  GIOP_USER_EXCEPTION,
  GIOP_SYSTEM_EXCEPTION,
  GIOP_LOCATION_FORWARD,
  GIOP_LOCATION_FORWARD_PERM, // > GIOP 1.2
  GIOP_NEEDS_ADDRESSING_MODE,   // > GIOP 1.2
  GIOP_ReplyStatusType_END 
};

/*
 * GIOP LocationStatus
 */
enum LocatieStatusType{
  GIOP_UNKNOWN_OBJECT,
  GIOP_OBJECT_HERE,
  GIOP_OBJECT_FORWARD,
  GIOP_OBJECT_FORWARD_PERM,		// > GIOP 1.2
  GIOP_LOC_SYSTEM_EXCEPTION,		// > GIOP 1.2
  GIOP_LOC_NEEDS_ADDRESSING_MODE,	// > GIOP 1.2
  GIOP_LocationStatusType_END
};

typedef short AddressingDisposition;

typedef union {
  CORBA_Sequence_Octet object_key; // when KeyAddr
  IOP_TaggedProfile profile; // when ProfileAddr 
  IORAddressingInfo ior;     // when ReafercnceAddr
} GIOP_TargetAddress;

/******* GIOP ************/
/*
 * GIOP Message Header
 */
typedef struct {
  octet major;
  octet minor;
} GIOP_Version;

typedef struct{
  char magic[4];
  GIOP_Version version;
  octet flags;  	/// GIOP1.0 --> byte_code
  octet message_type;
  unsigned long message_size;
} GIOP_MessageHeader;

/*
 * GIOP Request Header
 */
typedef struct {
  IOP_ServiceContextList service_context;
  unsigned long request_id;
  boolean  response_expected;
  CORBA_Sequence_Octet object_key;
  CORBA_String operation;
  CORBA_Sequence_Octet requesting_principal;
} GIOP_RequestHeader_1_0;

typedef struct{
  IOP_ServiceContextList service_context;
  unsigned long request_id;
  boolean  response_expected;
  unsigned char reserved[3];
  CORBA_Sequence_Octet object_key;
  CORBA_String operation;
  CORBA_Sequence_Octet requesting_principal;
} GIOP_RequestHeader_1_1;

typedef struct {
  unsigned long request_id;
  unsigned char response_flags;
  unsigned char reserved[3];
  unsigned short target_type;
  GIOP_TargetAddress target;
  CORBA_String operation;
  IOP_ServiceContextList service_context;
} GIOP_RequestHeader_1_2;

typedef GIOP_RequestHeader_1_2 GIOP_RequestHeader_1_3;

typedef union{
  GIOP_RequestHeader_1_0  _1_0;
  GIOP_RequestHeader_1_1  _1_1;
  GIOP_RequestHeader_1_2  _1_2;
} GIOP_RequestHeader;

/*
 * GIOP Reply Header
 */
typedef struct {
  IOP_ServiceContextList service_context;
  unsigned long request_id;
  unsigned long reply_status;
} GIOP_ReplyHeader_1_0;

typedef GIOP_ReplyHeader_1_0 GIOP_ReplyHeader_1_1;

typedef struct {
  unsigned long request_id;
  unsigned long reply_status;
  IOP_ServiceContextList service_context;
} GIOP_ReplyHeader_1_2;

typedef GIOP_ReplyHeader_1_2 GIOP_ReplyHeader_1_3;

typedef union{
  GIOP_ReplyHeader_1_0  _1_0;
  GIOP_ReplyHeader_1_2  _1_2;
} GIOP_ReplyHeader;


typedef struct {
  CORBA_String  exception_id;
  unsigned long minor_code_value;
  unsigned long completion_status;
} GIOP_SystemExceptionReplyBody;


/*
 * GIOP Cancel Request Header
 */
typedef struct {
  unsigned long request_id;
} GIOP_CancelRequestHeader;

/*
 * GIOP Locate Request Header
 */
typedef struct {
  unsigned long request_id;
  CORBA_Sequence_Octet object_key;
} GIOP_LocateRequestHeader_1_0;

typedef GIOP_LocateRequestHeader_1_0 GIOP_LocateRequestHeader_1_1;

typedef struct {
  unsigned long request_id;
  unsigned short target_type;
  GIOP_TargetAddress target;
} GIOP_LocateRequestHeader_1_2;

typedef GIOP_LocateRequestHeader_1_2 GIOP_LocateRequestHeader_1_3;

typedef union {
   GIOP_LocateRequestHeader_1_0 _1_0;
   GIOP_LocateRequestHeader_1_2 _1_2;
} GIOP_LocateRequestHeader;


/*
 * GIOP Locate Reply Header
 */
typedef struct {
  unsigned long request_id;
  unsigned long locate_status;
} GIOP_LocateReplyHeader_1_0;

typedef GIOP_LocateReplyHeader_1_0 GIOP_LocateReplyHeader_1_1;
typedef GIOP_LocateReplyHeader_1_0 GIOP_LocateReplyHeader_1_2;
typedef GIOP_LocateReplyHeader_1_0 GIOP_LocateReplyHeader_1_3;

typedef GIOP_LocateReplyHeader_1_0 GIOP_LocateReplyHeader;

typedef struct{
  unsigned long status;
  unsigned long body_size;
  octet *body;
  GIOP_SystemExceptionReplyBody exception;
} GIOP_ReplyBody;

/*
 * GIOP CloseConnection Header
 */

/*
 * GIOP MessageError Header
 */

/*
 * GIOP Fragment Request Header
 */

typedef struct {
  unsigned long request_id;
} GIOP_FragmentHeader_1_2;

typedef GIOP_FragmentHeader_1_2 GIOP_FragmentHeader_1_3;

typedef enum {
  CONNECTION_TYPE_SOCKET = 0,
  CONNECTION_TYPE_SHMC,
} GIOP_ConnectionType;
  
typedef struct
{
  GIOP_ConnectionType type;
  int	sock;
#ifdef USE_SHMC
  Shmc *shmc;
#endif
} GIOP_ConnectionHandler;

int GIOP_ConnectionHandler_recv(GIOP_ConnectionHandler *, char *buf, int size);
int GIOP_ConnectionHandler_send(GIOP_ConnectionHandler *, char *buf, int size);
void GIOP_ConnectionHandler_close(GIOP_ConnectionHandler *h);	
void * GIOP_ConnectionHandler_get_arg(GIOP_ConnectionHandler *h);

typedef struct GIOP_Request_struct {
  GIOP_ConnectionHandler *connh;
  char *buf;
  void *object;
} GIOP_Request_struct;

typedef GIOP_Request_struct * GIOP_Request_Item;

#ifdef __cplusplus
}
#endif 
#endif
