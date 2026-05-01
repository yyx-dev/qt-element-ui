#include "animation.h"

#include <QGraphicsOpacityEffect>
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsRotation>
#include <QLayout>

namespace Element
{
    static QEasingCurve getEasingCurve()
    {
        QEasingCurve curve;
        curve.setType(QEasingCurve::BezierSpline);
        curve.addCubicBezierSegment(QPointF(0.55, 0.0), QPointF(0.1, 1.0), QPointF(1.0, 1.0));
        return curve;
    }

    QParallelAnimationGroup* Animation::shrinkFadeOut(QWidget* widget, Direction dir, int duration,
                                  std::function<void()> onFinished)
    {
        QPropertyAnimation* scaleAnim = getScaleAnim(widget, dir, {1.0, 0.0}, duration);
        QPropertyAnimation* opacityAnim = getOpaAnim(widget, OpacityType::GraphicsEffect, {1.0, 0.0}, duration);

        QParallelAnimationGroup* group = new QParallelAnimationGroup;
        group->addAnimation(scaleAnim);
        group->addAnimation(opacityAnim);

        if (onFinished)
        {
            QObject::connect(group, &QParallelAnimationGroup::finished, onFinished);
        }
        QObject::connect(group, &QParallelAnimationGroup::finished,
                         group, &QObject::deleteLater);
        group->start();
        return group;
    }

    QPropertyAnimation* Animation::fadeIn(QWidget* widget, OpacityType type, int duration,
                           std::function<void()> onFinished)
    {
        return fade(widget, {0.0, 1.0}, type, duration, onFinished);
    }

    QPropertyAnimation* Animation::fadeOut(QWidget* widget, OpacityType type, int duration,
                            std::function<void()> onFinished)
    {
        return fade(widget, {1.0, 0.0}, type, duration, onFinished);
    }

    QParallelAnimationGroup* Animation::fadeInMove(QWidget* widget, OpacityType type,
                                  int offset, int duration, std::function<void()> onFinished)
    {
        QRect curRect = widget->geometry();
        QRect startRect = curRect;
        startRect.moveTop(curRect.y() + offset);
        return fadeMove(widget, {startRect, widget->geometry()}, {0.0, 1.0}, type, duration, onFinished);
    }

    QParallelAnimationGroup* Animation::fadeInMove(QWidget* widget, OpacityType type,
                              QRect startRect, int duration, std::function<void()> onFinished)
    {
        return fadeMove(widget, {startRect, widget->geometry()}, {0.0, 1.0}, type, duration, onFinished);
    }

    QParallelAnimationGroup* Animation::fadeOutMove(QWidget* widget, OpacityType type,
                                   int offset, int duration, std::function<void()> onFinished)
    {
        QRect curRect = widget->geometry();
        QRect endRect = curRect;
        endRect.moveTop(curRect.y() + offset);
        return fadeMove(widget, {widget->geometry(), endRect}, {1.0, 0.0}, type, duration, onFinished);
    }

    QParallelAnimationGroup* Animation::fadeOutMove(QWidget* widget, OpacityType type,
                        QRect endRect, int duration, std::function<void()> onFinished)
    {
        return fadeMove(widget, {widget->geometry(), endRect}, {1.0, 0.0}, type, duration, onFinished);
    }

    QPropertyAnimation* Animation::fade(QWidget* widget, OpacityRange opacity,OpacityType type,
                         int duration, std::function<void()> onFinished)
    {
        QPropertyAnimation* opaAnim = getOpaAnim(widget, type, {opacity.first, opacity.second}, duration);

        if (onFinished)
        {
            QObject::connect(opaAnim, &QPropertyAnimation::finished, onFinished);
        }

        QObject::connect(opaAnim, &QPropertyAnimation::finished, opaAnim, &QObject::deleteLater);
        opaAnim->start();
        return opaAnim;
    }

    QPropertyAnimation* Animation::move(QWidget* widget, const QRect& targetRect, int duration,
              std::function<void()> onFinished)
    {
        QPropertyAnimation* anim = new QPropertyAnimation(widget, "geometry");
        anim->setDuration(duration);
        anim->setEasingCurve(easingCurve());
        anim->setStartValue(widget->geometry());
        anim->setEndValue(targetRect);

        if (onFinished)
        {
            QObject::connect(anim, &QPropertyAnimation::finished, onFinished);
        }
        QObject::connect(anim, &QPropertyAnimation::finished, anim, &QObject::deleteLater);
        anim->start();
        return anim;
    }

    QParallelAnimationGroup* Animation::fadeMove(QWidget* widget, RectRange geometry, OpacityRange opacity,
                         OpacityType type, int duration, std::function<void()> onFinished)
    {
        QParallelAnimationGroup* group = new QParallelAnimationGroup;
        QPropertyAnimation* moveAnim = new QPropertyAnimation(widget, "geometry");
        moveAnim->setDuration(duration);
        moveAnim->setEasingCurve(easingCurve());
        moveAnim->setStartValue(geometry.first);
        moveAnim->setEndValue(geometry.second);
        group->addAnimation(moveAnim);

        QPropertyAnimation* opaAnim = getOpaAnim(widget, type, {opacity.first, opacity.second}, duration);
        group->addAnimation(opaAnim);

        if (onFinished)
        {
            QObject::connect(group, &QParallelAnimationGroup::finished, onFinished);
        }
        QObject::connect(group, &QParallelAnimationGroup::finished, group, &QObject::deleteLater);
        group->start();
        return group;
    }

    const QEasingCurve& Animation::easingCurve()
    {
        static const QEasingCurve curve = getEasingCurve();
        return curve;
    }

    QPropertyAnimation* Animation::getOpaAnim(QWidget* widget, OpacityType type,
                                              OpacityRange opacity, int duration)
    {
        QPropertyAnimation* anim = nullptr;
        if (type == Element::Animation::OpacityType::WindowOpacity)
        {
            widget->setWindowOpacity(opacity.first);
            anim = new QPropertyAnimation(widget, "windowOpacity");
        }
        else
        {
            QGraphicsOpacityEffect* effect = qobject_cast<QGraphicsOpacityEffect*>(widget->graphicsEffect());
            if (!effect)
            {
                effect = new QGraphicsOpacityEffect(widget);
                widget->setGraphicsEffect(effect);
            }
            effect->setOpacity(opacity.first);
            anim = new QPropertyAnimation(effect, "opacity");
        }
        if(anim)
        {
            anim->setStartValue(opacity.first);
            anim->setEndValue(opacity.second);
            anim->setDuration(duration);
            anim->setEasingCurve(easingCurve());
        }
        return anim;
    }

    QPropertyAnimation* Animation::getScaleAnim(QWidget* widget, Direction dir, ScaleRange scale, int duration)
    {
        QPropertyAnimation* scaleAnim = nullptr;
        if(dir == Direction::Horizontal)
            scaleAnim = new QPropertyAnimation(widget, "xScale");
        else
            scaleAnim = new QPropertyAnimation(widget, "yScale");

        scaleAnim->setDuration(duration);
        scaleAnim->setStartValue(scale.first);
        scaleAnim->setEndValue(scale.second);
        scaleAnim->setEasingCurve(easingCurve());
        return scaleAnim;
    }
}