#pragma once

#include "button.h"
#include "text.h"

#include <QWidget>
#include <QListWidget>

namespace Element
{
    class FileDrop : public QWidget
    {
    Q_OBJECT

    public:
        FileDrop& setMultiple(bool multiple);

    public:
        FileDrop(QWidget* parent = nullptr);

    signals:
        void fileSelected(const QString& filePath);
        void filesSelected(const QStringList& filePaths);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void dragEnterEvent(QDragEnterEvent* event) override;
        void dragLeaveEvent(QDragLeaveEvent* event) override;
        void dropEvent(QDropEvent* event) override;
        void enterEvent(QEvent* event) override;
        void leaveEvent(QEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

    private:
        bool _multiple = false;

    private:
        QLabel* _icon;
        QLabel* _dropTip;

        bool _isHover = false;
        bool _isDrag = false;
    };

    class FileListItemWidget : public QWidget
    {
    Q_OBJECT

    public:
        FileListItemWidget(QListWidgetItem* item, const QString& path);

    signals:
        void removeRequested(QListWidgetItem* item, const QString& path);

    protected:
        bool eventFilter(QObject* obj, QEvent* event) override;
        void enterEvent(QEvent* event) override;
        void leaveEvent(QEvent* event) override;

    private:
        QLabel* _icon;
        QLabel* _name;
        QLabel* _state;

    private:
        QListWidgetItem* _item;
        QString _path;
    };

    class FileList : public QListWidget
    {
    Q_OBJECT

    public:
        FileList& addItem(const QString& path);
        FileList& addItems(const QStringList& path);

    signals:
        void removeRequested(const QString& path);

    public:
        FileList(QWidget *parent = nullptr);
    };

    class Upload : public QWidget
    {
    Q_OBJECT

    public:
        Upload& setTip(const QString& tip, Text::Type type = Text::Type::Default);
        Upload& setMultiple(bool multiple);
        Upload& setShowFileList(bool showFileList);
        Upload& setAutoUpload(bool autoUpload);
        Upload& setDrag(bool drag);
        Upload& setLimit(int limit);

    signals:
        bool uploadRequested(const QStringList& paths);
        void removeRequested(const QString& path);

    public:
        Upload(QWidget* parent = nullptr);

    private:
        QStringList _paths;

        bool _multiple = false;
        bool _showFileList = true;
        bool _autoUpload = false;
        bool _drag = false;
        int _limit;

    private:
        Button* _select;
        Button* _upload;
        FileDrop* _drop;
        Text* _tip;
        FileList* _list;
    };
}
