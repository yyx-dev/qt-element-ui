#pragma once

#include "base.h"

#include <QLabel>

namespace Element
{

    class Link : public QLabel
    {
    Q_OBJECT

    public:
        enum class Type
        {
            Default = 0,
            Primary,
            Success,
            info,
            warning,
            Danger,
        };

        enum class Underline
        {
            Default = 0,
            Always,
            Hover,
            Never,
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
