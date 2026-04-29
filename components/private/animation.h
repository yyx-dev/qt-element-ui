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

        enum class Type {   WindowOpacity, GraphicsEffect  };

        static QParallelAnimationGroup* horShrinkFadeOut(QWidget* widget, Type type, int duration = 200,
                                          std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* fadeIn(QWidget* widget, Type type, int duration = 300,
                           std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* fadeOut(QWidget* widget, Type type, int duration = 300,
                            std::function<void()> onFinished = nullptr);

        // The default transition direction is top‑down.
        static QParallelAnimationGroup* fadeInMove(QWidget* widget, Type type,
                                  int offset = 20, int duration = 300,
                                  std::function<void()> onFinished = nullptr);

        static QParallelAnimationGroup* fadeInMove(QWidget* widget, Type type,
                                  QRect startRect, int duration = 300,
                                  std::function<void()> onFinished = nullptr);

        // The default transition direction is down-top.
        static QParallelAnimationGroup* fadeOutMove(QWidget* widget, Type type,
                                   int offset = 20, int duration = 300,
                                   std::function<void()> onFinished = nullptr);

        static QParallelAnimationGroup* fadeOutMove(QWidget* widget, Type type,
                                   QRect endRect, int duration = 300,
                                   std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* fade(QWidget* widget, OpacityRange opacity,
                         Type type, int duration,
                         std::function<void()> onFinished = nullptr);

        static QPropertyAnimation* move(QWidget* widget, const QRect& targetRect, int duration = 300,
                         std::function<void()> onFinished = nullptr);

        static QParallelAnimationGroup* fadeMove(QWidget* widget, RectRange geometry,
                             OpacityRange opacity, Type type,
                             int duration, std::function<void()> onFinished = nullptr);

    private:
        static const QEasingCurve& easingCurve();

        static QPropertyAnimation* getOpaAnim(QWidget* widget, Element::Animation::Type type, double startVal, double endVal, int duration);
    };
}