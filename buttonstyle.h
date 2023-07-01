#ifndef BUTTONSTYLE_H
#define BUTTONSTYLE_H

#include <QCommonStyle>
#include <QObject>
#include <QWidget>

class ButtonStyle : public QCommonStyle
{
    Q_OBJECT

public:
    ButtonStyle();

    //QPalette standardPalette() const override;

    /*void polish(QWidget *widget) override;
    void unpolish(QWidget *widget) override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option,
                    const QWidget *widget) const override;
    int styleHint(StyleHint hint, const QStyleOption *option,
                  const QWidget *widget, QStyleHintReturn *returnData) const override;
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const override;
    void drawControl(ControlElement control, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const override;*/
};

#endif // BUTTONSTYLE_H
