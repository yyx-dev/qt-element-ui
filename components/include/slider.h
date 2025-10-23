#pragma once

#include "tooltip.h"

#include <QSlider>

namespace Element
{

    class Slider : public QSlider
    {
    Q_OBJECT

    public:
        enum class Orientation { Horizontal, Vertical };

    public:
        Slider& setMin(int min);
        Slider& setMax(int max);
        Slider& setStep(int step);
        Slider& setValue(int value);
        Slider& setDisabled(bool disabled);
        Slider& setShowStops(bool showStops);
        Slider& setShowTooltip(bool showTooltip);
        Slider& setRange(bool range);
        Slider& setPlacement(Tooltip::Placement placement);
        Slider& setMarks(const QList<QPair<int, QString>>& marks);
        Slider& setOrientation(Orientation orient);
        Slider& setSize(int size);

        Slider& setOrientation(Qt::Orientation orient);

    public:
        Slider(QWidget* parent = nullptr);
        Slider(int value, QWidget* parent = nullptr);
        Slider(Orientation orientation, QWidget* parent = nullptr);
        Slider(int value, Orientation orientation, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void enterEvent(QEvent* event) override;
        void leaveEvent(QEvent* event) override;
        void moveEvent(QMoveEvent* event) override;

    private:
        QRect getHandleRect();
        QPoint getHandleCenter();
        int posToValue(const QPoint& pos);

    private:
        Orientation _orientation = Orientation::Horizontal;
        bool _showStops = false;
        bool _showTooltip = true;
        bool _range = false;

        Tooltip* _tooltip = nullptr;

        bool _isHovered = false;
        bool _isDragging = false;

        static const int _grvsize = 200; // 轨道长度
    };

}
