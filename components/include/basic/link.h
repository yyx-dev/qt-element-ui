#pragma once

#include "qsshelper.h"

#include <QLabel>

namespace QTElementUI
{

    class Link : public QLabel
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

        enum class Underline
        {
            default_ = 0,
            always,
            hover,
            never,
        };

    public:
        Type getType();
        Link& setType(Type type);

        Underline getUnderline();
        Link& setUnderline(Underline underline);

        bool getDisabled();
        Link& setDisabled(bool disabled);

        Link& setText(const QString& text);

    public:
        Link(QWidget* parent = nullptr);
        Link(const QString& text, QWidget* parent = nullptr);

    protected:
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;

    private:
        Type _type;
        Underline _underline;

     private:
        QSSHelper _qsshelper;
    };

}
