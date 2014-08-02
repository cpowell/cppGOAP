#include "gtest/gtest.h"

#define private public
#include "Node.h"

// The fixture for testing class SimVar.
class NodeTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for this component.
    Node n;

    // You can remove any or all of the following functions if its body is empty.

    NodeTest() {
        // You can do set-up work for each test here.
    }

    virtual ~NodeTest() {
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

TEST_F(NodeTest, constructs_in_sane_state) {
    ASSERT_EQ(0, n.f_);
    ASSERT_EQ(0, n.g_);
    ASSERT_EQ(0, n.h_);

    //std::cout << n;
}

TEST_F(NodeTest, compare_works_for_different_f_values) {
    n.f_ = 5;
    Node n1;
    n1.f_ = 10;
    ASSERT_TRUE(n < n1);
}

TEST_F(NodeTest, compare_works_for_same_f_values) {
    n.f_ = 5;
    Node n1;
    n1.f_ = 5;
    ASSERT_FALSE(n < n1);
}