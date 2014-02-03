/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/* $Id: corba-interface.hh,v 1.38 2008/04/18 13:38:26 yoshi Exp $ */
#ifndef __CORBA_INTERFACE_HH__
#define __CORBA_INTERFACE_HH__

#include <assert.h>


namespace CORBA_interface {

  template <typename T> class T_Ptr;

  //////////////////////////////////////////////////////////////////
  //
  //      T_Helper template class
  //
  //////////////////////////////////////////////////////////////////

  template <class T, class Ptr>
  class T_Helper 
  {
  public:
    T_Helper(CORBA_Object impl) : _ptr(impl) {}
    T_Helper(Ptr ptr) : _ptr(ptr) {}

    operator CORBA_Object () { return _ptr.impl(); }
    operator Ptr () { return _ptr; }
    operator CORBA_Object *() {
	    CORBA::Object *obj = _ptr.object();
	    return obj? obj->implptr(): NULL;
    }
      
  private:
    Ptr	_ptr;
  public:

    static CORBA_Object _retnew(Ptr ptr)
    {
      if (!ptr) { return NULL; }
      CORBA_Object impl = ptr->release();
      ptr.free_(true);
      return impl;
    }
    static Ptr _retnew(CORBA_Object obj)
    {
      return new T(obj);
    }
  };


  template <class T>
  class ObjHelper
  {
  public:
	  
    static T * duplicate(T *p)
    {
      if (!p) { return NULL; }
      return duplicate(p->_impl, &p->ev);
    }

    static T * duplicate(CORBA_Object obj)
    {
      if (!obj) { return NULL; }
      return duplicate(obj, NULL);
    }

    static T * release(CORBA::Object *p) {
      if (p) {
       if(!p->_release()){
         delete p;
       }
      }
      return NULL;
    }
    
    static T * destroy(CORBA::Object *p) {
      if (p) {
      	delete p;
      }
      return NULL;
    }
    
    static T * duplicate(CORBA_Object obj, CORBA_Environment *ev)
    {
      if (!obj) { return NULL; }
       CORBA_Object_duplicate(obj, ev);

      return new T(obj);
    }
  };

  template <class T>
  class CInArg {
    typedef T_Ptr<T> Ptr;
  public:
    CInArg(CORBA_Object impl) : _obj(NULL) {
 //     _obj = ObjHelper<T>::duplicate(impl);
      _obj = new T(impl);
    }
    ~CInArg() {
      delete _obj;
    }
    operator Ptr () { return Ptr(_obj); }
  private:
    T * _obj;
  };
  
  //////////////////////////////////////////////////////////////////
  //
  //      T_Ptr template class
  //
  //////////////////////////////////////////////////////////////////


  class Handle
  {
  protected:
    CORBA::Object * 	_obj;
  protected:
    Handle() : _obj(NULL) {
    }

    ~Handle() {
//      std::cerr << "   ~Handle()" << std::endl;
//       delete  _obj;
    }

    void delete_obj(){
      CORBA_Object_free(_obj->_impl) ;
//      std::cerr << "   Handle::delete_obj() :" << _obj << std::endl;
    }

  public:
    CORBA::Object *_object() const { return _obj;}
    CORBA_Object impl() const { return _obj? _obj->impl(): NULL; }

    operator CORBA_Object () { return impl(); }
    operator CORBA::Object_ptr () { return CORBA::Object_ptr(_obj); }
    inline operator CORBA::Object_ptr () const { return CORBA::Object_ptr(_obj); }

    bool operator!() const {
      return _obj == NULL? true: false;
    }
  };
  
  template <class T> class T_SeqElemPtr;
  
  template <class T> class T_Var;

  template <> class T_Var<CORBA::Object> : public Handle {};

  template <class T>
  class T_Var : public T_Var<typename T::_super_type>
  {
    friend class T_Ptr<T>;
  private:
    typedef T_Var<typename T::_super_type> Super;
    typedef T_Var<T> Var;
    typedef T_Ptr<T> Ptr;
    typedef ObjHelper<T> Helper;
  private:
    void set(CORBA_Object impl)
    {
      if (!impl) { return; }
      Super::_obj = new T(impl);
    }
  public:
    T_Var() : Super() {}
    T_Var(T *t) : Super(){
      Super::_obj = t;
    }
    T_Var(CORBA_Object impl);

    T_Var(Ptr p);
    T_Var(const T &t);
    T_Var(const Var &);
    virtual ~T_Var();

    Var &operator=(T *t); 
    Var &operator=(CORBA::Object_var);
    Var &operator=(CORBA_Object);
    Var &operator=(const Ptr &);
    Var &operator=(const Var &);

    
    T * _retn() {
      T *tmp = object();
      Super::_obj = 0;
      return tmp;
    }

    T * operator->() {
      return object();
    }

    T *object() const {
      return dynamic_cast<T*>(Super::_obj);
    }

/*
    T *in() const{
      return dynamic_cast<T*>(Super::_obj);
    }

    T& out() const{
      return &(dynamic_cast<T*>(Super::_obj));
    }
*/
    Ptr in() const{
      return Ptr(dynamic_cast<T*>(Super::_obj));
    }

    Ptr inout() {
      return Ptr(dynamic_cast<T*>(Super::_obj));
    }

  };


  //////////////////////////////////////////////////////////////////
  //
  //      T_Ptr template class
  //
  //////////////////////////////////////////////////////////////////

  class PtrHandle : public Handle
  {
  private:
    typedef Handle Super;
  protected:
    bool 		_release;
    PtrHandle() : Super(), _release(false) {
    }
    ~PtrHandle() {
//      std::cerr << "   ~PtrHandle() :" << _obj << std::endl;
    }
    void delete_obj(){
     // delete  _obj;
//      std::cerr << "   ~delete_obj() :" << _obj << std::endl;
      Super::delete_obj();
    }
  };


  template <typename T> class T_Ptr;
  template <> class T_Ptr<CORBA::Object> : public PtrHandle {};

  template <typename T>
  class T_Ptr : public T_Ptr<typename T::_super_type>
  {
    friend class T_Var<T>;
  private:
    typedef T_Ptr<typename T::_super_type> Super;
    typedef T_Ptr<T> Ptr;
    typedef T_Var<T> Var;
  private:
    void set(CORBA_Object impl)
    {
      if (!impl) { return; }
      T * obj = new T(impl);
      obj->duplicate();
      Super::_obj = obj;
      Super::_release = true;
    }
  private:
  public:

    T_Ptr() : Super() { }
    T_Ptr(const Ptr &o) : Super()
    {
      if (o.object() != NULL){
//        Super::_obj = (o.object())->duplicate();
        Super::_obj = o.object();
     }
    }
    
    T_Ptr(T * t) : Super()
    {
      Super::_obj = t;
    }
    T_Ptr(T &t) : Super() {
      Super::_obj = t;
    }

    T_Ptr(CORBA_Object impl) : Super() {
      set(impl);
    }

    T_Ptr(CORBA::Object_ptr ptr) {
//      Super::_obj = (ptr.operator->())->duplicate();
      Super::_obj = ptr.operator->();
    }

    T_Ptr(const Var &o)
    {
      if (o._obj != NULL){
//        Super::_obj = (o._obj)->duplicate();
        Super::_obj = o._obj;
     }
    }
    virtual ~T_Ptr() {
//      std::cerr << "   ~T_Ptr()" << "   _obj:" << Super::_obj << std::endl;
      if (Super::_release) {
//	delete Super::_obj;
	delete_obj();
	Super::_obj = NULL;
	Super::_release = false;
      }

    }

    void delete_obj(){
//      std::cerr << "   Super::delete_obj() :"  << std::endl;
      Super::delete_obj();
    }
	  
    Ptr & operator=(T *t);
    Ptr & operator=(const T &t);
    Ptr & operator=(const Ptr &o);
    Ptr & operator=(const Var &);

    Ptr & operator=(CORBA_Object impl) {
      set(impl);
      return *this;
    }

    T * operator->() {
      return object();
    }
    
    T * operator->() const {
      return object();
    }

    operator T * () { return object(); }
    operator T & () { return *Super::_obj; }

    T *object() const {
      return dynamic_cast<T*>(Super::_obj);
    }

    T *in() {
      return dynamic_cast<T*>(Super::_obj);
    }

    void free_(bool force)
    {
      if (Super::_obj) {
        if(!Super::_obj->_release()){
          delete Super::_obj;
        }
      }
      Super::_obj = NULL;
      Super::_release = false;
    }
  };


  //////////////////////////////////////////////////////////////////
  //
  //      T_SeqElemPtr member implementation
  //
  //////////////////////////////////////////////////////////////////

  template <class T>
  class T_SeqElemPtr
  {
    typedef T_SeqElemPtr<T> This;
    typedef T_Ptr<T> Ptr;
  private:
    CORBA_Object &_impl;
    T *	_obj;
  private:
    T_SeqElemPtr() {}
  public:
    T_SeqElemPtr(CORBA_Object &impl) : _impl(impl), _obj(NULL) {}
    T_SeqElemPtr(const This &o) : _impl(o._impl), _obj(NULL) {}

    virtual ~T_SeqElemPtr() {
      if (_obj) {
	delete _obj; _obj = NULL;
      }
    }

    T * operator->() { return object(); }

    operator Ptr () { return Ptr(_impl); }
    operator CORBA::Object_ptr () { return CORBA::Object_ptr(_impl); }

    //
    // Copy operators 
    //
    //  Call free_() every time copy operator is called!!
    //
    This & operator=(CORBA_Object impl) {
      free_();
      _impl = impl;
      return *this;
    }
    
    This & operator=(Ptr ptr)
    {
      free_();
      _impl = ptr.impl();
      return *this;
    }
    This & operator=(const This &o)
    {
      free_();
      _impl = o._impl;
      return *this;
    }
    This & operator=(CORBA::Object_ptr ptr)
    {
      free_();
      _impl = ptr.impl();
      return *this;
    }
  public:
    T * object() {
      if (!_obj) {
	_obj = new T(_impl);
      }
      return _obj;
    }

    T * in() { return object(); }
  private:
    void free_()
    {
      if (_obj) {
	delete _obj; _obj = NULL;
      }
    }
  private:
    This &operator=(T *) {}
  };
  

  //////////////////////////////////////////////////////////////////
  //
  //      T_Var member implementation
  //
  //////////////////////////////////////////////////////////////////

  template <class T> T_Var<T>::T_Var(Ptr p) : Super() {
    Super::_obj = Helper::duplicate(p.object());
  }

  template <class T> T_Var<T>::T_Var(const Var &o) : Super()
  {
    Super::_obj = Helper::duplicate(o.object());
  }

  template <class T> T_Var<T>::T_Var(CORBA_Object impl) : Super() {
    Super::_obj = Helper::duplicate(impl);
  }

  template <class T> T_Var<T>::~T_Var() {
    Helper::destroy(Super::_obj);
    Super::_obj = NULL;
  }

  template <class T> T_Var<T> & T_Var<T>::operator=(T *t) {
    Helper::release(Super::_obj);
//    Super::_obj = Helper::duplicate(t);
    Super::_obj = t;
    return *this;
  }

  template <class T> T_Var<T> & T_Var<T>::operator=(CORBA_Object impl) {
    Helper::release(Super::_obj);
    Super::_obj = Helper::duplicate(impl);
    return *this;
  }
  
  template <class T> T_Var<T> & T_Var<T>::operator=(const Var &var) {
    Helper::release(Super::_obj);
    Super::_obj = Helper::duplicate(var.object());
    return *this;
  }

  template <class T> T_Var<T> & T_Var<T>::operator=(const Ptr &p) {
    Helper::release(Super::_obj);
    Super::_obj = p.object();
    return *this;
  }
  
  //////////////////////////////////////////////////////////////////
  //
  //      T_Ptr member implementation
  //
  //////////////////////////////////////////////////////////////////

  template <class T> T_Ptr<T> & T_Ptr<T>::operator=(T *t) {
    free_(false);
    Super::_obj = t;
    return *this;
  }

  template <class T> T_Ptr<T> & T_Ptr<T>::operator=(const T_Ptr<T> &o)
  {
    free_(false);
    CORBA_Object impl = o.impl();
    set(impl);
    return *this;
  }

  template <class T> T_Ptr<T> & T_Ptr<T>::operator=(const T_Var<T> &v)
  {
    free_(false);
    Super::_obj = (v._obj)->duplicate();
    return *this;
  }

  template <class T>
  class Utils
  {
    typedef T_Ptr<T> Ptr;
  public:
    static Ptr duplicate(Ptr ptr) {
      if (!ptr) { return (T*) NULL; }
      CORBA_Object impl = ptr.impl();
      return new T(impl);
    }
  };
}

#endif /* __CORBA_INTERFACE_HH__ */
