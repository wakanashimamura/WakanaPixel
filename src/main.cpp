// ================================================================================================
//
// WakanaPixel - This software for creating digital art converts picture into pixel art.
// What is pixel art - https://en.wikipedia.org/wiki/Pixel_art.
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
// __          __   _                     _____ _          _
// \ \        / /  | |                   |  __ (_)        | |
//  \ \  /\  / /_ _| | ____ _ _ __   __ _| |__) |__  _____| |
//   \ \/  \/ / _` | |/ / _` | '_ \ / _` |  ___/ \ \/ / _ \ |
//    \  /\  / (_| |   < (_| | | | | (_| | |   | |>  <  __/ |
//     \/  \/ \__,_|_|\_\__,_|_| |_|\__,_|_|   |_/_/\_\___|_|
//
// ================================================================================================

#include <QApplication>
#include <cmath>

#include "wsmainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  WSMainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}