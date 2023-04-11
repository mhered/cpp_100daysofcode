#include <gtest/gtest.h>

// the class I want to test
struct BankAccount
{
    int balance = 0;
    // empty constructor
    BankAccount()
    {
    }

    // constructor that initializes the balance
    // explicit avoids implicit type conversion
    explicit BankAccount(const int balance) : balance{balance} {}

    // deposit method
    void Deposit(int amount)
    {
        balance += amount;
    }
    // withdrawal method
    bool Withdraw(int amount)
    {
        if (amount > balance)
            return false;
        balance -= amount;
        return true;
    }
};

// simple standalone test in its own test suite
TEST(AccountTest, BankAccountStartsEmpty1)
{
    BankAccount sample_account;
    EXPECT_EQ(0, sample_account.balance);
}

// A set of tests using a test fixture
struct BankAccountTest : testing::Test
{

    BankAccount *account;
    // constructor
    BankAccountTest()
    {
        account = new BankAccount;
    }
    // destructor
    virtual ~BankAccountTest()
    {
        delete account;
    }
};

// test using the fixture
TEST_F(BankAccountTest, BankAccountStartsEmpty2)
{
    EXPECT_EQ(0, account->balance);
}

// other test using the fixture
TEST_F(BankAccountTest, CanDepositMoney)
{
    int amount = 5;
    int pre_balance = account->balance;
    account->Deposit(amount);
    int post_balance = account->balance;
    EXPECT_EQ(amount, post_balance - pre_balance);
}

// A parametrized test

// a struct to hold the parametrized test cases
struct account_state
{
    int initial_balance;
    int withdrawal_amount;
    int final_balance;
    bool success; // is withdrawal opssible or not

    // we override the << operator to have a display method for account_state
    friend std::ostream &operator<<(std::ostream &os, const account_state &obj)
    {
        return os
               << "initial_balance: " << obj.initial_balance
               << " withdrawal_amount: " << obj.withdrawal_amount
               << " final_balance: " << obj.final_balance
               << " success: " << obj.success;
    }
};

// create a new fixture class derived from the previous one
// and also the struct of parametrized test cases
struct WithdrawAccountTest : BankAccountTest, testing::WithParamInterface<account_state>
{
    // with a constructor that loads the initial balance
    WithdrawAccountTest()
    {
        account->balance = GetParam().initial_balance;
    }
};

// the parametric test
TEST_P(WithdrawAccountTest, FinalBalance)
{
    // get parameters
    auto as = GetParam();
    // execute withdrawal
    auto success = account->Withdraw(as.withdrawal_amount);
    // assert final balance matches expected
    EXPECT_EQ(as.final_balance, account->balance);
    // assert result of withdrawal matches expected
    EXPECT_EQ(as.success, success);
}

INSTANTIATE_TEST_CASE_P(Default, WithdrawAccountTest,
                        testing::Values(
                            account_state{100, 50, 50, true},
                            account_state{100, 200, 100, false},
                            account_state{100, 100, 10, true}));

// invoking the tests
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}