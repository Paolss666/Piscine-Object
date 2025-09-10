#include "../incl/DivideAndRule.hpp"

// int main()
// {
//     Bank bank;
//     bank.setLiquidity(999);

//     Account *accountA = bank.createAccount();
//     bank.deposite(accountA->getId(), 100);
//     std::cout << bank << std::endl;

//     // accountA. = 0;
//     // accountA._value = 100;

//     Account *accountB = bank.createAccount();
//     bank.deposite(accountB->getId(), 100);

//     // accountB._id = 1;
//     // accountB._value = 100;
//     std::cout << " --GIVE LOAN 100--- " << std::endl;
//     bank.giveLoan(accountA->getId(), 100);
//     std::cout << *accountA << std::endl;

//     std::cout << " ----- " << std::endl;

//     std::cout << "Account : " << std::endl;
//     std::cout << *accountA << std::endl;
//     std::cout << *accountB << std::endl;
//     std::cout << " ----- " << std::endl;

//     std::cout << "Bank : " << std::endl;
//     std::cout << bank << std::endl;

//     return (0);
// }

void printSeparator(const std::string &title)
{
    std::cout << "\n========== " << title << " ==========" << std::endl;
}

void testAccountCreation(Bank &bank)
{
    printSeparator("TESTING ACCOUNT CREATION");

    std::cout << "Initial bank state:" << std::endl;
    std::cout << bank << std::endl;

    std::cout << "\nCreating 3 accounts..." << std::endl;
    Account *acc1 = bank.createAccount();
    Account *acc2 = bank.createAccount();
    Account *acc3 = bank.createAccount();

    std::cout << "Account 1 ID: " << acc1->getId() << ", Value: " << acc1->getValue() << std::endl;
    std::cout << "Account 2 ID: " << acc2->getId() << ", Value: " << acc2->getValue() << std::endl;
    std::cout << "Account 3 ID: " << acc3->getId() << ", Value: " << acc3->getValue() << std::endl;

    std::cout << "\nBank after account creation:" << std::endl;
    std::cout << bank << std::endl;
}

void testDepositSystem(Bank &bank)
{
    printSeparator("TESTING DEPOSIT SYSTEM (5% BANK FEE)");

    const std::vector<Account *> &accounts = bank.getListAccounts();
    if (accounts.size() < 2)
        return;

    int initialLiquidity = bank.getLiquidity();
    std::cout << "Initial bank liquidity: " << initialLiquidity << std::endl;

    std::cout << "\nDepositing 1000 to account " << accounts[0]->getId() << "..." << std::endl;
    bool success = bank.deposit(accounts[0]->getId(), 1000);
    std::cout << "Deposit success: " << (success ? "YES" : "NO") << std::endl;
    std::cout << "Account value: " << accounts[0]->getValue() << " (should be 950)" << std::endl;
    std::cout << "Bank liquidity: " << bank.getLiquidity() << " (should be " << (initialLiquidity + 50) << ")" << std::endl;

    std::cout << "\nDepositing 500 to account " << accounts[1]->getId() << "..." << std::endl;
    success = bank.deposit(accounts[1]->getId(), 500);
    std::cout << "Deposit success: " << (success ? "YES" : "NO") << std::endl;
    std::cout << "Account value: " << accounts[1]->getValue() << " (should be 475)" << std::endl;

    // Test invalid deposit
    std::cout << "\nTesting invalid deposit (negative amount)..." << std::endl;
    success = bank.deposit(accounts[0]->getId(), -100);
    std::cout << "Invalid deposit success: " << (success ? "YES" : "NO") << " (should be NO)" << std::endl;

    // Test deposit to non-existent account
    std::cout << "\nTesting deposit to non-existent account (ID: 999)..." << std::endl;
    success = bank.deposit(999, 100);
    std::cout << "Non-existent account deposit: " << (success ? "YES" : "NO") << " (should be NO)" << std::endl;
}

void testWithdrawSystem(Bank &bank)
{
    printSeparator("TESTING WITHDRAW SYSTEM");

    const std::vector<Account *> &accounts = bank.getListAccounts();
    if (accounts.empty())
        return;

    std::cout << "Account " << accounts[0]->getId() << " current value: " << accounts[0]->getValue() << std::endl;

    std::cout << "\nWithdrawing 200 from account " << accounts[0]->getId() << "..." << std::endl;
    bool success = bank.withdraw(accounts[0]->getId(), 200);
    std::cout << "Withdraw success: " << (success ? "YES" : "NO") << std::endl;
    std::cout << "Account value after withdrawal: " << accounts[0]->getValue() << std::endl;

    // Test overdraw
    std::cout << "\nTesting overdraw (withdrawing more than available)..." << std::endl;
    int currentValue = accounts[0]->getValue();
    success = bank.withdraw(accounts[0]->getId(), currentValue + 1000);
    std::cout << "Overdraw attempt: " << (success ? "YES" : "NO") << " (should be NO)" << std::endl;
    std::cout << "Account value unchanged: " << accounts[0]->getValue() << std::endl;
}

void testLoanSystem(Bank &bank)
{
    printSeparator("TESTING LOAN SYSTEM");

    const std::vector<Account *> &accounts = bank.getListAccounts();
    if (accounts.size() < 2)
        return;

    int bankLiquidity = bank.getLiquidity();
    int accountValue = accounts[1]->getValue();

    std::cout << "Bank liquidity: " << bankLiquidity << std::endl;
    std::cout << "Account " << accounts[1]->getId() << " value before loan: " << accountValue << std::endl;

    std::cout << "\nGiving loan of 300 to account " << accounts[1]->getId() << "..." << std::endl;
    bool success = bank.giveLoan(accounts[1]->getId(), 300);
    std::cout << "Loan success: " << (success ? "YES" : "NO") << std::endl;
    std::cout << "Account value after loan: " << accounts[1]->getValue() << " (should be " << (accountValue + 300) << ")" << std::endl;
    std::cout << "Bank liquidity after loan: " << bank.getLiquidity() << " (should be " << (bankLiquidity - 300) << ")" << std::endl;

    // Test loan exceeding bank liquidity
    std::cout << "\nTesting loan exceeding bank liquidity..." << std::endl;
    int currentLiquidity = bank.getLiquidity();
    success = bank.giveLoan(accounts[1]->getId(), currentLiquidity + 1000);
    std::cout << "Excessive loan attempt: " << (success ? "YES" : "NO") << " (should be NO)" << std::endl;
    std::cout << "Bank liquidity unchanged: " << bank.getLiquidity() << std::endl;
}

void testTransferSystem(Bank &bank)
{
    printSeparator("TESTING TRANSFER SYSTEM (5% FEE FROM SENDER)");

    const std::vector<Account *> &accounts = bank.getListAccounts();
    if (accounts.size() < 2)
        return;

    int fromValue = accounts[0]->getValue();
    int toValue = accounts[1]->getValue();
    int bankLiquidity = bank.getLiquidity();

    std::cout << "Before transfer:" << std::endl;
    std::cout << "From account " << accounts[0]->getId() << ": " << fromValue << std::endl;
    std::cout << "To account " << accounts[1]->getId() << ": " << toValue << std::endl;
    std::cout << "Bank liquidity: " << bankLiquidity << std::endl;

    std::cout << "\nTransferring 400 from account " << accounts[0]->getId() << " to " << accounts[1]->getId() << "..." << std::endl;
    bool success = bank.transfer(accounts[0]->getId(), accounts[1]->getId(), 400);
    std::cout << "Transfer success: " << (success ? "YES" : "NO") << std::endl;

    if (success)
    {
        std::cout << "After transfer:" << std::endl;
        std::cout << "From account " << accounts[0]->getId() << ": " << accounts[0]->getValue() << " (should be " << (fromValue - 420) << ")" << std::endl;
        std::cout << "To account " << accounts[1]->getId() << ": " << accounts[1]->getValue() << " (should be " << (toValue + 400) << ")" << std::endl;
        std::cout << "Bank liquidity: " << bank.getLiquidity() << " (should be " << (bankLiquidity + 20) << ")" << std::endl;
    }
}

void testAccountDeletion(Bank &bank)
{
    printSeparator("TESTING ACCOUNT DELETION");

    const std::vector<Account *> &accounts = bank.getListAccounts();
    if (accounts.size() < 3)
        return;

    std::cout << "Accounts before deletion:" << std::endl;
    std::cout << bank << std::endl;

    int accountToDelete = accounts[2]->getId();
    std::cout << "\nDeleting account " << accountToDelete << "..." << std::endl;
    bool success = bank.deleteAccount(accountToDelete);
    std::cout << "Deletion success: " << (success ? "YES" : "NO") << std::endl;

    std::cout << "\nAccounts after deletion:" << std::endl;
    std::cout << bank << std::endl;

    // Test deleting non-existent account
    std::cout << "\nTrying to delete non-existent account (ID: 999)..." << std::endl;
    success = bank.deleteAccount(999);
    std::cout << "Non-existent deletion: " << (success ? "YES" : "NO") << " (should be NO)" << std::endl;
}

void testGetters(Bank &bank)
{
    printSeparator("TESTING GETTERS (CONST BY REFERENCE)");

    const Bank &constBank = bank;

    std::cout << "Bank liquidity (via getter): " << constBank.getLiquidity() << std::endl;
    std::cout << "Number of accounts (via getter): " << constBank.getListAccounts().size() << std::endl;

    const std::vector<Account *> &accounts = constBank.getListAccounts();
    if (!accounts.empty())
    {
        std::cout << "First account ID (via getter): " << accounts[0]->getId() << std::endl;
        std::cout << "First account value (via getter): " << accounts[0]->getValue() << std::endl;
    }

    std::cout << "\nNote: All getters return const references, not copies!" << std::endl;
}

int main()
{
    Bank bank;
    bank.setLiquidity(2000);

    // Run all tests
    testAccountCreation(bank);
    testDepositSystem(bank);
    testWithdrawSystem(bank);
    testLoanSystem(bank);
    testTransferSystem(bank);
    testAccountDeletion(bank);
    testGetters(bank);

    printSeparator("FINAL BANK STATE");
    std::cout << bank << std::endl;

    return 0;
}