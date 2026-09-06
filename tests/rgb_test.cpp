#include <gtest/gtest.h>
#include <image/colors/rgb.h>

// clang-format off

constexpr std::uint32_t color = 0xff362b44;
constexpr std::uint32_t alpha = 0xff;
constexpr std::uint32_t red   = 0x36;
constexpr std::uint32_t green = 0x2b;
constexpr std::uint32_t blue  = 0x44;

TEST(RgbTest, ConstructsFromColor) {
  Rgb rgb(color);

  EXPECT_EQ(rgb.color(), color);
  EXPECT_EQ(rgb.alpha(), alpha);
  EXPECT_EQ(rgb.red()  , red  );
  EXPECT_EQ(rgb.green(), green);
  EXPECT_EQ(rgb.blue() , blue );
}

TEST(RgbTest, ConstructsFromChannels) {
  Rgb rgb(red, green, blue, alpha);

  EXPECT_EQ(rgb.color(), color);
  EXPECT_EQ(rgb.alpha(), alpha);
  EXPECT_EQ(rgb.red()  , red  );
  EXPECT_EQ(rgb.green(), green);
  EXPECT_EQ(rgb.blue() , blue );
}

TEST(RgbTest, ReturnsChannelByType) {
  Rgb rgb(color);

  EXPECT_EQ(rgb.color()          , color);
  EXPECT_EQ(rgb.color(Rgb::Alpha), alpha);
  EXPECT_EQ(rgb.color(Rgb::Red)  , red  );
  EXPECT_EQ(rgb.color(Rgb::Green), green);
  EXPECT_EQ(rgb.color(Rgb::Blue) , blue );
}

TEST(RgbTest, NotEqualOperator) {
  Rgb rgbA(54 , 43 , 68);
  Rgb rgbB(107, 188, 155);

  EXPECT_TRUE(rgbA != rgbB);
  EXPECT_FALSE(rgbA != rgbA);
}

TEST(RgbTest, EqualOperator) {
  Rgb rgbA(54 , 43 , 68);
  Rgb rgbB(107, 188, 155);

  EXPECT_TRUE(rgbA == rgbA);
  EXPECT_FALSE(rgbA == rgbB);
}