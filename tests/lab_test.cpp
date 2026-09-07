#include "image/colors/lab.h"

#include "image/colors/rgb.h"

#include <gtest/gtest.h>

TEST(LabTest, White) {
  Rgb color(255, 255, 255);

  Lab lab = Lab::fromRgb(color);

  EXPECT_NEAR(lab.l(), 100.0, 0.01);
  EXPECT_NEAR(lab.a(), 0.0, 0.01);
  EXPECT_NEAR(lab.b(), 0.0, 0.01);
}

TEST(LabTest, Black) {
  Rgb color(0, 0, 0);

  Lab lab = Lab::fromRgb(color);

  EXPECT_NEAR(lab.l(), 0.0, 0.01);
  EXPECT_NEAR(lab.a(), 0.0, 0.01);
  EXPECT_NEAR(lab.b(), 0.0, 0.01);
}

TEST(LabTest, Red) {
  Rgb color(255, 0, 0);

  Lab lab = Lab::fromRgb(color);

  EXPECT_NEAR(lab.l(), 53.24, 0.01);
  EXPECT_NEAR(lab.a(), 80.09, 0.01);
  EXPECT_NEAR(lab.b(), 67.20, 0.01);
}

TEST(LabTest, Green) {
  Rgb color(0, 255, 0);

  Lab lab = Lab::fromRgb(color);

  EXPECT_NEAR(lab.l(), 87.73, 0.01);
  EXPECT_NEAR(lab.a(), -86.18, 0.01);
  EXPECT_NEAR(lab.b(), 83.18, 0.01);
}

TEST(LabTest, Blue) {
  Rgb color(0, 0, 255);

  Lab lab = Lab::fromRgb(color);

  EXPECT_NEAR(lab.l(), 32.30, 0.01);
  EXPECT_NEAR(lab.a(), 79.19, 0.01);
  EXPECT_NEAR(lab.b(), -107.86, 0.01);
}

TEST(LabTest, Rgb120_117_148) {
  Rgb color(120, 117, 148);
  Lab lab = Lab::fromRgb(color);

  EXPECT_NEAR(lab.l(), 50.5154, 0.01);
  EXPECT_NEAR(lab.a(), 7.9448, 0.01);
  EXPECT_NEAR(lab.b(), -16.3585, 0.01);
}

TEST(LabTest, Rgb39_53_55) {
  Rgb color(39, 53, 55);
  Lab lab = Lab::fromRgb(color);

  EXPECT_NEAR(lab.l(), 21.0309, 0.01);
  EXPECT_NEAR(lab.a(), -5.2087, 0.01);
  EXPECT_NEAR(lab.b(), -3.1571, 0.01);
}