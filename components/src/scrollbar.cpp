#include "scrollbar.h"

#include <QApplication>

namespace Element
{

    void ScrollBar::setAppScrollBar()
    {
        qApp->setStyleSheet(R"(
            QScrollBar {
                background-color: transparent;
                width: 10px;
                height: 10px;
                border: none;
            }
            QScrollBar:vertical {
                width: 10px;
            }
            QScrollBar:horizontal {
                height: 10px;
            }
            QScrollBar::handle {
                background: #DDDEE0;
                border-radius: 5px;
                opacity: 0;
            }
            QScrollBar::handle:hover {
                background: #C7C9CC;
            }
            QScrollBar::handle:pressed {
                background: #C7C9CC;
            }
            QScrollBar::add-page, QScrollBar::sub-page {
                background: none;
            }
            QScrollBar::add-line:vertical {
                height: 0px;
                subcontrol-position: bottom;
                subcontrol-origin: margin;
            }
            QScrollBar::sub-line:vertical {
                height: 0px;
                subcontrol-position: top;
                subcontrol-origin: margin;
            }
            QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {
                height: 0px;
                width: 0px;
            }
            QScrollBar::add-line:horizontal {
                width: 0px;
                subcontrol-position: right;
                subcontrol-origin: margin;
            }
            QScrollBar::sub-line:horizontal {
                width: 0px;
                subcontrol-position: left;
                subcontrol-origin: margin;
            }
            QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {
                width: 0px;
                height: 0px;
            }
        )");
    }

    void ScrollBar::setInputTextScrollBar(InputText* inputText)
    {
        Q_UNUSED(inputText);
    }

}
