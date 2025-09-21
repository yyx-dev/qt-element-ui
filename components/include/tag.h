#pragma once

#include "tools/qsshelper.h"

#include <QLabel>

namespace Element
{
    class Tag : public QLabel
    {
    Q_OBJECT

    public:
        enum class Effect
        {
            Dark,
            Light,
            Plain,
        };

        enum class Type
        {
            Primary,
            Success,
            Info,
            Warning,
            Danger,
        };

        enum class Size
        {
            Default,
            Large,
            Small,
        };

    public:
        void setEffect(Effect effect);
        void setType(Type type);
        void setSize(Size size);

        void setCloseable(bool closeable);
        void setRound(bool round);

        void setText(const QString& text);

    public:
        Tag(QWidget* parent = nullptr);
        Tag(const QString& text, QWidget* parent = nullptr);
        Tag(const QString& text, Type type, QWidget* parent = nullptr);

    private:
        QString getColor();
        QString getBorderColor();
        QString getBackgroundColor();

    private:
        QString _text;

        Effect _effect = Effect::Light;
        Type _type = Type::Info;
        Size _size = Size::Default;

        bool _closeable;
        bool _round;

        QLabel* _icon;

    private:
        QSSHelper _qsshelper;
    };
}
