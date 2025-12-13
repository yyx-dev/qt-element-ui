#pragma once

#include "base.h"
#include "inputline.h"

#include <QLabel>
#include <QListWidget>
#include <QTimer>
#include <QWidget>


namespace Element
{
    class CompletionList;

    class Autocomplete : public InputLine
    {
        Q_OBJECT

    public:
        enum class Placement
        {
            Top,
            Bottom
        };

    public:
        Autocomplete& setCompletions(const QStringList& completions);
        Autocomplete& setTriggerOnFocus(bool triggerOnFocus);
        Autocomplete& setPlacement(Placement placement);

        Autocomplete& addItem(const QString& text);
        Autocomplete& addItems(const QStringList& texts);

        // TODO: 防抖

    public:
        Autocomplete(QWidget* parent = nullptr);
        Autocomplete(const QStringList& data, QWidget* parent = nullptr);

    private:
        void showPopList();
        void onTextChanged(const QString& text);

    protected:
        void focusOutEvent(QFocusEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    private:
        CompletionList* _popList = nullptr;

    private:
        QStringList _completions;
        bool _triggerOnFocus = true;
        Placement _placement = Placement::Bottom;
    };

    class CompletionListItemWidget : public QWidget
    {
        Q_OBJECT

    public:
        CompletionListItemWidget(const QString& text, QWidget* parent = nullptr);
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

    class CompletionList : public QListWidget
    {
        Q_OBJECT

    public:
        void addItem(const QString& text);
        void addItems(const QStringList& texts);
        void setItems(const QStringList& texts);
        void filterItems(const QString& text);

    public:
        CompletionList(QWidget* parent = nullptr);
        CompletionList(int width, QWidget* parent = nullptr);
        CompletionList(int width, const QStringList& data, QWidget* parent = nullptr);

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
