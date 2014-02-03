/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  RtORB: giop.h
 *   IIOP-GIOP
 *
 *  Copyright(C) 2006, Isao Hara, AIST
 *
 *  $Revision: 1.2 $
 *  $Date: 2008/05/29 04:54:57 $
 *  $Id: giop.h,v 1.2 2008/05/29 04:54:57 yoshi Exp $
 *
 */

#ifndef __FUNC_GIOP_H__
#define __FUNC_GIOP_H__

/*** GIOP_Connection ***/
GIOP_Connection * GIOP_Connection__create();
void GIOP_Connection__open(GIOP_Connection *conn, short port);
void GIOP_Connection__shutdown(GIOP_Connection *conn);
void GIOP_Connection__close(GIOP_Connection *conn);
void *GIOP_Connection__run(GIOP_Connection *conn);
void GIOP_Connection__free(GIOP_Connection *conn);

#if 0
GIOP_Connection * newGIOP_ServerConnection(short port);
void shutdownGIOP_ServerConnection(GIOP_Connection *conn);
void deleteGIOP_Connection(GIOP_Connection *conn);
void runGIOP_Server_Connection(GIOP_Connection *conn);
#endif

GIOP_MessageHeader *GIOP_Create_MessageHeader(int order, int version);
int receiveMessage(GIOP_ConnectionHandler *h, GIOP_MessageHeader *header, octet *buf, int maxMsg);
int reply_Message(GIOP_ConnectionHandler *h, GIOP_RequestHeader *request_header,
		GIOP_ReplyBody *reply_body, int version);

GIOP_ReplyBody *invokeServant(PortableServer_POA poa,
		GIOP_RequestHeader *header, 
		CORBA_Environment *env, octet *arg_buf, int version, int order);

int find_object(PortableServer_POA poa, char *key, char *ior);
int reply_locateMessage(PortableServer_POA poa, GIOP_ConnectionHandler *h,
		GIOP_LocateRequestHeader *locate_request_header, int version);

unsigned long createRequest(octet *buf, int response, char *object_key,
		int object_key_len, char *operation, int operation_len,
		octet *args, int args_len, int version);

unsigned long createCancelRequest(octet *buf, unsigned long request_id);
int createLocateRequest(octet *buf, char *object_key, int len);
unsigned long createCloseConnectionMessage(octet *buf);
unsigned long createMessageErrorMessage(octet *buf);
int requestLocation(GIOP_ConnectionHandler *h, CORBA_URL *ior);
int confirmLocation(GIOP_ConnectionHandler *h, CORBA_URL *ior);
int RecvMessage(GIOP_ConnectionHandler *h);
void free_request(void *arg);
PtrList *GIOP_enqueue_request(GIOP_ConnectionHandler *h, PtrList *lst);
PtrList *GIOP_execute_request(PortableServer_POA, PtrList *lst);

#endif
