#pragma once

#include "base.h"
#include "color.h"
#include "text.h"

#include <QString>
#include <QLabel>
#include <QHash>

namespace Element
{
    class Notification : public QWidget
    {
    Q_OBJECT

    public:
        enum class Type
        {
            Defualt,
            Primary,
            Success,
            Warning,
            Info,
            Error
        };

        enum class Position
        {
            TopRight,
            TopLeft,
            BottomRight,
            BottomLeft,
        };

    public:
        Notification& setTitle(const QString& title);
        Notification& setContent(const QString& content);

        Notification& setType(Type type);
        Notification& setShowClose(bool showClose = true, bool autoClose = true);
        Notification& setPosition(Position position);
        Notification& setDuration(int msec);

    public:
        Notification(const QString& title, const QString& message, QWidget* parent = nullptr);
        Notification(const QString& title, const QString& message, Type type = Type::Info, QWidget* parent = nullptr);

        void show();

    private:
        void updatePosition();
        void onTimeout();
        void setupUI();
        QPixmap getIcon();

    protected:
        void paintEvent(QPaintEvent *event) override;
        bool eventFilter(QObject *watched, QEvent *event) override;

    private:
        QLabel* _icon;
        QLabel* _title;
        QLabel* _close;
        QLabel* _content;

    private:
        Type _type = Type::Defualt;
        Position _positon = Position::TopRight;
        bool _showClose = true;
        int _duration = 4500;
        int _offset = 10;

    private:
        QTimer* _timer;
        QSSHelper _qsshelper;
        static QHash<Position, int> _count;
    };

    inline uint qHash(Notification::Position key, uint seed = 0) noexcept {
        return static_cast<uint>(std::hash<int>{}(static_cast<int>(key))) ^ seed;
    }

    inline QHash<Notification::Position, int> Notification::_count;
}
