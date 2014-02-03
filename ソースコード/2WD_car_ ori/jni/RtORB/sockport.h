/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  sockport.h
 *	Copyright(C) 2006, Isao Hara, AIST
 *
 *  $Revision: 1.3 $
 *  $Date: 2008/05/29 04:54:57 $
 *  $Id: sockport.h,v 1.3 2008/05/29 04:54:57 yoshi Exp $
 *
 */

#ifndef __SOCKPORT_H__
#define __SOCKPORT_H__

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/time.h>

#include <sys/ioctl.h>
#include <net/if.h>

#ifdef __cplusplus
extern "C"
{
#endif 

#ifndef FD_SETSIZE
#define FD_SETSIZE	32
#endif
#ifndef NFDBITS
#define NFDBITS		32
#endif

#ifndef __SOCK_ENUM__
#define __SOCK_ENUM__
enum {
  SOCK_CLOSED=0, SOCK_SERVER, SOCK_SERVICE, SOCK_CLIENT
};


enum {
  SHMC_CLOSED = SOCK_CLOSED,
  SHMC_SERVER = SOCK_SERVER,
  SHMC_SERVICE = SOCK_SERVICE,
  SHMC_CLIENT = SOCK_CLIENT,
};
  

struct sockport_profile{
  int type;
  void *arg;
  int (*connection_proc)(int, void*);
  int (*command_proc)(GIOP_ConnectionHandler*);
  int (*disconnect_proc)(int, void*);
};

#endif

/////
extern  struct sockport_profile  SockProfile[FD_SETSIZE];
/*
  2007/10/08 yoshi@msi.co.jp

  This causes compile error.
*/
/* extern  fd_set main_socket_bits;*/

#ifdef __cplusplus
}
#endif 

#endif
