#pragma once

#include <QLabel>

namespace Element
{

    class Image : public QWidget
    {
        Q_OBJECT
    public:
        enum class Fit
        {
            Fill,
            Contain,
            Cover,
            None,
            ScaleDown,
        };

    public:
        Image& setFit(Fit fit);
        Image& setImage(const QImage& image);
        Image& setPixmap(const QPixmap& pixmap);

    public:
        Image(QWidget* parent = nullptr);
        Image(const QPixmap& pixmap, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
        void resizeEvent(QResizeEvent* event) override;

    private:
        void updateGeometry();

    private:
        Fit _fit = Fit::Fill;
        QPixmap _pixmap;
        QSize _originalSize;
        QRect _imageRect;
        QRect _viewportRect;
    };

}
