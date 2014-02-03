/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/* $Id: corba-object-defs.hh,v 1.27 2008/06/06 08:01:40 yoshi Exp $ */
#ifndef __CORBA_OBJECT_DEFS_HH__
#define __CORBA_OBJECT_DEFS_HH__

extern "C"{
#include <RtORB/corba-defs.h>
}

#include <RtORB/corba-object-defs.h>

namespace CORBA {

  class Object;
  class Object_var;

  class Object_ptr
  {
  public:
    void set(CORBA_Object);
  public:
    Object_ptr() : _obj(NULL) {}
    Object_ptr(void *);
    Object_ptr(CORBA_Object impl);
    Object_ptr(Object *p);
    Object_ptr(const Object_ptr& ptr);

    virtual ~Object_ptr();

    bool operator!() {
      return _obj == NULL? true: false;
    }
    Object * operator->() { return _obj; }

    operator CORBA_Object () { return impl(); }
	  
    Object *object() { return _obj;}
    CORBA_Object impl();
  private:
    Object *_obj;
  };

  class Object
  {
    friend struct CORBA_any;
  public:
    typedef Object_ptr _ptr_type;
    typedef Object_var _var_type;
	  
  private:
    int _ref;

  public:
    void *_private;
    CORBA_Environment ev;
    CORBA_Object  _impl;

  public:
    Object();
    virtual ~Object();

    Object(Object * obj);
    Object(CORBA_Object obj);
    Object(const Object& other);

    Object& operator=(const Object &other);

    Object* duplicate();
    bool _release();

    operator Object_ptr () { return Object_ptr(this); }

    CORBA_boolean _is_equivalent(Object_ptr othor); 
    static Object_ptr _duplicate(Object_ptr ptr);
    static Object_var _duplicate(Object_var var);

    CORBA_Object release();
    // CORBA_ptr _nil() causes the ambiguous type matching of copy operator
    // Use this instead.
    static CORBA_Object _nil() { return NULL; }
    CORBA_Object impl() const { return _impl; }
    CORBA_Object * implptr() { return &_impl; }

    CORBA_boolean _non_existent();
    
  };


#if 0
#define COD_DUMP(MSG) printf MSG; printf("\n")
#else
#define COD_DUMP(MSG) 
#endif

  class Object_var
  {
    typedef Object_var Var;
  private:
    Object * _obj;
  private:
    CORBA_Environment * getEnv(CORBA_Object impl);
  private:
    void set(CORBA_Object impl);
    void free_();
  public:
    Object_var();
    Object_var(const Var &o);
    Object_var(Object *p);
    Object_var(CORBA_Object impl);
    Object_var(Object_ptr ptr);
    
    ~Object_var();

    operator Object_ptr ();
    
    Object * operator->();
    bool     operator!();
    Var &    operator=(CORBA_Object impl);
    Var &    operator=(Object_ptr);
    
    Object * object();
    Object * in() const { return _obj;}
    Object * inout() { return _obj;}
    Object_ptr & out(){ Object_ptr _ptr=Object_ptr(_obj);
     return _ptr;
     }

    CORBA_Object impl() { return _obj->impl();}

  };

  class Object_helper {
  public:
    static CORBA_Object _retnew(CORBA_Object obj) {
      return obj;
    }
  };

  class Object_arg {
  public:
    Object_arg(Object_ptr ptr) : _ptr(ptr) {;}
    operator CORBA_Object() { return _ptr.impl(); }
    operator Object_ptr() { return _ptr.impl(); }
  private:
    Object_ptr _ptr;
  };
  typedef Object_arg Object_CInArg;
  typedef Object_arg Object_COutArg;
  typedef Object_arg Object_CInOutArg;
  typedef Object_arg Object_CppInArg;
  typedef Object_arg Object_CppOutArg;
  typedef Object_arg Object_CppInOutArg;
}

template <class T>
class CORBA_Narrow
{
public:
  static T * narrow(CORBA::Object_ptr ptr) {
    if (!ptr) { return NULL; }
    CORBA_Object impl = ptr.impl();
    return new T(impl);
  }
};

#endif /* __CORBA_OBJECT_DEFS_HH__ */
