#include "core/pixelart.h"

#include "core/scale.h"

#include <QSize>

QImage pixelart(const QImage& image) {
  QImage processed = image;
  QSize size;

  if (image.width() > size.width() || image.height() > size.height()) {
    double scaleW      = static_cast<double>(320) / image.width();
    double scaleH      = static_cast<double>(256) / image.height();
    double coefficient = std::min(scaleW, scaleH);

    size.setWidth(image.width() * coefficient);
    size.setHeight(image.height() * coefficient);
  } else {
    size = image.size();
  }

  processed = downscale(image, size, RoundMode::kCeil);

  processed = upscale(processed, 8);

  return processed;
}
