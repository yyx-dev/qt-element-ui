/*
 *
 * https://element-plus.org/zh-CN/component/text
 *
 * */
#pragma once

#include <QString>
#include <QLabel>

namespace QTElementUI
{

    class Text : public QLabel
    {
    Q_OBJECT

    public:
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
            large = 0, // 12
            default_, // 10
            small, // 8
        };

        enum class Tag
        {
            default_ = 0,
            paragraph,
            bold,
            italic,
            subscript,
            superscript,
            inserted,
            deleted,
            marked,
        };

    public:
        Text(QWidget* parent = nullptr);
        Text(const QString &text, QWidget* parent = nullptr);

        Type getType();
        Text& setType(Type type);

        Size getSize();
        Text& setSize(Size size);

        Tag getTag();
        Text& setTag(Tag tag);

        bool getTruncated();
        Text& setTruncated(bool truncated);


    private:
        Type _type;
        Size _size;
        Tag _tag;

        bool _truncated;

    private:
        QString _fontFamily;
        int _fontSize;
        int _fontWeight;

        QString _fontColor;
        QString _backgroundColor;

        QString _fontStyle;

    private:
        void setFontColor(const QString& color);
        void setFontColor(int color);
        void setFontSize(int size);
        void setSubscript();
        void setSupscript();
    };

}
