#pragma once

#include "private/utils.h"

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

        bool isDisabled();
        Link& setDisabled(bool disabled);

        Link& setText(const QString& text);

    public:
        Link(QWidget* parent = nullptr);
        Link(const QString& text, QWidget* parent = nullptr);

    protected:
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent *event) override;

    private:
        Type _type;
        Underline _underline;

     private:
        QSSHelper _qsshelper;
    };

}
