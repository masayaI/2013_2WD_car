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
#ifndef __POA_HH__
#define __POA_HH__
#include <RtORB/corba-defs.hh>
#include <RtORB/corba-var.hh>

namespace PortableServer{
  class POA;
  typedef POA * POA_ptr;

  class ObjectId;
  typedef ObjectId * ObjectId_ptr;
  typedef CORBA_var<ObjectId> ObjectId_var;
  //typedef ObjectId * ObjectId_var;

  class RefCountServantBase;

  class POAManager;
  typedef POAManager * POAManager_ptr;
  typedef POAManager * POAManager_var;

  class ServantBase;

  ObjectId string_to_ObjectId(const CORBA_string oid);

 /*
  *  Class POA
  */
  class POA : public CORBA::Object
  {
  public:
    PortableServer_POA _impl;
    // long refs;

  public:
    POA();
    virtual ~POA();
    POA(PortableServer_POA poa);
    POA(const POA& other);
    POA& operator=(const POA& other);

    ObjectId_ptr activate_object(ServantBase *sb) throw (CORBA::Exception);
    void activate_object_with_id(ObjectId_ptr id, ServantBase *sb) throw (CORBA::Exception);
    void deactivate_object(const ObjectId &);

    void destroy(CORBA::Boolean etherealize, CORBA::Boolean wait_for_completion);

    ObjectId_ptr servant_to_id(ServantBase *sb) throw (CORBA::Exception);
    CORBA::Object_ptr id_to_reference(const ObjectId &) throw (CORBA::Exception);
    CORBA::Object_ptr servant_to_reference(ServantBase *) throw (CORBA::Exception);

    POAManager_ptr the_POAManager();
    static POA_ptr _narrow(CORBA::Object_ptr obj);
    static POA_ptr _nil();
    static POA_ptr _duplicate(POA_ptr);

    class ObjectNotActive: ::CORBA::UserException {
    };
    class ServantAlreadyActive: ::CORBA::UserException {
    };
    class ObjectAlreadyActive: ::CORBA::UserException {
    };
    class ServantNotActive: ::CORBA::UserException {
      public:
        char *_name() { return _msg; }
    };
    class WrongPolicy: ::CORBA::UserException {
      public:
        char *_name() { return _msg; }
    };
  };

  class POA_var
  {
  public:
    POA_var();
    POA_var(POA_ptr ptr);
    POA_var(const POA_var &var);
	  
    ~POA_var();
    POA_ptr operator->() { return _ptr; }

    operator POA_ptr () { return _ptr; }
    operator CORBA::Object_ptr () { return CORBA::Object_ptr(_ptr); }

    POA_var & operator=(POA_ptr ptr) {
      _ptr = ptr;
      return *this;
    }
	  
  private:
    POA * _ptr;
  };
	

 /*
  *  Class ObjectId
  */
  class ObjectId 
  {
     public:
       PortableServer_ObjectId _impl;

     public:
       ObjectId();
       ObjectId(PortableServer_ObjectId);
  };

 /*
  *  Class ServantBase
  */
  class ServantBase : public virtual CORBA::Object
  {
  public:
    CORBA_Environment _ev;
    impl_POA_ServantBase * poa_servant;
    long refs;
  public:
    ServantBase();
    ~ServantBase();

    void _add_ref()
    {
      refs++;
    }
    void _remove_ref()
    {
      refs--;
      if (refs < 0) {
	fprintf(stderr, "ServantBase: negative reference count\n");
	return;
      } else if (refs == 0) {
	delete this;
      }
    }

    PortableServer_ServantBase * getServantBase()
    {
      return poa_servant != NULL? &poa_servant->servant: NULL;
    }
    POA_ptr _default_POA();

    //static POA_ptr _root_POA(CORBA_Environment*);
    static POA_ptr _root_POA() throw (CORBA::Exception);

    CORBA_Object __this(CORBA_Environment *) throw (CORBA::Exception);
  };

 /*
  *  Class RefCountServantBase
  */
  class RefCountServantBase : public virtual ServantBase
  {
  public:
    PortableServer_POA _poa;
	
  };

 /*
  *  Class POAManager
  */
  class POAManager : public ServantBase
  {
  public:
    PortableServer_POAManager _mgr;

    POAManager(PortableServer_POAManager mgr);
  public:
    void activate() throw (CORBA::Exception);
    void deactivate(CORBA::Boolean etherealize,
		    CORBA::Boolean wait_for_completion) throw (CORBA::Exception);

  };

  /*
   *
   */
  class Servant{
    public:
     POA_var poa;
     CORBA::Object_var obj;
     PortableServer_Servant _servant;

    public:
     Servant(){}
     Servant(PortableServer_ServantBase *sb){
//        poa = new POA(sb->poa);
//	obj = new CORBA::Object(sb->obj);
     }
  };

};

#endif
