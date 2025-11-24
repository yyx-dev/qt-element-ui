#pragma once

#include "base.h"
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
        Badge& setType(Type type);
        Badge& setIsDot(bool isdot);
        Badge& setValue(int value);
        Badge& setValue(const QString& value);
        Badge& setMax(int max);

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
