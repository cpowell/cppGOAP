#include "gtest/gtest.h"

#define private public
#include "WorldState.h"

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
    ASSERT_EQ(false, ws.state_vars_[0]);
    ASSERT_EQ(true, ws.var_matters_[0]);
}

TEST_F(WorldStateTest, at_least_one_var_matters_for_validity) {
    ws.var_matters_[0] = false;
    ws.var_matters_[1] = false;
    ws.var_matters_[2] = false;
    ws.var_matters_[3] = false;
    ws.var_matters_[4] = false;
    ASSERT_FALSE(ws.valid());

    ws.var_matters_[1] = true;
    ASSERT_TRUE(ws.valid());
}

TEST_F(WorldStateTest, goal_meeting_works_for_exact_match) {
    WorldState dead_enemy_goal;
    dead_enemy_goal.var_matters_[0] = false;
    dead_enemy_goal.var_matters_[1] = true;
    dead_enemy_goal.var_matters_[2] = false;
    dead_enemy_goal.var_matters_[3] = false;
    dead_enemy_goal.var_matters_[4] = false;
    dead_enemy_goal.state_vars_[1] = true;

    ws.state_vars_[1] = true;
    ASSERT_TRUE(dead_enemy_goal.metBy(ws));
}

TEST_F(WorldStateTest, goal_not_met_for_nonmatch) {
    WorldState dead_enemy_goal;
    dead_enemy_goal.var_matters_[0] = false;
    dead_enemy_goal.var_matters_[1] = true;
    dead_enemy_goal.var_matters_[2] = false;
    dead_enemy_goal.var_matters_[3] = false;
    dead_enemy_goal.var_matters_[4] = false;
    dead_enemy_goal.state_vars_[1] = true;

    ws.state_vars_[1] = false;
    ASSERT_FALSE(dead_enemy_goal.metBy(ws));
}

TEST_F(WorldStateTest, no_difference_when_all_false) {
    ws.state_vars_[0] = false;
    ws.state_vars_[1] = false;
    ws.state_vars_[2] = false;
    ws.state_vars_[3] = false;
    ws.state_vars_[4] = false;

    WorldState ws2;
    ws2.state_vars_[0] = false;
    ws2.state_vars_[1] = false;
    ws2.state_vars_[2] = false;
    ws2.state_vars_[3] = false;
    ws2.state_vars_[4] = false;
    ws2.var_matters_[0] = false;
    ws2.var_matters_[1] = false;
    ws2.var_matters_[2] = false;
    ws2.var_matters_[3] = false;
    ws2.var_matters_[4] = false;

    ASSERT_EQ(0, ws.difference(ws2));
}

TEST_F(WorldStateTest, no_difference_when_nothing_matters) {
    ws.state_vars_[0] = true;
    ws.state_vars_[1] = false;
    ws.state_vars_[2] = false;
    ws.state_vars_[3] = true;
    ws.state_vars_[4] = false;

    WorldState ws2;
    ws2.state_vars_[0] = false;
    ws2.state_vars_[1] = true;
    ws2.state_vars_[2] = true;
    ws2.state_vars_[3] = false;
    ws2.state_vars_[4] = false;
    ws2.var_matters_[0] = false;
    ws2.var_matters_[1] = false;
    ws2.var_matters_[2] = false;
    ws2.var_matters_[3] = false;
    ws2.var_matters_[4] = false;

    ASSERT_EQ(0, ws.difference(ws2));
}

TEST_F(WorldStateTest, difference_counts_only_those_that_matter) {
    ws.state_vars_[0] = true;
    ws.state_vars_[1] = false;
    ws.state_vars_[2] = false;
    ws.state_vars_[3] = true;
    ws.state_vars_[4] = false;

    WorldState ws2;
    ws2.state_vars_[0] = false;
    ws2.state_vars_[1] = true;
    ws2.state_vars_[2] = true;
    ws2.state_vars_[3] = false;
    ws2.state_vars_[4] = false;
    ws2.var_matters_[0] = true;
    ws2.var_matters_[1] = false;
    ws2.var_matters_[2] = false;
    ws2.var_matters_[3] = false;
    ws2.var_matters_[4] = false;

    ASSERT_EQ(1, ws.difference(ws2));
    ws2.var_matters_[4] = true;
    ASSERT_EQ(1, ws.difference(ws2));
    ws.state_vars_[4] = true;
    ASSERT_EQ(2, ws.difference(ws2));

    //std::cout << ws << std::endl;
}
