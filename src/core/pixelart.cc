#include "core/pixelart.h"

#include "core/scale.h"

#include <QSize>

QImage pixelart(const QImage& image) {
  QImage processed = image;
  QSize size       = fitImageToScreen(image.size(), {320, 256});

  processed = scale(image, {size, RoundMode::Ceil});

  processed = upScale(processed, 8);

  return processed;
}
