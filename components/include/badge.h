#pragma once

#include "tools/qsshelper.h"
#include "color.h"

#include <QLabel>

namespace Element
{
    class Badge : public QLabel
    {
    Q_OBJECT

    public:
        enum class Type
        {
            Primary,
            Success,
            Info,
            Warning,
            Danger,
        };

    public:
        void setType(Type type);
        void setIsDot(bool isdot);
        void setValue(int value);
        void setValue(const QString& value);
        void setMax(int max);

    public:
        Badge(QWidget* parent = nullptr);
        Badge(bool isDot, QWidget* parent = nullptr);
        Badge(int value, QWidget* parent = nullptr);
        Badge(int value, int max, QWidget* parent = nullptr);
        Badge(const QString& value, QWidget* parent = nullptr);

    protected:
        void resizeEvent(QResizeEvent* event);

    private:
        QString getColor();
        void updatePosition();

    private:
        Type _type = Type::Danger;

    private:
        QWidget* _partner;

        int _numValue;
        int _max;
        QString _strValue;
        bool _isDot;

    private:
        QSSHelper _qsshelper;
    };
}
