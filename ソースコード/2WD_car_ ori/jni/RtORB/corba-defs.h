/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*

 Simple CORBA Implementation for x86 (Big Endian)
  
*/

#ifndef __CORBA_DEFS_H__
#define __CORBA_DEFS_H__

#if USE_THREAD
#include <pthread.h>
#endif
#include <RtORB/list.h>
#include <RtORB/array.h>
#include <RtORB/hashtable.h>
#include <RtORB/typecode.h>


#ifdef __cplusplus
namespace CORBA {
  class Any_var;
  class Object;
  class Object_ptr;
}

class cdrStream;
#endif

#ifdef __cplusplus
extern "C"
{
#endif 

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//// for experimental use
#ifndef CORBA_VPVID
#define CORBA_VPVID	0xfffff
#endif

#define CORBA_I_ARG_IN		0
#define CORBA_I_ARG_OUT		1
#define CORBA_I_ARG_INOUT	2

#define CORBA_OBJECT_NIL	NULL

// Alignments
#define CORBA_OCTET_ALIGN	1
#define CORBA_WCHAR_ALIGN	2
#define CORBA_SHORT_ALIGN	2
#define CORBA_LONG_ALIGN	4
#define CORBA_FLOAT_ALIGN	4
#define CORBA_DOUBLE_ALIGN	8
#define CORBA_LONG_LONG_ALIGN	8
#define CORBA_LONG_DOUBLE_ALIGN	16
#define CORBA_OBJECT_ALIGN	4
// SIZE_OF
#define CORBA_OCTET_SIZE	1
#define CORBA_WCHAR_SIZE	2
#define CORBA_SHORT_SIZE	2
#define CORBA_LONG_SIZE		4
#define CORBA_FLOAT_SIZE	4
#define CORBA_DOUBLE_SIZE	8
#define CORBA_LONG_LONG_SIZE	8
#define CORBA_LONG_DOUBLE_SIZE	16
#define CORBA_OBJECT_SIZE	4

///// Exception
  /*
enum CORBA_System_Exceptions{
  CORBA_BAD_PARAM=1, CORBA_INVALID_VALUE, CORBA_UNKNOWN_VALUE, END_EXCEPTION
};
  */

enum CORBA_ReplyStatusType{
   CORBA_NO_EXCEPTION, CORBA_USER_EXCEPTION, CORBA_SYSTEM_EXCEPTION, 
   CORBA_LOCATION_FORWARD,CORBA_LOCATION_FORWARD_PERM, NEEDS_ADDRESSING_MODE
};


/***  Basic Data Type **/
typedef short CORBA_short;
typedef long CORBA_long;
typedef long long CORBA_long_long;
typedef unsigned short  CORBA_unsigned_short;
typedef unsigned long  CORBA_unsigned_long;
typedef unsigned long long  CORBA_unsigned_long_long;
typedef float CORBA_float;
typedef double CORBA_double;
typedef long double CORBA_long_double;
typedef char CORBA_char;
typedef char CORBA_octet;
typedef unsigned short CORBA_wchar;
typedef unsigned char CORBA_boolean;
typedef  char * CORBA_string;
typedef  short * CORBA_wstring;

extern const unsigned long RTORB_ORB_TYPE;

#define CORBA_ANY_MAXBUF MaxMessageSize


struct CORBA_Object_struct;

typedef union
{
  CORBA_boolean val_bool;
  CORBA_octet val_octet;
  CORBA_char  val_char;
  CORBA_unsigned_long val_ulong;

  char * val_str;
  struct CORBA_Object_struct * val_obj;
  void * val_except;

  /* tk_struct */
  struct val_t {
    int   len;
    char * data;
  } val_encoded;
} CORBA_any_val;

typedef struct CORBA_any {
  struct CORBA_TypeCode_struct *_type;
  CORBA_any_val *_val;
//  CORBA_boolean _release;
  CORBA_unsigned_long _release;

#ifdef __cplusplus
  CORBA_any();
  CORBA_any(const CORBA_any &o);
  ~CORBA_any();

  CORBA_boolean hasData(struct CORBA_TypeCode_struct *) const;

  void setData(struct CORBA_TypeCode_struct *tc, char *data, int len);
  void copy_val(CORBA_TypeCode_struct *, CORBA_any_val *);
  void set_val(CORBA_TypeCode_struct *, CORBA_any_val *);
	
  void alloc(CORBA_TypeCode_struct *);
  void free_();
  
  CORBA_any & operator=(const CORBA_any &o);

  CORBA_any * duplicate();

  CORBA_TypeCode_struct * type() { return _type; }
		
  struct from_char {
    from_char(CORBA_char v) : val(v) {};
    CORBA_char val;
  };

  struct from_boolean {
    from_boolean(CORBA_boolean v) : val(v) {};
    CORBA_boolean val;
  };

  struct from_octet {
    from_octet(CORBA_octet v) : val(v) {};
    CORBA_octet val;
  };

  struct from_string {
    from_string(const char *v) : val(v) {}
    const char *val;
  };

  struct from_object {
    from_object(CORBA::Object_ptr &ptr_);
    CORBA::Object_ptr &ptr;
  };
  
  struct from_any {
    from_any(CORBA_any *v) : val(v) {}
    CORBA_any * val;
  };

  void operator<<=(from_char);
  void operator<<=(from_boolean);
  void operator<<=(from_octet);
  void operator<<=(from_string);
  void operator<<=(from_object);
  void operator<<=(from_any);
  void operator<<=(CORBA_unsigned_long);

  struct to_char {
    to_char(CORBA_char &buf_) : buf(buf_){}
    CORBA_char &buf;
  };

  struct to_octet {
    to_octet(CORBA_octet &buf_) : buf(buf_){}
    CORBA_octet &buf;
  };

  struct to_boolean {
    to_boolean(CORBA_boolean &buf_) : buf(buf_){}
    CORBA_boolean &buf;
  };

  struct to_string {
    to_string(char *& buf_) : buf(buf_){}
    to_string(const char *& buf_) : buf((char *&)buf_){}
    char * & buf;
  };

  struct to_object {
    to_object(CORBA::Object_ptr &ptr_) : ptr(ptr_) {}
    CORBA::Object_ptr &ptr;
  };
	
  CORBA_boolean operator>>=(to_char o) const;
  CORBA_boolean operator>>=(to_boolean o) const;
  CORBA_boolean operator>>=(to_octet o) const;
  CORBA_boolean operator>>=(to_string o) const;
  CORBA_boolean operator>>=(to_object o) const;
  CORBA_boolean operator>>=(CORBA_any &o) const;
  CORBA_boolean operator>>=(CORBA_unsigned_long &n) const;

#endif
} CORBA_any ;

void 	CORBA_any_alloc(CORBA_any *, struct CORBA_TypeCode_struct *, int clear);
void 	CORBA_any_clear(CORBA_any *any);

void    CORBA_any_set_value(CORBA_any*, struct CORBA_TypeCode_struct *, char *data, int len);
void * 	CORBA_any_get_value(CORBA_any*);	
char * 	CORBA_any_get_encoded(CORBA_any *any, int *len);

void 	CORBA_any_set_exception_value(CORBA_any *any, struct CORBA_TypeCode_struct * tc, void *value, CORBA_boolean release);
void 	CORBA_any_set_exception(CORBA_any *any, CORBA_any *src);

#ifdef __cplusplus

typedef CORBA_boolean         CORBA_boolean_var;
typedef CORBA_double          CORBA_double_var;
typedef CORBA_float           CORBA_float_var;
typedef CORBA_long            CORBA_long_var;
typedef CORBA_char            CORBA_char_var;
typedef CORBA_unsigned_long   CORBA_unsigned_long_var;
typedef CORBA_octet           CORBA_octet_var;
typedef CORBA_short           CORBA_short_var;
typedef CORBA_unsigned_short  CORBA_unsigned_short_var;


typedef CORBA_string CORBA_string_ptr;

class CORBA_string_var {
public:
  CORBA_string_var() : _str(0) {}
  CORBA_string_var(unsigned char *p) : _str(0)
  {
    _str = alloc((const char*)p);
  }
    
  CORBA_string_var(char *p) : _str(0)
  {
    _str = alloc(p);
  }

  CORBA_string_var(const char *p) : _str(0)
  {
    _str = alloc(p);
  }
  ~CORBA_string_var();

  operator CORBA_string () { return _str; }

  CORBA_string _retn() {
    char *tmp = _str;
    _str = NULL;
    return tmp;
  }

  const char * in() {
    return _str;
  }

private:
  char *_str;
  
private:
  char * alloc(const char *p);
};


typedef CORBA_wstring CORBA_wstring_ptr;

class CORBA_wstring_var {
public:
  CORBA_wstring_var() : _str(0) {}
  CORBA_wstring_var(unsigned char *p) : _str(0)
  {
    _str = alloc((const short*)p);
  }
    
  CORBA_wstring_var(short *p) : _str(0)
  {
    _str = alloc(p);
  }

  CORBA_wstring_var(const short *p) : _str(0)
  {
    _str = alloc(p);
  }
  ~CORBA_wstring_var();

  operator CORBA_wstring () { return _str; }

  CORBA_wstring _retn() {
    short *tmp = _str;
    _str = NULL;
    return tmp;
  }

private:
  short *_str;
  
private:
  short * alloc(const short *p);
};

#endif

//////////// Sequence
typedef struct{
  unsigned long _maximum;
  unsigned long _length;
  void * *_buffer;
//  boolean  _release;
  unsigned long  _release;
} CORBA_SequenceBase;

typedef struct{
  unsigned long _length;
  unsigned long _maximum;
  void *_buffer;
//  boolean  _release;
  unsigned long  _release;
  unsigned long _type;
} CORBA_Sequence;

typedef struct {
  unsigned long _length;
  unsigned long _maximum;
  unsigned char *_buffer;
//  boolean  _release;
  unsigned long  _release;
} CORBA_Sequence_Octet;

typedef CORBA_Sequence_Octet CORBA_String;

typedef struct CORBA_Environment{
  unsigned long _major; // Exception type
  unsigned char *_repo_id;
  CORBA_any _params; 
  unsigned long _cpp_flag; // flag for C++ Interface
} CORBA_Environment;

///////////////////
//
typedef struct CORBA_Ref{
  char *key;
  char *url;
} CORBA_Ref;

typedef struct CORBA_Config {
   char *server_id;
   char *orb_id;
   char *listenEndpoints;
   unsigned long flag_propietary_activation;
   PtrArray  *init_ref;
   char *default_init_ref;
   unsigned short port;
}CORBA_Config;

////////////////////////
//
typedef struct{
	unsigned long dummy;
}CORBA_InterfaceDef;

enum CORBA_SetOverrideType{
	CORBA_SET_OVERRIDE,CORBA_ADD_OVERRIDE
};

//// Policy
typedef unsigned long CORBA_PolicyType;

typedef struct{
  CORBA_PolicyType policy_type;  /// readonly
  CORBA_any state;
}CORBA_Policy_struct;

typedef CORBA_Policy_struct  * CORBA_Policy;

typedef struct{
  unsigned long _maximum;
  unsigned long _length;
  unsigned long _release;
  CORBA_Policy *_policies;
}CORBA_PolicyList;

typedef struct{
  unsigned long _maximum;
  unsigned long _length;
  unsigned long _release;
  CORBA_PolicyType *_types;
}CORBA_PolicyTypeSeq;

typedef int CORBA_PolicyErrorCode;

extern const CORBA_PolicyErrorCode BAD_POLICY;
extern const CORBA_PolicyErrorCode UNSUPPORTED_POLICY;
extern const CORBA_PolicyErrorCode BAD_POLICY_TYPE;
extern const CORBA_PolicyErrorCode BAD_POLICY_VALUE;
extern const CORBA_PolicyErrorCode UNSUPPORTED_POLICY_VALUE;

/////// Domain Manager
typedef struct{
  unsigned long _id;
}CORBA_DomainManager;

typedef struct{
  unsigned long _maximum;
  unsigned long _length;
  unsigned long _release;
  CORBA_DomainManager *_types;
}CORBA_DomainManagerList;

///////// ORB
typedef struct CORBA_ORB_struct{
  unsigned char *_id;
  PtrArray *_threads;
  PtrArray *_adapters;
  hashtable *_object_table;
  CORBA_PolicyList *_policies;

  char *hostname;

  unsigned long request_id;

  struct PortableServer_POAManagerFactory_struct *poa_mgr_factory;

  CORBA_Config cfg;

} CORBA_ORB_struct;

typedef CORBA_ORB_struct * CORBA_ORB;

typedef  long  CORBA_TCKind;
typedef  char *CORBA_RepositoryId;
typedef  char *CORBA_Identifier;
typedef  char *CORBA_Visibility;
typedef  char *CORBA_ValueModifier;

typedef struct CORBA_TypeCode_struct{
  void *			parents;
  CORBA_TCKind			kind;
  CORBA_RepositoryId		repository_id;
  CORBA_Identifier		identifier; 
  unsigned long			member_count; 	/* struct, union, enum, value, exception, event */
  CORBA_Identifier  		*member_name; 	/* struct, union, enum, value, exception, event */
  struct CORBA_TypeCode_struct 	**member_type; 	/* struct, union, value, exception, event */
  long 			*member_label; 	/* union */
  struct CORBA_TypeCode_struct 	*discriminator; /* union */
  long   			default_index;  /* union */
  unsigned long   		length; 	/* string, wstring, sequence, array */ 
  struct CORBA_TypeCode_struct 	*content_type;  /* sequence, array, value_box, alias */ 
  unsigned short		fixed_digits;   /* fixed */
  short				fixed_scale;    /* fixed */
  CORBA_Visibility		*member_visibility;  	/* value, event */
  CORBA_ValueModifier		type_modifier;  	/* value, event */
  struct CORBA_TypeCode_struct 	*concrete_base_type;  	/* value, event */
  short 			size;
  short				alignment;

#ifdef __cplusplus
  const char *id() const { return repository_id; }
  const char *name() const { return identifier; }
#endif
	
}CORBA_TypeCode_struct;

typedef CORBA_TypeCode_struct *CORBA_TypeCode ;

typedef struct CORBA_IArg {
  CORBA_TypeCode tc;
  unsigned char  io;
  char *name;
}CORBA_IArg;

typedef struct CORBA_Class_Method{
  char *name;
  CORBA_TypeCode retval;
//  void (*func)();
  int in_argc;
  CORBA_IArg *in_argv;
  int n_exceptinfo;
  CORBA_TypeCode *exceptinfo;
}CORBA_Class_Method;

typedef struct{
  CORBA_TypeCode tc;
  char *name;
  int n_methods; 
  struct CORBA_Class_Method *methods;
  int n_base_types;
  char **base_types;
} CORBA_Class_Impl;

extern const CORBA_TypeCode_struct TC_null_struct;
extern const CORBA_TypeCode_struct TC_void_struct;
extern const CORBA_TypeCode_struct TC_short_struct;
extern const CORBA_TypeCode_struct TC_long_struct;
extern const CORBA_TypeCode_struct TC_longlong_struct;
extern const CORBA_TypeCode_struct TC_ushort_struct;
extern const CORBA_TypeCode_struct TC_ulong_struct;
extern const CORBA_TypeCode_struct TC_ulonglong_struct ;
extern const CORBA_TypeCode_struct TC_float_struct;
extern const CORBA_TypeCode_struct TC_double_struct;
extern const CORBA_TypeCode_struct TC_longdouble_struct;
extern const CORBA_TypeCode_struct TC_boolean_struct;
extern const CORBA_TypeCode_struct TC_char_struct;
extern const CORBA_TypeCode_struct TC_wchar_struct;
extern const CORBA_TypeCode_struct TC_octet_struct;
extern const CORBA_TypeCode_struct TC_any_struct;
extern const CORBA_TypeCode_struct TC_TypeCode_struct;
extern const CORBA_TypeCode_struct TC_Object_struct;
extern const CORBA_TypeCode_struct TC_string_struct;
extern const CORBA_TypeCode_struct TC_wstring_struct;
extern const CORBA_TypeCode_struct TC_ValueBase_struct;
extern const CORBA_TypeCode_struct TC_Component_struct;
extern const CORBA_TypeCode_struct TC_Home_struct;
extern const CORBA_TypeCode_struct TC_EventBase_struct;

#define TC_null		 ((CORBA_TypeCode)&TC_null_struct)
#define TC_void   	 ((CORBA_TypeCode)&TC_void_struct)
#define TC_CORBA_short	 ((CORBA_TypeCode)&TC_short_struct)
#define TC_CORBA_long		 ((CORBA_TypeCode)&TC_long_struct)
#define TC_CORBA_long_long	 ((CORBA_TypeCode)&TC_longlong_struct)
#define TC_CORBA_ushort	 ((CORBA_TypeCode)&TC_ushort_struct)
#define TC_CORBA_unsigned_short	 ((CORBA_TypeCode)&TC_ushort_struct)
#define TC_CORBA_ulong	 ((CORBA_TypeCode)&TC_ulong_struct)
#define TC_CORBA_unsigned_long	 ((CORBA_TypeCode)&TC_ulong_struct)
#define TC_CORBA_ulonglong	 ((CORBA_TypeCode)&TC_ulonglong_struct)
#define TC_CORBA_unsigned_long_long	 ((CORBA_TypeCode)&TC_ulonglong_struct)
#define TC_CORBA_float	 ((CORBA_TypeCode)&TC_float_struct)
#define TC_CORBA_double	 ((CORBA_TypeCode)&TC_double_struct)
#define TC_CORBA_long_double	 ((CORBA_TypeCode)&TC_longdouble_struct)
#define TC_CORBA_boolean	 ((CORBA_TypeCode)&TC_boolean_struct)
#define TC_CORBA_char		 ((CORBA_TypeCode)&TC_char_struct)
#define TC_CORBA_wchar	 ((CORBA_TypeCode)&TC_wchar_struct)
#define TC_CORBA_octet	 ((CORBA_TypeCode)&TC_octet_struct)
#define TC_CORBA_any		 ((CORBA_TypeCode)&TC_any_struct)
#define TC_CORBA_TypeCode	 ((CORBA_TypeCode)&TC_TypeCode_struct)
#define TC_CORBA_Object	 ((CORBA_TypeCode)&TC_Object_struct)
#define TC_CORBA_string	 ((CORBA_TypeCode)&TC_string_struct)
#define TC_CORBA_wstring	 ((CORBA_TypeCode)&TC_wstring_struct)
#define TC_CORBA_ValueBase	 ((CORBA_TypeCode)&TC_ValueBase_struct)
#define TC_CORBA_Component	 ((CORBA_TypeCode)&TC_Component_struct)
#define TC_CORBA_Home		 ((CORBA_TypeCode)&TC_Home_struct)
#define TC_CORBA_EventBase	 ((CORBA_TypeCode)&TC_EventBase_struct)

////// For compatible to ORBit2
#define TC_CORBA_char_struct	 TC_char_struct
#define TC_CORBA_wchar_struct	 TC_wchar_struct
#define TC_CORBA_boolean_struct	 TC_boolean_struct
#define TC_CORBA_octet_struct	 TC_octet_struct
#define TC_CORBA_short_struct	 TC_short_struct
#define TC_CORBA_unsigned_short_struct	 TC_ushort_struct
#define TC_CORBA_long_struct	 TC_long_struct
#define TC_CORBA_unsigned_long_struct	 TC_ulong_struct
#define TC_CORBA_float_struct	 TC_float_struct
#define TC_CORBA_double_struct	 TC_double_struct
#define TC_CORBA_string_struct	 TC_string_struct
#define TC_CORBA_wstring_struct	 TC_wstring_struct
#define TC_CORBA_TypeCode_struct	 TC_TypeCode_struct
#define TC_CORBA_Object_struct	 TC_Object_struct
#define TC_CORBA_any_struct	 TC_any_struct

enum { PLT_NOT_SUPPORTED = -1, PLT_NONE, PLT_SIMPLE, PLT_COMPLEX,};
static int paramListType[] =  {
  PLT_NONE,             // tk_null                      // 0
  PLT_NONE,             // tk_void                      // 1
  PLT_NONE,             // tk_short                     // 2
  PLT_NONE,             // tk_long                      // 3
  PLT_NONE,             // tk_ushort                    // 4
  PLT_NONE,             // tk_ulong                     // 5
  PLT_NONE,             // tk_float                     // 6
  PLT_NONE,             // tk_double                    // 7
  PLT_NONE,             // tk_boolean                   // 8
  PLT_NONE,             // tk_char                      // 9
  PLT_NONE,             // tk_octet                     // 10
  PLT_NONE,             // tk_any                       // 11
  PLT_NONE,             // tk_TypeCode                  // 12
  PLT_NONE,             // tk_Principal                 // 13
  PLT_COMPLEX,          // tk_objref,                   // 14
  PLT_COMPLEX,          // tk_struct,                   // 15
  PLT_COMPLEX,          // tk_union,                    // 16
  PLT_COMPLEX,          // tk_enum,                     // 17
  PLT_SIMPLE,           // tk_string,                   // 18
  PLT_COMPLEX,          // tk_sequence,                 // 19
  PLT_COMPLEX,          // tk_array,                    // 20
  PLT_COMPLEX,          // tk_alias,                    // 21
  PLT_COMPLEX,          // tk_except,                   // 22
  PLT_NONE,             // tk_longlong,                 // 23
  PLT_NONE,             // tk_ulonglong,                // 24
  PLT_NONE,             // tk_longdouble,               // 25
  PLT_NONE,             // tk_wchar,                    // 26
  PLT_SIMPLE,           // tk_wstring,                  // 27
  PLT_NOT_SUPPORTED,    // tk_fixed,                    // 28
  PLT_NOT_SUPPORTED,    // tk_value,                    // 29
  PLT_NOT_SUPPORTED,    // tk_value_box,                        // 30
  PLT_NOT_SUPPORTED,    // tk_native,                   // 31
  PLT_NOT_SUPPORTED,    // tk_abstract_interface,       // 32
  PLT_NOT_SUPPORTED,    // tk_local_interface,          // 33
  PLT_NOT_SUPPORTED,    // tk_component,                        // 34
  PLT_NOT_SUPPORTED,    // tk_home,                     // 35
  PLT_NOT_SUPPORTED,    // tk_event,                    // 36

  // tk_END = 0xffffff
};

#define PARAM_LIST_TYPE(KIND) (paramListType[KIND])


#ifdef __cplusplus
}
#endif 


#endif
