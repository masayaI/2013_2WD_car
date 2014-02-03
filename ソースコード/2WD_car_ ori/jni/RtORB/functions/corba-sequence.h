/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */

/*
 *  Sequence:
 *
 *
 */
#ifndef __FUNC_CORBA_SEQUENCE_H__
#define __FUNC_CORBA_SEQUENCE_H__

////// CORBA_Sequence
unsigned long get_octet_size(unsigned long type);
unsigned long sizeof_CORBA_Sequence(CORBA_Sequence *seq);
CORBA_Sequence *new_CORBA_Sequence(unsigned long type, unsigned long len);
int copy_CORBA_Sequence_Octet(CORBA_Sequence_Octet *dist, CORBA_Sequence_Octet *src);
CORBA_SequenceBase *CORBA_SequenceBase__new(int _max, int _len);
void CORBA_SequenceBase__add(CORBA_SequenceBase *seq,  void *val);
void CORBA_SequenceBase__set(CORBA_SequenceBase *seq, int idx, void *val);
void CORBA_SequenceBase__clear(CORBA_SequenceBase *seq, void (*_free)());
void CORBA_SequenceBase__delete(CORBA_SequenceBase *seq, void (*_free)(), int flag);

#endif
