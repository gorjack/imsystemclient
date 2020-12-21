#ifndef XP_UIBASE_BASEWIDGET_CSPLITCONTAINER_H
#define XP_UIBASE_BASEWIDGET_CSPLITCONTAINER_H

#include <QtWidgets/QWidget.h>

namespace XP
{
    class CSplitContainer : public QWidget
    {
    public:
        CSplitContainer(Qt::Orientation orientation, int nSplitterWidth, QWidget *parent = NULL);
        virtual ~CSplitContainer();

        void setWidgets(QWidget *pFirstWidget, QWidget *pSecondWidget, bool bFirstStable, int nStableLength);
        int stableLength() const;
        void setStableLength(int nLength);

        void setFirstVisible(bool bVisible);
        void setSecondVisible(bool bVisible);

        bool firstVisible() const;
        bool secondVisible() const;

        void setFirstMinLength(int nLength);

        void setSpliterVisible(bool bVisible);
        int getSecondWidth();

    protected:
        void paintEvent(QPaintEvent *e);
        void resizeEvent(QResizeEvent *e);
        void mouseMoveEvent(QMouseEvent *e);
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        void leaveEvent(QEvent *e);

        void setChild(QWidget *pWidget)
        {
            if (NULL != pWidget)
            {
                pWidget->setParent(this);
            }
        }

        Qt::Orientation m_orientation;
        int         m_nSplitterWidth;
        QWidget     *m_pFirstWidget;
        QWidget     *m_pSecondWidget;
        bool        m_bFirstStable;
        int         m_nStableLength;
        QRect       m_rtDrag;

        bool        m_bDragging;
        int         m_nMouseDownStableLength;
        QPoint      m_ptGlobalMouseDown;

        bool        m_bFirstVisible;
        bool        m_bSecondVisible;
        bool        m_bSpliterVisible;

        int         m_nFirstMinLength;

        void resetLayout(QSize size);
    };
}

#endif
