#pragma once

#include <QWidget>
#include <QFont>
#include <QPointer>
#include <QPropertyAnimation>

namespace Element {

    /* Note:
     * To prevent font‑rendering errors (e.g., QWinFontEngine: unable to query transformed glyph metrics)
     * when the Tag's animation triggers a scaled text effect on Windows,
     * you must set the following environment variable before constructing your QApplication instance:
     *
     *     qputenv("QT_QPA_PLATFORM", "windows:fontengine=freetype");
     *
     * Failure to do so may result in console warnings, visual glitches, or incomplete animations.
     * This setting forces Qt to use the FreeType font engine, which correctly handles transformed text.
     */

    class Tag : public QWidget
    {
        Q_OBJECT
        Q_PROPERTY(double xScale READ xScale WRITE setXScale)
        Q_PROPERTY(double opacity READ opacity WRITE setOpacity)

    public:
        enum class Effect
        {
            Dark,
            Light,
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
            Large,
            Default,
            Small,
        };

    public:
        Tag(QWidget* parent = nullptr);
        Tag(const QString& text, QWidget* parent = nullptr);
        Tag(const QString& text, Type type, QWidget* parent = nullptr);

    public:
        Tag& setEffect(Effect effect);
        Tag& setType(Type type);
        Tag& setSize(Size size);
        Tag& setCloseable(bool closeable);
        Tag& setRound(bool round);
        Tag& setDisableTransitions(bool disabled);
        Tag& setText(const QString& text);

        void startClose();

        double xScale() const;
        void setXScale(double scalse);
        double opacity() const;
        void setOpacity(double opa);

    signals:
        void closed();

    protected:
        void paintEvent(QPaintEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void enterEvent(QEvent* event) override;
        void leaveEvent(QEvent* event) override;

    private:
        QString getColor();
        QString getBorderColor();
        QString getBackgroundColor();
        QRect closeIconRect();
        void updateCachedColors();

    private:
        bool _round = false;
        bool _closeable = false;
        bool _disTrans = false;
        bool _hover = false;
        bool _closeHover = false;
        double _xScale = 1.0;
        double _opacity = 1.0;
        Type _type = Type::Info;
        Effect _effect = Effect::Light;
        Size _size = Size::Default;

        QString _text;
        QString _textColor;
        QString _borderColor;
        QString _bgColor;
    };

}