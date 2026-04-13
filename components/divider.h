#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QPaintEvent>

#include "text.h"

namespace Element
{
    class Divider : public QWidget
    {
    Q_OBJECT
    public:
        enum class Direction
        {
            Horizontal,
            Vertical
        };

        enum class LineStyle
        {
            Solid,
            Dashed,
            Dotted,
            DashDotLine,
            DashDotDotLine
        };

    public:
        virtual Direction getDirection() const = 0;
        static QString getLineStyleString(LineStyle style);

    protected:
        explicit Divider(QWidget* parent = nullptr) : QWidget(parent) {}
    };

    class HLine;

    class HDivider : public Divider
    {
    Q_OBJECT
    public:
        enum class ContentPosition
        {
            Empty,
            Center,
            Left,
            Right,
        };

    public:
        HDivider(QWidget* parent = nullptr);
        HDivider(const QString& text, ContentPosition conPos = ContentPosition::Center, QWidget* parent = nullptr);
        HDivider(const QPixmap& pm, ContentPosition conPos = ContentPosition::Center, QWidget* parent = nullptr);
        HDivider(QWidget* content, ContentPosition conPos, QWidget* parent = nullptr);

    public:
        Direction getDirection() const override;
        ContentPosition getContentPosition();

    public:
        HDivider& setText(const QString text);
        HDivider& setContent(QWidget* content);
        HDivider& setContentPosition(HDivider::ContentPosition conPos);
        HDivider& setPixmap(const QPixmap& pm);
        HDivider& setLineColor(const QString& color);
        HDivider& setLineStyle(Divider::LineStyle ls);
        HDivider& setSpacing(int spacing);

    private:
        void init();
        void adjust(ContentPosition conPos);

    private:
        ContentPosition _conPos = ContentPosition::Empty;

    protected:
        QWidget* _content = nullptr;
        HLine* _leftLine;
        HLine* _rightLine;

    };

    class VDivider : public Divider
    {
        Q_OBJECT
    public:
        explicit VDivider(QWidget* parent = nullptr);
        Direction getDirection() const override;

    public:
        VDivider& setLineColor(const QString& color);
        VDivider& setLineStyle(Divider::LineStyle ls);

    protected:
        void paintEvent(QPaintEvent* event) override;
    };
}
