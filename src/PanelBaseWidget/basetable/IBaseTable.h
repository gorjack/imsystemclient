#ifndef   XP_IBASETABLE__H
#define   XP_IBASETABLE__H

#include <QtWidgets/QtWidgets>
#include <UiEvent/CEventDeliverer.h>
#include <UiEvent/CEventWidgetT.h>
#include "CBaseTableHeader.h"
#include "IBaseTablePanel.h"

namespace PC
{
    enum EBaseTableMenuFlag
    {
        BTMF_NONE = 0x00000000,       //
        BTMF_LOCK_LAYOUT = 0x00000001,       // 
        BTMF_UNLOCK_LAYOUT = 0x00000002,       // 
        BTMF_ADJUST_WIDTH = 0x00000004,       //
        BTMF_ADJUST_HEIGHT = 0x00000008,       // 
        BTMF_CUSTOM_COLUMNS = 0x00000010,       // 
        BTMF_EXPORT_DATA = 0x00000020,       // 
        BTMF_COPY_DATA = 0x00000040,       //
        BTMF_AUTO_ADJUST = 0x00000080,
        BTMF_LOCK_COLUME = 0x00000100,       // 
        BTMF_UNLOCK_COLUME = 0x00000200,       // 

        BTMF_DEFAULT = BTMF_LOCK_LAYOUT | BTMF_UNLOCK_LAYOUT | BTMF_ADJUST_WIDTH | BTMF_ADJUST_HEIGHT
        | BTMF_CUSTOM_COLUMNS | BTMF_EXPORT_DATA | BTMF_COPY_DATA | BTMF_AUTO_ADJUST,
    };

    Q_DECLARE_FLAGS(FBaseTableMenuFlag, EBaseTableMenuFlag)

    class PANELBASEWIDGET_EXPORT IBaseTable : public CEventWidgetT<QWidget>
    {
    public:
        IBaseTable(int nID, QWidget *parent = NULL, FBaseTableMenuFlag flag = BTMF_DEFAULT);
        virtual ~IBaseTable();

    protected:
        CBaseTableHeader            *m_pHeader;
        IBaseTablePanel             *m_pPanel;
    };
}


#endif