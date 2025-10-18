#include "dialog.h"

#include <QBoxLayout>


namespace Element
{
    Dialog::Dialog(QWidget* parent)
        : Dialog("", "", parent)
    {}

    Dialog::Dialog(const QString& title, const QString& content, QWidget* parent)
        : QDialog(parent)
        , _title(new Text(title, this))
        , _content(new Text(content, this))
        , _cancel(new Button("Cancel", this))
        , _confirm(new Button("Confirm", this))
    {
        setWindowFlags(windowFlags()
                       & ~Qt::WindowContextHelpButtonHint
                       & ~Qt::WindowCloseButtonHint);
        setWindowTitle("Dialog");
        setFixedSize(500, 175);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setStyleSheet("background-color: white;");

        _title->setSize(Text::Size::Large);
        _confirm->setType(Button::Type::Primary);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(20);

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(10);
        buttonLayout->addStretch();
        buttonLayout->addWidget(_cancel);
        buttonLayout->addWidget(_confirm);

        mainLayout->addWidget(_title);
        mainLayout->addWidget(_content);
        mainLayout->addLayout(buttonLayout);

        setLayout(mainLayout);

        connect(_cancel, &QPushButton::clicked, this, &QDialog::reject);
        connect(_confirm, &QPushButton::clicked, this, &QDialog::accept);
    }

    Dialog& Dialog::setTitle(const QString &title)
    {
        _title->setText(title);
        return *this;
    }

    Dialog& Dialog::setContent(const QString &content)
    {
        _content->setText(content);
        return *this;
    }

    // Dialog::Accepted / Dialog::Rejected
    int Dialog::show()
    {
        return exec();
    }

    void Dialog::showEvent(QShowEvent *event)
    {
        QDialog::showEvent(event);

        if (parentWidget())
        {
            int parentHeight = parentWidget()->height();
            int targetY = parentWidget()->pos().y() + parentHeight * 0.18;

            move(parentWidget()->pos().x() + (parentWidget()->width() - width()) / 2,
                 targetY);
        }
    }
}
