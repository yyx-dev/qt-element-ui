/*
 *
 * https://element-plus.org/zh-CN/component/button
 *
 * */

#pragma once

#include "icon.h"
#include "base.h"

#include <QString>
#include <QPushButton>


namespace Element
{

    class Button : public QPushButton
    {
    Q_OBJECT

    public:
        enum class Style
        {
            Default = 0,
            Plain,
            Round,
            Circle,
            Link,
            Text,
        };

        enum class Type
        {
            Default = 0,
            Primary,
            Success,
            Info,
            Warning,
            Danger,
        };

        enum class Size
        {
            Large = 0,
            Default,
            Small,
        };

        enum class IconPosition
        {
            Only = 0,
            Left,
            Right,
        };

    private:
        using Self = Button;

    public:
        Style getStyle();
        Button& setStyle(Style style);

        Type getType();
        Button& setType(Type type);

        Size getSize();
        Button& setSize(Size size);


        bool getDisabled();
        Button& setDisabled(bool disabled);

        bool getLoading();
        Button& setLoading(bool loading);

        QPair<Icon::Name, IconPosition> getIcon();
        Button& setIcon(Icon::Name name, IconPosition pos = IconPosition::Only);

        Button& setText(const QString& text);

    public:
        Button(QWidget* parent = nullptr);
        Button(const QString& text, QWidget* parent = nullptr);

    private:
        Style _style = Style::Default;
        Type _type = Type::Default;
        Size _size = Size::Default;

        bool _loading = false;

        Icon::Name _icon;
        IconPosition _iconPostion = IconPosition::Left;

        QString _color; // TODO

        QSSHelper _qsshelper;

    private:
        int _iconSize = 18;
        int _smallIconSize = 16;


    protected:
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;
    };

}
