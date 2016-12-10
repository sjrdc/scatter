#pragma once

#include <qwt_color_map.h>
#include <cmath>

class SwitchableLogColorMap : public QwtLinearColorMap
{
public:
    SwitchableLogColorMap(const QColor &from, const QColor &to)
        : QwtLinearColorMap(from, to),
          useLogScale_(false)
    {
    }

    QRgb rgb(const QwtInterval &interval, double value) const
    {
        if (useLogScale_)
        {
            return QwtLinearColorMap::rgb(QwtInterval(std::log(interval.minValue()),
                                                      std::log(interval.maxValue())),
                                          std::log(value));
        } else
        {
            return QwtLinearColorMap::rgb(interval, value);
        }
    }

    void toggle()
    {
        useLogScale_ = !useLogScale_;
    }

private:
    bool useLogScale_;
};
