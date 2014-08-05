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

}

TEST_F(ActionTest, elgibility_computes_correctly_when_eligible) {
    act.setPrecondition("var1", true);

    WorldState ws;
    ws.setVariable("var1", true);
    ASSERT_TRUE(act.eligibleFor(ws));

    ws.setVariable("var2", true);
    ws.setVariable("var3", false);
    ASSERT_TRUE(act.eligibleFor(ws));
}

TEST_F(ActionTest, elgibility_computes_correctly_when_ineligible) {
    act.setPrecondition("var1", true);

    WorldState ws;
    ws.setVariable("var1", false);
    ASSERT_FALSE(act.eligibleFor(ws));

    ws.setVariable("var2", true);
    ws.setVariable("var3", false);
    ASSERT_FALSE(act.eligibleFor(ws));
}

TEST_F(ActionTest, action_with_no_effects_has_no_effect) {
    WorldState ws;
    ws.setVariable("var1", true);

    WorldState ws_new = act.actOn(ws);
    ASSERT_EQ(ws, ws_new);
}

TEST_F(ActionTest, action_takes_effect_where_applicable) {
    WorldState ws;
    ws.setVariable("var1", true);
    ASSERT_TRUE(ws.vars_["var1"]);

    act.setPrecondition("var1", true);
    act.setEffect("var1", false);
    WorldState ws_new = act.actOn(ws);
    ASSERT_FALSE(ws_new.vars_["var1"]);
}

TEST_F(ActionTest, action_has_no_effect_where_inapplicable) {
    WorldState ws;
    ws.setVariable("var1", true);
    ws.setVariable("var2", true);
    ws.setVariable("var3", true);
    ws.setVariable("var4", true);
    ws.setVariable("var5", true);

    act.setPrecondition("var1", true);
    act.setEffect("var1", false);
    WorldState ws_new = act.actOn(ws);
    ASSERT_FALSE(ws_new.vars_["var1"]);
    ASSERT_TRUE(ws_new.vars_["var2"]);
    ASSERT_TRUE(ws_new.vars_["var3"]);
    ASSERT_TRUE(ws_new.vars_["var4"]);
    ASSERT_TRUE(ws_new.vars_["var5"]);
}

TEST_F(ActionTest, action_has_no_effect_when_ineligible) {
    WorldState ws;
    ws.setVariable("var1", true);
    ws.setVariable("var2", true);
    ws.setVariable("var3", true);
    ws.setVariable("var4", true);
    ws.setVariable("var5", true);

    act.setPrecondition("var1", false);
    act.setEffect("var2", false);

    WorldState ws_new = act.actOn(ws);
    ASSERT_TRUE(ws_new.vars_["var1"]);
    ASSERT_TRUE(ws_new.vars_["var2"]);
    ASSERT_TRUE(ws_new.vars_["var3"]);
    ASSERT_TRUE(ws_new.vars_["var4"]);
    ASSERT_TRUE(ws_new.vars_["var5"]);

}