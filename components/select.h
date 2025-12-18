#pragma once

#include "inputline.h"
#include "private/utils.h"

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

    protected:
        void focusOutEvent(QFocusEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseDoubleClickEvent(QMouseEvent* e) override;

    private:
        QStringList _options;
        Placement _placement = Placement::Bottom;

    private:
        OptionList* _popList = nullptr;
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
        QLabel* _label = nullptr;
        QSSHelper _qsshelper;
        static const int _itemHeight = 35;
    };

    class OptionList : public QListWidget
    {
        Q_OBJECT
    public:
        enum class Placement { Top, Bottom };

    public:
        void addItem(const QString& text);
        void addItems(const QStringList& texts);
        void setItems(const QStringList& texts);
        void filterItems(const QString& text);

    public:
        void show();

    public:
        OptionList(Placement placement,
                   Select* input = nullptr,
                   QWidget* parent = nullptr);
        OptionList(int width,
                   Placement placement,
                   Select* input = nullptr,
                   QWidget* parent = nullptr);
        OptionList(int width,
                   Placement placement,
                   const QStringList& data,
                   Select* input = nullptr,
                   QWidget* parent = nullptr);
    signals:
        void itemClicked(const QString& text);

    protected:
        void showEvent(QShowEvent* event) override;

    private:
        void updateHeight(int count);

    private:
        Placement _placement;
        Select* _input = nullptr;

        QSSHelper _qsshelper;
        static constexpr int _itemHeight = 35;
        static constexpr int _maxHeight = 300;
        static constexpr int _padding = 15;
    };



}