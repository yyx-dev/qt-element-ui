#pragma once

#include "base.h"
#include "text.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QSvgWidget>

namespace Element
{

    class Rate : public QWidget
    {
    Q_OBJECT

    public:
        enum class Size { Large, Default, Small };

    public:
        Rate& setScore(qreal score);
        qreal getScore();

        // It must be a multiple of 5.​
        Rate& setMax(int max);
        int getMax();

        Rate& setSize(Size size);
        Size getSize();

        Rate& setAllowHalf(bool allowHalf);
        bool getAllowHalf();

        Rate& setLowThreshold(int lowThreshold);
        int getLowThreshold();

        Rate& setHighThreshold(int highThreshold);
        int setHighThreshold();

        Rate& setShowText(bool showText);
        bool getShowText();

        Rate& setShowScore(bool showScore);
        bool getShowScore();

        Rate& setClearable(bool clearable);
        bool getClearable();

        Rate& setDisabled(bool disabled);
        bool isDisabled();

        Rate& setColors(const QString& lowColor = "#F7BA2A",
                        const QString& midColor = "#F7BA2A",
                        const QString& highColor = "#F7BA2A");
        Rate& setTexts(const QString& first, const QString& second, const QString& third,
                       const QString& fourth, const QString& fifth);

    public:
        Rate(QWidget* parent = nullptr);
        Rate(float value, QWidget* parent = nullptr);

    protected:
        bool eventFilter(QObject* obj, QEvent* event) override;

    private:
        void update(int value);

        QString getColor(int value);
        void setValue(int value);

        QByteArray partialStar(int percent,
                               const QString& fillColor, const QString& borderColor);

    private:
        Size _size = Size::Default;

        int _value = 0 * 10;
        int _max = 5 * 10;
        int _lowThreshold = 2 * 10;
        int _highThreshold = 4 * 10;

        bool _allowHalf = false;
        bool _showText = false;
        bool _showScore = false;
        bool _clearable = false;

    private:
        QString _lowColor = "#F7BA2A";
        QString _midColor = "#F7BA2A";
        QString _highColor = "#F7BA2A";
        QStringList _texts;

    private:
        QHBoxLayout* _layout = nullptr;
        QList<QSvgWidget*> _stars;
        Text* _text = nullptr;

    private:
        QSSHelper _qsshelper;
    };

}

// 区分value和成绩，一颗星的value是0到10，5颗星的value是0到50，这是固定不变的。
// 成绩 = 一共的占几颗星(value/10) * 单星的成绩(_max/50)，value/10 可以是小数，也就是可以占1.5个星。

// TODO: 无法显示半颗或部分星
