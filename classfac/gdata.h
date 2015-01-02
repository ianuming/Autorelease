#ifndef __GDATA__H__
#define __GDATA__H__

#pragma once

#include "gobject.h"

#define GDATA_SUPPORT_COM

#ifdef GDATA_SUPPORT_COM
#include <guiddef.h>
#include <unknwn.h>
#endif

class GData : public GObject
{
    DECLARE_GDYNAMIC_CLASS(GData)

public:
    typedef char FieldTypeType;
    typedef void* FieldValueType;
    typedef const char* FieldNameType;

    enum GDATA_TYPE
    {
	    GDATA_TYPE_NONE		= 0,
	    GDATA_TYPE_BOOL		= 1,
	    GDATA_TYPE_INT		= 2,
	    GDATA_TYPE_DATA		= 3,
	    GDATA_TYPE_ARRAY    = 4,
        GDATA_TYPE_OBJECT   = 5,
#ifdef GDATA_SUPPORT_COM
        GDATA_TYPE_GUID     = 6,
        GDATA_TYPE_INTERFACE= 7,
#endif
    };

public:
    GData(void);
    virtual ~GData(void);

    int  getFieldCount() const;
    FieldTypeType getFieldType(int index) const;
    FieldTypeType getFieldType(FieldNameType szKey) const;
	FieldNameType getFieldName(int index) const;

    void delField(int index);
    void delField(FieldNameType szKey);

    bool getBool(const char* szKey) const;
    int  getInt(const char* szKey) const;
#ifdef GDATA_SUPPORT_COM
    GUID getGuid(const char* szKey) const;
    IUnknown* getInterface(const char* szKey) const;
#endif

    void setBool(const char* szKey, bool value);
    void setInt(const char* szKey, int value);
#ifdef GDATA_SUPPORT_COM
    void setGuid(const char* szKey, REFGUID value);
    void setInterface(const char* szKey, IUnknown* value);
#endif
/*
	///��ȡBYTE����ֵ
	HRESULT GetByte([in, string] BSTR bsParamName, [out, retval] BYTE *pcValue);

	///��ȡchar����ֵ
	HRESULT GetChar([in, string] BSTR bsParamName, [out, retval] small *pchValue);

	///��ȡWord����ֵ
	HRESULT GetWord([in, string] BSTR bsParamName, [out, retval] WORD *pwValue);

	///��ȡShort����ֵ
	HRESULT GetShort([in, string] BSTR bsParamName, [out, retval] short *pshValue);

	///��ȡDWord����ֵ
	HRESULT GetDWord([in, string] BSTR bsParamName, [out, retval] DWORD *pdwValue);

	///��ȡint64����ֵ��
	HRESULT GetInt64([in, string] BSTR bsParamName, [out, retval] INT64 * pn64Var);

	///��ȡdouble����ֵ��
	HRESULT GetDouble([in, string] BSTR bsParamName, [out, retval] double * pdValue);

	///��ȡBstr����ֵ
	HRESULT GetStr([in, string] BSTR bsParamName, [out, retval] BSTR *pbsValue);

	/// ��ȡBuffer�����ص�ITXBuffer�ǿ������ݣ��޸�������Ӱ��ITXData�е����ݡ�
	HRESULT GetBuf([in, string] BSTR bsParamName, [out, retval] ITXBuffer** ppBufValue);

	/// ��ȡTyped Buffer
	HRESULT GetBufTyped([in, string]BSTR bsParamName, [out]ITXBuffer** ppBufValue, [out]DWORD* pdwSubType);

	///��ȡguid����ֵ��
	HRESULT GetGuid([in, string] BSTR bsParamName, [out, retval] GUID * pGuid);

	///��ȡ�ӿ�ָ������ֵ
	HRESULT GetInterface([in, string] BSTR bsParamName, [in] REFIID riid, [out, retval, iid_is(riid)] void **ppvValue);

	///��Data���ݴ�����ֽ���
	HRESULT GetDoc([out, retval] ITXBuffer **ppBufDoc);

	///�ѵ�ǰ�����ֶ����ݿ���������һ��TXData
	HRESULT CopyTo([in]ITXData *pData);

	///�ж�����TXData�����Ƿ���ͬ S_OK:equal	S_FALSE:not equal
	HRESULT Equal([in]ITXDataRead* pData);

	//////////////////////////////////////////////////////////////////////////
	// add for GF
	HRESULT FindStringEntry([in, string] BSTR bsParamName, [out, retval] const TCHAR ** ppv);

	///�ѵ�ǰ�����ֶ����ݿ���������һ��TXData, ���Ŀ��TXData���ظ��ֶΣ�������и���
	HRESULT CopyToNoOverwrite([in]ITXData *pData);

    ///����ĳ���ֶ�
    HRESULT CopyFieldTo([in]ITXData *pData, [in, string] BSTR bsParamName);

	///��ȡUInt64����ֵ
	HRESULT GetUInt64([in, string] BSTR bsParamName, [out, retval] UINT64 *pddwValue);
*/
    void clear(void);
    bool reserve(int size);

protected:
    void setValue(FieldNameType szKey, FieldTypeType type, FieldValueType value);
    bool getValue(const char* szKey, FieldTypeType& type, FieldValueType& value) const;
    void freeValue(FieldTypeType type, FieldValueType value);
    void freeItem(int index);

    void* allocBuffer(int size) const;
    void  freeBuffer(void* p) const;
    FieldNameType allocName(const char* szKey) const;
    void  freeName(FieldNameType name) const;

protected:
    typedef struct DATA_ITEM
    {
        FieldTypeType  type;
        FieldNameType  name;
        FieldValueType value;
    };

    int   m_fieldCount;
    int   m_allocCount;
    DATA_ITEM * m_buffer;
};

#endif