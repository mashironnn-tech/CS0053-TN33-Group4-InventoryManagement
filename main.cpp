#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <cctype>
#include <filesystem>
#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Expense {
    int id = 0;
    string date;
    string category;
    double amount = 0.0;
    string description;
};

string showMenu();
bool addExpense(vector<Expense>& expenses);                    // Member 1
void viewExpenses(const vector<Expense>& expenses);            // Member 2
void displayExpense(const Expense& expense);                   // Member 2
void searchExpenses(const vector<Expense>& expenses);          // Member 3
void loadExpenses(vector<Expense>& expenses);                  // Member 3
bool saveExpenses(const vector<Expense>& expenses);            // Member 3
Expense readExpenseDetails();                                 // Member 3
bool updateExpense(vector<Expense>& expenses);                 // Member 4
bool deleteExpense(vector<Expense>& expenses);                 // Member 4

// MEMBER 1: Main program and menu.
int main() {
    vector<Expense> expenses;
    loadExpenses(expenses);
    while (true) {
        string choice = showMenu();
        bool recordsChanged = false;
        if (choice == "0") {
            cout << "Goodbye!\n";
            break;
        } else if (choice == "1") recordsChanged = addExpense(expenses);
        else if (choice == "2") viewExpenses(expenses);
        else if (choice == "3") searchExpenses(expenses);
        else if (choice == "4") recordsChanged = updateExpense(expenses);
        else if (choice == "5") recordsChanged = deleteExpense(expenses);
        else cout << "Invalid choice. Enter 0 to 5.\n";
        if (recordsChanged && !saveExpenses(expenses))
            cout << "Could not save. Changes are only in memory.\n";
    }
    return 0;
}

// Helper for visual separation and pausing before returning to menu
void printDivider(char ch = '-', int width = 76) {
    cout << string(width, ch) << "\n";
}

void pauseScreen() {
    cout << "\nPress Enter to return to the menu...";
    string dummy;
    getline(cin, dummy);
}

// MEMBER 1: Menu UI
string showMenu() {
    cout << "\n";
    printDivider('=', 44);
    cout << "         PERSONAL EXPENSE TRACKER\n";
    printDivider('=', 44);
    cout << "  [1] Add Expense\n"
         << "  [2] View All Expenses\n"
         << "  [3] Search Expenses by Category\n"
         << "  [4] Update an Expense\n"
         << "  [5] Delete an Expense\n"
         << "  [0] Exit\n";
    printDivider('-', 44);
    cout << "Choose an option: ";

    string choice;
    if (!getline(cin, choice)) return "0";
    return choice;
}

// MEMBER 1: Add expense.
bool addExpense(vector<Expense>& expenses) {
    int nextId = 1;

    // Find an unused ID without assuming the list is sorted.
    for (const Expense& existing : expenses) {
        if (existing.id == numeric_limits<int>::max()) {
            cout << "Cannot add an expense: the ID limit was reached.\n";
            return false;
        }

        if (existing.id >= nextId) {
            nextId = existing.id + 1;
        }
    }

    Expense expense = readExpenseDetails();

    if (!cin) {
        cout << "Adding expense cancelled.\n";
        return false;
    }

    // Reject cancellation or an incomplete returned record.
    if (expense.date.empty() ||
        expense.category.empty() ||
        expense.description.empty() ||
        !isfinite(expense.amount) ||
        expense.amount <= 0.0) {
        cout << "Expense was not added: valid details are required.\n";
        return false;
    }

    expense.id = nextId;
    expenses.push_back(expense);

    cout << "Expense added successfully. ID: " << expense.id << "\n";
    return true;
}

// MEMBER 2: Table Header, Row Display, and Summary of expenses.
void printTableHeader() {
    cout << "\n";
    printDivider('=', 78);
    cout << left
         << setw(6)  << "ID"
         << setw(13) << "DATE"
         << setw(16) << "CATEGORY"
         << right << setw(14) << "AMOUNT (PHP)"
         << "   " << left << "DESCRIPTION\n";
    printDivider('-', 78);
}

void displayExpense(const Expense& expense) {
    // Truncate long descriptions cleanly so table rows never wrap awkwardly
    string desc = expense.description;
    if (desc.length() > 26) {
        desc = desc.substr(0, 23) + "...";
    }

    cout << left
         << setw(6)  << expense.id
         << setw(13) << expense.date
         << setw(16) << expense.category.substr(0, 14)
         << right << setw(14) << fixed << setprecision(2) << expense.amount
         << "   " << left << desc << "\n";
}

void viewExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\n[INFO] No expense records found.\n";
        pauseScreen();
        return;
    }

    printTableHeader();
    double total = 0.0;
    for (const auto& expense : expenses) {
        displayExpense(expense);
        total += expense.amount;
    }
    printDivider('-', 78);
    cout << right << setw(35) << "TOTAL EXPENSES: "
         << setw(14) << fixed << setprecision(2) << total << " PHP"
         << " (" << expenses.size() << " item" << (expenses.size() == 1 ? "" : "s") << ")\n";
    printDivider('=', 78);

    pauseScreen();
}

// MEMBER 3: Search, storage, and input validation.
bool validText(const string& text) {
    return text.find_first_not_of(" \t\r\n") != string::npos;
}

bool validDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (size_t i = 0; i < date.size(); ++i)
        if (i != 4 && i != 7 && !isdigit(static_cast<unsigned char>(date[i]))) return false;
    int year = stoi(date.substr(0, 4)), month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (year == 0 || month < 1 || month > 12) return false;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) days[1] = 29;
    return day >= 1 && day <= days[month - 1];
}

void searchExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses found.\n";
        return;
    }
    string category;
    cout << "Category to search: ";
    if (!getline(cin, category)) return;
    bool found = false;
    for (const Expense& expense : expenses) {
        if (expense.category == category) {
            displayExpense(expense);
            found = true;
        }
    }
    if (!found) cout << "No expenses found for that category.\n";
}

// A failed load must never be followed by overwriting the original file.
bool storageAvailable = true;
void loadExpenses(vector<Expense>& expenses) {
    error_code error;
    bool exists = filesystem::exists("expenses.txt", error);
    if (error) {
        cerr << "Could not check expenses.txt: " << error.message() << "\n";
        storageAvailable = false;
        return;
    }
    if (!exists) return;
    ifstream file("expenses.txt");
    if (!file) {
        cerr << "Could not open expenses.txt for reading.\n";
        storageAvailable = false;
        return;
    }
    vector<Expense> loaded;
    string line;
    while (getline(file, line)) {
        istringstream input(line);
        Expense expense;
        if (!(input >> expense.id >> quoted(expense.date) >> quoted(expense.category)
                    >> expense.amount >> quoted(expense.description)) ||
            expense.id <= 0 || !validDate(expense.date) || !validText(expense.category) ||
            !validText(expense.description) || !isfinite(expense.amount) || expense.amount <= 0) {
            cerr << "Invalid data in expenses.txt; saving is disabled.\n";
            storageAvailable = false;
            return;
        }
        input >> ws;
        if (!input.eof()) {
            cerr << "Invalid data in expenses.txt; saving is disabled.\n";
            storageAvailable = false;
            return;
        }
        for (const Expense& previous : loaded) {
            if (previous.id == expense.id) {
                cerr << "Duplicate ID in expenses.txt; saving is disabled.\n";
                storageAvailable = false;
                return;
            }
        }
        loaded.push_back(expense);
    }
    if (file.bad()) {
        cerr << "Could not read expenses.txt; saving is disabled.\n";
        storageAvailable = false;
        return;
    }
    expenses = loaded;
}

bool saveExpenses(const vector<Expense>& expenses) {
    if (!storageAvailable) return false;
    ofstream file("expenses.txt.tmp", ios::trunc);
    if (!file) {
        cerr << "Could not open temporary file for writing.\n";
        return false;
    }
    file << setprecision(17);
    for (const Expense& expense : expenses)
        file << expense.id << '\t' << quoted(expense.date) << '\t'
             << quoted(expense.category) << '\t' << expense.amount << '\t'
             << quoted(expense.description) << '\n';
    file.close();
    if (file.fail()) {
        cerr << "Could not finish writing temporary file.\n";
        return false;
    }
#ifdef _WIN32
    if (!MoveFileExA("expenses.txt.tmp", "expenses.txt", MOVEFILE_REPLACE_EXISTING)) {
#else
    if (rename("expenses.txt.tmp", "expenses.txt") != 0) {
#endif
        cerr << "Could not replace expenses.txt; original file was kept.\n";
        return false;
    }
    return true;
}

Expense readExpenseDetails() {
    Expense expense;
    string input;
    while (true) {
        cout << "Date (YYYY-MM-DD): ";
        if (!getline(cin, input)) return Expense{};
        if (validDate(input)) { expense.date = input; break; }
        cout << "Enter a real calendar date in YYYY-MM-DD format.\n";
    }
    while (true) {
        cout << "Category: ";
        if (!getline(cin, expense.category)) return Expense{};
        if (validText(expense.category)) break;
        cout << "Category cannot be empty.\n";
    }
    while (true) {
        cout << "Amount (PHP): ";
        if (!getline(cin, input)) return Expense{};
        istringstream amountInput(input);
        if (amountInput >> expense.amount) {
            amountInput >> ws;
            if (amountInput.eof() && isfinite(expense.amount) && expense.amount > 0) break;
        }
        cout << "Enter a positive amount, such as 125.50.\n";
    }
    while (true) {
        cout << "Description: ";
        if (!getline(cin, expense.description)) return Expense{};
        if (validText(expense.description)) break;
        cout << "Description cannot be empty.\n";
    }
    return expense;
}

// MEMBER 4: Update and later delete expenses.
bool updateExpense(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo expenses available to update.\n";
        return false;
    }

    cout << "Enter the ID of the expense to update: ";
    int targetId;
    if (!(cin >> targetId)) {
        cin.clear();
        cin.ignore(10000, '\n'); // Clear invalid input
        cout << "Invalid ID format.\n";
        return false;
    }
    cin.ignore(10000, '\n'); // Clear the newline character from the buffer

    for (auto& expense : expenses) {
        if (expense.id == targetId) {
            cout << "Found expense ID " << targetId << ". Enter new details:\n";
            
            // Reuse Member 3's function to get validated input
            Expense updatedData = readExpenseDetails();
            
            // Basic check to see if readExpenseDetails was cancelled/failed
            if (updatedData.date.empty() || updatedData.category.empty()) { 
                cout << "Update cancelled: valid details are required.\n";
                return false;
            }

            // Keep the original ID, apply the new details
            updatedData.id = expense.id;
            expense = updatedData;
            
            cout << "Expense updated successfully.\n";
            return true;
        }
    }

    cout << "Update failed: Expense with ID " << targetId << " not found.\n";
    return false;
}

bool deleteExpense(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo expenses available to delete.\n";
        return false;
    }

    cout << "Enter the ID of the expense to delete: ";
    int targetId;
    if (!(cin >> targetId)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid ID format.\n";
        return false;
    }
    cin.ignore(10000, '\n');

    for (auto it = expenses.begin(); it != expenses.end(); ++it) {
        if (it->id == targetId) {
            expenses.erase(it);
            cout << "Expense ID " << targetId << " deleted successfully.\n";
            return true;
        }
    }

    cout << "Delete failed: Expense with ID " << targetId << " not found.\n";
    return false;
}