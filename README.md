# restuarant-mangement-system
#Key Features:
1. Menu Management
Manages 5 categories of food: Chinese, Desi, Italian, FastFood, and Drinks
Each category stores menu items as a linked list with ID, name, and price
Supports adding, removing, updating, and searching menu items
Loads/saves menu data to/from a file (menu.txt)
2. Order Management
Uses a queue data structure to handle orders (FIFO - First In, First Out)
Orders include an order ID, list of items, and total price
Supports taking new orders, serving orders, canceling orders, and displaying pending orders
Saves/loads order data to/from a file (orders.txt)
3. Billing System
Uses a stack data structure for bill management (LIFO - Last In, First Out)
Allows adding items to bill, displaying bill with total, and saving bill to file (bill.txt)
4. Table Management
Manages reservations for 10 tables
Supports reserving tables for customers, freeing tables, showing available/reserved tables, and canceling reservations
5. Custom Utility Functions
Implements string manipulation functions (length, comparison, trimming, case conversion)
Converts strings to integers/floats without standard library functions
Uses ANSI color codes for colored console output
6. Main Interface
Provides a numbered menu system for all operations
Clears screen between operations for clean display
Saves all data when exiting the program
The program initializes with a default menu if no saved data exists, and persists all changes to files for data continuity between runs. It's designed as a complete backend system for restaurant operations.