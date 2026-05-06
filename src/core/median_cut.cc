// ================================================================================================
//
// WakanaPixel - This software for creating digital art converts picture into pixel art.
//
// Copyright (C) 2026-2026 Wakana Shimamura
//
// This file is part of WakanaPixel.
//
// WakanaPixel is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// WakanaPixel is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WakanaPixel. If not, see <https://www.gnu.org/licenses/>.
//
// https://github.com/wakanashimamura/WakanaPixel
//
// ================================================================================================

#include "core/median_cut.h"

#include "core/pixel_bits.h"

#include <QWidget>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {

using PixelFrequencyMap = std::unordered_map<RGB::ValueType, std::size_t>;

struct PixelFrequency {
  RGB color{};
  std::size_t count = 0;
};

struct ColorBox {
  std::size_t begin       = 0;
  std::size_t end         = 0;
  std::size_t population  = 0;
  RGB::Channel splitColor = RGB::Channel::Red;
  int splitRange          = 0;
};

constexpr std::size_t kMinPixelsForMultithreading = 16 * 1024;

[[nodiscard]] bool isSupportedImageFormat(const QImage& image) {
  return image.format() == QImage::Format_RGB32 || image.format() == QImage::Format_ARGB32;
}

[[nodiscard]] QImage normalizeImageFormat(const QImage& image) {
  if (isSupportedImageFormat(image)) {
    return image;
  }

  return image.convertToFormat(QImage::Format_ARGB32);
}

void buildPixelFrequencyChunk(
    const QImage& image, int startRow, int endRow, PixelFrequencyMap& localMap
) {
  ReadOnlyPixelBits bits(image);

  for (int y = startRow; y < endRow; ++y) {
    for (int x = 0; x < image.width(); ++x) {
      RGB color   = bits[y][x];
      color.alpha = 255;

      ++localMap[color.argb];
    }
  }
}

[[nodiscard]] std::vector<PixelFrequency> flattenPixelFrequencies(
    const PixelFrequencyMap& frequencyMap
) {
  std::vector<PixelFrequency> pixels;
  pixels.reserve(frequencyMap.size());

  for (const auto& [color, count] : frequencyMap) {
    pixels.push_back({RGB(color), count});
  }

  return pixels;
}

[[nodiscard]] std::vector<PixelFrequency> buildPixelFrequency(const QImage& image) {
  const std::size_t pixelCount =
      static_cast<std::size_t>(image.width()) * static_cast<std::size_t>(image.height());

  if (pixelCount == 0) {
    return {};
  }

  const std::size_t hardwareThreads = std::max<std::size_t>(1, std::thread::hardware_concurrency());
  const std::size_t threadCount =
      std::min<std::size_t>(hardwareThreads, static_cast<std::size_t>(image.height()));

  if (threadCount <= 1 || pixelCount < kMinPixelsForMultithreading) {
    PixelFrequencyMap frequencyMap;
    buildPixelFrequencyChunk(image, 0, image.height(), frequencyMap);
    return flattenPixelFrequencies(frequencyMap);
  }

  std::vector<PixelFrequencyMap> localMaps(threadCount);
  std::vector<std::thread> threads;
  threads.reserve(threadCount - 1);

  for (std::size_t threadIndex = 0; threadIndex + 1 < threadCount; ++threadIndex) {
    const int startRow = static_cast<int>((image.height() * threadIndex) / threadCount);
    const int endRow   = static_cast<int>((image.height() * (threadIndex + 1)) / threadCount);

    threads.emplace_back(
        buildPixelFrequencyChunk,
        std::cref(image),
        startRow,
        endRow,
        std::ref(localMaps[threadIndex])
    );
  }

  const int lastStartRow = static_cast<int>((image.height() * (threadCount - 1)) / threadCount);
  buildPixelFrequencyChunk(image, lastStartRow, image.height(), localMaps.back());

  for (std::thread& thread : threads) {
    thread.join();
  }

  PixelFrequencyMap mergedFrequencyMap;

  for (const PixelFrequencyMap& localMap : localMaps) {
    for (const auto& [color, count] : localMap) {
      mergedFrequencyMap[color] += count;
    }
  }

  return flattenPixelFrequencies(mergedFrequencyMap);
}

void updateBoxStats(const std::vector<PixelFrequency>& pixels, ColorBox& box) {
  box.splitColor = RGB::Channel::Red;
  box.splitRange = 0;

  if (box.begin >= box.end) {
    return;
  }

  RGB::ChannelType minRed   = pixels[box.begin].color.red;
  RGB::ChannelType maxRed   = pixels[box.begin].color.red;
  RGB::ChannelType minGreen = pixels[box.begin].color.green;
  RGB::ChannelType maxGreen = pixels[box.begin].color.green;
  RGB::ChannelType minBlue  = pixels[box.begin].color.blue;
  RGB::ChannelType maxBlue  = pixels[box.begin].color.blue;

  for (std::size_t index = box.begin + 1; index < box.end; ++index) {
    const RGB color = pixels[index].color;

    minRed   = std::min(minRed, color.red);
    maxRed   = std::max(maxRed, color.red);
    minGreen = std::min(minGreen, color.green);
    maxGreen = std::max(maxGreen, color.green);
    minBlue  = std::min(minBlue, color.blue);
    maxBlue  = std::max(maxBlue, color.blue);
  }

  const int redRange   = maxRed - minRed;
  const int greenRange = maxGreen - minGreen;
  const int blueRange  = maxBlue - minBlue;

  if (redRange >= greenRange && redRange >= blueRange) {
    box.splitColor = RGB::Channel::Red;
    box.splitRange = redRange;
  } else if (greenRange >= blueRange) {
    box.splitColor = RGB::Channel::Green;
    box.splitRange = greenRange;
  } else {
    box.splitColor = RGB::Channel::Blue;
    box.splitRange = blueRange;
  }
}

[[nodiscard]] bool canSplitBox(const ColorBox& box) {
  return box.end - box.begin >= 2 && box.population > 1;
}

void sortBox(std::vector<PixelFrequency>& pixels, const ColorBox& box) {
  const RGB::Channel channel = box.splitColor;
  auto first                 = pixels.begin() + static_cast<std::ptrdiff_t>(box.begin);
  auto last                  = pixels.begin() + static_cast<std::ptrdiff_t>(box.end);

  std::sort(first, last, [channel](const PixelFrequency& lhs, const PixelFrequency& rhs) {
    return lhs.color.color(channel) < rhs.color.color(channel);
  });
}

[[nodiscard]] std::pair<ColorBox, ColorBox> splitBox(
    std::vector<PixelFrequency>& pixels, const ColorBox& box
) {
  sortBox(pixels, box);

  std::size_t bestSplit          = box.begin + 1;
  std::size_t bestLeftPopulation = pixels[box.begin].count;
  std::size_t cumulativeCount    = 0;
  std::uint64_t bestImbalance    = std::numeric_limits<std::uint64_t>::max();

  for (std::size_t index = box.begin; index + 1 < box.end; ++index) {
    cumulativeCount += pixels[index].count;

    const std::uint64_t leftPopulation  = cumulativeCount;
    const std::uint64_t rightPopulation = box.population - cumulativeCount;
    const std::uint64_t imbalance       = (leftPopulation > rightPopulation)
                                              ? (leftPopulation - rightPopulation)
                                              : (rightPopulation - leftPopulation);

    if (imbalance < bestImbalance) {
      bestImbalance      = imbalance;
      bestSplit          = index + 1;
      bestLeftPopulation = cumulativeCount;
    }
  }

  ColorBox leftBox;
  leftBox.begin      = box.begin;
  leftBox.end        = bestSplit;
  leftBox.population = bestLeftPopulation;

  ColorBox rightBox;
  rightBox.begin      = bestSplit;
  rightBox.end        = box.end;
  rightBox.population = box.population - bestLeftPopulation;

  return {leftBox, rightBox};
}

[[nodiscard]] std::size_t selectBoxToSplit(
    const std::vector<PixelFrequency>& pixels, std::vector<ColorBox>& boxes
) {
  std::size_t bestIndex      = boxes.size();
  int bestRange              = -1;
  std::size_t bestPopulation = 0;
  std::size_t bestSize       = 0;

  for (std::size_t index = 0; index < boxes.size(); ++index) {
    updateBoxStats(pixels, boxes[index]);

    if (!canSplitBox(boxes[index])) {
      continue;
    }

    const std::size_t boxSize = boxes[index].end - boxes[index].begin;

    if (boxes[index].splitRange > bestRange ||
        (boxes[index].splitRange == bestRange && boxes[index].population > bestPopulation) ||
        (boxes[index].splitRange == bestRange && boxes[index].population == bestPopulation &&
         boxSize > bestSize)) {
      bestIndex      = index;
      bestRange      = boxes[index].splitRange;
      bestPopulation = boxes[index].population;
      bestSize       = boxSize;
    }
  }

  return bestIndex;
}

[[nodiscard]] RGB averageColor(const std::vector<PixelFrequency>& pixels, const ColorBox& box) {
  std::uint64_t redSum   = 0;
  std::uint64_t greenSum = 0;
  std::uint64_t blueSum  = 0;

  for (std::size_t index = box.begin; index < box.end; ++index) {
    const PixelFrequency& pixel = pixels[index];

    redSum += static_cast<std::uint64_t>(pixel.color.red) * pixel.count;
    greenSum += static_cast<std::uint64_t>(pixel.color.green) * pixel.count;
    blueSum += static_cast<std::uint64_t>(pixel.color.blue) * pixel.count;
  }

  return RGB(
      static_cast<RGB::ChannelType>(redSum / box.population),
      static_cast<RGB::ChannelType>(greenSum / box.population),
      static_cast<RGB::ChannelType>(blueSum / box.population)
  );
}

[[nodiscard]] Palette buildPaletteFromBoxes(
    const std::vector<PixelFrequency>& pixels, const std::vector<ColorBox>& boxes
) {
  Palette palette;

  for (const ColorBox& box : boxes) {
    palette.addColor(averageColor(pixels, box));
  }

  return palette;
}

[[nodiscard]] Palette buildPaletteFromPixels(const std::vector<PixelFrequency>& pixels) {
  Palette palette;

  for (const PixelFrequency& pixel : pixels) {
    palette.addColor(pixel.color);
  }

  return palette;
}

}  // namespace

Palette MedianCut::apply(const QImage& image, int colorCount) {
  if (image.isNull() || colorCount <= 0) {
    return Palette();
  }

  const QImage source                = normalizeImageFormat(image);
  std::vector<PixelFrequency> pixels = buildPixelFrequency(source);

  if (pixels.empty()) {
    return Palette();
  }

  if (pixels.size() <= static_cast<std::size_t>(colorCount)) {
    return buildPaletteFromPixels(pixels);
  }

  std::vector<ColorBox> boxes;
  boxes.reserve(static_cast<std::size_t>(colorCount));
  boxes.push_back({0, pixels.size(), static_cast<std::size_t>(source.width()) * source.height()});

  while (boxes.size() < static_cast<std::size_t>(colorCount)) {
    const std::size_t boxIndex = selectBoxToSplit(pixels, boxes);

    if (boxIndex == boxes.size()) {
      break;
    }

    auto [leftBox, rightBox] = splitBox(pixels, boxes[boxIndex]);
    boxes[boxIndex]          = leftBox;
    boxes.push_back(rightBox);
  }

  return buildPaletteFromBoxes(pixels, boxes);
}

QGroupBox* MedianCut::createSettingsWidget(QWidget* parent) {
  Q_UNUSED(parent);
  return nullptr;
}

PaletteGenerator MedianCut::id() const {
  return PaletteGenerator::MedianCut;
}

QString MedianCut::displayName() const {
  return QString("Median Cut");
}
