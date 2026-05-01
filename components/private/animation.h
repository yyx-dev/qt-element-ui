#pragma once

#include <QWidget>
#include <functional>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

namespace Element
{

    class Animation
    {
    public:
        // pair<Start_Value, End_Value>
        using RectRange = std::pair<QRect, QRect>;
        using OpacityRange = std::pair<double, double>;
        using ScaleRange = std::pair<double, double>;

        enum OpacityType {   WindowOpacity, GraphicsEffect  };

        enum Direction {    Horizontal, Vertical    };

        static QParallelAnimationGroup* shrinkFadeOut(QWidget* widget, Direction dir, int duration = 300,
                                  std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* fadeIn(QWidget* widget, OpacityType type, int duration = 300,
                           std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* fadeOut(QWidget* widget, OpacityType type, int duration = 300,
                            std::function<void()> onFinished = nullptr);

        // The default transition direction is top‑down.
        static QParallelAnimationGroup* fadeInMove(QWidget* widget, OpacityType type,
                                  int offset = 20, int duration = 300,
                                  std::function<void()> onFinished = nullptr);

        static QParallelAnimationGroup* fadeInMove(QWidget* widget, OpacityType type,
                                  QRect startRect, int duration = 300,
                                  std::function<void()> onFinished = nullptr);

        // The default transition direction is down-top.
        static QParallelAnimationGroup* fadeOutMove(QWidget* widget, OpacityType type,
                                   int offset = 20, int duration = 300,
                                   std::function<void()> onFinished = nullptr);

        static QParallelAnimationGroup* fadeOutMove(QWidget* widget, OpacityType type,
                                   QRect endRect, int duration = 300,
                                   std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* fade(QWidget* widget, OpacityRange opacity,
                         OpacityType type, int duration,
                         std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* move(QWidget* widget, const QRect& targetRect, int duration = 300,
                         std::function<void()> onFinished = nullptr);

        static QParallelAnimationGroup* fadeMove(QWidget* widget, RectRange geometry,
                             OpacityRange opacity, OpacityType type,
                             int duration, std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* getOpaAnim(QWidget* widget, OpacityType type, OpacityRange opacity, int duration);

        static QPropertyAnimation* getScaleAnim(QWidget* widget, Direction dir, ScaleRange scale, int duration);

        static const QEasingCurve& easingCurve();
    };
}