#ifndef __GDATA_TYPE_H__
#define __GDATA_TYPE_H__

#define GDATA_SUPPORT_COM

#ifdef GDATA_SUPPORT_COM
#include <guiddef.h>
#include <unknwn.h>
#endif

class GData;
class GArray;

enum GDATA_TYPE
{
	GDATA_TYPE_NONE		= 0,
	GDATA_TYPE_BOOL		= 1,
    GDATA_TYPE_INT		= 2,
    GDATA_TYPE_UINT     = 3,
    GDATA_TYPE_INT64    = 4,
    GDATA_TYPE_UINT64   = 5,
    GDATA_TYPE_FLOAT    = 6,
    GDATA_TYPE_STRING   = 7,
	GDATA_TYPE_STRINGW  = 8,
    GDATA_TYPE_BUFFER   = 9,
	GDATA_TYPE_DATA		= 10,
	GDATA_TYPE_ARRAY    = 11,
    GDATA_TYPE_OBJECT   = 12,
    GDATA_TYPE_INTVECTOR= 15,
    GDATA_TYPE_INTERFACE= 13,
    GDATA_TYPE_GUID     = 14,
    // 以下所有新增类型，必须保持TLV结构，否则兼容有问题
};

typedef char FieldTypeType;

struct data_string;
struct data_wstring;
struct int_vector;
struct buffer;

typedef union FieldValueType
{
    byte          bv;
    int32         iv;
    uint32        uv;
    float         fv;

    void*         pv;
    int64*        pi64;
    uint64*       pu64;
    data_string*  ps;
    data_wstring* pws;
    int_vector*   piv;
    buffer*       pb;
    GData*        pdata;
    GArray*       parray;

    inline FieldValueType(void* v = 0) : pv(v) {}
}FieldValueType;

#endif