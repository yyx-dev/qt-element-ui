#pragma once

#include "base.h"
#include "inputline.h"

#include <QWidget>

namespace Element
{
    class InputTag : public InputLine
    {
    Q_OBJECT

    public:
        enum class Effect
        {
            Light,
            Dark,
            Plain,
        };

        enum class Type
        {
            Primary,
            Success,
            Info,
            Warning,
            Danger,
        };

        enum class Size
        {
            Large = 0,
            Default,
            Small,
        };

    public:
//        Size getSize();
//        InputTag& setSize(Size size);

//        int getMax();
//        InputTag& setMax(int max);

//        InputTag& setCollapse(int visiableCount, bool tooltipVisiable);

//        bool isDisabled();
//        InputTag& setDisabled(bool disabled);

//        Effect getEffect();
//        InputTag& setEffect(Effect effect);

//        Type getType();
//        InputTag& setType(Type type);

//        QStringList getTags();
//        InputTag& setTags(const QStringList &tags);

    public:
        InputTag(QWidget* parent = nullptr);
        //InputTag(const QStringList& tags, QWidget* parent = nullptr);

    private:
        QList<QWidget*> tagWidgets;
        QStringList tags;

    private:
        QSSHelper _qssHelper;
    };
}
