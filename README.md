# 📦 Inventory Management System

A feature-rich console-based **Inventory Management System** built in C++ that helps businesses efficiently manage their product inventory with an intuitive color-coded interface.

## ✨ Features

- ➕ **Add Products** - Add new products with ID, name, price, and stock level
- 🗑️ **Delete Products** - Remove products from inventory with confirmation
- ✏️ **Update Products** - Modify product details (name, price, or stock)
- 🔍 **Search Products** - Quick search by product ID
- 📋 **View Inventory** - Display all products in a formatted table
- ⚠️ **Low Stock Alerts** - Automatic alerts for products with stock < 10 units
- 💾 **Data Persistence** - Auto-save inventory data to file
- 🎨 **Color-Coded UI** - Visual indicators for stock levels
  - 🟢 Green: Stock ≥ 50 (Healthy)
  - 🟡 Yellow: 10 ≤ Stock < 50 (Moderate)
  - 🔴 Red: Stock < 10 (Critical)

## 📋 Prerequisites

- **C++ Compiler** (GCC, MinGW, or Visual Studio)
- **Operating System**: Windows, Linux, or macOS
- **C++ Standard**: C++11 or higher

## 🚀 Installation & Setup

### Step 1: Clone the Repository
```bash
git clone https://github.com/Iramfatima12/inventory-management-system.git
cd inventory-management-system
```

### Step 2: Compile the Program

#### On Windows (using MinGW):
```bash
g++ -o inventory_manager inventory_manager.cpp
```

#### On Linux/macOS:
```bash
g++ -std=c++11 -o inventory_manager inventory_manager.cpp
```

### Step 3: Run the Program
```bash
./inventory_manager
```

## 💻 Usage Guide

### Main Menu
When you run the program, you'll see an interactive menu:

```
╔══════════════════════════════════════════════════╗
║      📦 INVENTORY MANAGEMENT SYSTEM 📦          ║
╚══════════════════════════════════════════════════╝

╔════════════════════════════════════════════════╗
║          MAIN MENU - SELECT OPTION            ║
╚════════════════════════════════════════════════╝

  1. ➕  Add New Product
  2. 🗑️  Delete Product
  3. ✏️  Update Product
  4. 🔍 Search Product by ID
  5. 📋 Display All Products
  6. ⚠️  Low Stock Alert
  7. 💾 Save & Exit
```

### Adding a Product
1. Select option `1` from the main menu
2. Enter product details:
   - Product ID (unique integer)
   - Product Name
   - Price (positive decimal number)
   - Stock Level (non-negative integer)

### Viewing Inventory
Select option `5` to see all products in a formatted table:

```
ID      Product Name             Price      Stock Level    Total Value
--------------------------------------------------------------------------------
101     Laptop                   $899.99           25         $22499.75
102     Mouse                    $25.50            150        $3825.00
103     Keyboard                 $45.00            5          $225.00
================================================================================
Total Products: 3 | Grand Total Value: $26549.75
```

### Low Stock Alerts
Select option `6` to view products with critically low stock levels (< 10 units):

```
⚠️  LOW STOCK ALERT (Stock < 10)
================================================================================
ID      Product Name             Price      Stock Level
--------------------------------------------------------------------------------
103     Keyboard                 $45.00            5
```

## 📁 Project Structure

```
inventory-management-system/
│
├── inventory_manager.cpp      # Main source code
├── inventory.txt              # Data storage file (auto-generated)
├── README.md                  # Documentation
└── .gitignore                 # Git ignore file
```

## 🔧 Technical Details

### Data Structure
```cpp
struct Product {
    int id;                    // Unique product identifier
    char name[50];            // Product name (max 50 chars)
    double price;             // Product price
    int stockLevel;           // Current stock quantity
};
```

### File Format
Data is stored in `inventory.txt` using CSV format:
```
101,Laptop,899.99,25
102,Mouse,25.50,150
103,Keyboard,45.00,5
```

### Key Functions
- `addProduct()` - Adds new product with duplicate ID check
- `deleteProduct()` - Removes product with confirmation
- `updateProduct()` - Updates product details selectively
- `displayInventory()` - Shows all products with color coding
- `searchProduct()` - Finds product by ID
- `lowStockAlert()` - Displays low stock items
- `writeToFile()` - Saves data to file
- `readFromFile()` - Loads data from file

## 🎯 Features in Detail

### Input Validation
- Numeric validation for IDs, prices, and stock levels
- Duplicate ID prevention
- Negative value checks for prices and stock
- Invalid input handling with user-friendly error messages

### Color-Coded Display
The system uses ANSI color codes to enhance user experience:
- **Green**: Success messages and healthy stock
- **Yellow**: Warnings and moderate stock
- **Red**: Errors and critical stock levels
- **Cyan**: Headers and menu items
- **Blue**: Title and branding

### Data Persistence
- Automatic data loading on startup
- Manual save option
- Auto-save on exit
- CSV format for easy data migration

## 🐛 Known Issues & Solutions

### Issue: Colors not displaying on Windows
**Solution**: Use Windows Terminal or enable ANSI support:
```bash
reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
```

### Issue: File not found on first run
**Solution**: This is normal behavior. The program creates `inventory.txt` on first save.

## 🚀 Future Enhancements

- [ ] Add category management for products
- [ ] Implement user authentication
- [ ] Add sales tracking functionality
- [ ] Generate inventory reports (PDF/Excel)
- [ ] Add barcode scanning support
- [ ] Implement backup and restore features
- [ ] Add multi-language support
- [ ] Create GUI version using Qt or wxWidgets

## 📝 Version History

### Version 2.0 (Current)
- ✨ Enhanced UI with color coding
- ✨ Added low stock alert feature
- ✨ Improved input validation
- ✨ Better error handling
- ✨ Added product search functionality
- ✨ Confirmation prompts for delete operations

### Version 1.0
- Basic CRUD operations
- File-based data storage
- Simple console interface



- GitHub: https://github.com/Iramfatima12


⭐ **If you find this project helpful, please consider giving it a star!** ⭐

---

