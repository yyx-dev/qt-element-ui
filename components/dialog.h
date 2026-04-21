#pragma once

#include "text.h"
#include "button.h"
#include "mask.h"

#include <QDialog>

namespace Element
{
    class Dialog : public QDialog
    {
    Q_OBJECT

    signals:
        void accepted();
        void rejected();
        void closed();  // Click ESC, mask or close button.

    public:
        Dialog& setTitle(const QString& title);
        Dialog& setContent(const QString& content);
        Dialog& setModal(bool modal);
        Dialog& setBeforeClose(const std::function<void(std::function<void()>)>& callback);

        void show();
        void closeDialog(int result, bool emitClosed);
        void getFocus();

    public:
        Dialog(QWidget* parent = nullptr);
        Dialog(const QString& title, const QString& content, QWidget* parent = nullptr);

    protected:
        void showEvent(QShowEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        bool eventFilter(QObject* watched, QEvent* event) override;

    private:
        void doClose(int result, bool emitClosed);
        void updatePosition();

    private:
        bool _modal = true;
        bool isClosing = false;
        Mask* _mask = nullptr;
        Text* _title;
        Text* _content;
        Button* _cancel;
        Button* _confirm;
        std::function<void(std::function<void()>)> _beforeCloseCallback;
        QLabel* _close;
    };
}
