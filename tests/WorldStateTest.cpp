#include "gtest/gtest.h"

#include "WorldState.h"

using namespace goap;

// The fixture for testing class SimVar.
class WorldStateTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    WorldState ws;

    // You can remove any or all of the following functions if its body is empty.

    WorldStateTest() {
        // You can do set-up work for each test here.
    }

    virtual ~WorldStateTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(WorldStateTest, constructs_in_sane_state) {
    ASSERT_EQ(0, ws.priority_);
    ASSERT_EQ("", ws.name_);
}

TEST_F(WorldStateTest, goal_meeting_works_for_exact_match) {
    WorldState dead_enemy_goal;
    dead_enemy_goal.setVariable(0, true);

    ws.setVariable(0, true);
    ASSERT_TRUE(ws.meetsGoal(dead_enemy_goal));
}

TEST_F(WorldStateTest, goal_not_met_for_nonmatch) {
    WorldState dead_enemy_goal;
    dead_enemy_goal.setVariable(0, true);

    ws.setVariable(0, false);
    ASSERT_FALSE(ws.meetsGoal(dead_enemy_goal));
}

TEST_F(WorldStateTest, no_difference_when_all_false) {
    ws.setVariable(1, false);
    ws.setVariable(2, false);
    ws.setVariable(3, false);

    WorldState goal;
    goal.setVariable(1, false);
    goal.setVariable(2, false);
    goal.setVariable(3, false);

    ASSERT_EQ(0, ws.distanceTo(goal));
}

TEST_F(WorldStateTest, no_difference_when_nothing_matters) {
    ws.setVariable(1, false);
    ws.setVariable(2, false);
    ws.setVariable(3, false);

    WorldState goal;
    ASSERT_EQ(0, ws.distanceTo(goal));
}

TEST_F(WorldStateTest, difference_counts_only_those_that_matter) {
    ws.setVariable(1, false);
    ws.setVariable(2, true);
    ws.setVariable(3, false);
    ws.setVariable(4, true);
    ws.setVariable(5, true);

    WorldState goal;
    goal.setVariable(1, false);

    ASSERT_EQ(0, ws.distanceTo(goal));

    goal.setVariable(2, false);
    ASSERT_EQ(1, ws.distanceTo(goal));

    goal.setVariable(3, false);
    ASSERT_EQ(1, ws.distanceTo(goal));
}

TEST_F(WorldStateTest, distance_computes_correctly) {
    ws.setVariable(1, false);
    ws.setVariable(2, true);
    ws.setVariable(3, false);
    ws.setVariable(4, true);
    ws.setVariable(5, true);

    WorldState goal;
    goal.setVariable(1, false);
    goal.setVariable(2, true);
    goal.setVariable(3, false);
    goal.setVariable(4, true);
    goal.setVariable(5, true);
    ASSERT_EQ(0, ws.distanceTo(goal));

    goal.setVariable(1, true);
    goal.setVariable(2, false);
    goal.setVariable(3, true);
    goal.setVariable(4, false);
    goal.setVariable(5, false);
    ASSERT_EQ(5, ws.distanceTo(goal));
}
