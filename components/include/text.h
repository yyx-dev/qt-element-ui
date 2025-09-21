/*
 *
 * https://element-plus.org/zh-CN/component/text
 *
 * */
#pragma once

#include "tools/qsshelper.h"

#include <QString>
#include <QLabel>
#include <QEnterEvent>

namespace Element
{

    class Text : public QLabel
    {
    Q_OBJECT

    public:
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
            Large = 0, // 12
            Default, // 10
            Small, // 8
        };

        enum class Tag
        {
            Default = 0,
            Paragraph,
            Bold,
            Italic,
            Subscript,
            Superscript,
            Inserted,
            Deleted,
            Marked,
        };

    public:
        Text(QWidget* parent = nullptr);
        Text(const QString &text, QWidget* parent = nullptr);
        Text(const QString &text, Type type, QWidget* parent = nullptr);

        Type getType();
        Text& setType(Type type);

        Size getSize();
        Text& setSize(Size size);

        Tag getTag();
        Text& setTag(Tag tag);

        bool getTruncated();
        Text& setTruncated(bool truncated);

        void setColor(const QString& color);

    signals:
        void clicked();
        void rightClicked();
        void hovered(bool isHovered);

    protected:
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;

    private:
        Type _type = Type::Default;
        Size _size = Size::Default;
        Tag _tag = Tag::Default;
        bool _truncated = false;

    private:
        QSSHelper _qsshelper;

    private:
        void setFontColor(const QString& color);
        void setFontColor(int color);
        void setFontSize(int size);
        void setSubscript();
        void setSupscript();
    };

}
