/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef __GIOP_H__
#define __GIOP_H__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <unistd.h>

#include <RtORB/giop-defs.h>
#include <RtORB/util.h>


#ifdef __cplusplus
extern "C"
{
#endif 

GIOP_ConnectionHandler * make_client_connection(GIOP_Connection *conn);

#ifdef __cplusplus
}
#endif 

#endif
