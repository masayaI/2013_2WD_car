/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/* $Id: corba-seq.hh,v 1.48 2008/06/06 08:01:40 yoshi Exp $ */ 
#ifndef __CORBA_SEQ_HH__
#define __CORBA_SEQ_HH__

#include <RtORB/corba-defs.hh>

namespace CORBA_sequence {


  /*
  template <class T>
  class T_ElemPtrHelper
  {
  public:
    static T * nil() { return 0; }
    static T * duplicate(T *t) {
      return new T(t);
    }
    static void release(T *p) { delete p; }
  };
  */

  template <class T>
  class T_ElemRefHelper
  {
  public:
    static void nil(T &t) {
      //t = T();
      //t.T::T();
    }
    static T & duplicate(T & t) { return t; }
    static void release(T &t) {
//      fprintf(stderr, "class T_ElemRefHelper buffer=%x \n",&t);
//      delete &t;
    }
  };


  class T_ElemCOHelper
  {
  public:
    static void nil(CORBA_Object &obj)
    {
      obj = NULL;
    }
    static CORBA_Object duplicate(CORBA_Object obj) {
      if (obj) {
	CORBA_Object_duplicate(obj, NULL);
      }
      return obj;
    }
    static void release(CORBA_Object obj) {
      if (obj) {
	CORBA_Object_release(obj, NULL);
      }
    }
  };
  
  template <class T> class T_Ptr;
  template <class T> class T_SeqOut;


  template <class CType, class Elem, class ElemHelper>
  class T_Seq
  {
    typedef T_Seq<CType, Elem, ElemHelper> Seq;
  protected:
    T_Seq(int n) : _impl(NULL), _tc( CType::_type_code() ), _release(true) 
    {
      alloc();
      length((CORBA::ULong)n);
    }
    T_Seq(bool release) : _impl(NULL), _tc( CType::_type_code() ), _release(release)
    {
      alloc();
    }
    
    T_Seq(CType *impl, bool release) : _impl(impl), _tc( CType::_type_code() ), _release(release) {}
    T_Seq(const CType *impl) : _impl( const_cast<CType*>(impl) ), _tc( CType::_type_code() ), _release(false) {}
    T_Seq(const CType &o) : _impl(NULL), _tc ( CType::_type_code() ), _release(true) 
    {
      alloc();
      copy(o, *this->_impl);
    }
    T_Seq(const Seq &o) : _impl(NULL), _tc ( CType::_type_code() ), _release(true)
    {
      alloc();
      copy(*o._impl, *this->_impl);
    }
      

    void free_()
    {
      if (_release && _impl) {
	if (_impl->_length > 0) {
//            fprintf(stderr, " Call free_  (%d)\n", _impl->_length);
	  for (CORBA::ULong i=0; i<_impl->_length; i++) {
            RtORB_free_by_typecode_cpp(_tc->member_type[0], (void *)&_impl->_buffer[i], 0);
/*
	    ElemHelper::release(_impl->_buffer[i]);
*/
	  }
	  RtORB__free(_impl->_buffer, "~T_Seq(buffer)");
	}
	RtORB__free(_impl, "~T_Seq");
	_impl = NULL;
      }
    }
  public:
    virtual ~T_Seq() {
      free_();
    }

    CORBA::ULong length() const {
      return _impl != NULL? _impl->_length:0;
    }

    CORBA::ULong length(CORBA::ULong n)
    {
      return length(this->_impl, n);
    }

    void copyTo(CType &to) const
    {

      if (!_impl) {
	return;
      }
      copy(*_impl, to);
    }
/*
    void setTo(CType &to) const
    {
      if (!_impl) {
	return;
      }

      set_val(*_impl, to);
    }
*/
  public:
    static void copy(const CType &from, CType &to) {
      CORBA::ULong n = from.length();
      to.length(n);
      for (CORBA::ULong i=0; i<n; i++) {
	to._buffer[i] = ElemHelper::duplicate(from._buffer[i]);
      }
    }
/*
    static void set_val(const CType &from, CType &to) {
      to._length=from._length;
      to._maximum=from._maximum;
      to._buffer = from._buffer;
    }
*/
    static CORBA::ULong length(CType *impl, CORBA::ULong n)
    {
      CORBA::ULong i;
      if (n <= 0) { return 0; }
      
      if (impl->_buffer == NULL) {
	Elem *newbuf= (Elem *)RtORB_calloc(sizeof(Elem), n,  "CORBA_sequenct::T_Seq::length");
	for (i=0; i<n; i++) {
	  ElemHelper::nil(newbuf[i]);
	}
	impl->_buffer = newbuf;
	impl->_maximum = impl->_length = n;
      } else if (n > impl->_length) {

	size_t oldsize = impl->_length * sizeof(Elem);
	size_t newsize = n * sizeof(Elem);
	Elem * newbuf = (Elem*)RtORB_realloc(impl->_buffer, newsize, "CORBA_sequenct::T_Seq::length");
	memset(newbuf + impl->_length, 0x00, newsize - oldsize);
	for (i=impl->_length; i<n; i++) {
	  ElemHelper::nil(newbuf[i]);
	}
	impl->_buffer = newbuf;
	impl->_maximum = impl->_length = n;
      }
      return n;
    }

  protected:
    void alloc()
    {
//      if(_impl) return;
      _impl = (CType *)RtORB_alloc(sizeof(CType)*1, "T_Seq::alloc");
      _impl->_length = _impl->_maximum = 0;
      _impl->_buffer = NULL;
    }

    
  public:
    CType * _retn()  {
       CType *tmp = _impl;
       _impl = NULL;
       return tmp; 
    }
    CType * cobj() const { return _impl; }
    CType ** cptr() { return & _impl; }
    CType * release() {
      CType *tmp = _impl;
      _impl = NULL;
      return tmp;
    }

  protected:
    CType *_impl;
    CORBA_TypeCode _tc;
    bool _release;
  };

  template <class CType, class CppType>	 class T_CInArg;
  template <class CType, class CppType>	 class T_COutArg;
  template <class CType, class CppType>	 class T_CInOutArg;
  template <class CType, class CppType>	 class T_CppInArg;
  template <class CType, class CppType>	 class T_CppOutArg;
  template <class CType, class CppType>	 class T_CppInOutArg;

  template <class CType_, class Elem, class ElemHelper>
  class T_RefSeq : public T_Seq<CType_, Elem, ElemHelper>
  {
  public:
    typedef T_RefSeq<CType_, Elem, ElemHelper> Seq;
    typedef T_Seq<CType_, Elem, ElemHelper> Super;
    typedef CType_ CType;
    typedef T_Ptr<Seq> Ptr;
    typedef Elem & ElemRef;
  public:
    typedef T_CInArg<CType_, Seq> CInArg;
    typedef T_COutArg<CType_, Seq> COutArg;
    typedef T_CInOutArg<CType_, Seq> CInOutArg;
    typedef T_CppInArg<CType_, Seq> CppInArg;
    typedef T_CppOutArg<CType_, Seq> CppOutArg;
    typedef T_CppInOutArg<CType_, Seq> CppInOutArg;
  private:
  public:
    T_RefSeq(int n) : Super(n) {}
    T_RefSeq(CORBA::ULong n) : Super((int)n) {}
    T_RefSeq(bool release) : Super(release) {}
    T_RefSeq() : Super(0) {}
    T_RefSeq(CType *impl, bool release = true) : Super(impl, release) {}
    T_RefSeq(const CType *impl) : Super((const CType *) impl) {}
    T_RefSeq(const Seq &o) : Super((int)o.length()) 
    {
      o.copyTo(*this->_impl);
    }
    T_RefSeq(const CType &o) : Super(o)
    {

    }

    ~T_RefSeq() {
//	std::cerr << " ~T_RefSeq Called "<< std::endl;
    }
    
    Elem & operator[] (int n)
    {
      return element(this->_impl, n);
    }

    Elem & operator[] (CORBA::Long n)
    {
      return element(this->_impl, (int)n);
    }
    
    Elem & operator[] (CORBA::ULong n)
    {
      return element(this->_impl, (int)n);
    }

    Elem & operator[] (CORBA::ULong n) const
    {
      return element(this->_impl, (int)n);
    }

    Seq & operator=(const Seq &o)
    {
      o.copyTo(*this->_impl);
      return *this;
    }

    Elem & elementAt(int n){
      CORBA_TypeCode tc = CType::_type_code();
      int swap = tc->size / sizeof(void*);
      Elem &t = this->_impl->_buffer[n * swap];
    }

    static Elem & element(const CType *impl, int n)
    {
      Elem &t = impl->_buffer[n];
      return t;
    }
    static Elem & element(CType *impl, int n)
    {
//      CORBA_TypeCode tc = CType::_type_code();
//      int swap = tc->size / sizeof(void*);
//      Elem &t = impl->_buffer[n * swap];
      Elem &t = impl->_buffer[n];
      return t;
    }
  };

  template <class CType_, class Elem, class ElemPtr, class ElemHelper>
  class T_PtrSeq : public T_Seq<CType_, Elem, ElemHelper>
  {
  public:
    typedef T_PtrSeq<CType_, Elem, ElemPtr, ElemHelper> Seq;
    typedef T_Seq<CType_, Elem, ElemHelper> Super;
    typedef CType_ CType;
    typedef T_Ptr<Seq> Ptr;
    
    typedef ElemPtr ElemRef;
  public:
    T_PtrSeq(int n) : Super(n) {}
    T_PtrSeq(CORBA::ULong n) : Super((int)n) {}
    T_PtrSeq(bool release = true) : Super(release) {}
    T_PtrSeq(CType *impl, bool release=true) : Super(impl, release) {}
    T_PtrSeq(const CType *impl) : Super(impl) {}
    T_PtrSeq(const CType &impl) : Super(impl) {}
    T_PtrSeq(const Seq &o) : Super(o) {}

    ElemPtr operator[] (int n)
    {
      return element(this->_impl, n);
    }
    
    ElemPtr operator[] (CORBA::Long n)
    {
      return element(this->_impl, (int)n);
    }
    
    ElemPtr operator[] (CORBA::ULong n)
    {
      return element(this->_impl, (int)n);
    }

    ElemPtr operator[] (CORBA::ULong n) const
    {
      return element(this->_impl, (int)n);
    }

    Seq & operator=(const Seq &o)
    {
      o.copyTo(*this->_impl);
      return *this;
    }
  public:
    static ElemPtr element(const CType *impl, int i)
    {
      return ElemPtr(impl->_buffer[i]);
    }
    static ElemPtr element(CType *impl, int i)
    {
      return ElemPtr(impl->_buffer[i]);
    }
  };


  template <class T, bool RELEASE>
  class T_PtrVarBase
  {
    friend class T_SeqOut<T>;
  public:
    typedef typename T::ElemRef ElemRef;
    typedef T_PtrVarBase<T, RELEASE> This;
  public:
    T_PtrVarBase() : _obj(NULL), _release(RELEASE) {}
    T_PtrVarBase(T *p) : _obj(p), _release(RELEASE) {}
    T_PtrVarBase(const T &o) : _obj(NULL), _release(RELEASE)
    {
      _obj = new T(o);
    } 

    virtual ~T_PtrVarBase() {
      release();
    }
      
    ElemRef operator[] (int n)
    {
      return _obj->operator[](n);
    }
    
    ElemRef operator[] (CORBA::Long n)
    {
      return _obj->operator[](n);

    }
    
    ElemRef operator[] (CORBA::ULong n)
    {
      return _obj->operator[](n);
    }
      
    ElemRef operator[] (CORBA::ULong n) const
    {
      return _obj->operator[](n);
    }

    CORBA::ULong length(CORBA::ULong n) {
      if (!_obj) { return 0; }
      return _obj->length(n);
    }
    CORBA::ULong length() const
    {
      return _obj? _obj->length(): 0;
    }

    T & operator*() { return *_obj; }
    T * operator->() { return _obj; }
    operator T &() { return *_obj; }
    operator T *() { return _obj; }

  public:
    T * _retn() {
      T *tmp = _obj;
      _obj = 0;
      return tmp;
    }

  public:
    T & inout() { return *_obj; }
    T * in() const { return _obj; }

  protected:
    T * _obj;
    bool _release;
  protected:
    void release() {
      if (_release && _obj != NULL) {
	delete _obj; _obj = NULL;
      }
    }
  };


  template <class T>
  class T_Ptr : public T_PtrVarBase<T, false>
  {
    typedef T_PtrVarBase<T, false> Super;
    typedef T_Ptr<T> Ptr;
    typedef typename T::CType CType;
  public:
    T_Ptr(CType &o) : Super(new T(const_cast<CType*>(&o), false))
    {
      Super::_release = true;
    }

    T_Ptr(const T &o) : Super(o) {}
    T_Ptr(CType *impl) : Super(new T(impl, false)) {}
	  
    T_Ptr(T* t) : Super(t) {}
    T_Ptr(const Ptr &o) {
      Super::_obj = o._obj;
      Super::_release = false;
    }
  };

  template <class T>
  class T_Var : public T_PtrVarBase<T, true>
  {
    typedef T_PtrVarBase<T, true> Super;
    typedef T_Var<T> This;
  public:
    T_Var() : Super() {}
    T_Var(T * p) : Super(p) {}
    T_Var(const T &o) : Super(o) {}

    This &operator=(T *p)
    {
      Super::release();
      Super::_obj = p;
      return *this;
    }
    This &operator=(const T &o)
    {
      Super::release();
      Super::_obj = new T(o);
      return *this;
    }

    T * &out(){
      return Super::_obj;
    }

    T &inout(){
      return *Super::_obj;
    }
  };

  template <class T>
  class T_SeqOut
  {
    typedef typename T::CType CType;

    typedef T_SeqOut<T> This;
    typedef T_Var<T> Var;
    typedef T_Ptr<T> Ptr;
  private:
    T * & _ref;
  public:

    T_SeqOut(T * &ref) : _ref(ref)
    {
      //_ref = NULL;
    };
    
    T_SeqOut(Var & var) : _ref(var._obj)
    {
      //_ref = NULL;
    };

    This & operator=(T *p)
    {
      _ref = p;
      return *this;
    }

    operator CType **() {
      if (!_ref) {
	_ref = new T(true);
      }
      return _ref->cptr();
    }
    
    Ptr ptr() {
      return Ptr(_ref);
    }

    Ptr operator->() { return Ptr(_ref); }
    
  };

  template <class CType, class CppType>	
  class T_CInArg
  {
  private:
    CppType *_obj;
  public:
    T_CInArg(CType *p) : _obj(NULL) {
      _obj = new CppType(p, false);
    }
    ~T_CInArg() {
      delete _obj;
    }
    operator CppType & ()
    {
      return *_obj;
    }
  };

  template <class CType, class CppType>
  class T_COutArg
  {
    typedef T_SeqOut<CppType> SeqOut;
  private:
    CType **_ref;
    CppType *_obj;
  public:
    T_COutArg(CType **ref) : _ref(ref), _obj(NULL)
    {
    }
    ~T_COutArg() {
      if (_obj) {
	*_ref = _obj->release();
	delete _obj;
      }
    }
      
    operator SeqOut ()
    {
      if (!_obj) {
	_obj = new CppType(true);
      }

      return SeqOut(_obj);
    }
  };

  template <class CType, class CppType>
  class T_CInOutArg
  {
  private:
    CppType *_obj;
  public:
    T_CInOutArg(CType *impl) {
      _obj = new CppType(impl, false);
    }
    T_CInOutArg() {
      delete _obj;
    }
    operator CppType &() { return *_obj; }
  };

  template <class CType, class CppType>
  class T_CppInArg {
    typedef T_SeqOut<CppType> Out;
  private:
    const CppType &_obj;
  public:
    T_CppInArg(const CppType &obj) : _obj(obj) {}
    operator CType *() { return _obj.cobj(); }
  };

  template <class CType, class CppType>
  class T_CppOutArg {
    typedef T_SeqOut<CppType> Out;
  private:
    Out &m_out;
  public:
    T_CppOutArg(Out &out) : m_out(out) {}
    operator CType **() { return (CType **) m_out; }
  };

  template <class CType, class CppType>
  class T_CppInOutArg {
  private:
    CppType &_obj;
  public:
    T_CppInOutArg(CppType &obj) : _obj(obj) {}
    operator CType *() { return _obj.cobj(); }
  };
  
  template <class CType, class CppType>
  class T_Helper {
  public:
    static CType * _retnew(CppType *p)
    {
      if (!p) { return NULL; }
      return p->cobj();
    }

    static CppType* _retnew(CType &t)
    {
      CppType *p = new CppType(t);
      return p;
    }
  };
}

#endif // __CORBA_SEQ_HH__
 
