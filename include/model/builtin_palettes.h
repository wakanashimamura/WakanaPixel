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
// clang-format off

#ifndef BUILTIN_PALETTES_H_
#define BUILTIN_PALETTES_H_

#include "model/palette.h"

#include <vector>

inline const std::vector<Palette> createDefaultPalettes() {
  std::vector<Palette> palettes;

  palettes.emplace_back(
    "Monochrome",
    Palette::RGBColorsType {
      0xFF000000,
      0xFFFFFFFF
    }
  );

    palettes.emplace_back(
    "Grayscale 2bit",
    Palette::RGBColorsType {
      0xFF000000,
      0xFF666666,
      0xFFBBBBBB,
      0xFFFFFFFF
    }
  );
 
  palettes.emplace_back(
      "Grayscale 4bit",
      Palette::RGBColorsType {
        0xFF000000,
        0xFF111111,
        0xFF222222,
        0xFF333333,
        0xFF444444,
        0xFF555555,
        0xFF666666,
        0xFF777777,
        0xFF888888,
        0xFF999999,
        0xFFAAAAAA,
        0xFFBBBBBB,
        0xFFCCCCCC,
        0xFFDDDDDD,
        0xFFEEEEEE,
        0xFFFFFFFF
      }
  );

  Palette::RGBColorsType grayColor;
  for (int i = 0; i < 256; ++i) {
    grayColor.emplace_back(i, i, i);
  }
  palettes.emplace_back("Grayscale 8bit", grayColor);


  palettes.emplace_back(
    "Nostalgi2", 
    Palette::RGBColorsType {
      0xFF2E253D,
      0xFFB0B0B0
    }
  );

  palettes.emplace_back(
    "Windows 95", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF800000,
      0xFF008000,
      0xFF808000,
      0xFF000080,
      0xFF800080,
      0xFF008080,
      0xFFC0C0C0,
      0xFFC0DCC0,
      0xFFA6CAF0,
      0xFF2A3FAA,
      0xFF2A3FFF,
      0xFF2A5F00,
      0xFF2A5F55,
      0xFF2A5FAA,
      0xFF2A5FFF,
      0xFF2A7F00,
      0xFF2A7F55,
      0xFF2A7FAA,
      0xFF2A7FFF,
      0xFF2A9F00,
      0xFF2A9F55,
      0xFF2A9FAA,
      0xFF2A9FFF,
      0xFF2ABF00,
      0xFF2ABF55,
      0xFF2ABFAA,
      0xFF2ABFFF,
      0xFF2ADF00,
      0xFF2ADF55,
      0xFF2ADFAA,
      0xFF2ADFFF,
      0xFF2AFF00,
      0xFF2AFF55,
      0xFF2AFFAA,
      0xFF2AFFFF,
      0xFF550000,
      0xFF550055,
      0xFF5500AA,
      0xFF5500FF,
      0xFF551F00,
      0xFF551F55,
      0xFF551FAA,
      0xFF551FFF,
      0xFF553F00,
      0xFF553F55,
      0xFF553FAA,
      0xFF553FFF,
      0xFF555F00,
      0xFF555F55,
      0xFF555FAA,
      0xFF555FFF,
      0xFF557F00,
      0xFF557F55,
      0xFF557FAA,
      0xFF557FFF,
      0xFF559F00,
      0xFF559F55,
      0xFF559FAA,
      0xFF559FFF,
      0xFF55BF00,
      0xFF55BF55,
      0xFF55BFAA,
      0xFF55BFFF,
      0xFF55DF00,
      0xFF55DF55,
      0xFF55DFAA,
      0xFF55DFFF,
      0xFF55FF00,
      0xFF55FF55,
      0xFF55FFAA,
      0xFF55FFFF,
      0xFF7F0000,
      0xFF7F0055,
      0xFF7F00AA,
      0xFF7F00FF,
      0xFF7F1F00,
      0xFF7F1F55,
      0xFF7F1FAA,
      0xFF7F1FFF,
      0xFF7F3F00,
      0xFF7F3F55,
      0xFF7F3FAA,
      0xFF7F3FFF,
      0xFF7F5F00,
      0xFF7F5F55,
      0xFF7F5FAA,
      0xFF7F5FFF,
      0xFF7F7F00,
      0xFF7F7F55,
      0xFF7F7FAA,
      0xFF7F7FFF,
      0xFF7F9F00,
      0xFF7F9F55,
      0xFF7F9FAA,
      0xFF7F9FFF,
      0xFF7FBF00,
      0xFF7FBF55,
      0xFF7FBFAA,
      0xFF7FBFFF,
      0xFF7FDF00,
      0xFF7FDF55,
      0xFF7FDFAA,
      0xFF7FDFFF,
      0xFF7FFF00,
      0xFF7FFF55,
      0xFF7FFFAA,
      0xFF7FFFFF,
      0xFFAA0000,
      0xFFAA0055,
      0xFFAA00AA,
      0xFFAA00FF,
      0xFFAA1F00,
      0xFFAA1F55,
      0xFFAA1FAA,
      0xFFAA1FFF,
      0xFFAA3F00,
      0xFFAA3F55,
      0xFFAA3FAA,
      0xFFAA3FFF,
      0xFFAA5F00,
      0xFFAA5F55,
      0xFFAA5FAA,
      0xFFAA5FFF,
      0xFFAA7F00,
      0xFFAA7F55,
      0xFFAA7FAA,
      0xFFAA7FFF,
      0xFFAA9F00,
      0xFFAA9F55,
      0xFFAA9FAA,
      0xFFAA9FFF,
      0xFFAABF00,
      0xFFAABF55,
      0xFFAABFAA,
      0xFFAABFFF,
      0xFFAADF00,
      0xFFAADF55,
      0xFFAADFAA,
      0xFFAADFFF,
      0xFFAAFF00,
      0xFFAAFF55,
      0xFFAAFFAA,
      0xFFAAFFFF,
      0xFFD40000,
      0xFFD40055,
      0xFFD400AA,
      0xFFD400FF,
      0xFFD41F00,
      0xFFD41F55,
      0xFFD41FAA,
      0xFFD41FFF,
      0xFFD43F00,
      0xFFD43F55,
      0xFFD43FAA,
      0xFFD43FFF,
      0xFFD45F00,
      0xFFD45F55,
      0xFFD45FAA,
      0xFFD45FFF,
      0xFFD47F00,
      0xFFD47F55,
      0xFFD47FAA,
      0xFFD47FFF,
      0xFFD49F00,
      0xFFD49F55,
      0xFFD49FAA,
      0xFFD49FFF,
      0xFFD4BF00,
      0xFFD4BF55,
      0xFFD4BFAA,
      0xFFD4BFFF,
      0xFFD4DF00,
      0xFFD4DF55,
      0xFFD4DFAA,
      0xFFD4DFFF,
      0xFFD4FF00,
      0xFFD4FF55,
      0xFFD4FFAA,
      0xFFD4FFFF,
      0xFFFF0055,
      0xFFFF00AA,
      0xFFFF1F00,
      0xFFFF1F55,
      0xFFFF1FAA,
      0xFFFF1FFF,
      0xFFFF3F00,
      0xFFFF3F55,
      0xFFFF3FAA,
      0xFFFF3FFF,
      0xFFFF5F00,
      0xFFFF5F55,
      0xFFFF5FAA,
      0xFFFF5FFF,
      0xFFFF7F00,
      0xFFFF7F55,
      0xFFFF7FAA,
      0xFFFF7FFF,
      0xFFFF9F00,
      0xFFFF9F55,
      0xFFFF9FAA,
      0xFFFF9FFF,
      0xFFFFBF00,
      0xFFFFBF55,
      0xFFFFBFAA,
      0xFFFFBFFF,
      0xFFFFDF00,
      0xFFFFDF55,
      0xFFFFDFAA,
      0xFFFFDFFF,
      0xFFFFFF55,
      0xFFFFFFAA,
      0xFFCCCCFF,
      0xFFFFCCFF,
      0xFF33FFFF,
      0xFF66FFFF,
      0xFF99FFFF,
      0xFFCCFFFF,
      0xFF007F00,
      0xFF007F55,
      0xFF007FAA,
      0xFF007FFF,
      0xFF009F00,
      0xFF009F55,
      0xFF009FAA,
      0xFF009FFF,
      0xFF00BF00,
      0xFF00BF55,
      0xFF00BFAA,
      0xFF00BFFF,
      0xFF00DF00,
      0xFF00DF55,
      0xFF00DFAA,
      0xFF00DFFF,
      0xFF00FF55,
      0xFF00FFAA,
      0xFF2A0000,
      0xFF2A0055,
      0xFF2A00AA,
      0xFF2A00FF,
      0xFF2A1F00,
      0xFF2A1F55,
      0xFF2A1FAA,
      0xFF2A1FFF,
      0xFF2A3F00,
      0xFF2A3F55,
      0xFFFFFBF0,
      0xFFA0A0A4,
      0xFF808080,
      0xFFFF0000,
      0xFF00FF00,
      0xFFFFFF00,
      0xFF0000FF,
      0xFFFF00FF,
      0xFF00FFFF,
      0xFFFFFFFF
    }
  );

  palettes.emplace_back(
    "windows 16-color", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF800000,
      0xFF008000,
      0xFF808000,
      0xFF000080,
      0xFF800080,
      0xFF008080,
      0xFFC0C0C0,
      0xFF808080,
      0xFFFF0000,
      0xFF00FF00,
      0xFFFFFF00,
      0xFF0000FF,
      0xFFFF00FF,
      0xFF00FFFF,
      0xFFFFFFFF
    }
  );

  palettes.emplace_back(
    "windows 20-color", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF800000,
      0xFF008000,
      0xFF808000,
      0xFF000080,
      0xFF800080,
      0xFF008080,
      0xFFC0C0C0,
      0xFFC0DCC0,
      0xFFA6CAF0,
      0xFFFFFBF0,
      0xFFA0A0A4,
      0xFF808080,
      0xFFFF0000,
      0xFF00FF00,
      0xFFFFFF00,
      0xFF0000FF,
      0xFFFF00FF,
      0xFF00FFFF,
      0xFFFFFFFF
    }
  );

  palettes.emplace_back(
    "Solaris OS", 
    Palette::RGBColorsType {
      0xFF000000, 
      0xFFFF0000,
      0xFF00FF00,
      0xFFBF7F00,
      0xFF0000FF,
      0xFFFF00FF,
      0xFF00FFFF,
      0xFFCFCFCF,
      0xFF9F9F9F,
      0xFFFF7F7F,
      0xFF7FFF7F,
      0xFFFFFF00,
      0xFF7F7FFF,
      0xFFFF7FFF,
      0xFF7FFFFF,
      0xFFFFFFFF
    }
  );

  palettes.emplace_back(
    "GNOME 32", 
    Palette::RGBColorsType {
      0xFFEAE8E3,
      0xFFBAB5AB,
      0xFF807D74,
      0xFF565248,
      0xFFC5D2C8,
      0xFF83A67F,
      0xFF5D7555,
      0xFF445632,
      0xFFE0B6AF,
      0xFFC1665A,
      0xFF884631,
      0xFF663822,
      0xFFADA7C8,
      0xFF887FA3,
      0xFF625B81,
      0xFF494066,
      0xFF9DB8D2,
      0xFF7590AE,
      0xFF4B6983,
      0xFF314E6C,
      0xFFEFE0CD,
      0xFFE0C39E,
      0xFFB39169,
      0xFF826647,
      0xFFDF421E,
      0xFF990000,
      0xFFEED680,
      0xFFD1940C,
      0xFF46A046,
      0xFF267726,
      0xFFFFFFFF,
      0xFF000000
    }
  );

    palettes.emplace_back(
    "Commodore 64", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF626262,
      0xFF898989,
      0xFFADADAD,
      0xFFFFFFFF,
      0xFF9F4E44,
      0xFFCB7E75,
      0xFF6D5412,
      0xFFA1683C,
      0xFFC9D487,
      0xFF9AE29B,
      0xFF5CAB5E,
      0xFF6ABFC6,
      0xFF887ECB,
      0xFF50459B,
      0xFFA057A3
    }
  );

  palettes.emplace_back(
    "RISC OS", 
    Palette::RGBColorsType {
      0xFFFFFFFF,
      0xFFDDDDDD,
      0xFFBBBBBB,
      0xFF999999,
      0xFF777777,
      0xFF555555,
      0xFF333333,
      0xFF000000,
      0xFF004499,
      0xFFEEEE00,
      0xFF00CC00,
      0xFFDD0000,
      0xFFEEEEBB,
      0xFF558800,
      0xFFFFBB00,
      0xFF00BBFF

   }
  );

  palettes.emplace_back(
    "ZX Spectrum", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF0000D8,
      0xFF0000FF,
      0xFFD80000,
      0xFFFF0000,
      0xFF00FFFF,
      0xFFD8D800,
      0xFFFFFF00,
      0xFFD8D8D8,
      0xFFD800D8,
      0xFFFF00FF,
      0xFF00D800,
      0xFF00FF00,
      0xFF00D8D8,
      0xFFFFFFFF
    }
  );

   palettes.emplace_back(
    "ZX",
    Palette::RGBColorsType {
        0xFF000000,
        0xFF0011CB,
        0xFF0022FF,
        0xFFDD2211,
        0xFFFF3312,
        0xFFDD32CC,
        0xFF01CC22,
        0xFFFE33FF,
        0xFF00CCCB,
        0xFF00FF23,
        0xFF00FFFF,
        0xFFCDCC22,
        0xFFCCCCCC,
        0xFFFFFF33,
        0xFFFFFFFF
    }
  );

  palettes.emplace_back(
    "Apple 1", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF666666,
      0xFF979797,
      0xFFEEEEEE,
      0xFF0088CC
    }
  );

  palettes.emplace_back(
    "Apple 2 Hi Res", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFFB63DFF,
      0xFFEA5D15,
      0xFF10A4E3,
      0xFF43C300,
      0xFFFFFFFF
    }
  );

  palettes.emplace_back(
    "Apple 2", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF515C16,
      0xFF843D52,
      0xFFEA7D27,
      0xFF514888,
      0xFFE85DEF,
      0xFFF5B7C9,
      0xFF006752,
      0xFF00C82C,
      0xFF919191,
      0xFFC9D199,
      0xFF00A6F0,
      0xFF98DBC9,
      0xFFC8C1F7,
      0xFFFFFFFF
    }
  );

  palettes.emplace_back(
    "Apple Macintosh", 
    Palette::RGBColorsType {
      0xFFFFFFFF,
      0xFFFFFF00,
      0xFFFF6500,
      0xFFDC0000,
      0xFFFF0097,
      0xFF360097,
      0xFF0000CA,
      0xFF0097FF,
      0xFF00A800,
      0xFF006500,
      0xFF653600,
      0xFF976536,
      0xFFB9B9B9,
      0xFF868686,
      0xFF454545,
      0xFF000000
    }
  );

  palettes.emplace_back(
    "PICO 8", 
    Palette::RGBColorsType {
      0xFF000000,
      0xFF1D2B53,
      0xFF7E2553,
      0xFF008751,
      0xFFAB5236,
      0xFF5F574F,
      0xFFC2C3C7,
      0xFFFFF1E8,
      0xFFFF004D,
      0xFFFFA300,
      0xFFFFEC27,
      0xFF00E436,
      0xFF29ADFF,
      0xFF83769C,
      0xFFFF77A8,
      0xFFFFCCAA
    }
  );

  palettes.emplace_back(
    "Bastille-8 Palette", 
    Palette::RGBColorsType {
      0xFF181923,
      0xFF292D41,
      0xFF38405D,
      0xFF4C546D,
      0xFF6F687A,
      0xFF8B7983,
      0xFFA58D89,
      0xFFB59E90 
    }
  );
  return palettes;
}

inline const std::vector<Palette> kBuiltinPalettes = createDefaultPalettes();

#endif  // !BUILTIN_PALETTES_H_
