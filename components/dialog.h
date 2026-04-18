#pragma once

#include "text.h"
#include "button.h"

#include <QDialog>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

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

    public:
        Dialog(QWidget* parent = nullptr);
        Dialog(const QString& title, const QString& content, QWidget* parent = nullptr);

    protected:
        void showEvent(QShowEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        bool eventFilter(QObject* watched, QEvent* event) override;

    private:
        void doClose(int result, bool emitClosed);

    private:
        bool _modal = true;
        Text* _title;
        Text* _content;
        Button* _cancel;
        Button* _confirm;
        std::function<void(std::function<void()>)> _beforeCloseCallback;

    private:
        QLabel* _close;
        QPropertyAnimation* _opaAni;
        QPropertyAnimation* _moveAni;
        QParallelAnimationGroup* _inAni;
        QParallelAnimationGroup* _outAni;
    };
}
