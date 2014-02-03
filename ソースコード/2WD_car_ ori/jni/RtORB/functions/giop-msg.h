/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 * RtORB: giop-msg.h
 *   IIOP-GIOP
 *
 *  Copyright(C) 2006, Isao Hara, AIST
 *
 *  $Revision: 1.2 $
 *  $Date: 2008/05/20 05:46:29 $
 *  $Id: giop-msg.h,v 1.2 2008/05/20 05:46:29 yoshi Exp $
 */

#ifndef __FUNC_GIOP_MSG_H__
#define __FUNC_GIOP_MSG_H__
///////////////////////////////

#define delete_CORBA_String(str, flag)  delete_CORBA_Sequence_Octet(str, flag)

#if 0
/******* Global Variable ************/
GIOP_Version GIOP_1_0 = {1,0};
GIOP_Version GIOP_1_1 = {1,1};
GIOP_Version GIOP_1_2 = {1,2};
GIOP_Version GIOP_1_3 = {1,3};

unsigned long request_counter = 0;
#endif

///////////////////////////////////////////////////////////////////////////////
octet *setSystemException( GIOP_SystemExceptionReplyBody *e_body, char *id,  int code, int state);

void delete_CORBA_Sequence_Octet(CORBA_Sequence_Octet *seq, int flag);
void delete_IOP_ServiceContextList(IOP_ServiceContextList *list, int flag);
void delete_CORBA_TargetAddress(GIOP_TargetAddress *target, unsigned short type, int flag);

GIOP_RequestHeader *newRequestHeader();
GIOP_ReplyHeader *newReplyHeader();
GIOP_CancelRequestHeader *newCancelRequestHeader();
GIOP_LocateRequestHeader *newLocateRequestHeader();
GIOP_LocateReplyHeader *newLocateReplyHeader();
CORBA_Sequence_Octet *new_CORBA_Sequence_Octet(int size);

CORBA_Sequence_Octet *new_CORBA_Sequence_Octet2(int size);
void delete_CORBA_Sequence_Octet2(CORBA_Sequence_Octet *seq, int flag);

void set_CORBA_Sequence_Octet(CORBA_Sequence_Octet *seq, octet *val, int size);
void clear_CORBA_Sequence_Octet(CORBA_Sequence_Octet *seq);

void deleteRequestHeader(GIOP_RequestHeader *header, int version);
void deleteSystemExceptionReplyBody(GIOP_SystemExceptionReplyBody *exp);
void deleteReplyBody(GIOP_ReplyBody *body);
void deleteReplyHeader(GIOP_ReplyHeader *header, int version);
void deleteLocateRequestHeader(GIOP_LocateRequestHeader *header, int version);

//////////////////////////////////////////////////////////////////////////////////
//   demarshal Messages
int deMarshalRequest(GIOP_RequestHeader *header, CORBA_Sequence_Octet *body,
		char *buf, GIOP_MessageHeader *m_header);
int deMarshalRequest_1_0(GIOP_RequestHeader *Header, CORBA_Sequence_Octet *body,
		char *buf, GIOP_MessageHeader *m_header);
int deMarshalRequest_1_2(GIOP_RequestHeader *Header, CORBA_Sequence_Octet *body,
		char *buf, GIOP_MessageHeader *m_header);

int deMarshalReply(GIOP_ReplyHeader *header, CORBA_Sequence_Octet *body,
		unsigned char *buf, GIOP_MessageHeader *m_header);

int deMarshalCancelRequest(GIOP_CancelRequestHeader *header,
		unsigned char *buf, GIOP_MessageHeader *m_header);

int deMarshalLocateRequest(GIOP_LocateRequestHeader *header,
		unsigned char *buf, GIOP_MessageHeader *m_header);

int deMarshalLocateReply(GIOP_LocateReplyHeader *header,
		CORBA_Sequence_Octet *body, 
		unsigned char *buf, GIOP_MessageHeader *m_header);

/////////////////////////////////////////////////////////////////////////////
//   Marshal Request & Reply
/////////////////////////////////////////////////////////////////////////////
int MarshalRequest(char *buf, GIOP_RequestHeader *header, octet *body,
		int body_size, int version);
int MarshalRequest_1_0(char *buf, GIOP_RequestHeader *Header, octet *args,
		int size, int version);
int MarshalRequest_1_2(char *buf, GIOP_RequestHeader *Header, octet *args,
		int size, int version);
int MarshalReply(unsigned char *buf, int *size, GIOP_ReplyHeader *header,
		octet *body, int body_size, int version);
int MarshalLocateRequest(char *buf, GIOP_LocateRequestHeader *header,
		int version);
int MarshalLocateReply(unsigned char *buf, int *size,
		GIOP_LocateReplyHeader *header, char *ior, int version);
unsigned long next_request_id();

#define RTORB_LITTLE_ENDIAN (1)
#define RTORB_BIG_ENDIAN    (0)

#define RTORB_BYTE_ORDER RTORB_LITTLE_ENDIAN

#endif
