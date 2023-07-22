#include <iostream>
#include <fstream>
using namespace std;

class ATM {
private:
    double balance;
    double prevBalance;
    string password;
    int incorrectAttempts;
    const double MAX_WITHDRAWAL_AMOUNT = 50000;

public:
    ATM() : balance(0), prevBalance(0), password(""), incorrectAttempts(0) {}

    void showBalance() {
        cout << "Your current balance is: " << balance << " taka" << endl;
    }

    void deposit(double amount) {
        if (amount >= 500) {
            prevBalance = balance;
            balance += amount;
            cout << amount << " taka deposited successfully." << endl;
            saveBalanceToFile();
        } else {
            cout << "Minimum deposit amount is 500 taka." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount >= 500 && amount <= balance && amount <= MAX_WITHDRAWAL_AMOUNT) {
            prevBalance = balance;
            balance -= amount;
            cout << amount << " taka withdrawn successfully. Remaining balance: " << balance << " taka" << endl;
            saveBalanceToFile(); 
        } else {
            cout << "Invalid withdrawal amount or insufficient funds or exceeding maximum withdrawal limit (50,000 taka)." << endl;
        }
    }

    void changePassword() {
        string currentPassword, newPassword;
        cout << "Enter current password: ";
        cin >> currentPassword;

        if (currentPassword == password) {
            cout << "Enter new password: ";
            cin >> newPassword;
            password = newPassword;
            cout << "Password changed successfully." << endl;

            ofstream passwordFile("password.txt");
            if (passwordFile.is_open()) {
                passwordFile << password;
                passwordFile.close();
            } else {
                cout << "Error: Unable to save the new password." << endl;
            }
        } else {
            cout << "Incorrect password. Password not changed." << endl;
        }
    }

    bool checkPassword(string inputPassword) {
        if (inputPassword == password) {
            incorrectAttempts = 0; 
            return true;
        } else {
            incorrectAttempts++;
            if (incorrectAttempts >= 3) {
                cout << "Incorrect password entered multiple times. Account blocked." << endl;
                exit(0);
            } else {
                cout << "Incorrect password. Please try again." << endl;
            }
            return false;
        }
    }

    void loadPasswordFromFile() {
        ifstream passwordFile("password.txt");
        if (passwordFile.is_open()) {
            getline(passwordFile, password);
            passwordFile.close();
        }
    }

    void loadBalanceFromFile() {
        ifstream balanceFile("balance.txt");
        if (balanceFile.is_open()) {
            balanceFile >> balance;
            prevBalance = balance; 
            balanceFile.close();
        } else {

            prevBalance = balance;
        }
    }

    void saveBalanceToFile() {
        ofstream balanceFile("balance.txt");
        if (balanceFile.is_open()) {
            balanceFile << balance;
            balanceFile.close();
        } else {
            cout << "Error: Unable to save balance." << endl;
        }
    }
};

int main() {
    ATM atm;
    atm.loadPasswordFromFile();
    atm.loadBalanceFromFile();

    cout << "Welcome to the ATM!" << endl;

    while (true) {
        string inputPassword;
        cout << "Enter your password: ";
        cin >> inputPassword;

        if (atm.checkPassword(inputPassword)) {
            cout << "\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. Change Password\n5. Exit\nEnter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    atm.showBalance();
                    break;
                case 2:
                    double depositAmount;
                    cout << "Enter the amount to deposit (in taka): ";
                    cin >> depositAmount;
                    atm.deposit(depositAmount);
                    break;
                case 3:
                    double withdrawAmount;
                    cout << "Enter the amount to withdraw (in taka): ";
                    cin >> withdrawAmount;
                    atm.withdraw(withdrawAmount);
                    break;
                case 4:
                    atm.changePassword();
                    break;
                case 5:
                    atm.saveBalanceToFile(); 
                    cout << "Thank you for using the ATM. Have a nice day!" << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    return 0;
}
