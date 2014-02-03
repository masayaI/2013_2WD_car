/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/* $Id: server_loop.h,v 1.2 2008/05/29 04:54:57 yoshi Exp $ */ 
#ifndef __FUNC_SERVER_LOOP_H__
#define __FUNC_SERVER_LOOP_H__

void server_loop(float time_out_float, void (*idle)(void*), void *arg);

#endif /* __FUNC_SERVER_LOOP_H__ */
 
