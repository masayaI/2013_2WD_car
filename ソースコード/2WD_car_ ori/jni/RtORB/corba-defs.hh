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
 *
 */

#ifndef __CORBA_HH__
#define __CORBA_HH__
extern "C"{
#include <RtORB/corba.h>
}

#include "RtORB/corba-object-defs.hh"


namespace CORBA{

  class ORB;

  typedef CORBA_string String;
  typedef CORBA_string_ptr String_ptr;
  typedef CORBA_string_var String_var;

 extern ORB *_root_ORB_;

  class Exception
  {
  private:
    CORBA_Environment *ev;
  public:
    char _msg[256];

    const char *msg();
  protected:
    Exception();
    Exception(const char *type);
    Exception(const char *type, const char *msg);
    Exception(const char *type, CORBA_Environment *ev);
  public:
    virtual ~Exception() {}
  };
  class UserException : public Exception
  {
  public:
    UserException();
    UserException(CORBA_Environment *ev);
    virtual ~UserException() {}
  };
  class SystemException : public Exception
  {
  public:
    unsigned long minor;

    SystemException(CORBA_Environment *ev);
    SystemException(const char *msg);
    void minor(unsigned long minor_val){ minor = minor_val; }
    unsigned long minor(){ return minor; }
  };

  class COMM_FAILURE : public Exception {};

  class INV_OBJREF : public Exception {};
  class OBJECT_NOT_EXIST : public Exception {};
  class OBJ_ADAPTER : public Exception {};

  //  Class ORB
  //
  class ORB;
  
  //
  // Class Object
  //
  //class Object
  class ORB : public Object {
  public:
    class InvalidName {};
    typedef ORB * Ptr;


    public:
      CORBA_ORB _impl;
      CORBA_Environment ev;

    public:
      ORB();
      ORB(CORBA_ORB);
      ORB(const ORB& other);
      ~ORB();

      void __set_impl(CORBA_ORB orb);
      CORBA_boolean __is_nil();
	  
      Object_ptr resolve_initial_references(char *name) throw (Exception);
      String_ptr object_to_string(Object_ptr obj) throw (Exception);
      String_ptr object_to_string2(CORBA_Object obj) throw (Exception);
      void run();
      void shutdown(boolean flag);
      void destroy();
      static Ptr _duplicate(Ptr ptr) { return ptr->_duplicate(); }
      Ptr _duplicate();
	  
    static Ptr _nil();

    Object_ptr string_to_object(const char*) throw (Exception);

    CORBA_boolean work_pending();
    void perform_work();

    inline CORBA_ORB impl() { return _impl; }
    inline CORBA_ORB in() { return _impl; }
  };
  typedef ORB* ORB_ptr;

  class ORB_var
  {
  private:
    ORB * _ptr;
  public:
    ORB_var() : _ptr(NULL) {};
    ORB_var(ORB *obj) : _ptr(obj) {};
    ~ORB_var();
    
    ORB_ptr operator->() { return _ptr; }
    operator ORB_ptr () { return _ptr; }
    operator Object_ptr () { return Object_ptr(_ptr); }

//    ORB_var & operator=(ORB *ptr);
    ORB_var & operator=(ORB_ptr ptr);

    ORB * in(){ return _ptr; }
  };

  ORB_ptr ORB_init(int& argc, char **argv);

  /*
   *
   *
   */
  CORBA_string string_dup(const char *);
  CORBA_string string_alloc(CORBA_unsigned_long);

  CORBA_boolean is_nil(Object_ptr ptr);
/*
  {
    if(!ptr){
      return true;
    }else{
      if (ptr.object()){
        return false;
      }else{
        return true;
      }
    }
//    return !ptr? true: (!ptr.object() ? true : false);
  }
*/

  typedef CORBA_boolean 	Boolean;
  typedef CORBA_double 		Double;
  typedef CORBA_float 		Float;
  typedef CORBA_long 		Long;
  typedef CORBA_char 		Char;
  typedef CORBA_unsigned_long 	ULong;
  typedef CORBA_octet		Octet;
  typedef CORBA_short		Short;
  typedef CORBA_unsigned_short  UShort;

  typedef Double 		Double_var;
  typedef Float			Float_var;
  typedef Boolean		Boolean_var;

  template <typename T>
  class ValueType_helper
  {
  private:
    T _v;
  public:
    ValueType_helper(T v) : _v(v) {}
    operator T () { return _v; }
  public:
    static T _retnew(T v) { return v; }
  };

#define DECLARE_VALUETYPE_HELPERS(CLS) \
typedef ValueType_helper<CLS> CLS##_helper; \
typedef ValueType_helper<CLS> CLS##_CInArg; \
typedef ValueType_helper<CLS> CLS##_COutArg; \
typedef ValueType_helper<CLS> CLS##_CInOutArg; \
typedef ValueType_helper<CLS> CLS##_CppInArg; \
typedef ValueType_helper<CLS> CLS##_CppOutArg; \
typedef ValueType_helper<CLS> CLS##_CppInOutArg; \

  DECLARE_VALUETYPE_HELPERS(Long);
  DECLARE_VALUETYPE_HELPERS(ULong);
  DECLARE_VALUETYPE_HELPERS(Boolean);
  DECLARE_VALUETYPE_HELPERS(Double);

#undef DECLARE_VALUETYPE_HELPERS

};

class CORBA_string_helper
{
public:
  CORBA_string_helper(const char * s) : _s(s) {;}

  operator const char *() { return _s; }
private:
  const char *_s;
public:
  static CORBA_string _retnew(CORBA_string s) { return s; }
};

typedef CORBA_string_helper CORBA_string_CInArg;
typedef CORBA_string_helper CORBA_string_COutArg;
typedef CORBA_string_helper CORBA_string_CInOutArg;
typedef CORBA_string_helper CORBA_string_CppInArg;
typedef CORBA_string_helper CORBA_string_CppOutArg;
typedef CORBA_string_helper CORBA_string_CppInOutArg;

class CORBA_enum_helper
{
public:
  CORBA_enum_helper(int n) : _n(n) {}
  operator int () { return _n; }
private:
  int _n;
public:
  static int _retnew(int n) { return n; }
};


#define DECLARE_VALUETYPE_HELPERS(CLS) \
typedef CORBA::ValueType_helper<CLS> CLS##_helper; \
typedef CORBA::ValueType_helper<CLS> CLS##_CInArg; \
typedef CORBA::ValueType_helper<CLS> CLS##_COutArg; \
typedef CORBA::ValueType_helper<CLS> CLS##_CInOutArg; \
typedef CORBA::ValueType_helper<CLS> CLS##_CppInArg; \
typedef CORBA::ValueType_helper<CLS> CLS##_CppOutArg; \
typedef CORBA::ValueType_helper<CLS> CLS##_CppInOutArg; \

  DECLARE_VALUETYPE_HELPERS(CORBA_float);

#undef DECLARE_VALUETYPE_HELPERS

#endif
