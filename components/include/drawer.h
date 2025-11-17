#pragma once

#include "button.h"

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

namespace Element
{
    class Drawer : public QWidget
    {
    Q_OBJECT

    public:
        enum class Direction
        {
            RightToLeft,
            LeftToRight,
            TopToBottom,
            BottomToTop,
        };

    public:
        Drawer& setModal(bool modal);
        Drawer& setDirection(Direction direction);
        Drawer& setShowClose(bool showClose);
        Drawer& setSize(int percent);
        Drawer& setTitle(const QString& title);
        Drawer& setWithHeader(bool withHeader);
        Drawer& setWithFooter(bool withFooter);
        Drawer& setBody(QWidget* body);

    signals:
        void confirm();

    public:
        Drawer(QWidget* topWidget);

    protected:
        void resizeEvent(QResizeEvent* event) override;
        bool eventFilter(QObject* watched, QEvent* event) override;

    private:
        void setupHeader();
        void setupBody();
        void setupFooter();

    private:
        bool _modal = false;
        Direction _direction = Direction::RightToLeft;
        bool _showClose = true;
        int _percent = 30;
        QString _title = "I am the title";
        bool _withHeader = true;
        bool _withFooter = true;

    private:
        QWidget* _header = nullptr;
        QWidget* _body = nullptr;
        QWidget* _footer = nullptr;
        QVBoxLayout* _layout = nullptr;
        QVBoxLayout* _bodyLayout = nullptr;

    private:
        QLabel* _closeIcon = nullptr;
        Button* _cancelBtn = nullptr;
        Button* _confirmBtn = nullptr;
    };

}
