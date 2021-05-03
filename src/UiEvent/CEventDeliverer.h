#ifndef XP_UIBASE_UIEVENT_CEVENTDELIVERER_H
#define XP_UIBASE_UIEVENT_CEVENTDELIVERER_H
#include <QString>
#include <QtWidgets/QtWidgets>

namespace PC
{
    /**
     *  简单的消息传递类，不带UI
     */
    class DLL_EXPORT_UIEVENT CEventDeliverer
    {
    public:
        CEventDeliverer(CEventDeliverer *parent = NULL);
        virtual ~CEventDeliverer();

    protected:

        void deliverEvent(
            int nEventID,
            int nSenderID = 0,
            int nIntParam = 0,
            QString qsParam = "",
            void *pParam = NULL
            );
        void nrDeliverEvent(
            int nEventID,
            int nSenderID = 0,
            int nIntParam = 0,
            QString qsParam = "",
            void *pParam = NULL
            );

        virtual bool handleEvent(
            int nEventID,
            int nSenderID = 0,
            int nIntParam = 0,
            QString qsParam = "",
            void *pParam = NULL
            );


        CEventDeliverer        *m_pParentDeliverer;
    };

    DLL_EXPORT_UIEVENT CEventDeliverer *castEventDeliverer(QWidget *pWidget);
}

#endif
