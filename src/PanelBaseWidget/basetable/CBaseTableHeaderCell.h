/**
 *  表格列头单元
 *
 *  @author zhangyi
 *  @since  2012-05-23
 */

#ifndef XP_UIBASE_BASEWIDGET_BASETABLE_CBASETABLEHEADERCELL_H
#define XP_UIBASE_BASEWIDGET_BASETABLE_CBASETABLEHEADERCELL_H

#include "CPushButton.h"

namespace PC
{
    class CBaseTableHeaderCellToolWidget;
    class CBaseTableHeaderCellTipWidget;
    class CBaseTableColumnFilterWidget;
    class CCheckBox;

    /**
     *  表格header按钮
     */
    class PANELBASEWIDGET_EXPORT CBaseTableHeaderCell : public CPushButton
    {
    public:
        CBaseTableHeaderCell(
            QString qsImgFile,
            int nID,
            QWidget *parent = NULL
            );

        CBaseTableHeaderCell(
            QString qsImgFile,
            int nID,
            int nXSplit1,
            int nXSplit2,
            int nYSplit1,
            int nYSplit2,
            QWidget *parent = NULL
            );
        virtual ~CBaseTableHeaderCell();
    };

}

#endif
