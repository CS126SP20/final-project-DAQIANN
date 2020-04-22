// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>
#include <mylibrary/sprite_location.h>
#include <mylibrary/sprite.h>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Sprite Location", "[sprite]") {
  mylibrary::Sprite sprite_test({1, 2});
  REQUIRE(sprite_test.GetLocation().Row() == 1);
  REQUIRE(sprite_test.GetLocation().Col() == 2);
}