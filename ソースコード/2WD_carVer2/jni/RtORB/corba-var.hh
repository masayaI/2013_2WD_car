/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/* $Id: corba-var.hh,v 1.5 2008/01/30 12:22:25 yoshi Exp $ */ 
#ifndef CORBA_var_hh
#define CORBA_var_hh

#include <RtORB/corba.h>

template <class T>
class CORBA_var {
private:
	typedef T * Ptr;
	typedef CORBA_var<T> V;
public:
	CORBA_var() : _ptr(0) {;}
	CORBA_var(const V &o) : _ptr(o._ptr) {;}
	CORBA_var(const T &t) : _ptr(&t) {;}
	CORBA_var(const T * ptr) : _ptr(const_cast<Ptr>(ptr)) {;}
        ~CORBA_var() {
	  if (_ptr) {
	    delete _ptr; _ptr = NULL;
	  }
	}
public:
	Ptr _retn() { return _ptr; }
	operator Ptr () { return _ptr; }
	operator const Ptr () const { return _ptr; }
	operator T & () { return *_ptr; }

	//	template <class S> operator * () { return _ptr; }

	V &operator=(const V &o) { _ptr = o._ptr; return *this; }
	//V &operator=(const Ptr &o) { _ptr = o; }
	
	V &operator=(const T &o) { _ptr = const_cast<Ptr>(&o); return *this; }
	Ptr in () { return _ptr; }
private:
	Ptr _ptr;
};

template <class T, class ImplPtr, class Ptr>
class CORBA_ptrvar {
private:
	typedef CORBA_ptrvar<T, ImplPtr, Ptr> V;
public:
	CORBA_ptrvar() {;}
	CORBA_ptrvar(const Ptr &ptr) : _ptr(ptr) {;}

	operator T     () { return *_ptr; }
	operator Ptr & () { return _ptr; }
	operator ImplPtr () { return (ImplPtr)_ptr.impl(); }
        bool operator!() const { return !_ptr; }
private:
	Ptr _ptr;
};

template <class T>
class CORBA_ptr
{
public:
	CORBA_ptr() : _ptr(0) {;}
	CORBA_ptr(T *p) : _ptr(p) {;}
	CORBA_ptr(const T *p) : _ptr(const_cast<T*>(p)) {;}

	operator T *() { return _ptr; }
private:
	T * _ptr;
};

template <class ObjPtr>
class CORBA_ptrptr
{
private:
	typedef CORBA_ptrptr<ObjPtr> Ptr;
public:
	CORBA_ptrptr() : _objptr(0) {;}
	CORBA_ptrptr(ObjPtr objptr) : _objptr(objptr) {;}
	//CORBA_ptrptr(const ObjPtr objptr) : _objptr(const_cast<ObjPtr>(objptr)) {;}

	Ptr & operator=(const Ptr &p) {
		_objptr = p._objptr;
		return *this;
	}
	operator ObjPtr () { return _objptr; }
	operator ObjPtr * () { return _objptr; }
private:
	ObjPtr _objptr;
};

	  
#endif // CORBA_var_hh
 

