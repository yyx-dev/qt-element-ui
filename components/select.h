#pragma once

#include "inputline.h"
#include "base.h"

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QTimer>

namespace Element
{
    class OptionList;

    class Select : public InputLine
    {
    Q_OBJECT

    public:
        enum class Placement { Top, Bottom };

    public:
        Select& setOptions(const QStringList& options);
        Select& setPlacement(Placement placement);

        Select& addItem(const QString& text);
        Select& addItems(const QStringList& texts);

    public:
        Select(QWidget* parent = nullptr);
        Select(const QStringList& data, QWidget* parent = nullptr);

    private:
        void showPopList();

    protected:
        void focusOutEvent(QFocusEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    private:
        QStringList _options;
        Placement _placement = Placement::Bottom;

    private:
        OptionList* _popList;
    };

    class OptionListItemWidget : public QWidget
    {
    Q_OBJECT

    public:
        OptionListItemWidget(const QString& text, QWidget* parent = nullptr);
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

    class OptionList : public QListWidget
    {
    Q_OBJECT

    public:
        void addItem(const QString& text);
        void addItems(const QStringList& texts);
        void setItems(const QStringList& texts);
        void filterItems(const QString& text);

    public:
        OptionList(QWidget* parent = nullptr);
        OptionList(int width, QWidget* parent = nullptr);
        OptionList(int width, const QStringList& data, QWidget* parent = nullptr);

    signals:
        void itemClicked(const QString& text);

    private:
        void updateHeight(int count);

    private:
        QSSHelper _qsshelper;
        static constexpr int _itemHeight = 35;
        static constexpr int _maxHeight = 300;
        static constexpr int _padding = 15;
    };



}