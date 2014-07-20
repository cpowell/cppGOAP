#include "gtest/gtest.h"

#define private public
#include "Action.h"

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
	ASSERT_FALSE(act.has_effect_[0]);
	ASSERT_FALSE(act.effects_[0]);
}

