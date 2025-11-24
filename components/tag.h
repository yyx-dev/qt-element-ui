#pragma once

#include "base.h"

#include <QLabel>
#include <QBoxLayout>

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
            Large,
            Default,
            Small,
        };

    public:
        Tag& setEffect(Effect effect);
        Tag& setType(Type type);
        Tag& setSize(Size size);

        Tag& setCloseable(bool closeable);
        Tag& setRound(bool round);

        Tag& setText(const QString& text);

    public:
        Tag(QWidget* parent = nullptr);
        Tag(const QString& text, QWidget* parent = nullptr);
        Tag(const QString& text, Type type, QWidget* parent = nullptr);

    private:
        QString getColor();
        QString getBorderColor();
        QString getBackgroundColor();

        bool eventFilter(QObject* obj, QEvent* event);

    private:
        Effect _effect = Effect::Light;
        Type _type = Type::Info;
        Size _size = Size::Default;

        bool _closeable;
        bool _round;

        QLabel* _textLabel = nullptr;
        QLabel* _closeIcon = nullptr;
        QHBoxLayout* _layout = nullptr;

    private:
        QSSHelper _qsshelper;
        QSSHelper _internalQsshelper;
    };
}
