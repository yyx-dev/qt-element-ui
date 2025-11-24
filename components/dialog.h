#pragma once

#include "text.h"
#include "button.h"

#include <QDialog>

namespace Element
{
    class Dialog : public QDialog
    {
    Q_OBJECT

    public:
        Dialog& setTitle(const QString& title);
        Dialog& setContent(const QString& content);
        int show();

    public:
        Dialog(QWidget* parent = nullptr);
        Dialog(const QString& title, const QString& content, QWidget* parent = nullptr);

    protected:
        void showEvent(QShowEvent *event) override;

    private:
        Text* _title;
        Text* _content;
        Button* _cancel;
        Button* _confirm;
    };
}
