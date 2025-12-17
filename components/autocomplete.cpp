#include "autocomplete.h"

#include "base.h"
#include "color.h"
#include "shadow.h"
#include "scrollbar.h"

#include <QBoxLayout>
#include <QMouseEvent>

namespace Element
{
    CompletionListItemWidget::CompletionListItemWidget(const QString& text, QWidget* parent)
        : QWidget(parent)
        , _label(new QLabel(text, this))
    {
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(_label);

        _label->setFont(FontHelper().setPixelSize(16).getFont());

        _qsshelper.setProperty("QWidget", "color", Color::regularText());
        _qsshelper.setProperty("QWidget", "padding-left", "15px");
        _qsshelper.setProperty("QWidget:hover", "background-color", Color::lightFill());
        setStyleSheet(_qsshelper.generate());

        setFixedHeight(_itemHeight);
    }

    QLabel* CompletionListItemWidget::getLabel()
    {
        return _label;
    }

    void CompletionListItemWidget::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
            emit clicked(_label->text());
        QWidget::mousePressEvent(event);
    }

    CompletionList::CompletionList(Placement placement, Autocomplete* input, QWidget* parent)
        : CompletionList(300, placement, {}, input, parent)
    {}

    CompletionList::CompletionList(int width, Placement placement, Autocomplete* input, QWidget* parent)
        : CompletionList(width, placement, {}, input, parent)
    {}

    CompletionList::CompletionList(int width, Placement placement, const QStringList& data, Autocomplete* input, QWidget* parent)
        : QListWidget(parent)
        , _placement(placement)
        , _input(input)
    {
        _qsshelper.setProperty("QListWidget", "background-color", "white");
        _qsshelper.setProperty("QListWidget", "border", "1px solid " + Color::darkBorder());
        _qsshelper.setProperty("QListWidget", "border-radius", "4px");
        _qsshelper.setProperty("QListWidget", "padding", QString::number(_padding) + "px 0px");
        setStyleSheet(_qsshelper.generate());

        setMouseTracking(true);
        setFocusPolicy(Qt::NoFocus);
        setVerticalScrollBar(new ScrollBar(Qt::Vertical, this));

        setSelectionMode(QAbstractItemView::NoSelection);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        ShadowEf::setShadow(this, ShadowEf::Type::Basic);

        setFixedSize(width, _padding * 2 + 2);
        addItems(data);
    }

    void CompletionList::addItem(const QString& text)
    {
        QListWidgetItem* item = new QListWidgetItem(this);
        CompletionListItemWidget* widget = new CompletionListItemWidget(text, this);

        item->setSizeHint(widget->size());
        setItemWidget(item, widget);

        connect(widget, &CompletionListItemWidget::clicked, this, [&](const QString& text) {
            hide();
            emit itemClicked(text);
        });

        updateHeight(count());
    }

    void CompletionList::addItems(const QStringList& texts)
    {
        for (const QString& text : texts)
            addItem(text);
    }

    void CompletionList::setItems(const QStringList& texts)
    {
        clear();
        addItems(texts);
    }

    void CompletionList::filterItems(const QString& text)
    {
        int visibleCount = 0;

        for (int i = 0; i < count(); ++i)
        {
            QListWidgetItem* item = this->item(i);
            CompletionListItemWidget* widget = qobject_cast<CompletionListItemWidget*>(itemWidget(item));

            if (!widget) return;

            bool matches = text.isEmpty() ||
                    widget->getLabel()->text().startsWith(text, Qt::CaseInsensitive);
            item->setHidden(!matches);
            if (matches)
                visibleCount++;
        }

        updateHeight(visibleCount);
    }

    void CompletionList::show()
    {
        QWidget::raise();
        QWidget::show();
    }

    void CompletionList::showEvent(QShowEvent* event)
    {
        static const int interval = _padding;

        if (_placement == Placement::Bottom)
            move(_input->x(), _input->y() + _input->height() + interval);
        else
            move(_input->x(), _input->y() - height() - interval);

        QWidget::showEvent(event);
    }

    void CompletionList::updateHeight(int count)
    {
        int totalHeight = _itemHeight * count + _padding * 2 + 2;
        int newHeight = qMin(totalHeight, _maxHeight);
        setFixedHeight(newHeight);
    }


    Autocomplete::Autocomplete(QWidget* parent)
        : Autocomplete({}, parent)
    {}

    Autocomplete::Autocomplete(const QStringList& data, QWidget* parent)
        : InputLine(parent)
        , _popList(new CompletionList(width(),
            (CompletionList::Placement)_placement, data, this, parent))
    {
        _popList->hide();

        connect(_popList, &CompletionList::itemClicked, this, [this](const QString& text) {
            setText(text);
            setFocus();
            _popList->hide();
        });

        connect(this, &Autocomplete::textChanged, this, &Autocomplete::onTextChanged);
    }

    Autocomplete& Autocomplete::setCompletions(const QStringList& completions)
    {
        _completions = completions;
        _popList->setItems(completions);
        return *this;
    }

    Autocomplete& Autocomplete::setTriggerOnFocus(bool triggerOnFocus)
    {
        _triggerOnFocus = triggerOnFocus;
        return *this;
    }

    Autocomplete& Autocomplete::setPlacement(Placement placement)
    {
        _placement = placement;
        return *this;
    }

    Autocomplete& Autocomplete::addItem(const QString& text)
    {
        _popList->addItem(text);
        return *this;
    }

    Autocomplete& Autocomplete::addItems(const QStringList& texts)
    {
        _popList->addItems(texts);
        return *this;
    }

    void Autocomplete::focusOutEvent(QFocusEvent* event)
    {
        InputLine::focusOutEvent(event);
        _popList->hide();
    }

    void Autocomplete::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (_triggerOnFocus)
            {
                if (!_popList->isVisible())
                    _popList->show();
            }
        }
        InputLine::mousePressEvent(event);
    }

    void Autocomplete::onTextChanged(const QString& text)
    {
        if (!_triggerOnFocus && text.isEmpty())
        {
             _popList->hide();
             return;
        }

        _popList->filterItems(text);
    }
}
