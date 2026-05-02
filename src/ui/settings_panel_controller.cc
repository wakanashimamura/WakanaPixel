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

#include "ui/settings_panel_controller.h"

SettingsPanelController::SettingsPanelController(QWidget* parent)
    : QWidget(parent) {
  m_layout = new QVBoxLayout(this);
  m_layout->setSpacing(0);
  m_layout->setContentsMargins(0, 0, 0, 0);
}

void SettingsPanelController::addWidget(QWidget* widget) {
  if (widget) {
    m_settingsWidget.push_back(widget);
  }
}

int SettingsPanelController::currentIndex() const {
  if (m_settingsWidget.empty()) {
    return -1;
  }

  return m_currentIndex;
}

void SettingsPanelController::setWidget(int index) {
  m_layout->addWidget(m_settingsWidget[index]);
  m_settingsWidget[index]->show();
}

void SettingsPanelController::removeWidget(int index) {
  m_layout->removeWidget(m_settingsWidget[index]);
  m_settingsWidget[index]->hide();
}

void SettingsPanelController::setCurrentIndex(int index) {
  if (!m_settingsWidget.empty() && index < m_settingsWidget.size()) {
    removeWidget(m_currentIndex);
    setWidget(index);

    m_currentIndex = index;
  }
}
