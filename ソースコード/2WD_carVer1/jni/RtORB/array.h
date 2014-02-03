/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 * array.h
 *
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif 

typedef struct {
  unsigned long length;
  unsigned long maximum;
  unsigned long *array;

  void (*free_op)(unsigned long);
} PtrArray;


//// Array
PtrArray * new_PtrArray();
void destroy_PtrArray(PtrArray *array);
unsigned int PtrArray_add (PtrArray *array, void *new_data);
int PtrArray_delete(PtrArray *array, int index);
void *PtrArray_get(PtrArray *array, int index);
int PtrArray_find(PtrArray *array, void *val, int (*cmp)(void*,unsigned long) );
void PtrArray_foreach(PtrArray *array, void *(*func)(unsigned long) );

#ifdef __cplusplus
}
#endif 

#endif
