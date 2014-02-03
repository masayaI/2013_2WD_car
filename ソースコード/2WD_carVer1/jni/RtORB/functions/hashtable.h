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
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2008/01/08 07:56:06 $
 *  $Id: hashtable.h,v 1.1.1.1 2008/01/08 07:56:06 yoshi Exp $
 *
 */
/*
 *  Hash table
 */

#ifndef __FUNC_HASHTABLE_H__
#define __FUNC_HASHTABLE_H__

unsigned long elfhash(const unsigned char *name) ;
int cmp_string(char *str1, char *str2);

hashtable *createHashtable(int size);
void set_cmp_func(hashtable *tbl, int (*cmp_func)());
void set_hash_func(hashtable *tbl, unsigned long (*hash_func)());
void set_delete_func(hashtable *tbl, void (*del_func)());

hashtable *resizeHashtable(hashtable *tbl, int size);
void rehash_table(hashtable *tbl);
void destoryHashTable(hashtable *tbl);

int getNewKey(hashtable *tbl, void *k);
int hashtableNextKey(hashtable *tbl, int k);
hashtableItem *getItemByKey(hashtable *tbl, void *k);
int getIndexByKey(hashtable *tbl, void *k);
void *getValue(hashtable *tbl, void *key);
int registerItem(hashtable *tbl, void *k, void *val);
void deleteItem(hashtable *tbl, void *k);

#endif
