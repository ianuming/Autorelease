#ifndef __GAUTO_RELEASE_POOL__
#define __GAUTO_RELEASE_POOL__

#include <list>

#include "gobject.h"

class GAPI GAutoreleasePool : public GObject
{
	DECLARE_GDYNAMIC_CLASS(GAutoreleasePool)
public:
    GAutoreleasePool(void);
    virtual ~GAutoreleasePool(void);

private:
    void drain(void);
    void add(GObject* obj);

    void pushTls(void);
    void popTls(void);
private:
    typedef std::list<GObject*> GObjectList;
    GObjectList         m_list;
    GAutoreleasePool*   m_prev;

public:
    static void addObject(GObject* obj);
    static void drainObject();

    // ��ʵ����
    // 1. Ӧ���и��ٽ���ɶ��
    // 2. Tlsϵ�к������԰�װ�����󣬷����ƽ̨
    static unsigned int _tlsKey;
};

#endif

