#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// STARTER: The menu works. Replace TODO sections with your team's code.
// (void) marks unused inputs in placeholders. Remove it when you use the input.
struct Expense {
    int id = 0;
    string date;
    string category;
    double amount = 0.0;
    string description;
};

// Function declarations: agree as a team before changing these.
// & shares the original list; const means the function cannot change it.
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
        } else if (choice == "1") {
            recordsChanged = addExpense(expenses);
        } else if (choice == "2") {
            viewExpenses(expenses);
        } else if (choice == "3") {
            searchExpenses(expenses);
        } else if (choice == "4") {
            recordsChanged = updateExpense(expenses);
        } else if (choice == "5") {
            recordsChanged = deleteExpense(expenses);
        } else {
            cout << "Invalid choice. Enter 0 to 5.\n";
        }

        // Save only after an expense was added, updated, or deleted.
        if (recordsChanged) {
            bool saved = saveExpenses(expenses);
            if (!saved) {
                cout << "Could not save. Changes are only in memory.\n";
            }
        }
    }

    return 0;
}

string showMenu() {
    cout << "\n=== Personal Expense Tracker ===\n";
    cout << "1. Add expense\n";
    cout << "2. View expenses\n";
    cout << "3. Search expenses\n";
    cout << "4. Update expense\n";
    cout << "5. Delete expense (later)\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";

    string choice;
    if (!getline(cin, choice)) {
        return "0"; // Exit if input ends.
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

// MEMBER 3: Search, storage, and input validation.
void searchExpenses(const vector<Expense>& expenses) {
    (void)expenses;
    // TODO: Ask for a category. Display matching records or a no-results message.
    cout << "Member 3: Search expenses is not implemented yet.\n";
}

void loadExpenses(vector<Expense>& expenses) {
    (void)expenses;
    // TODO: Read expenses.txt. Missing file means an empty list; report bad data.
    cout << "Member 3: Loading expenses is not implemented yet.\n";
}

bool saveExpenses(const vector<Expense>& expenses) {
    (void)expenses;
    // TODO: Write expenses.txt using the same format as loadExpenses().
    // Return true only when the file was saved successfully.
    cout << "Member 3: Saving expenses is not implemented yet.\n";
    return false;
}

Expense readExpenseDetails() {
    // TODO: Ask for a valid date, nonempty category/description, and positive amount.
    // Retry invalid input; handle input ending without looping forever.
    // Add assigns the ID; update keeps the original ID. Do not use this stub yet.
    cout << "Member 3: Reading expense details is not implemented yet.\n";
    Expense expense;
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
