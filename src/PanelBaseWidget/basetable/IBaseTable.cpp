#include "IBaseTable.h"

namespace PC
{

    IBaseTable::IBaseTable(int nID, QWidget *parent /*= NULL*/, FBaseTableMenuFlag flag /*= BTMF_DEFAULT*/)
    {
        m_pHeader = new CBaseTableHeader(nID, this);
    }

    IBaseTable::~IBaseTable()
    {

    }

}