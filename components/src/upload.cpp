#include "upload.h"

#include "icon.h"
#include "color.h"
#include "base.h"

#include <QFileInfo>
#include <QMimeData>

#include <QBoxLayout>
#include <QPainter>
#include <QFileDialog>

namespace Element
{
    FileDrop::FileDrop(QWidget* parent)
        : QWidget(parent)
        , _icon(new QLabel(this))
        , _dropTip(new QLabel(this))
    {
        setMinimumSize(400, 200);
        setMouseTracking(true);
        setAcceptDrops(true);
        setStyleSheet("background-color: white;");

        _icon->setAlignment(Qt::AlignCenter);
        _icon->setFixedSize(80, 80);
        _icon->setPixmap(Icon::instance()
                         .getPixmap(Icon::UploadFilled, Color::placeholderText(), 80));

        _dropTip->setText("<span style='color:#606266;'>Drop file here or</span> "
                          "<span style='color:#409EFF;'>click to upload</span>");
        _dropTip->setAlignment(Qt::AlignCenter);

        QFont font = _dropTip->font();
        font.setFamilies(Comm::fontFmailies);
        font.setPointSize(Comm::defaultFontSize);
        _dropTip->setFont(font);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(40, 10, 40, 10);
        layout->setSpacing(0);

        layout->addWidget(_icon, 0, Qt::AlignHCenter);
        layout->addSpacing(15);
        layout->addWidget(_dropTip, 0, Qt::AlignHCenter);

        setMultiple(_multiple);
    }

    FileDrop& FileDrop::setMultiple(bool multiple)
    {
        _multiple = multiple;
        return *this;
    }

    void FileDrop::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角背景
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(1, 1, -1, -1), 8, 8, Qt::AbsoluteSize);
        painter.setClipPath(path);

        // 填充背景
        painter.fillPath(path, Qt::white);

        QPen pen;
        pen.setStyle(Qt::DashLine);

        // 绘制边框
        if (_isDrag)
        {
            pen.setWidth(2);
            pen.setColor(QColor(Color::primary()));
        }
        else if (_isHover)
        {
            pen.setWidth(1);
            pen.setColor(QColor(Color::primary()));
        }
        else
        {
            pen.setWidth(1);
            pen.setColor(QColor(Color::baseBorder()));
        }

        painter.setPen(pen);
        painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 8, 8, Qt::AbsoluteSize);

        QWidget::paintEvent(event);
    }


    void FileDrop::dragEnterEvent(QDragEnterEvent* event)
    {
        if (event->mimeData()->hasUrls())
        {
            _isDrag = true;
            event->acceptProposedAction();
        }
        else {
            event->ignore();
        }
        update();
    }

    void FileDrop::dragLeaveEvent(QDragLeaveEvent* event)
    {
        Q_UNUSED(event);
        _isDrag = false;
        update();
    }

    void FileDrop::dropEvent(QDropEvent* event)
    {
        const QMimeData *mimeData = event->mimeData();

        if (mimeData->hasUrls())
        {
            QStringList paths;
            QList<QUrl> urlList = mimeData->urls();

            foreach (const QUrl &url, urlList)
            {
                QString path = url.toLocalFile();
                if (QFileInfo(path).isFile())
                    paths << path;
            }

            if (!paths.isEmpty())
            {
                if (paths.count() != 1)
                    emit filesSelected(paths);
                else
                    emit fileSelected(paths.first());
            }
        }

        _isDrag = false;
        update();
    }

    void FileDrop::enterEvent(QEvent* event)
    {
        _isHover = true;
        update();
        QWidget::enterEvent(event);
    }

    void FileDrop::leaveEvent(QEvent* event)
    {
        _isHover = false;
        _isDrag = false;
        update();
        QWidget::leaveEvent(event);
    }

    void FileDrop::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            QStringList paths;

            if (_multiple)
            {
                paths = QFileDialog::getOpenFileNames(
                        this, "打开", QDir::rootPath(),
                        "All Files (*.*)"); // "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
            }
            else
            {
                QString path = QFileDialog::getOpenFileName(
                        this, "打开", QDir::rootPath(), "All Files (*.*)");
                if (!path.isEmpty())
                    paths.append(path);
            }

            if (!paths.isEmpty())
            {
                if (paths.count() != 1)
                    emit filesSelected(paths);
                else
                    emit fileSelected(paths.first());
            }
        }

        QWidget::mousePressEvent(event);
    }



    FileListItemWidget::FileListItemWidget(QListWidgetItem* item, const QString& path)
        : _icon(new QLabel(this))
        , _name(new QLabel(QFileInfo(path).fileName(), this))
        , _state(new QLabel(this))
        , _item(item)
        , _path(path)
    {
        _icon->setPixmap(Icon::instance().getPixmap(Icon::Document, Color::secondaryText(), 18));
        _state->setPixmap(Icon::instance().getPixmap(Icon::CircleCheck, Color::success(), 18));

        _name->setStyleSheet("QLabel { color: #606266; }");

        QFont font = _name->font();
        font.setFamilies(Comm::fontFmailies);
        font.setPointSize(Comm::defaultFontSize);
        _name->setFont(font);

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        layout->addSpacing(10);
        layout->addWidget(_icon);
        layout->addSpacing(10);
        layout->addWidget(_name);
        layout->addStretch();
        layout->addWidget(_state);
        layout->addSpacing(10);

        setMouseTracking(true);
        _state->setMouseTracking(true);
        _state->installEventFilter(this);
    }

    bool FileListItemWidget::eventFilter(QObject* obj, QEvent* event)
    {
        if (obj == _state)
        {
            if (event->type() == QEvent::Enter)
                _state->setPixmap(Icon::instance().getPixmap(Icon::Close, Color::primary(), 18));
            else if (event->type() == QEvent::Leave)
                _state->setPixmap(Icon::instance().getPixmap(Icon::Close, "#85878B", 18));
            else if (event->type() == QEvent::MouseButtonPress)
            {
                if (static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton)
                    emit removeRequested(_item, _path);

            }
        }
        return QWidget::eventFilter(obj, event);
    }

    void FileListItemWidget::enterEvent(QEvent* event)
    {
        _name->setStyleSheet("QLabel { color: #409EFF; }");
        _state->setPixmap(Icon::instance().getPixmap(Icon::Close, "#85878B", 18));
        QWidget::enterEvent(event);
    }

    void FileListItemWidget::leaveEvent(QEvent* event)
    {
        _name->setStyleSheet("QLabel { color: #606266; }");
        _state->setPixmap(Icon::instance().getPixmap(Icon::CircleCheck, Color::success(), 18));
        QWidget::leaveEvent(event);
    }



    FileList::FileList(QWidget* parent)
        : QListWidget(parent)
    {
        // setFocusPolicy(Qt::NoFocus); // already set show-decoration-selected in QSS
        setMouseTracking(true);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setFrameStyle(QFrame::NoFrame);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        setStyleSheet(R"(
            show-decoration-selected: 0;
            QListWidget { background: transparent; border: none; }
            QListWidget::item { border-radius: 4px; }
            QListWidget::item:hover { background: #F5F7FA; }
            QListWidget::item { outline: none; }
        )");
    }

    FileList& FileList::addItem(const QString& path)
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(width(), 30 + 5));
        QListWidget::addItem(item);

        FileListItemWidget* widget = new FileListItemWidget(item, path);
        setItemWidget(item, widget);

        connect(widget, &FileListItemWidget::removeRequested, this, [&](QListWidgetItem* item, const QString& path) {
            delete item;
            emit removeRequested(path);
        });

        return *this;
    }

    FileList& FileList::addItems(const QStringList& paths)
    {
        for (auto& path : paths)
            addItem(path);
        return *this;
    }


    Upload::Upload(QWidget* parent)
        : QWidget(parent)
        , _select(new Button("select file", this))
        , _upload(new Button("upload to server", this))
        , _drop(new FileDrop(this))
        , _tip(new Text(this))
        , _list(new FileList(this))
    {
        _select->setType(Button::Type::Primary);
        _upload->setType(Button::Type::Success);

        _tip->setWordWrap(true);
        _tip->setSize(Text::Size::Small);

        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(_select);
        layout->addWidget(_upload);
        layout->addStretch();

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addLayout(layout);
        mainLayout->addWidget(_drop, 1);
        mainLayout->addWidget(_tip);
        mainLayout->addWidget(_list, 1);
        mainLayout->addStretch(0);

        setMultiple(_multiple);
        setDrag(_drag);

        connect(_drop, &FileDrop::fileSelected, this, [&](const QString& path) {
            _list->addItem(path);
            _paths.append(path);
        });
        connect(_drop, &FileDrop::filesSelected, this, [&](const QStringList& paths) {
            _list->addItems(paths);
            _paths.append(paths);
        });

        connect(_upload, &QPushButton::clicked, this, [&] {
            if (!_paths.isEmpty())
                emit uploadRequested(_paths);
        });

        connect(_list, &FileList::removeRequested, this, [&](const QString& path) {
            if (!_paths.removeOne(path))
                Log::error("Upload::Upload: remove path failed");

            emit removeRequested(path);
        });

    }

    Upload& Upload::setTip(const QString& tip, Text::Type type)
    {
        _tip->setText(tip);
        _tip->setType(type);
        return *this;
    }

    Upload& Upload::setMultiple(bool multiple)
    {
        _multiple = multiple;

        if (_multiple)
        {
            _select->setText("select files");
            connect(_select, &Button::clicked, this, [&] {
                QStringList paths = QFileDialog::getOpenFileNames(
                        this, "打开", QDir::rootPath(), "All Files (*.*)");

                if (!paths.isEmpty())
                {
                    _list->addItems(paths);
                    _paths.append(paths);
                }
            });
        }
        else
        {
            _select->setText("select file");
            connect(_select, &Button::clicked, this, [&] {
                QString path = QFileDialog::getOpenFileName(
                        this, "打开", QDir::rootPath(), "All Files (*.*)");

                if (!path.isEmpty())
                {
                    _list->addItem(path);
                    _paths.append(path);
                }
            });
        }

        return *this;
    }

    Upload& Upload::setDrag(bool drag)
    {
        _select->setVisible(!drag);
        _drop->setVisible(drag);
        return *this;
    }
}
