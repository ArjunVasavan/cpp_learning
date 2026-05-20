#include <iostream>
using namespace std;

class BankAccount{
    private:
        string owner;
        double balance;
    public:
        BankAccount(string name, double bal) : owner(name), balance(bal) {};
        friend void printDetails(BankAccount acc);
};
 /* Friend Function , Defined Outside and here no need of using :: "Scope Resolution" */
void printDetails(BankAccount acc ) {
    std::cout << "Owner: " << acc.owner << std::endl; /* accessed private */
    std::cout << "Balance: " << acc.balance << std::endl; /* accessed private */
}

int main() {

    BankAccount acc("Arjun",0000);

    printDetails(acc);
    
}
