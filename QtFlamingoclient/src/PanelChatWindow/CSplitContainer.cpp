#include "CSplitContainer.h"
#include <QMouseEvent>

namespace XP
{

    CSplitContainer::CSplitContainer(Qt::Orientation orientation, int nSplitterWidth, QWidget *parent /*= NULL*/)
        : QWidget(parent),
        m_orientation(orientation),
        m_nSplitterWidth(nSplitterWidth),
        m_pFirstWidget(NULL),
        m_pSecondWidget(NULL),
        m_bFirstStable(false),
        m_nStableLength(0),
        m_nMouseDownStableLength(0),
        m_bDragging(false),
        m_bFirstVisible(true),
        m_bSecondVisible(true),
        m_nFirstMinLength(0),
        m_bSpliterVisible(false)
    {
        setMouseTracking(true);
    }

    CSplitContainer::~CSplitContainer()
    {

    }

    void CSplitContainer::setWidgets(QWidget *pFirstWidget, QWidget *pSecondWidget, bool bFirstStable, int nStableLength)
    {
        if (NULL != pFirstWidget && NULL != pSecondWidget)
        {
            m_pFirstWidget = pFirstWidget;
            m_pFirstWidget->setMouseTracking(true);
            m_pFirstWidget->setCursor(Qt::ArrowCursor);
            setChild(m_pFirstWidget);
            m_pSecondWidget = pSecondWidget;
            m_pSecondWidget->setMouseTracking(true);
            m_pSecondWidget->setCursor(Qt::ArrowCursor);
            setChild(m_pSecondWidget);
            m_bFirstStable = bFirstStable;
            m_nStableLength = qMax(nStableLength, m_nFirstMinLength);
        }
    }

    int CSplitContainer::stableLength() const
    {
        return m_nStableLength;
    }

    void CSplitContainer::setStableLength(int nLength)
    {
        m_nStableLength = qMax(nLength, m_nFirstMinLength);;
        resetLayout(size());
    }

    void CSplitContainer::setFirstVisible(bool bVisible)
    {
        m_bFirstVisible = bVisible;

        resetLayout(size());
    }

    void CSplitContainer::setSecondVisible(bool bVisible)
    {
        m_bSecondVisible = bVisible;

        resetLayout(size());
    }

    void CSplitContainer::setFirstMinLength(int nLength)
    {
        m_nFirstMinLength = nLength;
        m_nStableLength = qMax(m_nStableLength, m_nFirstMinLength);

        resetLayout(size());
    }

    bool CSplitContainer::firstVisible() const
    {
        return m_bFirstVisible;
    }

    bool CSplitContainer::secondVisible() const
    {
        return m_bSecondVisible;
    }

    void CSplitContainer::paintEvent(QPaintEvent *e)
    {
        QWidget::paintEvent(e);

        //if (m_bSpliterVisible)
        //{
        //    QPainter painter(this);
        //    painter.fillRect(m_rtDrag, *TT_COLOR("clr_multi_splitter_default"));
        //}

        //QPainter painter(this);
        //if (Qt::Horizontal == m_orientation)
        //{
        //    QRect rtSlider = m_rtDrag;
        //    int nHeight = qMin(m_rtDrag.height() / 10, 50);
        //    nHeight = qMax(nHeight, 5);
        //    rtSlider.setY(m_rtDrag.y() + (m_rtDrag.height() - nHeight) / 2);
        //    rtSlider.setHeight(nHeight);

        //    painter.setPen(*TT_COLOR("clr_multi_splitter_default"));
        //    painter.drawLine(m_rtDrag.x() + m_rtDrag.width() / 2, m_rtDrag.y(), m_rtDrag.x() + m_rtDrag.width() / 2, m_rtDrag.y() + m_rtDrag.height());
        //    painter.fillRect(rtSlider, *TT_COLOR("clr_splitter_slider"));
        //}
        //else
        //{
        //    QRect rtSlider = m_rtDrag;
        //    int nWidth = qMin(m_rtDrag.width() / 10, 50);
        //    nWidth = qMax(nWidth, 5);
        //    rtSlider.setX(m_rtDrag.x() +(m_rtDrag.width() - nWidth) / 2);
        //    rtSlider.setWidth(nWidth);

        //    painter.setPen(*TT_COLOR("clr_multi_splitter_default"));
        //    painter.drawLine(m_rtDrag.x(), m_rtDrag.y() + m_rtDrag.height() / 2, m_rtDrag.x() + m_rtDrag.width(), m_rtDrag.y() + m_rtDrag.height() / 2);
        //    painter.fillRect(rtSlider, *TT_COLOR("clr_splitter_slider"));
        //}
    }

    void CSplitContainer::resizeEvent(QResizeEvent *e)
    {
        resetLayout(e->size());
    }

    void CSplitContainer::mouseMoveEvent(QMouseEvent *e)
    {
        QWidget::mouseMoveEvent(e);
        if (m_bFirstVisible && m_bSecondVisible)
        {
            if (m_rtDrag.contains(e->pos()))
            {
                setCursor(Qt::Horizontal == m_orientation ? Qt::SizeHorCursor : Qt::SizeVerCursor);
            }
            if (m_bDragging)
            {
                QPoint ptGlobalNow = mapToGlobal(e->pos());
                if (Qt::Horizontal == m_orientation)
                {
                    int nXOffset = ptGlobalNow.x() - m_ptGlobalMouseDown.x();
                    m_nStableLength = m_nMouseDownStableLength + (m_bFirstStable ? nXOffset : (-nXOffset));
                    m_nStableLength = qMax(m_nStableLength, m_nFirstMinLength);
                    m_nStableLength = qMin(m_nStableLength, size().width() - 21);
                    resetLayout(size());
                }
                else if (Qt::Vertical == m_orientation)
                {
                    int nYOffset = ptGlobalNow.y() - m_ptGlobalMouseDown.y();
                    m_nStableLength = m_nMouseDownStableLength + (m_bFirstStable ? nYOffset : (-nYOffset));
                    m_nStableLength = qMax(m_nStableLength, m_nFirstMinLength);
                    m_nStableLength = qMin(m_nStableLength, size().width() - 21);
                    resetLayout(size());
                }
            }
        }
    }

    void CSplitContainer::mousePressEvent(QMouseEvent *e)
    {
        QWidget::mousePressEvent(e);
        if (m_rtDrag.contains(e->pos()) && m_bFirstVisible && m_bSecondVisible)
        {
            m_bDragging = true;
            m_nMouseDownStableLength = m_nStableLength;
            m_ptGlobalMouseDown = mapToGlobal(e->pos());
        }
    }

    void CSplitContainer::mouseReleaseEvent(QMouseEvent *e)
    {
        if (m_bDragging)
        {
            //deliverEvent(XP::EVT_SPLIT_CONTAINER_RESIZE);
        }

        m_bDragging = false;
        m_nMouseDownStableLength = 0;
        m_ptGlobalMouseDown.setX(0);
        m_ptGlobalMouseDown.setY(0);
    }

    void CSplitContainer::leaveEvent(QEvent *e)
    {
        setCursor(Qt::ArrowCursor);
        m_bDragging = false;
        m_nMouseDownStableLength = 0;
        m_ptGlobalMouseDown.setX(0);
        m_ptGlobalMouseDown.setY(0);
    }

    void CSplitContainer::resetLayout(QSize size)
    {
        if (m_bFirstVisible && m_bSecondVisible)
        {
            int nUnStableLength = (
                (Qt::Horizontal == m_orientation)
                ? (size.width() - m_nStableLength - m_nSplitterWidth)
                : (size.height() - m_nStableLength - m_nSplitterWidth)
                );
            if (Qt::Horizontal == m_orientation)
            {
                int nFirstWidth = m_bFirstStable ? m_nStableLength : nUnStableLength;
                int nSecondWidth = m_bFirstStable ? nUnStableLength : m_nStableLength;
                if (NULL != m_pFirstWidget)
                {
                    m_pFirstWidget->setGeometry(0, 0, nFirstWidth, size.height());
                    m_pFirstWidget->show();
                }
                if (NULL != m_pSecondWidget)
                {
                    m_pSecondWidget->setGeometry(nFirstWidth + m_nSplitterWidth, 0, nSecondWidth, size.height());
                    m_pSecondWidget->show();
                }
                m_rtDrag.setLeft(nFirstWidth);
                m_rtDrag.setTop(0);
                m_rtDrag.setRight(m_rtDrag.left() + m_nSplitterWidth - 1);
                m_rtDrag.setBottom(size.height() - 1);
            }
            else if (Qt::Vertical == m_orientation)
            {
                int nFirstHeight = m_bFirstStable ? m_nStableLength : nUnStableLength;
                int nSecondHeight = m_bFirstStable ? nUnStableLength : m_nStableLength;
                if (NULL != m_pFirstWidget)
                {
                    m_pFirstWidget->setGeometry(0, 0, size.width(), nFirstHeight);
                    m_pFirstWidget->show();
                }
                if (NULL != m_pSecondWidget)
                {
                    m_pSecondWidget->setGeometry(0, nFirstHeight + m_nSplitterWidth, size.width(), nSecondHeight);
                    m_pSecondWidget->show();
                }
                m_rtDrag.setLeft(0);
                m_rtDrag.setTop(nFirstHeight);
                m_rtDrag.setRight(size.width() - 1);
                m_rtDrag.setBottom(m_rtDrag.top() + m_nSplitterWidth - 1);
            }
        }
        else
        {
            if (m_bFirstVisible && !m_bSecondVisible)
            {
                if (NULL != m_pSecondWidget)
                {
                    m_pSecondWidget->hide();
                }
                if (NULL != m_pFirstWidget)
                {
                    m_pFirstWidget->show();
                    m_pFirstWidget->setGeometry(rect());
                }
            }
            else if (!m_bFirstVisible && m_bSecondVisible)
            {
                if (NULL != m_pFirstWidget)
                {
                    m_pFirstWidget->hide();
                }
                if (NULL != m_pSecondWidget)
                {
                    m_pSecondWidget->show();
                    m_pSecondWidget->setGeometry(rect());
                }
            }
            else
            {
                if (NULL != m_pFirstWidget)
                {
                    m_pFirstWidget->hide();
                }
                if (NULL != m_pSecondWidget)
                {
                    m_pSecondWidget->hide();
                }
            }
        }
    }

    void CSplitContainer::setSpliterVisible(bool bVisible)
    {
        m_bSpliterVisible = bVisible;
    }

    int CSplitContainer::getSecondWidth()
    {
        int nWidth = 0;
        if (NULL != m_pSecondWidget)
        {
            const QRect & qSecondRect = m_pSecondWidget->geometry();
            nWidth = qSecondRect.width();
        }
        return nWidth;
    }
}
