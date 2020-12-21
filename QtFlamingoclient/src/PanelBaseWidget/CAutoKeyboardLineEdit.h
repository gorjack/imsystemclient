#ifndef TC__SMARTKEYBOARD_CAUTOKEYBOARDLINEEDIT_H
#define TC__SMARTKEYBOARD_CAUTOKEYBOARDLINEEDIT_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include "CAutoKeyboardWidget.h"

namespace QF
{
    class CLineEdit;
    class CPushButton;
}

namespace XP
{
    class CAutoKeyboardOperator;

    class CAutoKeyboardLineEdit : public QWidget
    {
        Q_OBJECT

    public:
        CAutoKeyboardLineEdit(ISearchDataModel *pData,int nID, QWidget *parent = NULL, bool bNeedCustom = false);
        virtual ~CAutoKeyboardLineEdit();

        QString toString();
        virtual void clear();

        void setText(const QString& strId, const QString& qsText, bool bTestString = true);
        void setTextFontKey( QString qsTextFontKey );
        void setShowName(bool bShowName);
        QString getText() const;

        void setFrame(bool bShowFrame);
        void clearCache();
        void setIndexAndText(int nIndex, QString qsText);
        int getIndex() const;
        void clearIndex();
        QString getInput() const; 
        void  setcurrentId(int id);
        void setWidgetWidth(int iWidth);
        //void setFixedSize(int iWidth,int iHeight);

        void setNeedCustom(bool bNeedCustom);
        void setValidator(QValidator* pValidator);

        void setAutoToUpper(bool autoToUpper);
        void setPinYinAdapter(bool bAdapter);

        void setFilterSpecialChar(bool bFilterSpecialChar);
        void setFilterChar(QList<int> filterCharList);
        QLineEdit *getLineEdit()const;
        void setPullBtnShow(bool bTrue);


        void setDataModel(ISearchDataModel *pDataModel);
        ISearchDataModel * getDataModel() { return m_pWidget->getDataModel(); };

    protected:
        void focusInEvent(QFocusEvent *e);
        void focusOutEvent(QFocusEvent *e);

        void resizeEvent(QResizeEvent *e);
        bool eventFilter(QObject *pObj, QEvent *pEvent);

    protected Q_SLOTS:
        void slotChangeText(int, const QString& qsText, const QString& qsParam);
        void slotTextEdited(const QString &);
        void slotFocusIn();
        void slotFocusOut();
        void slotHandleClicked();

    protected:
        int                                         m_nID;
        int                                         m_nIndex;
        QF::CLineEdit*                             m_pLineEdit;
        QF::CPushButton*                           m_pPullBtn;
        CAutoKeyboardOperator*                      m_pOperator;
        CAutoKeyboardWidget*                        m_pWidget;
        QString                                     m_qsRealCode;
        bool                                        m_bNeedCustom;
        bool                                        m_bFilterSpecialChar;
        QList<int>                                  m_listFilterChar;
    private:
    };
    
}

#endif