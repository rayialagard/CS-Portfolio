#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    void LoadItemsFromFile(string fileName);
    void CreateBackupFile(string fileName);
    int GetItemFrequency(string itemName);
    void PrintAllFrequencies();
    void PrintHistogram();
};

// Reads grocery items from the input file and stores each item's frequency.
void GroceryTracker::LoadItemsFromFile(string fileName) {
    ifstream inputFile(fileName);
    string itemName;

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open input file." << endl;
        return;
    }

    while (inputFile >> itemName) {
        itemFrequency[itemName]++;
    }

    inputFile.close();
}

// Creates the frequency.dat backup file automatically.
void GroceryTracker::CreateBackupFile(string fileName) {
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        cout << "Error: Unable to create backup file." << endl;
        return;
    }

    for (const auto& pair : itemFrequency) {
        outputFile << pair.first << " " << pair.second << endl;
    }

    outputFile.close();
}

// Returns the frequency count for a specific grocery item.
int GroceryTracker::GetItemFrequency(string itemName) {
    if (itemFrequency.count(itemName) > 0) {
        return itemFrequency[itemName];
    }

    return 0;
}

// Prints each grocery item with its numeric frequency.
void GroceryTracker::PrintAllFrequencies() {
    for (const auto& pair : itemFrequency) {
        cout << pair.first << " " << pair.second << endl;
    }
}

// Prints each grocery item with a histogram using asterisks.
void GroceryTracker::PrintHistogram() {
    for (const auto& pair : itemFrequency) {
        cout << pair.first << " ";

        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }

        cout << endl;
    }
}

// Displays the user menu.
void DisplayMenu() {
    cout << "\n====================================" << endl;
    cout << "        CORNER GROCER MENU" << endl;
    cout << "====================================" << endl;
    cout << "1. Search for an item" << endl;
    cout << "2. Display all item frequencies" << endl;
    cout << "3. Display item frequency histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker;
    int userChoice = 0;
    string itemName;

    tracker.LoadItemsFromFile("CS210_Project_Three_Input_File.txt");
    tracker.CreateBackupFile("frequency.dat");

    while (userChoice != 4) {
        DisplayMenu();
        cin >> userChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 4." << endl;
            continue;
        }

        switch (userChoice) {
        case 1:
            cout << "Enter the item name to search for: ";
            cin >> itemName;

            cout << itemName << " was purchased "
                << tracker.GetItemFrequency(itemName)
                << " time(s)." << endl;
            break;

        case 2:
            cout << "\nItem Frequencies" << endl;
            cout << "----------------" << endl;
            tracker.PrintAllFrequencies();
            break;

        case 3:
            cout << "\nItem Frequency Histogram" << endl;
            cout << "------------------------" << endl;
            tracker.PrintHistogram();
            break;

        case 4:
            cout << "Thank you for using the Corner Grocer program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number from 1 to 4." << endl;
            break;
        }
    }

    return 0;
}