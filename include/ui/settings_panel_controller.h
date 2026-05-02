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

#ifndef SETTINGS_PANEL_CONTROLLER_H_
#define SETTINGS_PANEL_CONTROLLER_H_

#include "core/utils.h"
#include "ui/resize_mode_control.h"
#include "ui/size_control.h"

#include <QVBoxLayout>
#include <QWidget>

#include <vector>

class SettingsPanelController : public QWidget {
  Q_OBJECT
 public:
  explicit SettingsPanelController(QWidget* parent = nullptr);

  void addWidget(QWidget* widget);
  int currentIndex() const;

 public slots:
  void setCurrentIndex(int index);

 private:
  void setWidget(int index);
  void removeWidget(int index);

  std::vector<QWidget*> m_settingsWidget;
  int m_currentIndex = 0;

  QVBoxLayout* m_layout;
};

#endif  // !SETTINGS_PANEL_CONTROLLER_H_