/*
  cdrMemoryStream 
*/

#ifndef __CDRSTREAM_H__
#define __CDRSTREAM_H__

#ifdef __cplusplus


#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <RtORB/corba.h>

#define SWAP16(s) ((((s) & 0xff) << 8) | (((s) >> 8 ) & 0xff))
#define SWAP32(l) ((((l) & 0xff000000) >> 24)  | \
                   (((l) & 0x00ff0000) >> 8 )  | \
                   (((l) & 0x0000ff00) << 8 )  | \
                   (((l) & 0x000000ff) << 24 ) )

#define SWAP64(l) ((((l) & 0xff00000000000000) >> 56)  | \
                   (((l) & 0x00ff000000000000) >> 40 )  | \
                   (((l) & 0x0000ff0000000000) >> 24 )  | \
                   (((l) & 0x000000ff00000000) >> 8 )  | \
                   (((l) & 0x00000000ff000000) << 8 )  | \
                   (((l) & 0x0000000000ff0000) << 24 )  | \
                   (((l) & 0x000000000000ff00) << 40 )  | \
                   (((l) & 0x00000000000000ff) << 56 ) )

#define IS_DIFFERENT_ENDIAN(s) if(s.byte_order != __CDR_ORDER__)

typedef union {
 char c[4];
 long l;
 float f;
} f2l;

typedef union {
 char c[8];
 long l[2];
 double d;
} d2l;


class cdrStream
{
public:
 cdrStream();
 virtual ~cdrStream();

 void *out_buf;
 unsigned long out_len;
 unsigned long out_c;
 unsigned int byte_order;

 int _ref;

#define Marshal(s, type, align, a)  do{\
   int len = sizeof(type); 	\
   s.put_octet_array((char *) a, len, align); 	\
  }while(0)

#define Unmarshal(s, type, align, a) do{\
   int len = sizeof(type); 	\
   s.get_octet_array((char *) a, len, align); 	\
 }while(0);


 friend inline void operator>>=(char a, cdrStream& s){
   Marshal(s, char, 1, &a);
   return;
 }

 friend inline void operator<<=(char& a, cdrStream& s){
   Unmarshal(s, char, 1, &a);
   return;
 }
 friend inline void operator>>=(unsigned char a, cdrStream& s){
   Marshal(s, unsigned char, 1, &a);
   return;
 }
 friend inline void operator<<=(unsigned char& a, cdrStream& s){
   Unmarshal(s,unsigned char, 1, &a);
   return;
 }
 friend inline void operator>>=(short a, cdrStream& s){
   IS_DIFFERENT_ENDIAN(s) a=SWAP16(a);
   Marshal(s, short, 2, &a);
   return;
 }
 friend inline void operator<<=(short& a, cdrStream& s){
   Unmarshal(s, short, 2, &a);
   IS_DIFFERENT_ENDIAN(s) a=SWAP16(a);
   return;
 }
 friend inline void operator>>=(unsigned short a, cdrStream& s){
   IS_DIFFERENT_ENDIAN(s) a=SWAP16(a);
   Marshal(s, unsigned short, 2, &a);
   return;
 }
 friend inline void operator<<=(unsigned short& a, cdrStream& s){
   Unmarshal(s, unsigned short, 2, &a);
   IS_DIFFERENT_ENDIAN(s) a=SWAP16(a);
   return;
 }
 friend inline void operator>>=(int a, cdrStream& s){
   IS_DIFFERENT_ENDIAN(s) a=SWAP32(a);
   Marshal(s, long, 4, &a);
   return;
 }
 friend inline void operator<<=(int& a, cdrStream& s){
   Unmarshal(s, long, 4, &a);
   IS_DIFFERENT_ENDIAN(s) a=SWAP32(a);
   return;
 }

 friend inline void operator>>=(long a, cdrStream& s){
   IS_DIFFERENT_ENDIAN(s) a=SWAP32(a);
   Marshal(s, long, 4, &a);
   return;
 }
 friend inline void operator<<=(long& a, cdrStream& s){
   Unmarshal(s, long, 4, &a);
   IS_DIFFERENT_ENDIAN(s) a=SWAP32(a);
   return;
 }
 friend inline void operator>>=(unsigned long a, cdrStream& s){
   IS_DIFFERENT_ENDIAN(s) a=SWAP32(a);
   Marshal(s, unsigned long, 4, &a);
   return;
 }

 friend inline void operator<<=(unsigned long& a, cdrStream& s){
   Unmarshal(s, unsigned long, 4, &a);
   IS_DIFFERENT_ENDIAN(s) a=SWAP32(a);
   return;
 }

 friend inline void operator>>=(float f, cdrStream& s){
   f2l a;
   a.f = f;
   IS_DIFFERENT_ENDIAN(s) a.l=SWAP32(a.l);
   Marshal(s, float, 4, &a.l);
   return;
 }
 friend inline void operator<<=(float& f, cdrStream& s){
   f2l a;
   Unmarshal(s, float, 4, &a.l);
   IS_DIFFERENT_ENDIAN(s) a.l=SWAP32(a.l);
   f=a.f;
   return;
 }

 friend inline void operator>>=(double d, cdrStream& s){
   d2l a;
   long lup, llow;
   a.d = d;
   IS_DIFFERENT_ENDIAN(s){
      lup=SWAP32(a.l[1]);
      llow=SWAP32(a.l[0]);
      a.l[0]=llow;
      a.l[1]=lup;
   }
   Marshal(s, double, 8, a.l);
   return;
 }
 friend inline void operator<<=(double& d, cdrStream& s){
   d2l a;
   long lup, llow;
   Unmarshal(s, double, 8, a.l);
   IS_DIFFERENT_ENDIAN(s){
      lup=SWAP32(a.l[1]);
      llow=SWAP32(a.l[0]);
      a.l[0]=llow;
      a.l[1]=lup;
   }
   d=a.d;
   return;
 }

 friend inline void operator>>=(CORBA_string str, cdrStream& s){
   long len=strlen(str)+1;
   Marshal(s, long, 4, len);
   s.put_octet_array((char *) str, len, 1);
   return;
 }

 friend inline void operator<<=(CORBA_string& str, cdrStream& s){
   long len;
   char *buf;
   s.get_octet_array((char *)&len, 4, 4);
   buf = (char *)RtORB_alloc(len, "cdrStrem:string");
   s.get_octet_array(buf, len, 1);
   if(*str) RtORB_free(str, "cdrStrem:string");
   str = buf;
   return;
 }

 friend inline void operator>>=(CORBA_wstring str, cdrStream& s){ /// for GIOP 1.2 or lator
   long len=wcslen((const wchar_t *)str);
   Marshal(s, long, 4, len);
   s.put_octet_array((char *) str, len*2, 2);
   return;
 }

 friend inline void operator<<=(CORBA_wstring& str, cdrStream& s){
   long len;
   short *buf;
   s.get_octet_array((char *)&len, 4, 4);
   buf = (short *)RtORB_alloc(sizeof(short) * (len+1), "cdrStream:wstring");
   s.get_octet_array((char *)buf, len*2, 2);
   if(*str) RtORB_free(str, "cdrStrem:string");
   str = buf;
   return;
 }

 friend inline void operator>>=(CORBA_any any, cdrStream& s){
   s.marshal_CORBA_any(any);
 }

 friend void operator<<=(CORBA_any& any, cdrStream& s){
   if(any._type) CORBA_any_clear(&any);
   any = s.unmarshal_CORBA_any();
 }

 friend void operator>>=(CORBA_TypeCode typ, cdrStream& s){
   s.marshal_CORBA_TypeCode(typ);
 }

 friend void operator<<=(CORBA_TypeCode& typ, cdrStream& s){
  typ = s.unmarshal_CORBA_TypeCode();
 }

 friend void operator>>=(CORBA_Object obj, cdrStream& s){
   s.marshal_CORBA_Object(obj);
 }

 friend void operator<<=(CORBA_Object& obj, cdrStream& s){
   CORBA_Object_free(obj);
   obj = s.unmarshal_CORBA_Object();
 }

 void get_octet_array(char *octet, int size, int align=1);
 void put_octet_array(char *octet, int size, int align=1);

 void marshal_sequence(void *buf, int size, CORBA_TypeCode tc);
 void *unmarshal_sequence(int size, CORBA_TypeCode tc);

 void marshal_CORBA_any(CORBA_any);
 CORBA_any unmarshal_CORBA_any();
 void marshal_CORBA_TypeCode(CORBA_TypeCode);
 CORBA_TypeCode unmarshal_CORBA_TypeCode();
 void marshal_CORBA_Object(CORBA_Object);
 CORBA_Object unmarshal_CORBA_Object();

};

class cdrMemoryStream: public cdrStream
{
public:
 cdrMemoryStream(int initBufsize=0, int clsMemory=0);
 cdrMemoryStream(const cdrMemoryStream &cms);
/*
 cdrMemoryStream(const cdrMemoryStream &cms, int read_only=0);
 cdrMemoryStream(void *databuffer);
*/
 cdrMemoryStream(void *databuffer, int maxLen);

// virtual ~cdrMemoryStream();

// void rewindInputPtr();
 void rewindPtrs();

 unsigned long bufSize() const;
 void *bufPtr() const;

 void setByteSwapFlag(int byte_order);

 int readOnly(); // boolean

// virtual void* ptrToClass(int *cptr);
// void get_octet_array(const char *octet, int size, int align=1);
// void put_octet_array(char *octet, int size, int align=1);

 void skipInput(unsigned long size);

// int  checkInputOverrun(unsigned long itemSize, unsigned long nItems, int align=1);
 int  checkOutputOverrun(unsigned long itemSize, unsigned long nItems, int align=1);
/*
 void  copy_to(cdrStream &cs, int size, int align=1);
 void  fetchInputData(int align, int size);

 int  reseveOutputSpaceForPrimitiveType(int align, int size);
 int  maybeReseveOutputSpace(int align, int size);

 unsigned long currentInputPtr() const;
*/
 unsigned long currentOutputPtr() const;

 cdrMemoryStream& operator=(const cdrMemoryStream &cms);
};

#endif //__cplusplus

#endif

