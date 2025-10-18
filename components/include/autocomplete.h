#pragma once

#include "inputline.h"
#include "base.h"

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QTimer>

namespace Element
{
    class PopListItemWidget : public QWidget
    {
    Q_OBJECT

    public:
        PopListItemWidget(const QString& text, QWidget* parent = nullptr);
        QLabel* getLabel();

    signals:
        void clicked(const QString& text);

    protected:
        void mousePressEvent(QMouseEvent* event) override;

    private:
        QLabel* _label;
        QSSHelper _qsshelper;
        static const int _itemHeight = 35;
    };

    class PopList : public QListWidget
    {
    Q_OBJECT

    public:
        void addItem(const QString& text);
        void addItems(const QStringList& texts);
        void setItems(const QStringList& texts);
        void filterItems(const QString& text);

    public:
        PopList(QWidget* parent = nullptr);
        PopList(int width, QWidget* parent = nullptr);
        PopList(int width, const QStringList& data, QWidget* parent = nullptr);

    signals:
        void itemClicked(const QString& text);

    private:
        void updateHeight(int count);

    private:
        QSSHelper _qsshelper;
        static const int _itemHeight = 35;
        static const int _maxHeight = 300;
        static const int _padding = 15;
    };

    class AutoComplete : public InputLine
    {
    Q_OBJECT

    public:
        enum class Placement { Top, Bottom };

    public:
        AutoComplete& setData(const QStringList& data);
        AutoComplete& setTriggerOnFocus(bool triggerOnFocus);
        AutoComplete& setPlacement(Placement placement);

        AutoComplete& addItem(const QString& text);
        AutoComplete& addItems(const QStringList& texts);

        // TODO: 防抖

    public:
        AutoComplete(QWidget* parent = nullptr);
        AutoComplete(const QStringList& data, QWidget* parent = nullptr);

    private:
        void showPopList();
        void onTextChanged(const QString& text);

    protected:
        void focusInEvent(QFocusEvent* event) override;
        void focusOutEvent(QFocusEvent* event) override;

    private:
        PopList* _popList;

    private:
        QStringList _data;
        bool _triggerOnFocus = true;
        Placement _placement = Placement::Bottom;
    };

}
