#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_PRODUCTS = 100;

// Color codes for terminal output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

struct Product {
    int id;
    char name[50];
    double price;
    int stockLevel;
};

// Function prototypes
void addProduct(Product* inventory, int& numProducts);
void deleteProduct(Product* inventory, int& numProducts);
void updateProduct(Product* inventory, int numProducts);
void displayInventory(Product* inventory, int numProducts);
void displayProduct(Product* inventory, int numProducts);
void searchProduct(Product* inventory, int numProducts);
void lowStockAlert(Product* inventory, int numProducts);
void writeToFile(Product* inventory, int numProducts);
void readFromFile(Product* inventory, int& numProducts);
void clearScreen();
void printHeader();
void printDivider(char symbol, int length);
void waitForEnter();

int main() {
    Product inventory[MAX_PRODUCTS];
    int numProducts = 0;
    int choice;

    readFromFile(inventory, numProducts);

    do {
        clearScreen();
        printHeader();
        
        cout << CYAN << "╔════════════════════════════════════════════════╗\n";
        cout << "║          MAIN MENU - SELECT OPTION            ║\n";
        cout << "╚════════════════════════════════════════════════╝\n" << RESET;
        
        cout << GREEN << "  1. " << RESET << "➕  Add New Product\n";
        cout << GREEN << "  2. " << RESET << "🗑️  Delete Product\n";
        cout << GREEN << "  3. " << RESET << "✏️  Update Product\n";
        cout << GREEN << "  4. " << RESET << "🔍 Search Product by ID\n";
        cout << GREEN << "  5. " << RESET << "📋 Display All Products\n";
        cout << GREEN << "  6. " << RESET << "⚠️  Low Stock Alert\n";
        cout << GREEN << "  7. " << RESET << "💾 Save & Exit\n";
        
        printDivider('-', 50);
        cout << YELLOW << "Enter your choice (1-7): " << RESET;
        
        // Input validation
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input! Please enter a number: " << RESET;
        }

        switch (choice) {
            case 1:
                clearScreen();
                printHeader();
                addProduct(inventory, numProducts);
                waitForEnter();
                break;
            case 2:
                clearScreen();
                printHeader();
                deleteProduct(inventory, numProducts);
                waitForEnter();
                break;
            case 3:
                clearScreen();
                printHeader();
                updateProduct(inventory, numProducts);
                waitForEnter();
                break;
            case 4:
                clearScreen();
                printHeader();
                searchProduct(inventory, numProducts);
                waitForEnter();
                break;
            case 5:
                clearScreen();
                printHeader();
                displayInventory(inventory, numProducts);
                waitForEnter();
                break;
            case 6:
                clearScreen();
                printHeader();
                lowStockAlert(inventory, numProducts);
                waitForEnter();
                break;
            case 7:
                clearScreen();
                writeToFile(inventory, numProducts);
                cout << GREEN << "\n✓ Thank you for using Inventory Management System!\n" << RESET;
                break;
            default:
                cout << RED << "\n✗ Invalid choice! Please enter a number from 1 to 7.\n" << RESET;
                waitForEnter();
                break;
        }

    } while (choice != 7);

    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader() {
    cout << BOLD << BLUE;
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║                                                  ║\n";
    cout << "║      📦 INVENTORY MANAGEMENT SYSTEM 📦          ║\n";
    cout << "║                                                  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << RESET << "\n";
}

void printDivider(char symbol, int length) {
    cout << CYAN;
    for (int i = 0; i < length; i++) {
        cout << symbol;
    }
    cout << RESET << "\n";
}

void waitForEnter() {
    cout << YELLOW << "\nPress Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void addProduct(Product* inventory, int& numProducts) {
    if (numProducts >= MAX_PRODUCTS) {
        cout << RED << "✗ Inventory is full! Cannot add more products.\n" << RESET;
        return;
    }

    Product newProduct;
    cout << CYAN << "➕ ADD NEW PRODUCT\n" << RESET;
    printDivider('=', 50);
    
    cout << "Enter Product ID: ";
    while (!(cin >> newProduct.id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input! Enter numeric ID: " << RESET;
    }

    // Check for duplicate ID
    for (int i = 0; i < numProducts; i++) {
        if (newProduct.id == inventory[i].id) {
            cout << RED << "✗ Product with ID " << newProduct.id << " already exists!\n" << RESET;
            return;
        }
    }

    cout << "Enter Product Name: ";
    cin.ignore();
    cin.getline(newProduct.name, 50);

    cout << "Enter Product Price: $";
    while (!(cin >> newProduct.price) || newProduct.price < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input! Enter positive price: $" << RESET;
    }

    cout << "Enter Stock Level: ";
    while (!(cin >> newProduct.stockLevel) || newProduct.stockLevel < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input! Enter non-negative quantity: " << RESET;
    }

    inventory[numProducts] = newProduct;
    numProducts++;

    cout << GREEN << "\n✓ Product added successfully!\n" << RESET;
}

void deleteProduct(Product* inventory, int& numProducts) {
    if (numProducts == 0) {
        cout << RED << "✗ Inventory is empty! No products to delete.\n" << RESET;
        return;
    }

    int productId;
    cout << CYAN << "🗑️ DELETE PRODUCT\n" << RESET;
    printDivider('=', 50);
    
    cout << "Enter Product ID to delete: ";
    while (!(cin >> productId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input! Enter numeric ID: " << RESET;
    }

    for (int i = 0; i < numProducts; i++) {
        if (productId == inventory[i].id) {
            cout << "\nProduct Found:\n";
            cout << "  Name: " << inventory[i].name << "\n";
            cout << "  Price: $" << fixed << setprecision(2) << inventory[i].price << "\n";
            
            char confirm;
            cout << YELLOW << "\nAre you sure you want to delete? (y/n): " << RESET;
            cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < numProducts - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                numProducts--;
                cout << GREEN << "\n✓ Product deleted successfully!\n" << RESET;
            } else {
                cout << YELLOW << "\n⊗ Deletion cancelled.\n" << RESET;
            }
            return;
        }
    }

    cout << RED << "\n✗ Product with ID " << productId << " not found!\n" << RESET;
}

void updateProduct(Product* inventory, int numProducts) {
    if (numProducts == 0) {
        cout << RED << "✗ Inventory is empty! No products to update.\n" << RESET;
        return;
    }

    int productId;
    cout << CYAN << "✏️ UPDATE PRODUCT\n" << RESET;
    printDivider('=', 50);
    
    cout << "Enter Product ID to update: ";
    while (!(cin >> productId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input! Enter numeric ID: " << RESET;
    }

    for (int i = 0; i < numProducts; i++) {
        if (productId == inventory[i].id) {
            cout << "\nCurrent Details:\n";
            cout << "  Name: " << inventory[i].name << "\n";
            cout << "  Price: $" << fixed << setprecision(2) << inventory[i].price << "\n";
            cout << "  Stock: " << inventory[i].stockLevel << "\n\n";

            char updateChoice;
            cout << "What would you like to update?\n";
            cout << "  1. Name\n  2. Price\n  3. Stock Level\n  4. All\n";
            cout << "Choice: ";
            cin >> updateChoice;

            cin.ignore();

            if (updateChoice == '1' || updateChoice == '4') {
                cout << "Enter new name: ";
                cin.getline(inventory[i].name, 50);
            }

            if (updateChoice == '2' || updateChoice == '4') {
                cout << "Enter new price: $";
                while (!(cin >> inventory[i].price) || inventory[i].price < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << RED << "Invalid! Enter positive price: $" << RESET;
                }
            }

            if (updateChoice == '3' || updateChoice == '4') {
                cout << "Enter new stock level: ";
                while (!(cin >> inventory[i].stockLevel) || inventory[i].stockLevel < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << RED << "Invalid! Enter non-negative quantity: " << RESET;
                }
            }

            cout << GREEN << "\n✓ Product updated successfully!\n" << RESET;
            return;
        }
    }

    cout << RED << "\n✗ Product with ID " << productId << " not found!\n" << RESET;
}

void displayInventory(Product* inventory, int numProducts) {
    if (numProducts == 0) {
        cout << RED << "✗ Inventory is empty!\n" << RESET;
        return;
    }

    cout << CYAN << "📋 COMPLETE INVENTORY\n" << RESET;
    printDivider('=', 80);
    
    cout << left << setw(8) << "ID" 
         << setw(25) << "Product Name" 
         << right << setw(12) << "Price" 
         << setw(15) << "Stock Level"
         << setw(15) << "Total Value" << "\n";
    printDivider('-', 80);

    double grandTotal = 0;
    for (int i = 0; i < numProducts; i++) {
        double totalValue = inventory[i].price * inventory[i].stockLevel;
        grandTotal += totalValue;
        
        // Color code based on stock level
        if (inventory[i].stockLevel < 10) {
            cout << RED;
        } else if (inventory[i].stockLevel < 50) {
            cout << YELLOW;
        } else {
            cout << GREEN;
        }
        
        cout << left << setw(8) << inventory[i].id 
             << setw(25) << inventory[i].name 
             << right << "$" << setw(11) << fixed << setprecision(2) << inventory[i].price
             << setw(15) << inventory[i].stockLevel
             << "$" << setw(14) << fixed << setprecision(2) << totalValue
             << RESET << "\n";
    }
    
    printDivider('=', 80);
    cout << BOLD << "Total Products: " << numProducts 
         << " | Grand Total Value: $" << fixed << setprecision(2) << grandTotal << RESET << "\n";
}

void searchProduct(Product* inventory, int numProducts) {
    if (numProducts == 0) {
        cout << RED << "✗ Inventory is empty!\n" << RESET;
        return;
    }

    int productId;
    cout << CYAN << "🔍 SEARCH PRODUCT\n" << RESET;
    printDivider('=', 50);
    
    cout << "Enter Product ID: ";
    while (!(cin >> productId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input! Enter numeric ID: " << RESET;
    }

    for (int i = 0; i < numProducts; i++) {
        if (productId == inventory[i].id) {
            cout << GREEN << "\n✓ Product Found!\n" << RESET;
            printDivider('-', 50);
            cout << "  Product ID:    " << inventory[i].id << "\n";
            cout << "  Product Name:  " << inventory[i].name << "\n";
            cout << "  Price:         $" << fixed << setprecision(2) << inventory[i].price << "\n";
            cout << "  Stock Level:   " << inventory[i].stockLevel << " units\n";
            cout << "  Total Value:   $" << fixed << setprecision(2) 
                 << (inventory[i].price * inventory[i].stockLevel) << "\n";
            printDivider('-', 50);
            
            if (inventory[i].stockLevel < 10) {
                cout << RED << "  ⚠️ WARNING: Low stock level!\n" << RESET;
            }
            return;
        }
    }

    cout << RED << "\n✗ Product with ID " << productId << " not found!\n" << RESET;
}

void lowStockAlert(Product* inventory, int numProducts) {
    if (numProducts == 0) {
        cout << RED << "✗ Inventory is empty!\n" << RESET;
        return;
    }

    cout << YELLOW << "⚠️  LOW STOCK ALERT (Stock < 10)\n" << RESET;
    printDivider('=', 80);

    bool foundLowStock = false;
    cout << left << setw(8) << "ID" 
         << setw(25) << "Product Name" 
         << right << setw(12) << "Price" 
         << setw(15) << "Stock Level" << "\n";
    printDivider('-', 80);

    for (int i = 0; i < numProducts; i++) {
        if (inventory[i].stockLevel < 10) {
            foundLowStock = true;
            cout << RED << left << setw(8) << inventory[i].id 
                 << setw(25) << inventory[i].name 
                 << right << "$" << setw(11) << fixed << setprecision(2) << inventory[i].price
                 << setw(15) << inventory[i].stockLevel << RESET << "\n";
        }
    }

    if (!foundLowStock) {
        cout << GREEN << "\n✓ All products have adequate stock levels!\n" << RESET;
    }
}

void writeToFile(Product* inventory, int numProducts) {
    ofstream outfile("inventory.txt");

    if (!outfile) {
        cout << RED << "✗ Error: Could not open file for writing!\n" << RESET;
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        outfile << inventory[i].id << "," 
                << inventory[i].name << "," 
                << inventory[i].price << "," 
                << inventory[i].stockLevel << "\n";
    }

    outfile.close();
    cout << GREEN << "✓ Inventory data saved successfully!\n" << RESET;
}

void readFromFile(Product* inventory, int& numProducts) {
    ifstream infile("inventory.txt");

    if (!infile) {
        return;
    }

    char buffer[100];
    while (infile.getline(buffer, 100)) {
        char* idString = strtok(buffer, ",");
        char* name = strtok(NULL, ",");
        char* priceString = strtok(NULL, ",");
        char* stockLevelString = strtok(NULL, ",");

        if (idString && name && priceString && stockLevelString) {
            Product newProduct;
            newProduct.id = atoi(idString);
            strcpy(newProduct.name, name);
            newProduct.price = atof(priceString);
            newProduct.stockLevel = atoi(stockLevelString);

            inventory[numProducts] = newProduct;
            numProducts++;
        }
    }

    infile.close();
}
