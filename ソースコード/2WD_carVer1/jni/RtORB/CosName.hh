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
#ifndef __COSNAME_HH__
#define __COSNAME_HH__

#include <RtORB/corba.hh>
#include <CosName/CosNaming.h>

typedef CORBA_unsigned_long _CORBA_ULong;
typedef CORBA_boolean _CORBA_Boolean;

extern void _CORBA_new_operator_return_null();
extern void _CORBA_bound_check_error();

class cdrStream {};

namespace CosNaming {

  enum BindingType {
    nobject = CosNaming_nobject,
    ncontext = CosNaming_ncontext,
  };

  template <class T, class S>
  class SequenceVar
  {
    typedef S *Ptr;
    Ptr _ptr;
  public:
    SequenceVar();
    SequenceVar(Ptr p);

    T &operator[](CORBA_unsigned_long i)
    {
      return _ptr->operator[](i);
    }
    Ptr operator->() { return _ptr; }

    operator Ptr () { return _ptr; }
    operator S () { return *_ptr; }
  };

  typedef CORBA_SequenceT<CosNaming_NameComponent, CosNaming_Name> Name;

  //typedef Name * Name_var;
  typedef SequenceVar<Name::ElemType, Name> Name_var;

  class NamingContext;
  typedef NamingContext * NamingContext_ptr;
  typedef NamingContext * NamingContext_var;
	

  class NamingContextExt;
  typedef NamingContextExt * NamingContextExt_ptr;
  typedef NamingContextExt * NamingContextExt_var;

  typedef CosNaming_Binding Binding;
  typedef CORBA_SequenceT<Binding, CosNaming_BindingList> BindingList;

  typedef BindingList * BindingList_ptr;

  typedef SequenceVar<BindingList::ElemType, BindingList> BindingList_var;

  /*
  class BindingList_var
  {
    typedef BindingList *Ptr;
    Ptr _ptr;
  public:
    BindingList_var();
    BindingList_var(Ptr *p);
    Binding &operator[](CORBA_unsigned_long i)
    {
      return _ptr->operator[](i);
    }
    Ptr operator->() { return _ptr; }

    operator Ptr () { return _ptr; }
  };
  */


  class BindingIterator : public CORBA::Object
  {
    typedef POA_CosNaming_BindingIterator__epv Itr;
  private:
    Itr *_curr;
  public:
    BindingIterator *operator->() { return this; }
    void next_n(const CORBA_unsigned_long how_many,
		BindingList * bl);

    void destroy();
    
  };
  typedef BindingIterator *BindingIterator_ptr;
  typedef BindingIterator *BindingIterator_var;
  
  class  NamingContext : public CORBA::Object
  {
     public:
     /*
      * exceptions
      */
      enum  NotFoundReason {missing_node, not_context, not_object};
      class NotFound {
      public:
	  NotFoundReason why;
	  Name rest_of_name;
      };
      class CannotProceed {
      public:
	CannotProceed(NamingContext_ptr cxt_, const Name &rest_of_name_);
      public:
        NamingContext_ptr cxt;
        Name rest_of_name;
      };

      class InvalidName{ };
      class AlreadyBound{};
      class NotEmpty{};

    public:
      NamingContext();
      NamingContext(CORBA_Object obj);
      ~NamingContext();

  public:
    void bind(const Name &, ::CORBA::Object_ptr);
    void rebind(const Name &, ::CORBA::Object_ptr);
    void bind_context(const Name &, NamingContext_ptr);
    void rebind_context(const Name &, NamingContext_ptr);

    ::CORBA::Object_ptr resolve(const Name &);
    NamingContext_ptr new_context();
    NamingContext_ptr bind_new_context(const Name &);

    void unbind(const Name &);
    void destroy();


    void list(CORBA_unsigned_long how_many, BindingList_ptr, BindingIterator_ptr);
      
    static NamingContext_var _narrow(CORBA::Object_ptr);
    static NamingContext_ptr _duplicate(NamingContext_ptr);
    static NamingContext_ptr _nil();
  };

  class  NamingContextExt : public NamingContext
  {
    typedef NamingContextExt * Ptr;
  public:
    typedef CosNaming_NamingContextExt_InvalidAddress InvalidAddress;


    char *to_url(const char *addre, const char *string_name);
    
  public:
    static Ptr _nil();
    static Ptr _narrow(CORBA::Object_ptr);
    static Ptr _duplicate(Ptr);

  };


};
#endif
