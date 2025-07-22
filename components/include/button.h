/*
 *
 * https://element-plus.org/zh-CN/component/button
 *
 * */

#pragma once

#include "color.h"
#include "../../tools/include/qsshelper.h"

#include <QString>
#include <QPushButton>
#include <QApplication>

namespace QTElementUI
{

    class Button : public QPushButton
    {
    Q_OBJECT

    public:
        enum class Style
        {
            default_ = 0,
            plain,
            round,
            circle,
            link,
            text,
        };

        enum class Type
        {
            default_ = 0,
            primary,
            success,
            info,
            warning,
            danger,
        };

        enum class Size
        {
            default_ = 0,
            large,
            small,
        };

        enum class IconPosition
        {
            only = 0,
            left,
            right,
        };

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

        QPair<QString, IconPosition> getIcon();
        Button& setIcon(const QString& name, IconPosition pos = IconPosition::only);

        Button& setText(const QString& text);

    public:
        Button(QWidget* parent = nullptr);
        Button(const QString& text, QWidget* parent = nullptr);

    protected:
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;

    private:
        Style _style = Style::default_;
        Type _type = Type::default_;
        Size _size = Size::default_;

        bool _disabled = false;
        bool _loading = false;

        QString _icon;
        IconPosition _iconPostion = IconPosition::left;

        QString _color; // TODO

        QSSHelper _qsshelper;

    private:
        int _iconSize = 18;
        int _smallIconSize = 16;
    };

}
