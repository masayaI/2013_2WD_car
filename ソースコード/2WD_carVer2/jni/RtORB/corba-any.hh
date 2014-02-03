/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
#ifndef __CORBA_ANY_HH__
#define __CORBA_ANY_HH__

namespace CORBA {
	
  typedef CORBA_any Any;
  typedef Any * Any_ptr;

  class Any_out {
    Any ** _pp;
  public:
    Any_out() : _pp(NULL) {}
    Any_out(Any **pp) : _pp(pp) {}
    Any * ptr() { return *_pp; }

    Any_out & operator=(Any *p) {
      *_pp = p;
      return *this;
    }

    operator Any ** () { return _pp; }
  };

  class Any_var {
  public:
    Any_var() : _ptr(NULL), _out(NULL) {}
    Any_var(Any *p) : _ptr(p), _out(NULL) {}

    Any_var & operator=(Any *p) {
      _ptr = p;
      return *this;
    }
    ~Any_var() {
      if (_ptr) { delete _ptr; _ptr = NULL;}
      if (_out) { delete _out; _out = NULL; }
    }
  public:
    operator Any &() { return *_ptr; }
    operator Any *() { return _ptr; }
    
    Any * _retn() {
      Any *tmp = _ptr;
      _ptr = 0;
      return tmp;
    }

    Any & inout() { return *_ptr; }
    Any & in() { return *_ptr; }
    Any_out & out() {
      if (!_out) {
	_out = new Any_out(&_ptr);
      }
      return *_out;
    }
    
    void operator<<=(ULong n);
    void operator<<=(const char *);
    void operator<<=(char *);

  private:
    Any * _ptr;
    Any_out *_out;
  };

  class Any_Arg {
  private:
    CORBA_any * _ptr;
  public:
    Any_Arg(CORBA_any * p) : _ptr(p) {}

    Any_Arg(const CORBA_any &obj) : _ptr(NULL)
    {
      _ptr = const_cast<CORBA_any*>(&obj);
    }
    
    operator CORBA_any *() { return _ptr; }
    operator CORBA_any & () { return *_ptr; }
  public:
  };

  typedef Any_Arg Any_CInArg;
  typedef Any_out Any_COutArg;
  typedef Any_Arg Any_CInOutArg;
  typedef Any_Arg Any_CppInArg;
  typedef Any_out Any_CppOutArg;
  typedef Any_Arg Any_CppInOutArg;

  class Any_helper {
  public:
    static Any * _retnew(Any *p)
    {
      return p;
    }
  };
};

#endif /* __CORBA_ANY_HH__ */
