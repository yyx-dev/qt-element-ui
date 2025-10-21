#include "autocomplete.h"

#include "base.h"
#include "color.h"
#include "shadow.h"


#include <QBoxLayout>
#include <QMouseEvent>

namespace Element
{

    PopListItemWidget::PopListItemWidget(const QString& text, QWidget* parent)
        : QWidget(parent)
        , _label(new QLabel(text, this))
    {
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(_label);

        QFont font = FontManager::font();
        font.setPixelSize(16);
        _label->setFont(font);

        _qsshelper.setProperty("QWidget", "color", Color::regularText());
        _qsshelper.setProperty("QWidget", "padding-left", "15px");
        _qsshelper.setProperty("QWidget:hover", "background-color", Color::lightFill());
        setStyleSheet(_qsshelper.generate());

        setFixedHeight(_itemHeight);
    }

    QLabel* PopListItemWidget::getLabel()
    {
        return _label;
    }

    void PopListItemWidget::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
            emit clicked(_label->text());
        QWidget::mousePressEvent(event);
    }

    PopList::PopList(QWidget* parent)
        : PopList(300, {}, parent)
    {}

    PopList::PopList(int width, QWidget* parent)
        : PopList(width, {}, parent)
    {}

    PopList::PopList(int width, const QStringList& data, QWidget* parent)
        : QListWidget(parent)
    {
        _qsshelper.setProperty("QListWidget", "background-color", "white");
        _qsshelper.setProperty("QListWidget", "border", "1px solid " + Color::darkBorder());
        _qsshelper.setProperty("QListWidget", "border-radius", "4px");
        _qsshelper.setProperty("QListWidget", "padding", QString::number(_padding) + "px 0px");
        setStyleSheet(_qsshelper.generate());


        setMouseTracking(true);
        setFocusPolicy(Qt::NoFocus);

        setSelectionMode(QAbstractItemView::NoSelection);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        Element::Shadow::setShadow(this, Element::Shadow::Type::Basic);

        setFixedSize(width, _padding * 2 + 2);
        addItems(data);
    }

    void PopList::addItem(const QString& text)
    {
        QListWidgetItem* item = new QListWidgetItem(this);
        PopListItemWidget* widget = new PopListItemWidget(text, this);

        item->setSizeHint(widget->size());
        setItemWidget(item, widget);

        connect(widget, &PopListItemWidget::clicked, this, [&](const QString& text) {
            hide();
            emit itemClicked(text);
        });

        updateHeight(count());
    }

    void PopList::addItems(const QStringList& texts)
    {
        for (const QString& text : texts)
            addItem(text);
    }

    void PopList::setItems(const QStringList& texts)
    {
        clear();
        addItems(texts);
    }

    void PopList::filterItems(const QString& text)
    {
        int visibleCount = 0;

        for (int i = 0; i < count(); ++i)
        {
            QListWidgetItem* item = this->item(i);
            PopListItemWidget* widget = qobject_cast<PopListItemWidget*>(itemWidget(item));

            if (!widget) return;

            bool matches =
                    text.isEmpty() ||
                    widget->getLabel()->text().startsWith(text, Qt::CaseInsensitive);
            item->setHidden(!matches);
            if (matches)
                visibleCount++;
        }

        updateHeight(visibleCount);
    }

    void PopList::updateHeight(int count)
    {
        int totalHeight = _itemHeight * count + _padding * 2 + 2;
        int newHeight = qMin(totalHeight, _maxHeight);
        setFixedHeight(newHeight);
    }

    AutoComplete::AutoComplete(QWidget* parent)
        : AutoComplete({}, parent)
    {}

    AutoComplete::AutoComplete(const QStringList& data, QWidget* parent)
        : InputLine(parent)
        , _popList(new PopList(width(), data, parent))
    {
        _popList->hide();

        connect(_popList, &PopList::itemClicked, this, [this](const QString& text) {
            setText(text);
            setFocus();
            _popList->hide();
        });

        connect(this, &AutoComplete::textChanged, this, &AutoComplete::onTextChanged);
    }

    AutoComplete& AutoComplete::setData(const QStringList& data)
    {
        _data = data;
        _popList->setItems(data);
        return *this;
    }

    AutoComplete& AutoComplete::setTriggerOnFocus(bool triggerOnFocus)
    {
        _triggerOnFocus = triggerOnFocus;
        return *this;
    }

    AutoComplete& AutoComplete::setPlacement(Placement placement)
    {
        _placement = placement;
        return *this;
    }

    AutoComplete& AutoComplete::addItem(const QString& text)
    {
        _popList->addItem(text);
        return *this;
    }

    AutoComplete& AutoComplete::addItems(const QStringList& texts)
    {
        _popList->addItems(texts);
        return *this;
    }

    void AutoComplete::focusInEvent(QFocusEvent* event)
    {
        InputLine::focusInEvent(event);
        if (_triggerOnFocus)
            showPopList();
    }

    void AutoComplete::focusOutEvent(QFocusEvent* event)
    {
        InputLine::focusOutEvent(event);
        _popList->hide();
    }

    void AutoComplete::showPopList()
    {
        if (_placement == Placement::Bottom)
            _popList->move(x(), y() + height() + 15);
        else
            _popList->move(x(), y() - _popList->height() - 15);

        _popList->raise();
        _popList->show();
    }

    void AutoComplete::onTextChanged(const QString& text)
    {
        if (!_triggerOnFocus && text.isEmpty())
        {
             _popList->hide();
             return;
        }

        _popList->filterItems(text);
    }
}
