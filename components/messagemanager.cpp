#include "messagemanager.h"

namespace Element
{
    MessageManager::MessageManager(QWidget* parent)
        : QObject(parent)
    {
        Message::_managersHash[parent] = this;
    }

    MessageManager::~MessageManager()
    {
        for (auto& list : _messagesList)
        {
            for (Message* msg : list)
            {
                msg->close();
            }
            list.clear();
        }
        _messagesList.clear();
    }

    void MessageManager::addMessage(Message* msg)
    {
        if(!msg) return;

        QWidget* pw = qobject_cast<QWidget*>(parent());

        if(!pw) return;

        if (msg->parentWidget() != pw)
            msg->setParent(pw);

        Message::Place place = msg->getPlacement();
        _messagesList[place].append(msg);

        msg->setGeometry(calNewMsgGeometry(msg));
    }

    void MessageManager::removeMessage(Message* msg)
    {
        if (!msg) return;

        QWidget* pw = qobject_cast<QWidget*>(parent());

        if(!pw) return;

        Message::Place place = msg->getPlacement();
        QList<Message*>& list = _messagesList[place];
        int index = list.indexOf(msg);
        if (index != -1)
        {
            list.removeAt(index);
            if (!list.isEmpty())
                adjust(place);
        }
    }

    void MessageManager::adjust(Message::Place placement)
    {
        QList<Message*>& list = _messagesList[placement];
        if (list.isEmpty()) return;

        QWidget* pw = qobject_cast<QWidget*>(parent());
        if (!pw) return;

        bool topAligned = (placement == Message::Place::Top ||
                           placement == Message::Place::TopLeft ||
                           placement == Message::Place::TopRight);
        int curY = topAligned ? _offset : (pw->height() - _offset);

        for (int i = 0; i < list.size(); ++i)
        {
            Message* msg = list[i];
            int w = msg->width();
            int h = msg->height();

            int x = 0, y;
            switch (placement)
            {
            case Message::Place::Top:
            case Message::Place::Bottom:
                x = (pw->width() - w) / 2;
                break;
            case Message::Place::TopLeft:
            case Message::Place::BottomLeft:
                x = 10;
                break;
            case Message::Place::TopRight:
            case Message::Place::BottomRight:
                x = pw->width() - w - 10;
                break;
            }

            if (topAligned)
            {
                y = curY;
                curY += h + 10;
            }
            else
            {
                y = curY - h;
                curY -= (h + 10);
            }

            QRect newRect(x, y, w, h);
            QRect oldRect = msg->geometry();
            if (oldRect != newRect)
            {
                msg->stopFadeIn();
                QPropertyAnimation* anim = new QPropertyAnimation(msg, "geometry");
                anim->setDuration(300);
                anim->setEasingCurve(QEasingCurve::OutCubic);
                anim->setStartValue(oldRect);
                anim->setEndValue(newRect);
                anim->start(QAbstractAnimation::DeleteWhenStopped);
            }
        }
    }

    QRect MessageManager::calNewMsgGeometry(Message* msg) const
    {
        QWidget* pw = qobject_cast<QWidget*>(parent());
        if (!pw) return QRect();

        Message::Place place = msg->_placement;
        const QList<Message*>& list = _messagesList[place];

        int index = list.size() - 1;

        QSize msgSize = msg->size();
        int x = 0;
        int y = 0;

        switch (place)
        {
        case Message::Place::Top:
        case Message::Place::Bottom:
            x = (pw->width() - msgSize.width()) / 2;
            break;
        case Message::Place::TopLeft:
        case Message::Place::BottomLeft:
            x = 10;
            break;
        case Message::Place::TopRight:
        case Message::Place::BottomRight:
            x = pw->width() - msgSize.width() - 10;
            break;
        }

        int yOffset = _offset;
        bool topAligned = (place == Message::Place::Top ||
                           place == Message::Place::TopLeft ||
                           place == Message::Place::TopRight);

        if (topAligned)
        {
            for (int i = 0; i < index; ++i)
                yOffset += list[i]->height() + 10;

            y = yOffset;
        }
        else
        {
            int totalHeight = 0;
            for (int i = 0; i <= index; ++i)
                totalHeight += list[i]->height() + 10;

            totalHeight -= 10;
            y = pw->height() - _offset - totalHeight;
        }

        return QRect(x, y, msgSize.width(), msgSize.height());
    }

    void MessageManager::stopMsgFadeIn(Message* msg)
    {
        msg->stopFadeIn();
    }

    Message::Place MessageManager::getMsgPlacement(Message* msg)
    {
        return msg->getPlacement();
    }

    MessageManager& MessageManager::setOffset(int offset)
    {
        _offset = offset;
        return *this;
    }
}