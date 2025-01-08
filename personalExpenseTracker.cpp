#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure to hold expense data
struct Expense {
    string date;
    string category;
    double amount;
};

// Function prototypes
void addExpense(vector<Expense> &expenses);
void viewExpenses(const vector<Expense> &expenses);
void saveExpenses(const vector<Expense> &expenses, const string &filename);
void loadExpenses(vector<Expense> &expenses, const string &filename);

int main() {
    vector<Expense> expenses;
    string filename = "expenses.txt";

    // Load expenses from file
    loadExpenses(expenses, filename);

    int choice;
    do {
        cout << "\nPersonal Expense Tracker\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                saveExpenses(expenses, filename);
                cout << "Expenses saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

// Add a new expense
void addExpense(vector<Expense> &expenses) {
    Expense newExpense;

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> newExpense.date;
    cout << "Enter category (e.g., Food, Transport): ";
    cin >> newExpense.category;
    cout << "Enter amount: ";
    cin >> newExpense.amount;

    expenses.push_back(newExpense);
    cout << "Expense added successfully.\n";
}

// View all expenses
void viewExpenses(const vector<Expense> &expenses) {
    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }

    cout << "\nDate        | Category       | Amount\n";
    cout << "-------------------------------------\n";
    for (const auto &expense : expenses) {
        cout << left << setw(12) << expense.date
             << "| " << setw(15) << expense.category
             << "| " << fixed << setprecision(2) << expense.amount << "\n";
    }
}

// Save expenses to a file
void saveExpenses(const vector<Expense> &expenses, const string &filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error saving to file.\n";
        return;
    }

    for (const auto &expense : expenses) {
        outFile << expense.date << " " << expense.category << " " << expense.amount << "\n";
    }

    outFile.close();
}

// Load expenses from a file
void loadExpenses(vector<Expense> &expenses, const string &filename) {
    ifstream inFile(filename);

    if (!inFile) {
        return; // No file to load, start fresh
    }

    Expense expense;
    while (inFile >> expense.date >> expense.category >> expense.amount) {
        expenses.push_back(expense);
    }

    inFile.close();
}
