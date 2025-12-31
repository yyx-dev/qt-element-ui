#pragma once

#include "private/utils.h"
#include "color.h"
#include "icon.h"

#include <QWidget>
#include <QVariant>

namespace Element
{

    class Switch : public QWidget
    {
    Q_OBJECT
    public:
        enum class Size { Large, Default, Small };

    public:
        Switch& setSize(Size size);

        Switch& setActiveColor(const QString& color);
        Switch& setInactiveColor(const QString& color);

        Switch& setDisabled(bool disabled);
        bool isDisabled();

        Switch& setLoading(bool loading);
        bool isLoading();

        Switch& setActive(bool active);
        bool isActive();

        Switch& setActiveText(const QString& text);
        Switch& setInactiveText(const QString& text);

        Switch& setActiveIcon(Icon::Name icon);
        Switch& setInactiveIcon(Icon::Name icon);

        Switch& setActiveAction(Icon::Name icon);
        Switch& setActiveAction(char ch);

        Switch& setInactiveAction(Icon::Name icon);
        Switch& setInactiveAction(char ch);

        Switch& setActiveValue(const QVariant& value);
        QVariant getActiveValue();

        Switch& setInactiveValue(const QVariant& value);
        QVariant getInactiveValue();

    signals:
        void stateChanged(bool active);

    public:
        Switch(QWidget* parent = nullptr);
        Switch(bool active, QWidget* parent = nullptr);
        Switch(const QString& activeText, const QString& inactiveText, QWidget* parent = nullptr);
        Switch(bool active, const QString& activeText, const QString& inactiveText, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent *event) override;

    private:
        Size _size = Size::Default;

        bool _active = false;
        bool _loading = false;

        QString _activeColor = Color::primary();
        QString _inactiveColor = Color::baseBorder();

        QString _activeText;
        QString _inactiveText;

        Icon::Name _activeIcon = Icon::None;
        Icon::Name _inactiveIcon = Icon::None;

        Icon::Name _activeActionIcon = Icon::None;
        Icon::Name _inactiveActionIcon = Icon::None;

        char _activeActionChar = 0;
        char _inactiveActionChar = 0;

        QVariant _activeValue;
        QVariant _inactiveValue;
    };

}
