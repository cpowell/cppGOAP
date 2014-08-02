#include "gtest/gtest.h"

#define private public
#include "Action.h"
#include "WorldState.h"

// The fixture for testing class SimVar.
class ActionTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    Action act;

    // You can remove any or all of the following functions if its body is empty.

    ActionTest() {
        // You can do set-up work for each test here.
    }

    virtual ~ActionTest() {
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

TEST_F(ActionTest, constructs_in_sane_state) {
    ASSERT_EQ(0, act.cost_);
    ASSERT_EQ("", act.name_);

    ASSERT_FALSE(act.preconditions_[0]);
    ASSERT_FALSE(act.precondition_matters_[0]);
    ASSERT_FALSE(act.has_effect_[0]);
    ASSERT_FALSE(act.effects_[0]);
}

TEST_F(ActionTest, elgibility_computes_correctly_when_eligible) {
    act.setPrecondition(0, true);

    WorldState ws;
    ws.state_vars_[0] = true;
    ASSERT_TRUE(act.eligibleFor(ws));

    ws.state_vars_[1] = true;
    ws.state_vars_[2] = true;
    ASSERT_TRUE(act.eligibleFor(ws));
}

TEST_F(ActionTest, elgibility_computes_correctly_when_ineligible) {
    act.setPrecondition(0, true);

    WorldState ws;
    ws.state_vars_[0] = false;
    ASSERT_FALSE(act.eligibleFor(ws));

    ws.state_vars_[1] = true;
    ws.state_vars_[2] = true;
    ASSERT_FALSE(act.eligibleFor(ws));
}

TEST_F(ActionTest, action_with_no_effects_has_no_effect) {
    WorldState ws;
    ws.state_vars_[0] = true;

    WorldState ws_new = act.actOn(ws);
    ASSERT_EQ(ws, ws_new);
}

TEST_F(ActionTest, action_takes_effect_where_applicable) {
    WorldState ws;
    ws.state_vars_[0] = true;
    ASSERT_EQ(true, ws.state_vars_[0]);

    act.setPrecondition(0, true);
    act.setEffect(0, false);
    WorldState ws_new = act.actOn(ws);
    ASSERT_EQ(true, ws.state_vars_[0]);
    ASSERT_EQ(false, ws_new.state_vars_[0]);
}

TEST_F(ActionTest, action_has_no_effect_where_inapplicable) {
    WorldState ws;
    ws.state_vars_[0] = true;
    ws.state_vars_[1] = true;
    ws.state_vars_[2] = true;
    ws.state_vars_[3] = true;
    ws.state_vars_[4] = true;

    act.setPrecondition(0, true);
    act.setEffect(0, false);
    WorldState ws_new = act.actOn(ws);
    ASSERT_FALSE(ws_new.state_vars_[0]);
    ASSERT_TRUE(ws_new.state_vars_[1]);
    ASSERT_TRUE(ws_new.state_vars_[2]);
    ASSERT_TRUE(ws_new.state_vars_[3]);
    ASSERT_TRUE(ws_new.state_vars_[4]);
}

TEST_F(ActionTest, action_has_no_effect_when_ineligible) {
    WorldState ws;
    ws.state_vars_[0] = true;
    ws.state_vars_[1] = true;
    ws.state_vars_[2] = true;
    ws.state_vars_[3] = true;
    ws.state_vars_[4] = true;

    act.setPrecondition(0, false);
    act.setEffect(1, false);

    WorldState ws_new = act.actOn(ws);
    ASSERT_TRUE(ws_new.state_vars_[0]);
    ASSERT_TRUE(ws_new.state_vars_[1]);
    ASSERT_TRUE(ws_new.state_vars_[2]);
    ASSERT_TRUE(ws_new.state_vars_[3]);
    ASSERT_TRUE(ws_new.state_vars_[4]);
}