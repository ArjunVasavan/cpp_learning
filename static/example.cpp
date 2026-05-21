#include <iostream>
using namespace std;

class BankAccount {
private:
    string owner;
    double balance;
    static int totalAccounts;       // shared count
    static double totalMoneyInBank; // shared sum

public:
    BankAccount(string owner, double initialBalance) {
        this->owner   = owner;
        this->balance = initialBalance;
        totalAccounts++;
        totalMoneyInBank += initialBalance;
    }

    void deposit(double amount) {
        balance          += amount;
        totalMoneyInBank += amount;
    }

    void print() const {
        cout << owner << ": Rs." << balance << endl;
    }

    // Static function — reports class-wide data, needs no object
    static void bankReport() {
        cout << "Total accounts : " << totalAccounts    << endl;
        cout << "Total money    : Rs." << totalMoneyInBank << endl;
    }
};

// Define static members outside
int    BankAccount::totalAccounts    = 0;
double BankAccount::totalMoneyInBank = 0.0;

int main() {
    BankAccount a("Alice", 5000);
    BankAccount b("Bob",   3000);

    a.deposit(1000);

    a.print();   // Alice: Rs.6000
    b.print();   // Bob:   Rs.3000

    BankAccount::bankReport();
    // Total accounts : 2
    // Total money    : Rs.9000

    return 0;
}
