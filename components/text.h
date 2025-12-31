#pragma once

#include "private/utils.h"
#include "color.h"

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

    public:
        Text& setColor(const QString& color);
        Text& setFontSize(int size);

    signals:
        void clicked();
        void rightClicked();
        void hovered(bool isHovered);

    protected:
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent *event) override;

    private:
        Type _type = Type::Default;
        Size _size = Size::Default;
        Tag _tag = Tag::Default;
        bool _truncated = false;

    private:
        void setFontColor(int color);
        void setSubscript();
        void setSupscript();
    };

    inline Text* h1(const QString& text, QWidget* parent)
    {
        Text* h1 = new Text(text, parent);
        h1->setFontSize(25);
        return h1;
    }

    inline Text* h2(const QString& text, QWidget* parent)
    {
        Text* h2 = new Text(text, parent);
        h2->setColor(Color::primaryText());
        h2->setFontSize(20);
        return h2;
    }

    inline Text* h3(const QString& text, QWidget* parent)
    {
        Text* h3 = new Text(text, parent);
        h3->setColor(Color::primaryText());
        h3->setFontSize(16);
        return h3;
    }

    inline Text* p(const QString& text, QWidget* parent)
    {
        Text* p = new Text(text, parent);
        p->setColor(Color::primaryText());
        p->setFontSize(11);
        return p;
    }

}
