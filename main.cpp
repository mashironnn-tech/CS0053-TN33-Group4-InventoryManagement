        if (!member3::validRecord(expenses[i])) {
            cerr << "Could not save: an expense is invalid.\n";
            return false;
        }
        for (size_t j = 0; j < i; ++j) {
            if (expenses[i].id == expenses[j].id) {
                cerr << "Could not save: an expense has a duplicate ID.\n";
                return false;
            }
        }
    }
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

    ofstream file("expenses.txt", ios::trunc);
    if (!file) {
        cerr << "Could not open expenses.txt for writing.\n";
        return false;
    }
    file << setprecision(17);
    for (const Expense& expense : expenses) {
        file << expense.id << '\t' << quoted(expense.date) << '\t'
             << quoted(expense.category) << '\t' << expense.amount << '\t'
             << quoted(expense.description) << '\n';
    }

    file.close();
    if (file.fail()) {
        cerr << "Could not finish writing expenses.txt.\n";
        return false;
    }
    return true;
}

Expense readExpenseDetails() {
    Expense expense;
    string input;

    while (true) {
        if (!member3::readLine("Date (YYYY-MM-DD): ", input)) {
            return Expense{};
        }
        if (member3::validDate(input)) {
            expense.date = input;
            break;
        }
        cout << "Enter a real calendar date in YYYY-MM-DD format.\n";
    }

    while (true) {
        if (!member3::readLine("Category: ", input)) {
            return Expense{};
        }
        if (member3::validText(input)) {
            expense.category = input;
            break;
        }
        cout << "Category cannot be empty.\n";
    }

    while (true) {
        if (!member3::readLine("Amount (PHP): ", input)) {
            return Expense{};
        }
        istringstream amountInput(input);
        double amount = 0.0;
        if (amountInput >> amount) {
            amountInput >> ws;
            if (amountInput.eof() && isfinite(amount) && amount > 0.0) {
                expense.amount = amount;
                break;
            }
        }
        cout << "Enter a positive amount using a decimal point, such as 125.50.\n";
    }

    while (true) {
        if (!member3::readLine("Description: ", input)) {
            return Expense{};
        }
        if (member3::validText(input)) {
            expense.description = input;
            break;
        }
        cout << "Description cannot be empty.\n";
    }
    return choice;
}

// MEMBER 1: Add expense.
bool addExpense(vector<Expense>& expenses) {
    (void)expenses;
    // TODO: Call readExpenseDetails(), assign a unique ID, and add to the list.
    // Return true only after adding an expense.
    cout << "Member 1: Add expense is not implemented yet.\n";
    return false;
}

// MEMBER 2: View and display expenses.
void viewExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo expenses found.\n";
        return;
    }

    cout << "\n--- All Expense Records ---\n";
    for (const auto& expense : expenses) {
        displayExpense(expense);
    }
}

void displayExpense(const Expense& expense) {
    cout << "ID: " << expense.id << " | "
         << "Date: " << expense.date << " | "
         << "Category: " << expense.category << " | "
         << "Amount: PHP " << fixed << setprecision(2) << expense.amount << " | "
         << "Description: " << expense.description << "\n";
}

    return expense;
}

// MEMBER 4: Update and later delete expenses.
bool updateExpense(vector<Expense>& expenses) {
    (void)expenses;
    // TODO: Find by ID, read valid details, and edit the record. Keep its ID.
    // Return true only when a record changes. Handle missing IDs and empty lists.
    cout << "Member 4: Update expense is not implemented yet.\n";
    return false;
}

bool deleteExpense(vector<Expense>& expenses) {
    (void)expenses;
    // TODO LATER: Find by ID, confirm, then remove. Return true only after deletion.
    // This is the fifth feature required before submission.
    cout << "Member 4: Delete expense is not implemented yet.\n";
    return false;
}
