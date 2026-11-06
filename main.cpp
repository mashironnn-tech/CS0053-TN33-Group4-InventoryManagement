#include <iostream>
#include <string>
#include <vector>

using namespace std;
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

// STARTER: The menu works. Replace TODO sections with your team's code.
// (void) marks unused inputs in placeholders. Remove it when you use the input.
struct Expense {
    int id = 0;
    string date;
    string category;
    double amount = 0.0;
    string description;
};
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
    file.close();
    if (file.fail()) {
        cerr << "Could not finish writing expenses.txt.\n";
        return false;
    }
    return true;
}

// MEMBER 1: Main program and menu.
int main() {
    vector<Expense> expenses;
    loadExpenses(expenses);
Expense readExpenseDetails() {
    Expense expense;
    string input;

    while (true) {
        string choice = showMenu();
        bool recordsChanged = false;
        if (!member3::readLine("Date (YYYY-MM-DD): ", input)) {
            return Expense{};
        }
        if (member3::validDate(input)) {
            expense.date = input;
            break;
        }
        cout << "Enter a real calendar date in YYYY-MM-DD format.\n";
    }

        if (choice == "0") {
            cout << "Goodbye!\n";
    while (true) {
        if (!member3::readLine("Category: ", input)) {
            return Expense{};
        }
        if (member3::validText(input)) {
            expense.category = input;
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
        cout << "Category cannot be empty.\n";
    }

        // Save only after an expense was added, updated, or deleted.
        if (recordsChanged) {
            bool saved = saveExpenses(expenses);
            if (!saved) {
                cout << "Could not save. Changes are only in memory.\n";
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

// MEMBER 2: View and display expenses.
void viewExpenses(const vector<Expense>& expenses) {
    (void)expenses;
    // TODO: Show an empty-list message, or call displayExpense() for each record.
    cout << "Member 2: View expenses is not implemented yet.\n";
}

void displayExpense(const Expense& expense) {
    (void)expense;
    // TODO: Print all fields. Show the PHP amount with two decimal places.
    cout << "Member 2: Display expense is not implemented yet.\n";
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
