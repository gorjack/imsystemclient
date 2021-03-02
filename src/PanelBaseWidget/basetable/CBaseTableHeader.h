/**
 *  表格头
 *
 *  @author zhangyi
 *  @since  2012-05-23
 */

#ifndef XP_UIBASE_BASEWIDGET_BASETABLE_CBASETABLEHEADER_H
#define XP_UIBASE_BASEWIDGET_BASETABLE_CBASETABLEHEADER_H

#include <QtWidgets/QtWidgets>
#include <UiEvent/CEventDeliverer.h>
#include <UiEvent/CEventWidgetT.h>

namespace PC
{
    class CBaseTableHeaderCell;

    class PANELBASEWIDGET_EXPORT CBaseTableHeader : public CEventWidgetT<QWidget>
    {
        Q_OBJECT

    public:
        CBaseTableHeader(int nID, QWidget *parent = NULL);
        virtual ~CBaseTableHeader();

        QList<CBaseTableHeaderCell *>   m_vColumnHeaderButtons;
    };
}

#endif
