/*
 *
 * https://element-plus.org/zh-CN/component/text
 *
 * */
#pragma once

#include <QString>
#include <QLabel>

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
        void setFontColor(const QString& color);
        void setFontColor(int color);
        void setFontSize(int size);
        void setSubscript();
        void setSupscript();
    };

}
