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
 *  list.h
 *
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif 
typedef struct PtrList{
  unsigned long length;
  //unsigned long *item;
  void **item;
  struct PtrList *prev, *next;
  void (*free_op)(void**);
  char released;
} PtrList;

///// List
PtrList * PtrList_new_item(void *value, void (*free_op)(void**));
PtrList * PtrList_append(PtrList *lst, void *value, void (*free_op)(void**));
int PtrList_length(PtrList *lst);
void * PtrList_get_item(PtrList *lst, int index);
PtrList * PtrList_get(PtrList *lst, int index);
void PtrList_free(PtrList *lst);
PtrList * PtrList_remove(PtrList *lst, int index);
PtrList * PtrList_set_item(PtrList *lst, int index, void *value);
PtrList * PtrList_remove_item(PtrList *lst);
void PtrList_remove_item_all(PtrList *lst);
PtrList *PtrList_remove_released_items(PtrList *lst);
PtrList *PtrList_first(PtrList *lst);

#ifdef __cplusplus
}
#endif 

#endif
