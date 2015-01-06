#include "guiobject.h"

IMPLEMENT_GDYNAMIC_CLASS(GUIObject, GObject)

GUIObject::GUIObject(void)
: m_bVisible(true)
, m_bEnable(true)
, m_bEnter(false)
, m_bMouseDown(false)
{
}

GUIObject::~GUIObject(void)
{
}

void GUIObject::setId(const char* id)
{
    if (!id)
    {
        m_id.clear();
    }
    else
    {
        m_id = id;
    }
}

const char* GUIObject::getId(void) const
{
    return m_id.c_str();
}

bool GUIObject::isHit(const GPoint& pt) const
{
    if (!m_bVisible) return false;

    GRect rect(m_pos, m_pos + m_size);
    return rect.PtInRect(pt);
}

void GUIObject::setVisible(bool bVisible)
{
    if (bVisible != m_bVisible)
    {
        m_bVisible = bVisible;
        onVisibleChange();
    }
}

bool GUIObject::isEnable() const
{
    return m_bEnable;
}

void GUIObject::setEnable(bool bEnable)
{
    if (m_bEnable != bEnable)
    {
        m_bEnable = bEnable;
        onEnableChange();
    }
}

bool GUIObject::isVisible() const
{
    return m_bVisible;
}

void GUIObject::GetPos(GPoint& pt) const
{
    pt = m_pos;
}

void GUIObject::SetPos(const GPoint& pt)
{
    if (pt != m_pos)
    {
        GPoint ptOld = m_pos;
        m_pos = pt;
        onMove(ptOld, pt);
    }
}

void GUIObject::GetSize(GSize& size) const
{
    size = m_size;
}

void GUIObject::SetSize(const GSize& size)
{
    if (size != m_size)
    {
        GSize szOld = m_size;
        m_size = size;
        onResize(szOld, size);
    }
}

void GUIObject::Update(const GRect* rc)
{

}

void GUIObject::GetRect(GRect& rect) const
{
    rect.SetRect(m_pos, m_pos + m_size);
}

void GUIObject::onClick(const GPoint& pt, uint button, uint keyState, uint clickTimes, bool& bHandled)
{
}

void GUIObject::onMouseDown(const GPoint& pt, uint button, uint keyState, bool& bHandled)   
{
    m_bMouseDown = true;
    Update();
}

void GUIObject::onMouseUp(const GPoint& pt, uint button, uint keyState, bool& bHandled)
{
    m_bMouseDown = false;
    Update();
}

void GUIObject::onMouseMove(const GPoint& pt, uint keyState, bool& bHandled)
{
}

void GUIObject::onMouseHover()
{
}

void GUIObject::onMouseEnter()
{
    m_bEnter = true;
    Update();
}

void GUIObject::onMouseLeave()
{
    m_bEnter = false;
    Update();
}

void GUIObject::onMouseWheel(const GPoint& pt, uint keyState, int16 zDelta, bool& bHandled)
{
}

void GUIObject::onKeyDown(uint nChar, uint nRepCnt, uint nFlags)
{
}

void GUIObject::onKeyUp(uint nChar, uint nRepCnt, uint nFlags)
{
}

void GUIObject::onMove(const GPoint& ptOld, const GPoint& ptNew)
{
    GFireEvent(OnMoveEventFunc, OnMove, (this, ptOld, ptNew));
}

void GUIObject::onResize(const GSize& szOld, const GSize& szNew)
{
    GFireEvent(OnResizeEventFunc, OnResize, (this, szOld, szNew));
}

void GUIObject::onVisibleChange()
{
}

void GUIObject::onEnableChange()
{
}

#include <Windows.h>

void GUIObject::onPaint(HGCANVAS hCanvas)
{
    HDC hdc = (HDC)hCanvas;

    if (m_bMouseDown)
    {
        RECT rc = {0,0,m_size.cx,m_size.cy};
        ::FillRect(hdc,&rc, (HBRUSH)::GetStockObject(WHITE_BRUSH));
    }

    if (m_bEnter)
        ::SelectObject(hdc, ::GetStockObject(WHITE_PEN));
    else
        ::SelectObject(hdc, ::GetStockObject(BLACK_PEN));

    ::MoveToEx(hdc, 0, 0, NULL);
    ::LineTo(hdc, m_size.cx, m_size.cy);
    ::MoveToEx(hdc, m_size.cx, 0, NULL);
    ::LineTo(hdc, 0, m_size.cy);
}
