/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 * socket.h
 *
 *      Copyright(c) Isao Hara, 2006
 *
 * $Revision: 1.2 $
 * $Date: 2008/05/29 04:54:57 $
 * $Id: socket.h,v 1.2 2008/05/29 04:54:57 yoshi Exp $
 *
 */

#ifndef __FUNC_SOCKET_H__
#define __FUNC_SOCKET_H__


int make_server_socket_port(int port_no) ;
long accept_connection(long port_no) ;

int copy_fds_set(fd_set *target, fd_set *src) ;
int select_server_sockets(fd_set *sockbits, int server_port,
		struct timeval time_out,
	void (*connection_request)(int), int  (*command_request)(GIOP_ConnectionHandler *));

void server_socket_loop(int server_port, float time_out_float, void (*idle)(),
  void (*connection_request)(int), int (*command_request)(GIOP_ConnectionHandler *));

short get_socket_port(int sock);
char *get_ip_address(int sock);
int make_client_socket_port(char *hostname, int port);
int select_client_socket( int client_port, int timeout,
		void (*exception_request)(), int (*command_request)());

void init_SockProfile();
void clear_SockProfile(int fd);
void set_SockProfile_arg(int fd, void *arg);
void* get_SockProfile_arg(int fd);
/*
void set_SockProfile_type(int fd, int type);
void set_SockProfile_arg(int fd, void *arg);
void set_SockProfile_service(int fd, int (*command_request)());
*/


/*
void get_Servers_from_SockProfile(int *res, int *n, int start_fd);
void copy_sockport_profile(int dist, int src);
*/
int set_SockProfile(int fd, int type,
		    int (*connection_request)(int, void*),
		    int (*disconnect_request)(int, void*), int (*command_request)(GIOP_ConnectionHandler*));

int clear_socket_profile(int fd, void (*clear_func)(int));
/*
int check_current_sockbits(int fd);
int next_active_socket(fd_set *socks, int start_fd);
int select_socket_ports( fd_set *sockbits, struct timeval time_out);
*/

void init_socket_servers();
void select_socket_servers(struct timeval time_out);

void socket_main_loop(float time_out_float, void (*idle)(), void *arg);

#endif
