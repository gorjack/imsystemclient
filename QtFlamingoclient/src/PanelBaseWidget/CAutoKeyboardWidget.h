/**
 *  输入代码提示widget，对外提供一个接口，接收一个QStringList并进行显示，而对于QStringList的过滤工作，交给具体的数据类来完成
 *
 *  @author huangxu
 *  @since  2016-03-26
 */

#ifndef TC_UICOMPONENT_SMARTKEYBOARD_ISEARCHDATAMODEL_H
#define TC_UICOMPONENT_SMARTKEYBOARD_ISEARCHDATAMODEL_H

#include <QtWidgets/QListWidget>

namespace XP
{
    //用于传入数据的接口的基类
    class ISearchDataModel
    {
    public:
        virtual const QStringList & getStringList() const = 0;      // 返回一个可以被填入下拉列表之中的字符串列表
        virtual const QStringList & getRealStringList() const = 0;  // 当选中一个选项时，返回的实际上显示在文本框里的文本
        virtual int testData(const QString & qsParam) const = 0;    // 测试最终输入的结果是否合法
        virtual void clearModelData() {};
        virtual void addData(const QString& qStrData, const QString& qStrRealData) {}    // 测试最终输入的结果是否合法
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
        void setDataModel(ISearchDataModel *pDataModel);    // 设置接口，将数据内容和过滤方法传入，更新m_qsListShow
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
        ISearchDataModel                * m_pListData;  // 接口，数据载入和判断过滤工作的完成者
        QMap<QString, QPair<QString, QString> > m_itemMap;
        bool m_autoToUpper;

        void initCacheMap(const QStringList & allDatas, const QStringList & realDatas);
        void setListWidgetItem(std::string & strFilter, QString & qsKey);
        bool m_bPinYinAdapter;
    };
}

#endif