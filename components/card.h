#pragma once

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

namespace Element
{

    class Card : public QWidget
    {
    Q_OBJECT

    public:
        enum class Shadow { Always, Hover, Never };

    public:
        Card& setHeader(const QString& header);
        Card& setFooter(const QString& footer);

        Card& setBody(QWidget* widget);

        Card& setShadow(Shadow shadow);

    public:
        Card(QWidget* parent = nullptr);
        Card(const QString& header, QWidget* widget, QWidget* parent = nullptr);
        Card(const QString& header, QWidget* widget, const QString& footer, QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent* event) override;
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif
        void leaveEvent(QEvent* event) override;

    private:
        void setupUI();
        void cleanLayout(QWidget* widget);

    private:
        Shadow _shadow = Shadow::Hover;

    private:
        QLabel* _header = nullptr;
        QLabel* _footer = nullptr;
        QWidget* _body = nullptr;

        QVBoxLayout* _mainLayout = nullptr;
    };

}
