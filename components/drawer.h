#pragma once

#include "button.h"
#include "mask.h"

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

    signals:
        void opened();
        void accepted();
        void rejected();
        void closed();

    public:
        Drawer& setModal(bool modal);
        Drawer& setDirection(Direction direction);
        Drawer& setShowClose(bool showClose);
        Drawer& setSize(int percent);
        Drawer& setTitle(const QString& title);
        Drawer& setWithHeader(bool withHeader);
        Drawer& setWithFooter(bool withFooter);
        Drawer& setBody(QWidget* body);
        Drawer& setBeforeOpen(const std::function<void(std::function<void()>)>& callback);
        Drawer& setBeforeClose(const std::function<void(std::function<void()>)>& callback);

        void closeDrawer(bool expectedClose = true);

    public:
        Drawer(QWidget* topWidget);

    protected:
        bool eventFilter(QObject* watched, QEvent* event) override;
        void showEvent(QShowEvent* event) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        void setupHeader();
        void setupBody();
        void setupFooter();
        void updatePosition();
        void startOpen();
        void startClose();
        QRect getSlideInPosition();
        QRect getSlideOutPosition();

    private:
        bool _modal = true;
        Direction _direction = Direction::RightToLeft;
        bool _showClose = true;
        int _percent = 30;
        QString _title = "I am the title";
        bool _withHeader = true;
        bool _withFooter = true;
        bool _isClosing = false;
        std::function<void(std::function<void()>)> _beforeOpenCallback;
        std::function<void(std::function<void()>)> _beforeCloseCallback;

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
        Mask* _mask = nullptr;
    };

}