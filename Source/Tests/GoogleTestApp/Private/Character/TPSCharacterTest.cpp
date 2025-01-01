#pragma once

#include "GoogleTestApp.h"
#include "gtest/gtest.h"

#include "TPS_Multiplayer/Public/Character/TPSCharacter.h"

class TPSCharacterTest : public ::testing::Test {

};


TEST_F(TPSCharacterTest, TestCanConstructAndDestruct) {
    TPSCharacter* c = new TPSCharacter();

    ASSERT_NE(nullptr, c);
    delete c;

    ASSERT_TRUE(true);
}
