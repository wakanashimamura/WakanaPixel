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

#include "core/algorithm_factory.h"

AlgorithmFactory& AlgorithmFactory::create() {
  static AlgorithmFactory factory;
  return factory;
}

IDithering& AlgorithmFactory::dithering(const DitheringAlgorithm& id) const {
  return *m_ditheringAlgorithms[static_cast<int>(id)];
}

std::vector<DitheringAlgorithm> AlgorithmFactory::availableDitheringAlgorithms() const {
  std::vector<DitheringAlgorithm> algorithms;
  algorithms.reserve(m_ditheringAlgorithms.size());

  for (int i = 0; i < m_ditheringAlgorithms.size(); ++i) {
    algorithms.push_back(m_ditheringAlgorithms[i]->id());
  }

  return algorithms;
}

IPaletteGenerator& AlgorithmFactory::generator(const PaletteGenerator& id) const {
  return *m_generatorAlgorithms[static_cast<int>(id)];
}

std::vector<PaletteGenerator> AlgorithmFactory::availableGeneratorAlgorithms() const {
  std::vector<PaletteGenerator> algorithms;
  algorithms.reserve(m_generatorAlgorithms.size());

  for (int i = 0; i < m_generatorAlgorithms.size(); ++i) {
    algorithms.push_back(m_generatorAlgorithms[i]->id());
  }

  return algorithms;
}

AlgorithmFactory::AlgorithmFactory() {
  registerDithering(new NoDithering);
  registerDithering(new FloydSteinbergDithering);

  registerGenerator(new MedianCut);
}

void AlgorithmFactory::registerDithering(IDithering* ptr) {
  m_ditheringAlgorithms.push_back(ptr);
}

void AlgorithmFactory::registerGenerator(IPaletteGenerator* ptr) {
  m_generatorAlgorithms.push_back(ptr);
}
