#include "gtest/gtest.h"

// https://stackoverflow.com/questions/14186245/unit-testing-c-how-to-test-private-members
#define TEST_FRIENDS \
    friend class ActionTest_constructs_in_sane_state_Test;\

#include "Action.h"
#include "WorldState.h"

namespace goap {
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
        act.setPrecondition(0, true);

        WorldState ws;
        ws.setVariable(0, true);
        ASSERT_TRUE(act.operableOn(ws));

        ws.setVariable(1, true);
        ws.setVariable(2, false);
        ASSERT_TRUE(act.operableOn(ws));
    }

    TEST_F(ActionTest, elgibility_computes_correctly_when_ineligible) {
        act.setPrecondition(0, true);

        WorldState ws;
        ws.setVariable(0, false);
        ASSERT_FALSE(act.operableOn(ws));

        ws.setVariable(1, true);
        ws.setVariable(2, false);
        ASSERT_FALSE(act.operableOn(ws));
    }

    TEST_F(ActionTest, action_with_no_effects_has_no_effect) {
        WorldState ws;
        ws.setVariable(0, true);

        WorldState ws_new = act.actOn(ws);
        ASSERT_EQ(ws, ws_new);
    }

    TEST_F(ActionTest, action_takes_effect_where_applicable) {
        WorldState ws;
        ws.setVariable(0, true);
        ASSERT_TRUE(ws.vars_[0]);

        act.setPrecondition(0, true);
        act.setEffect(0, false);
        WorldState ws_new = act.actOn(ws);
        ASSERT_FALSE(ws_new.vars_[0]);
    }

    TEST_F(ActionTest, action_has_an_effect_even_where_inapplicable) {
        WorldState ws;
        ws.setVariable(0, true);
        ws.setVariable(1, true);
        ws.setVariable(2, true);
        ws.setVariable(3, true);
        ws.setVariable(4, true);

        act.setPrecondition(0, true);
        act.setEffect(0, false);
        WorldState ws_new = act.actOn(ws);
        ASSERT_FALSE(ws_new.vars_[0]);
        ASSERT_TRUE(ws_new.vars_[1]);
        ASSERT_TRUE(ws_new.vars_[2]);
        ASSERT_TRUE(ws_new.vars_[3]);
        ASSERT_TRUE(ws_new.vars_[4]);
    }

    TEST_F(ActionTest, action_has_an_effect_even_when_ineligible) {
        WorldState ws;
        ws.setVariable(0, true);
        ws.setVariable(1, true);
        ws.setVariable(2, true);
        ws.setVariable(3, true);
        ws.setVariable(4, true);

        act.setPrecondition(0, false);
        act.setEffect(1, false);

        WorldState ws_new = act.actOn(ws);
        ASSERT_TRUE(ws_new.vars_[0]);
        ASSERT_FALSE(ws_new.vars_[1]);
        ASSERT_TRUE(ws_new.vars_[2]);
        ASSERT_TRUE(ws_new.vars_[3]);
        ASSERT_TRUE(ws_new.vars_[4]);

    }
}