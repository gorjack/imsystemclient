#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class CBuddyItem : public QWidget
{
public:
    explicit CBuddyItem(QWidget *parent = 0);

    void initUi();

    QWidget         *m_pHead = NULL;  
    QLabel          *m_pName = NULL;   
    QLabel          *m_pSign = NULL; 
    QString          m_pHeadPath;

    int              m_nId;
    bool eventFilter(QObject *obj, QEvent *event);
};