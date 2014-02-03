/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 * Speech Event - Action Translator ver.1.0
 *
 *   Copyright(c) 2005    Isao Hara, AIST
 */
/*
 *  Hash table
 */

#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif 
/////////////////////
typedef struct hashtableItem{
  void *key;
  void *value;
} hashtableItem;

typedef struct hashtable{
  hashtableItem *items;
  int size;
//  int deleted;
  int n_items;
  int (*cmp_func)(char*, char*);
  unsigned long (*hash_func)(const unsigned char*);
  void  (*del_func)(hashtableItem);
} hashtable;

unsigned long elfhash(const unsigned char *name);
hashtable *createHashtable(int size);
void destoryHashTable(hashtable *tbl);
int hashtableNextKey(hashtable *tbl, int k);
int getNewKey(hashtable *tbl, void *k);
hashtableItem *getItemByKey(hashtable *tbl, void *k);
int registerItem(hashtable *tbl, void *k, void *val);
void deleteItem(hashtable *tbl, void *k );
void *getValue(hashtable *tbl, void *key);

#ifdef __cplusplus
}
#endif 
#endif
