/**
 *  ÊäÈëÌáÊ¾widget
 *
 *  @author zhangyi
 *  @since  2011-03-29
 */

#include "CAutoKeyboardWidget.h"

namespace XP
{
    CAutoKeyboardWidget::CAutoKeyboardWidget(QWidget *parent /* = NULL */)
        : QListWidget(parent)
        , m_pListData(NULL)
        , m_autoToUpper(true)
        , m_bPinYinAdapter(true)
    {
        setMouseTracking(true);
        connect(this, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(onItemDoubleClicked(QListWidgetItem *)));
        resize(150, 150);
        setFocusPolicy(Qt::NoFocus);
        setFixedHeight(150);
        setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

        clear();
    }

    CAutoKeyboardWidget::~CAutoKeyboardWidget()
    {

    }

    QString CAutoKeyboardWidget::getSelection() const
    {
        QListWidgetItem *pItem = currentItem();
        if (NULL != pItem)
        {
            QString s = pItem->text();

            return pItem->text();
        }
        return "";
    }

    QString CAutoKeyboardWidget::getParam() const
    {
        QListWidgetItem *pItem = currentItem();
        if (NULL != pItem)
        {
            QVariant v = pItem->data(Qt::UserRole);
            if (v.isValid() && v.type() == QVariant::String)
            {
                QString s = v.toString();
                return v.toString();
            }
        }  
        return "";
    }

    void CAutoKeyboardWidget::onItemDoubleClicked(QListWidgetItem *pItem)
    {
        if (NULL != pItem)
        {
            emit sigItemDoubleClicked(pItem->text());
        }
        hide();
    }

    void CAutoKeyboardWidget::setDataModel(ISearchDataModel *pDataModel)
    {
        m_pListData = pDataModel;
    }

    void CAutoKeyboardWidget::clearCache()
    {
        m_itemMap.clear();
    }

    void CAutoKeyboardWidget::setAutoToUpper(bool autoToUpper)
    {
        m_autoToUpper = autoToUpper;
    }

    void CAutoKeyboardWidget::display(QPoint ptGlobal, QString qsKey)
    {
        QPoint pt = ptGlobal;
        filter(qsKey);
        move(pt);
        show();
        raise();
    }

    void CAutoKeyboardWidget::shift(QPoint ptShift)
    {
        QPoint pt = pos() + ptShift;
        move(pt);
        raise();
    }

    int CAutoKeyboardWidget::testString( QString qsParam ) const
    {
        if (NULL == m_pListData)
        {
            return -1;
        }

        return m_pListData->testData(qsParam);
    }

    bool CAutoKeyboardWidget::isListDataEmpty() const
    {
        return m_pListData->getStringList().isEmpty();
    }

    void CAutoKeyboardWidget::filter( QString qsKey )
    {
        if (m_autoToUpper)
        {
            qsKey = qsKey.toUpper();
        }
        
        std::string strFilter = qsKey.toLocal8Bit().constData();

        if (m_itemMap.isEmpty() || m_itemMap.size() != m_pListData->getStringList().size())
        {
            initCacheMap(m_pListData->getStringList(), m_pListData->getRealStringList());
        }

        setListWidgetItem(strFilter, qsKey);

        if (0 == count())
        {
            addItem(qsKey);
        }

        setCurrentRow(0);
    }

    void CAutoKeyboardWidget::initCacheMap( const QStringList & allDatas, const QStringList & realDatas )
    {
        QStringList::const_iterator itAllDatas = allDatas.begin();
        QStringList::const_iterator itRealDatas = realDatas.begin();
        for (; itAllDatas != allDatas.end() && itRealDatas != realDatas.end(); ++itAllDatas, ++itRealDatas)
        {
            QString qsText = *itAllDatas;
            QString qsPy = "";

            QString qsCodeName = qsText/* + "_" + qsPy*/;
            QPair<QString, QString> qItemPair;
            QStringList strTemps = (*itRealDatas).split("&&");
            if (strTemps.size() > 1)
            {
                qItemPair.first = strTemps[0];
                qItemPair.second = strTemps[1];
            }

            if (m_autoToUpper)
            {
                qsCodeName = qsCodeName.toUpper();
            }

            m_itemMap[qsCodeName] = qItemPair;
        }
    }

    void CAutoKeyboardWidget::setListWidgetItem( std::string & strFilter, QString & qsKey )
    {
        clear();

        QMap<int, QMap<QString, QPair<QString, QString> > > cacheMap;
        for (QMap<QString, QPair<QString, QString> >::iterator iter = m_itemMap.begin(); iter != m_itemMap.end(); iter++)
        {
            int nStringIndex = iter.key().indexOf(qsKey, 0, Qt::CaseInsensitive);
            if (strFilter.empty() || nStringIndex >= 0)
            {
                QString qsCode = iter.value().first;
                QString qsName = iter.value().second;
                if (m_autoToUpper)
                {
                    qsCode = qsCode.toUpper();
                }

                cacheMap[nStringIndex].insert(iter.key(), QPair<QString, QString>(qsCode, qsName));
            }
        }
        for (QMap<int, QMap<QString, QPair<QString, QString> > >::iterator iter = cacheMap.begin(); iter != cacheMap.end(); ++iter)
        {
            for(QMap<QString, QPair<QString, QString> >::iterator it = iter.value().begin(); it != iter.value().end(); ++it)
            {
                QListWidgetItem* pItem = new QListWidgetItem(it.key(), NULL);
                if (NULL != pItem)
                {
                    pItem->setData(Qt::UserRole, it.value().first);
                    addItem(pItem);
                }
            }
        }
    }

    void CAutoKeyboardWidget::setPinYinAdapter( bool bAdapter )
    {
        m_bPinYinAdapter = bAdapter;
    }

    int CDefaultDataModel::m_nIndex = 0;
    const QStringList & CDefaultDataModel::getStringList() const
    {
        return m_allData;
    }


    const QStringList & CDefaultDataModel::getRealStringList() const
    {
        return m_realData;
    }


    int CDefaultDataModel::testData(const QString & qsParam) const
    {
        auto iter = m_testData.find(qsParam);
        if (iter != m_testData.end())
        {
            return iter.value();
        }
        return -1;
    }


    void CDefaultDataModel::addData(const QString& qStrData, const QString& qStrRealData)
    {
        m_allData.push_back(qStrData);
        m_realData.push_back(qStrRealData);
        QStringList strList = qStrRealData.split("&&");
        if (strList.size() > 1)
        {
            m_testData[strList.at(0)] = m_nIndex++;
        }
    }


    void CDefaultDataModel::clearModelData()
    {
        m_allData.clear();
        m_realData.clear();
        m_testData.clear();
    }
}