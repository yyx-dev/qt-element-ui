#pragma once

#include "message.h"

#include <QObject>
#include <QHash>
#include <QList>
#include <QPropertyAnimation>
#include <QApplication>
#include <QScreen>

/* The MessageManager class is responsible for managing the positional information of Message objects.
 * When using this class, a non‑null parent widget is required. */

namespace Element
{
    class MessageManager : public QObject
    {
    Q_OBJECT

    public:
        MessageManager& setOffset(int offset);
        void addMessage(Element::Message* msg);
        void removeMessage(Element::Message* msg);

    public:
        MessageManager(QWidget* parent);
        virtual ~MessageManager();

    private:
        int _offset = 20;

    private:
        QHash<Element::Message::Place, QList<Element::Message*>> _messagesList;

    protected:
        Message::Place getMsgPlacement(Message* msg);
        void stopMsgFadeIn(Message* msg);

    protected:
        virtual void adjust(Element::Message::Place placement);
        virtual QRect calNewMsgGeometry(Message* msg) const;
    };
}
