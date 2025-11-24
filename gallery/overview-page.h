#pragma once

#include "layout.h"

#include <QWidget>

namespace Element
{
    class OverviewPage : public QWidget
    {
        Q_OBJECT
    public:
        OverviewPage(QWidget* parent = nullptr);

    private:
        void setupWidget();

    private:
        Layout* _layout;
    };
}