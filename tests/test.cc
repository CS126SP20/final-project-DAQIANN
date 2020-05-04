// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/game_engine.h>
#include <mylibrary/sprite.h>
#include <mylibrary/sprite_location.h>
#include <mylibrary/player_sprite.h>
#include <mylibrary/player.h>

#include <catch2/catch.hpp>

TEST_CASE("Sprite test") {
  mylibrary::Sprite sprite_test({1, 2});
  SECTION("Location check") {
    REQUIRE(sprite_test.GetLocation().Row() == 1);
    REQUIRE(sprite_test.GetLocation().Col() == 2);
  }

  SECTION("Collectable check") {
    sprite_test.SetCollectable(true);
    REQUIRE(sprite_test.IsCollectable() == true);
  }
}

TEST_CASE("Player test") {
  mylibrary::PlayerSprite player_test({1, 2});
  SECTION("Location check") {
    REQUIRE(player_test.GetLocation().Row() == 1);
    REQUIRE(player_test.GetLocation().Col() == 2);
  }

  SECTION("Set location check") {
    player_test.SetLocation({2,3});
    REQUIRE(player_test.GetLocation().Row() == 2);
    REQUIRE(player_test.GetLocation().Col() == 3);
  }

  SECTION("Blocked check") {
    player_test.SetBlocked(true);
    REQUIRE(player_test.IsBlocked() == true);
  }
}

TEST_CASE("Sprite location operators test") {
  mylibrary::SpriteLocation location_one(1, 2);
  mylibrary::SpriteLocation location_two(2, 3);
  mylibrary::SpriteLocation location_three(1, 2);

  SECTION("Equality") {
    REQUIRE(location_one == location_three);
    REQUIRE(location_one != location_two);
    REQUIRE(location_one < location_two);
  }

  SECTION("Adding") {

  }
}
//TEST_CASE("Test adding sprite") {
//  mylibrary::GameEngine engine_test({16,16});
//  engine_test.AddSprite(false);
//  REQUIRE(engine_test.GetSpriteCount() == 1);
//}