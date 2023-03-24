#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Transaction {
    string description;
    double amount;
    bool is_income;
};

void display_transactions(const vector<Transaction>& transactions) {
    cout << "TRANSACTION HISTORY:" << endl;
    for (vector<Transaction>::const_iterator it = transactions.begin(); it != transactions.end(); ++it) {
        const Transaction& transaction = *it;
        cout << "Description: " << transaction.description << endl;
        cout << "Amount: " << transaction.amount << endl;
        if (transaction.is_income) {
            cout << "Type: INCOME" << endl;
        } else {
            cout << "Type: EXPENSE" << endl;
        }
        cout << endl;
    }
}

double calculate_balance(const vector<Transaction>& transactions) {
    double balance = 0;
    for (vector<Transaction>::const_iterator it = transactions.begin(); it != transactions.end(); ++it) {
        const Transaction& transaction = *it;
        if (transaction.is_income) {
            balance += transaction.amount;
        } else {
            balance -= transaction.amount;
        }
    }
    return balance;
}

int main() {
    vector<Transaction> transactions;
    int choice;
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Add income" << endl;
        cout << "2. Add expense" << endl;
        cout << "3. View transaction history" << endl;
        cout << "4. View current balance" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;
        
        switch (choice) {
            case 1: {
                Transaction transaction;
                cout << "Enter income description: ";
                cin >> transaction.description;
                cout << "Enter income amount: ";
                cin >> transaction.amount;
                transaction.is_income = true;
                transactions.push_back(transaction);
                break;
            }
            case 2: {
                Transaction transaction;
                cout << "Enter expense description: ";
                cin >> transaction.description;
                cout << "Enter expense amount: ";
                cin >> transaction.amount;
                transaction.is_income = false;
                transactions.push_back(transaction);
                break;
            }
            case 3:
                display_transactions(transactions);
                break;
            case 4:
                cout << "Current balance: " << calculate_balance(transactions) << endl;
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        
    } while (choice != 5);

    return 0;
}

