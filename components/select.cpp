#include "select.h"

#include "base.h"
#include "color.h"
#include "shadow.h"


#include <QBoxLayout>
#include <QMouseEvent>

namespace Element
{

    OptionListItemWidget::OptionListItemWidget(const QString& text, QWidget* parent)
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

    QLabel* OptionListItemWidget::getLabel()
    {
        return _label;
    }

    void OptionListItemWidget::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
            emit clicked(_label->text());
        QWidget::mousePressEvent(event);
    }

    OptionList::OptionList(QWidget* parent)
        : OptionList(300, {}, parent)
    {}

    OptionList::OptionList(int width, QWidget* parent)
        : OptionList(width, {}, parent)
    {}

    OptionList::OptionList(int width, const QStringList& data, QWidget* parent)
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
        ShadowEf::setShadow(this, ShadowEf::Type::Basic);

        setFixedSize(width, _padding * 2 + 2);
        addItems(data);
    }

    void OptionList::addItem(const QString& text)
    {
        QListWidgetItem* item = new QListWidgetItem(this);
        OptionListItemWidget* widget = new OptionListItemWidget(text, this);

        item->setSizeHint(widget->size());
        setItemWidget(item, widget);

        connect(widget, &OptionListItemWidget::clicked, this, [&](const QString& text) {
            hide();
            emit itemClicked(text);
        });

        updateHeight(count());
    }

    void OptionList::addItems(const QStringList& texts)
    {
        for (const QString& text : texts)
            addItem(text);
    }

    void OptionList::setItems(const QStringList& texts)
    {
        clear();
        addItems(texts);
    }

    void OptionList::filterItems(const QString& text)
    {
        int visibleCount = 0;

        for (int i = 0; i < count(); ++i)
        {
            QListWidgetItem* item = this->item(i);
            OptionListItemWidget* widget = qobject_cast<OptionListItemWidget*>(itemWidget(item));

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

    void OptionList::updateHeight(int count)
    {
        int totalHeight = _itemHeight * count + _padding * 2 + 2;
        int newHeight = qMin(totalHeight, _maxHeight);
        setFixedHeight(newHeight);
    }

    Select::Select(QWidget* parent)
        : Select({}, parent)
    {}

    Select::Select(const QStringList& data, QWidget* parent)
        : InputLine(parent)
        , _popList(new OptionList(width(), data, parent))
    {
        setPlaceholder("Select");
        setReadOnly(true);
        setSuffixIcon(Icon::Name::ArrowDown);


        _popList->hide();

        connect(_popList, &OptionList::itemClicked, this, [this](const QString& text) {
            setText(text);
            setFocus();
            _popList->hide();
        });
    }

    Select& Select::setOptions(const QStringList& options)
    {
        _options = options;
        _popList->setItems(options);
        return *this;
    }

    Select& Select::setPlacement(Placement placement)
    {
        _placement = placement;
        return *this;
    }

    Select& Select::addItem(const QString& text)
    {
        _popList->addItem(text);
        return *this;
    }

    Select& Select::addItems(const QStringList& texts)
    {
        _popList->addItems(texts);
        return *this;
    }

    void Select::focusOutEvent(QFocusEvent* event)
    {
        InputLine::focusOutEvent(event);
        setSuffixIcon(Icon::Name::ArrowDown);
        _popList->hide();
    }

    void Select::mousePressEvent(QMouseEvent* event)
    {
        InputLine::mousePressEvent(event);
        if (event->button() == Qt::LeftButton)
        {
            if (_popList->isVisible())
            {
                setSuffixIcon(Icon::Name::ArrowDown);
                _popList->hide();
            }
            else
            {
                setSuffixIcon(Icon::Name::ArrowUp);
                showPopList();
            }
        }
    }

    void Select::showPopList()
    {
        if (_placement == Placement::Bottom)
            _popList->move(x(), y() + height() + 15);
        else
            _popList->move(x(), y() - _popList->height() - 15);

        _popList->raise();
        _popList->show();
    }

}
