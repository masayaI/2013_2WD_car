/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/* $Id: corba-struct.hh,v 1.6 2008/04/11 07:26:40 yoshi Exp $ */ 
#ifndef __CORBA_STRUCT_HH__
#define __CORBA_STRUCT_HH__

namespace CORBA_struct {

  template <class T> class T_Var;
  
  template <class T>
  class T_Out
  {
    typedef T_Out<T> Out;
    typedef T_Var<T> Var;
  private:
    T * _ref;
  public:
    T_Out(T * ref) : _ref(ref) {}
    T_Out(const T_Out &o) : _ref(o._ref) {}

    T * ptr() { return _ref; }

    operator T & () {
      /* supposed to be NOT NULL */
      return *_ref;
    }

    Out & operator=(T *t)
    {
      _ref = t;
      return *this;
    }
  };

  template <class T>
  class T_Arg
  {
  public:
    T_Arg(T *p) : _ptr(p) {}
    T_Arg(const T &t) : _ptr( const_cast<T*>(&t) ) {}

    operator T * () { return _ptr; }
    operator T ** () { return &_ptr; }
    operator T & () { return *_ptr; }
  private:
    T * _ptr;
  };

  template <class T>
  class T_COutArg
  {
    typedef T_Out<T> Out;
  private:
    Out *_out;
  public:
    T_COutArg(T * t) : _out(NULL) {
      _out = new Out(t);
    }
    
    T_COutArg(T** pp) : _out(NULL) {
      T *p = *pp;
      if (!p) {
	p = new T();
	*pp = p;
      }
      _out = new Out(p);
    }
    ~T_COutArg() {
      if (_out) {
	delete _out; _out = NULL;
      }
    }

    operator T & () { return *(_out->ptr()); }
    operator Out & () { return *_out; }
  };

  template <class T>
  class T_Helper
  {
  public:
    static T * _retnew(T &t) {
      T *p = new T();
      *p = t;
      return p;
    }
  };

  template <class T>
  class T_Ptr
  {
  public:
    T_Ptr(T * p) : _ptr(p) {;}
    T_Ptr(const T & o) : _ptr(const_cast<T*>(&o)) {;}

    operator T *() { return _ptr; }
    operator T &() { return _ptr; }

    T * operator->() { return _ptr; }
  private:
    T * _ptr;
  };

  template <class T>
  class T_Var
  {
    typedef T_Out<T> Out;
    typedef T_Var<T> Var;
    typedef T_Ptr<T> Ptr;
  public:
    T_Var() : _ptr(NULL), _out(NULL) {;}
    T_Var(T *t) : _ptr(t), _out(NULL) {;}
    ~T_Var() {
      free_();
    }

    operator T& () { return *_ptr; }
    operator Ptr () { return Ptr(_ptr); }

    Var &operator=(T *t) {
      free_();
      _ptr = t;
      return *this;
    }

    T * operator->() { return _ptr; }
  
    T *_retn() {
      T *tmp = _ptr;
      _ptr = NULL;

      free_();
      
      return tmp;
    }

    T &inout() { return *_ptr; }
    T & in() { return *_ptr; }
    Out & out() {
      if (!_out) {
	_out = new Out(_ptr);
      }
      return *_out;
    }
  private:
    void free_() {
      if (_out) {
	delete _out; _out = NULL;
      }
      if (_ptr) {
	delete _ptr; _ptr = NULL;
      }
    }
  private:
    T *_ptr;
    Out *_out;
  };


}

#endif // __CORBA_STRUCT_HH__
 
