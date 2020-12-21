/**
 *    键盘精灵输入辅助关联工具类
 *
 *  @author zhangyi
 *  @since  2012-03-29
 *  @modify by huangxu
 *  @since since 2016-03-27
 */

#ifndef TC_UICOMPONENT_SMARTKEYBOARD_CSMARTKEYBOARDOPERATOR_H
#define TC_UICOMPONENT_SMARTKEYBOARD_CSMARTKEYBOARDOPERATOR_H

#include <QObject>
#include <QVector>
#include <QSet>

namespace QF
{
    class CLineEdit;
}

namespace XP
{
    class CAutoKeyboardWidget;
    class  CAutoKeyboardOperator : public QObject
    {
        Q_OBJECT

    public:
        CAutoKeyboardOperator(QObject *parent = NULL);
        virtual ~CAutoKeyboardOperator();

        void setLineEdit(QF::CLineEdit* pLineEdit);
        void addSmartKeyboardWidget(CAutoKeyboardWidget *pSmartKeyboardWidget);
        void testSmartKeyboardWidgets();
        void hideSmartKeyboardWidgets();

        bool anySmartKeyboardShow() const;

    Q_SIGNALS:
        void sigChangeText(int, const QString&, const QString&);

    protected Q_SLOTS:
        void slotItemDoubleClicked(QString qsText);

    protected:

        bool eventFilter(QObject *pObj, QEvent *pEvent);

        QVector<CAutoKeyboardWidget *>     m_vSmartKeyboardWidgets;
        QVector<bool>                       m_vSmartKeyboardShow;

        QSet<QObject *>                     m_evtFiltered;
        QF::CLineEdit                          *m_pLineEdit;

        void testSmartKeyboardWidget(int i);
        void showSmartKeyboardWidget(int x, int y, int w, int h, QString qsKey, int i);
        void hideSmartKeyboardWidget(int i);
        void pushSelectionOnTextEdit(int i);
        bool hasVisibleSmartKeyboardWidgets();

        void reinstallEvtFilter();
        void clearEvtFilter();
    };
}

#endif
