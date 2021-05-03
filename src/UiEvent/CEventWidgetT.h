#ifndef XP_UIBASE_UIEVENT_CEVENTWIDGETT_H
#define XP_UIBASE_UIEVENT_CEVENTWIDGETT_H

#include <UiBase/UiEvent/CEventDeliverer.h>
#include "eventDef.h"

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    #include <QtWidgets/qwidget.h>
#else
    #ifdef Q_OS_WIN
        #include <private/qwidget_p.h>
    #endif // Q_OS_WIN
#endif

namespace PC
{
    typedef boost::function<void (QWidget *)> EnumWidgetFunc;

    /**
     *  zhangyi : 2012-08-02
     *
     *  此模板有以下作用：
     *
     *  1. 方便地将任何QT标准控制转化为event widget
     *  2. 定义CBaseWidget、CBaseDialog、CBaseWindow的各种共同行为，不用重复写代码
     *
     *  由于不同Qt标准控件不同，构造函数不同，因此将实现全部写在头文件中，不显式实例化
     *  因为显式实体会会强制对相应模板实参生成每一个构造函数的实例
     *  而并不是每个标准控件都拥有如下每一种参数类型的构造函数
     *  而隐式实例化只会实例化真正被调用的那些构造函数
     */
    template <class TWidget>
    class CEventWidgetT : public TWidget, public CEventDeliverer
    {
    public:
        CEventWidgetT(QWidget *parent, Qt::WindowFlags f = 0)
            : TWidget(parent)
            , CEventDeliverer(castEventDeliverer(parent))
            , m_pInnerWidget(NULL)
            , m_nInnerLeftSpace(0)
            , m_nInnerTopSpace(0)
            , m_nInnerRightSpace(0)
            , m_nInnerBottomSpace(0)
            , m_bInnerStrech(false)
            , m_bInShow(false)
        {
            setWindowFlags(f);
        }

        /**
         *  设置唯一内部控件，用于自动调整其区域
         *  @param  pWidget         唯一内部控件
         *  @param  nLeftSpace      左边距
         *  @param  nTopSpace       上边距
         *  @param  nRightSpace     右边距
         *  @param  nBottomSpace    下边距
         */
        void setInnerStretchWidget(QWidget *pWidget, int nLeftSpace = 0, int nTopSpace = 0, int nRightSpace = 0, int nBottomSpace = 0)
        {
            m_pInnerWidget = pWidget;
            m_nInnerLeftSpace = nLeftSpace;
            m_nInnerTopSpace = nTopSpace;
            m_nInnerRightSpace = nRightSpace;
            m_nInnerBottomSpace = nBottomSpace;
            m_bInnerStrech = true;
            if (NULL != pWidget)
            {
                setChild(pWidget);
            }
        }

        /**
         *  设置唯一内部控件，永远以固定大小居中布局
         *  @param  pWidget         唯一内部控件
         */
        void setInnerFixWidget(QWidget *pWidget)
        {
            m_pInnerWidget = pWidget;
            m_nInnerLeftSpace = -1;
            m_nInnerTopSpace = -1;
            m_nInnerRightSpace = -1;
            m_nInnerBottomSpace = -1;
            m_bInnerStrech = false;
            if (NULL != pWidget)
            {
                setChild(pWidget);
            }
        }

        void setChild(QWidget *pWidget)
        {
            if (NULL != pWidget)
            {
                pWidget->setParent(this);
            }
        }

        void grabMouseSafely()
        {
#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0) 
            grabMouse();
#else
            // grabMouse calls SetWindowsHookEx() - this function causes a system-wide
            // freeze if any other app on the system installs a hook and fails to
            // process events.
            QWidgetPrivate *p = qt_widget_private(this);
            p->grabMouseWhileInWindow();
#endif
#else
            grabMouse();
#endif
        }

        /**
         *  是否有某个子控件
         *  @param  pWidget         子控件
         *  @return                 是否有子控件
         */
        bool hasChildWidget(const QWidget *pWidget) const
        {
            return hasChildWidget(this, pWidget);
        }

        /**
         *  母控件是否有某个子控件
         *  非static的hasChildWidget的递归实现
         *  @param  pParentWidget   母控件
         *  @param  pChildWidget    子控件
         *  @return                 母控件是否有子控件
         */
        static bool hasChildWidget(const QWidget * pParentWidget, const QWidget *pChildWidget)
        {
            if (NULL != pChildWidget)
            {
                QWidget *pOneWidget = pChildWidget->parentWidget();
                while (NULL != pOneWidget)
                {
                    if (pOneWidget == pParentWidget)
                    {
                        return true;
                    }
                    pOneWidget = pOneWidget->parentWidget();
                }
            }
            return false;
        }

        /**
         *  递归对控件及其所有子控件作同样的操作
         *  @param  pWidget         控件
         *  @param  func            操作函数
         */
        static void enumChildrenRecursive(QWidget *pWidget, EnumWidgetFunc func)
        {
            func(pWidget);
            if (NULL != pWidget)
            {
                QObjectList list = pWidget->children();
                foreach(QObject *pObject, list)
                {
                    QWidget *pQWidget = dynamic_cast<QWidget *>(pObject);
                    if (NULL != pQWidget)
                    {
                        enumChildrenRecursive(pQWidget, func);
                    }
                }
            }
        }

        /**
         *  和showEvent、hideEvent强关联，返回当前widget是否可见的信息
         */
        bool isInShow() const
        {
            return m_bInShow;
        }

    protected:
        void focusInEvent(QFocusEvent *e)
        {
            TWidget::focusInEvent(e);

            deliverEvent(EVT_BASE_WIDGET_ACTIVE, 0, 0, "", this);
        }

        void resizeEvent(QResizeEvent *e)
        {
            TWidget::resizeEvent(e);

            resetInnerWidgetGeometry(e->size());
        }

        void showEvent(QShowEvent *e)
        {
            TWidget::showEvent(e);

            m_bInShow = true;
        }

        void hideEvent(QHideEvent *e)
        {
            TWidget::hideEvent(e);

            m_bInShow = false;
        }

        void resetInnerWidgetGeometry(QSize size)
        {
            if (NULL != m_pInnerWidget)
            {
                if (m_bInnerStrech)
                {
                    m_pInnerWidget->setGeometry(
                        m_nInnerLeftSpace,
                        m_nInnerTopSpace,
                        size.width() - m_nInnerLeftSpace - m_nInnerRightSpace,
                        size.height() - m_nInnerTopSpace - m_nInnerBottomSpace
                        );
                }
                else
                {
                    m_pInnerWidget->move(
                        (size.width() - m_pInnerWidget->width()) / 2,
                        (size.height() - m_pInnerWidget->height()) / 2
                        );
                }
            }
        }
        
        void changeEvent(QEvent *e)
        {
            TWidget::changeEvent(e);

            if (QEvent::ParentChange == e->type())
            {
                m_pParentDeliverer = castEventDeliverer(parentWidget());
                int a = 0;
            }
        }

        QWidget                 *m_pInnerWidget;
        int                     m_nInnerLeftSpace;
        int                     m_nInnerTopSpace;
        int                     m_nInnerRightSpace;
        int                     m_nInnerBottomSpace;
        bool                    m_bInnerStrech;
        bool                    m_bInShow;
    };
}

#endif
