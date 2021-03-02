/**
 *  表格主面板接口
 *
 *  @author zhangyi
 *  @since  2012-07-30
 */

#ifndef XP_UIBASE_BASEWIDGET_BASETABLE_IBASETABLEPANEL_H
#define XP_UIBASE_BASEWIDGET_BASETABLE_IBASETABLEPANEL_H

#include <QtWidgets/QtWidgets>
#include <UiEvent/CEventDeliverer.h>
#include <UiEvent/CEventWidgetT.h>

namespace PC
{
    using namespace std;

    class CBaseTableHeader;
    /**
     *  无论是普通表格还是高性能表格，其面板所具有的特征都包括：
     *  各列单独成控件，可定制UI风格，可按行或列获取内容，可选择行，可获取行和列的ID<->下标对应关系，可移动隐藏锁定列，等等。
     *  因此在基类中定义上述行为。
     */
    class PANELBASEWIDGET_EXPORT IBaseTablePanel : public CEventWidgetT<QWidget>
    {
    public:
        IBaseTablePanel(int nTableID, CBaseTableHeader *pHeader, QWidget *parent = NULL);
        virtual ~IBaseTablePanel();
    };
}

#endif
