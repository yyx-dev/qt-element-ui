#pragma once

#include <QWidget>
#include <functional>

namespace Element
{
    class Progress : public QWidget
    {
        Q_OBJECT

    public:
        enum class Type
        {
            Line,
            Circle,
            Dashboard,
        };

        enum class Status
        {
            None,
            Success,
            Exception,
            Warning,
        };

        enum class StrokeLinecap
        {
            Butt,
            Round,
            Square,
        };

    public:
        Progress& setPercentage(int percentage);
        Progress& setType(Type type);
        Progress& setStrokeWidth(int width);
        Progress& setTextInside(bool textInside);
        Progress& setStatus(Status status);
        Progress& setIndeterminate(bool indeterminate);
        Progress& setDuration(int duration);
        Progress& setColor(const std::function<QString(int)>& precent2Color);
        Progress& setShowText(bool showText);
        Progress& setStrokeLinecap(StrokeLinecap linecap);
        Progress& setFormat(const std::function<QString(int)>& format);

    public:
        Progress(QWidget* parent = nullptr);
        Progress(int percentage, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        QString getColor();
        void paintLine(QPainter& painter);
        void paintCircle(QPainter& painter);
        void paintDashboard(QPainter& painter);

    private:
        int _precentage = 0;
        Type _type = Type::Line;
        int _strokeWidth = 6;
        bool _textInside = false;
        Status _status = Status::None;
        bool _indeterminate = false;
        int _duration = 3;
        std::function<QString(int)> _color = nullptr;
        bool _showText = true;
        StrokeLinecap _strokeLinecap = StrokeLinecap::Round;
        std::function<QString(int)> _format = nullptr;
    };

}
