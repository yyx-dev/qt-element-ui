#pragma once

#include <QMainWindow>

namespace Element
{
    class Window : public QMainWindow
    {
        Q_OBJECT
    public:
        void setWidget(QWidget* widget);

    public:
        Window(QWidget* parent = nullptr);

    protected:
        void changeEvent(QEvent *event) override;

    private:
        void setCentralWidget(QWidget* widget);
    };

}