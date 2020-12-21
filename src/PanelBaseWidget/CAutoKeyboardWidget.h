/**
 *  ���������ʾwidget�������ṩһ���ӿڣ�����һ��QStringList��������ʾ��������QStringList�Ĺ��˹�������������������������
 *
 *  @author huangxu
 *  @since  2016-03-26
 */

#ifndef TC_UICOMPONENT_SMARTKEYBOARD_ISEARCHDATAMODEL_H
#define TC_UICOMPONENT_SMARTKEYBOARD_ISEARCHDATAMODEL_H

#include <QtWidgets/QListWidget>

namespace XP
{
    //���ڴ������ݵĽӿڵĻ���
    class ISearchDataModel
    {
    public:
        virtual const QStringList & getStringList() const = 0;      // ����һ�����Ա����������б�֮�е��ַ����б�
        virtual const QStringList & getRealStringList() const = 0;  // ��ѡ��һ��ѡ��ʱ�����ص�ʵ������ʾ���ı�������ı�
        virtual int testData(const QString & qsParam) const = 0;    // ������������Ľ���Ƿ�Ϸ�
        virtual void clearModelData() {};
        virtual void addData(const QString& qStrData, const QString& qStrRealData) {}    // ������������Ľ���Ƿ�Ϸ�
    };

    class  CDefaultDataModel : public XP::ISearchDataModel
    {
    public:
        CDefaultDataModel() = default;

        virtual const QStringList & getStringList() const;
        virtual const QStringList & getRealStringList() const;
        virtual int testData(const QString & qsParam) const;

        void addData(const QString& qStrData, const QString& qStrRealData) override;
        void clearModelData() override;
    protected:
        static int              m_nIndex;
        QStringList             m_allData;
        QStringList             m_realData;
        QMap<QString, int>      m_testData;
    };

    class  CAutoKeyboardWidget : public QListWidget
    {
        Q_OBJECT

    public:
        CAutoKeyboardWidget(QWidget *parent = NULL);
        virtual ~CAutoKeyboardWidget();
        virtual void display(QPoint ptGlobal, QString qsKey);
        virtual void shift(QPoint ptShift);
        int testString(QString qsParam) const;
        bool isListDataEmpty() const;
        virtual QString getSelection() const;
        virtual QString getParam() const;
        void setDataModel(ISearchDataModel *pDataModel);    // ���ýӿڣ����������ݺ͹��˷������룬����m_qsListShow
        ISearchDataModel * getDataModel() { return m_pListData; }

        void clearCache();

        void setAutoToUpper(bool autoToUpper);
        void setPinYinAdapter(bool bAdapter);

    Q_SIGNALS:
        void sigItemDoubleClicked(QString qsText);

    protected Q_SLOTS:
        void onItemDoubleClicked(QListWidgetItem *);

    protected:
        void filter(QString qsKey);

    protected:
        ISearchDataModel                * m_pListData;  // �ӿڣ�����������жϹ��˹����������
        QMap<QString, QPair<QString, QString> > m_itemMap;
        bool m_autoToUpper;

        void initCacheMap(const QStringList & allDatas, const QStringList & realDatas);
        void setListWidgetItem(std::string & strFilter, QString & qsKey);
        bool m_bPinYinAdapter;
    };
}

#endif