#include <iostream>
#include <fstream>
using namespace std;
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

int stringLength(const char* str) 
{
    int length = 0;
    while (str[length] != '\0')
     {
        length++;
     }
    return length;
}
int stringLength(string str) 
{
    int length = 0;
    while (str[length] != '\0') 
    {
        length++;
    }
    return length;
}



char toLowerChar(char c) 
{
    if (c >= 'A' && c <= 'Z')
     {
        return c + 32;
     }
    return c;
}

string toLower(string str) 
{
    string result = "";
    int len = stringLength(str);
    for (int i = 0; i < len; i++) 
    {
        result = result + toLowerChar(str[i]);
    }
    return result;
}

bool stringCompare(string str1, string str2) 
{
    int len1 = stringLength(str1);
    int len2 = stringLength(str2);
    
    if (len1 != len2) 
     return false;
    
    for (int i = 0; i < len1; i++)
     {
        if (str1[i] != str2[i]) 
        {
            return false;
        }
     }
    return true;
}

string stringTrim(string str) 
{
    int start = 0;
    int end = stringLength(str) - 1;
    
    while (start < stringLength(str) && str[start] == ' ') 
    {
        start++;
    }
    
    while (end >= 0 && str[end] == ' ') 
    {
        end--;
    }
    
    if (start > end)
    {
        return "";
    }
    
    string result = "";
    for (int i = start; i <= end; i++)
     {
        result = result + str[i];
     }
    return result;
}

float stringToFloat(string str)
 {
    float result = 0.0;
    float decimal = 0.1;
    bool isDecimal = false;
    bool isNegative = false;
    int i = 0;
    
    if (str[0] == '-') 
    {
        isNegative = true;
        i = 1;
    }
    
    while (i < stringLength(str)) 
    {
        if (str[i] == '.')
         {
            isDecimal = true;
            i++;
            continue;
         }
        
        if (str[i] >= '0' && str[i] <= '9') 
        {
            if (isDecimal) 
            {
                result = result + (str[i] - '0') * decimal;
                decimal = decimal * 0.1;
            } 
            else 
            {
                result = result * 10 + (str[i] - '0');
            }
        }
        i++;
    }
    
    if (isNegative)
     {
        result = -result;
     }
    
    return result;
}

int stringToInt(string str) 
{
    int result = 0;
    bool isNegative = false;
    int i = 0;
    
    if (str[0] == '-') 
    {
        isNegative = true;
        i = 1;
    }
    
    while (i < stringLength(str)) 
    {
        if (str[i] >= '0' && str[i] <= '9') 
        {
            result = result * 10 + (str[i] - '0');
        }
        i++;
    }
    
    if (isNegative) 
    {
        result = -result;
    }
    
    return result;
}

class OrderItemNode 
{
public:
    string itemName;
    float itemPrice;
    OrderItemNode* next;
    
    OrderItemNode(string name, float price)
     {
        itemName = name;
        itemPrice = price;
        next = NULL;
     }
};


// MENU class
class MenuNode 
{
 public:
    int id;
    string name;
    float price;
    MenuNode* next;

    MenuNode(int i, string n, float p)
     {
        id = i;
        name = n;
        price = p;
        next = NULL;
     }
};

class Menu 
{
    MenuNode* head;

 public:
    Menu()
     {
      head = NULL;
     }

    void addMenuItem(int id, string name, float price) 
    {
        MenuNode* n = new MenuNode(id, name, price);
        if (!head)
         {
          head = n; 
          
         }
         else
         {
         MenuNode* t = head;
         while (t->next!=NULL) 
          t = t->next;
          t->next = n;
        }
    }

    bool removeMenuItem(int id)
     {
        if (!head) 
        return false;
        if (head->id == id) 
        {
            MenuNode* d = head;
            head = head->next;
            delete d;
            return true;
        }
        MenuNode* t = head;
        while (t->next && t->next->id != id) 
         t = t->next;
        if (!t->next) 
         return false;
        MenuNode* d = t->next;
         t->next = d->next;
         delete d;
         return true;
     }

    bool updateMenuItem(int id, string name, float price) 
    {
        MenuNode* t = head;
        while (t!=NULL)
         {
            if (t->id == id)
             {
                t->name = name;
                t->price = price;
                return true;
             }
            t = t->next;
         }
        return false;
    }

    void displayMenuItem() 
    {
        if (!head) 
        { 
         cout << RED << "(No items)\n" << RESET;
           return;
        }
        MenuNode* t = head;
        while (t)
         {
            cout << CYAN << "ID: " << t->id << RESET << " | " 
                 << GREEN << t->name << RESET << " | " 
                 << YELLOW << "Rs." << t->price << RESET << endl;
                 t = t->next;
         }
    }

    void displayItemByID(int id)
     {
        MenuNode* t = head;
        while (t!=NULL)
         {
            if (t->id == id)
             {
                cout << CYAN << "ID: " << t->id << RESET << " | " 
                     << GREEN << t->name << RESET << " | " 
                     << YELLOW << "Rs." << t->price << RESET << endl;
                        return;
             }
             t = t->next;
         }
        cout << RED << "Item not found!\n" << RESET;
     }

    void searchMenuItem(string name) 
    {
        MenuNode* t = head;
        bool found = false;
        string searchName = toLower(stringTrim(name));
        
        while (t!=NULL)                                   
         {
            if (stringCompare(toLower(t->name), searchName)) 
            {
                cout << CYAN << "ID: " << t->id << RESET << " | " 
                     << GREEN << t->name << RESET << " | " 
                     << YELLOW << "Rs." << t->price << RESET << endl;
                      found = true;
            }
            t = t->next;
         }
        if (!found)
         cout << RED << "Item not found!\n" << RESET;
    }

    MenuNode* getHead() 
    { 
    return head; 
    }
    
    float getPriceByName(string name)
     {
        MenuNode* t = head;
        string searchName = toLower(stringTrim(name));
        
        while (t) 
        {
            if (stringCompare(toLower(t->name), searchName)) 
            {
                return t->price;
            }
            t = t->next;
        }
        return -1;
     }
    
    MenuNode* findItemByName(string name)
     {
        MenuNode* t = head;
        string searchName = toLower(stringTrim(name));
        
        while (t)
         {
            if (stringCompare(toLower(t->name), searchName)) 
            {
                return t;
            }
            t = t->next;
         }
        return NULL;
     }
};


class OrderNode
{
 public:
    int orderId;
    OrderItemNode* itemsHead;
    float total;
    OrderNode* next;

    OrderNode(int i, OrderItemNode* items, float t) 
    {
        orderId = i;
        itemsHead = items;
        total = t;
        next = NULL;
    }
};

class OrderQueue 
{
    OrderNode* front;
    OrderNode* rear;

 public:
    OrderQueue() 
    { 
     front = rear = NULL; 
    }

    void takeOrder(int id, OrderItemNode* items, float total) 
    {
        addOrderNode(id, items, total);
        cout << GREEN << " Order Taken Successfully!\n" << RESET;
    }

    void addOrderNode(int id, OrderItemNode* items, float total) 
    {
        OrderNode* n = new OrderNode(id, items, total);
        if (!rear)
         front = rear = n;
        else
         { 
          rear->next = n; 
           rear = n; 
         }
    }

    void serveOrder() 
    {
        if (!front) 
        { 
         cout << YELLOW << "No pending orders!\n" << RESET;
          return;
        }
        OrderNode* d = front;
        cout << GREEN << "Serving Order ID: " << d->orderId << RESET << endl;
        
        OrderItemNode* item = d->itemsHead;
        while (item) 
        {
            OrderItemNode* temp = item;
            item = item->next;
            delete temp;
        }
        
        front = front->next;
        if (!front) 
         rear = NULL;
         delete d;
    }

    void displayPendingOrder() 
    {
        if (!front) 
        { 
         cout << YELLOW << "No pending orders!\n" << RESET; 
         return; 
        }
        OrderNode* t = front;
        cout << MAGENTA << "\n========= PENDING ORDERS ==========\n" << RESET;
        while (t) 
        {
            cout << CYAN << "OrderID: " << t->orderId << RESET << " | ";
            
            OrderItemNode* item = t->itemsHead;
            bool firstItem = true;
            while (item) 
            {
                if (!firstItem)
                 cout << ", ";
                 cout << GREEN << item->itemName << RESET;
                 firstItem = false;
                 item = item->next;
            }
            
            cout << " | " << YELLOW << "Rs." << t->total << RESET << endl;
             t = t->next;
        }
        cout << MAGENTA << "===============================================\n" << RESET;
    }

    bool cancelOrder(int orderId) 
    {
        if (!front) 
        { 
         cout << YELLOW << "No pending orders!\n" << RESET;
         return false; 
        }
        if (front->orderId == orderId) 
        {
            OrderNode* d = front;
            
            OrderItemNode* item = d->itemsHead;
            while (item) 
            {
                OrderItemNode* temp = item;
                item = item->next;
                delete temp;
            }
            
            front = front->next;
            if (!front) 
            rear = NULL;
            delete d;
            cout << RED << " Order ID " << orderId << " cancelled!\n" << RESET;
             return true;
        }
        OrderNode* t = front;
        while (t->next && t->next->orderId != orderId)
         t = t->next;
        if (!t->next) 
        {
          cout << RED << "Order ID not found!\n" << RESET;
            return false;
        }
        OrderNode* d = t->next;
        
        OrderItemNode* item = d->itemsHead;
        while (item)
         {
            OrderItemNode* temp = item;
            item = item->next;
            delete temp;
         }
        
        t->next = d->next;
        if (d == rear) 
         rear = t;
         delete d;
        cout << RED << " Order ID " << orderId << " cancelled!\n" << RESET;
         return true;
    }

    void saveOrderToFile() 
    {
        ofstream fout("orders.txt");
        OrderNode* t = front;
        while (t) 
        {
            fout << t->orderId << " " << t->total << " ";
            
            OrderItemNode* item = t->itemsHead;
            bool firstItem = true;
            while (item) 
            {
                if (!firstItem)
                 fout << ", ";
                 fout << item->itemName << ":" << item->itemPrice;
                 firstItem = false;
                 item = item->next;
            }
            fout << endl;
            t = t->next;
        }
        fout.close();
    }

    void loadOrderFromFile() 
    {
        ifstream fin("orders.txt");
        if (!fin) 
        return;

        string line = "";
        while (true) 
        {
            char ch = fin.get();
            if (fin.eof())
             break;
            
            if (ch == '\n' || ch == '\r') 
            {
                if (stringLength(line) > 0) 
                {
                    int id;
                    float total;
                    int firstSpace = -1;
                    int secondSpace = -1;
                    
                    for (int i = 0; i < stringLength(line); i++) 
                    {
                        if (line[i] == ' ')
                         {
                            firstSpace = i;
                            break;
                         }
                    }
                    
                    for (int i = firstSpace + 1; i < stringLength(line); i++) 
                    {
                        if (line[i] == ' ') 
                        {
                            secondSpace = i;
                            break;
                        }
                    }
                    
                    string idStr = "";
                    for (int i = 0; i < firstSpace; i++) 
                    {
                        idStr = idStr + line[i];
                    }
                    id = stringToInt(idStr);
                    
                    string totalStr = "";
                    for (int i = firstSpace + 1; i < secondSpace; i++) 
                    {
                        totalStr = totalStr + line[i];
                    }
                    total = stringToFloat(totalStr);
                    
                    OrderItemNode* itemsHead = NULL;
                    OrderItemNode* itemsTail = NULL;
                    
                    int pos = secondSpace + 1;
                    while (pos < stringLength(line)) 
                    {
                        int colonPos = -1;
                        int commaPos = -1;
                        
                        for (int i = pos; i < stringLength(line); i++) 
                        {
                            if (line[i] == ':') 
                            {
                                colonPos = i;
                                 break;
                            }
                        }
                        
                        if (colonPos == -1)
                         break;
                        
                        for (int i = colonPos; i < stringLength(line); i++) 
                        {
                            if (line[i] == ',') 
                            {
                                commaPos = i;
                                 break;
                            }
                        }
                        
                        string itemName = "";
                        for (int i = pos; i < colonPos; i++) 
                        {
                            itemName = itemName + line[i];
                        }
                        
                        string priceStr = "";
                        if (commaPos == -1) 
                        {
                            for (int i = colonPos + 1; i < stringLength(line); i++) 
                            {
                                priceStr = priceStr + line[i];
                            }
                            pos = stringLength(line);
                        } 
                        else
                         {
                            for (int i = colonPos + 1; i < commaPos; i++) 
                            {
                                priceStr = priceStr + line[i];
                            }
                            pos = commaPos + 2;
                         }
                        
                        float itemPrice = stringToFloat(priceStr);
                        
                        OrderItemNode* newItem = new OrderItemNode(itemName, itemPrice);
                        if (!itemsHead) 
                        {
                            itemsHead = itemsTail = newItem;
                        }
                         else 
                        {
                            itemsTail->next = newItem;
                            itemsTail = newItem;
                        }
                    }
                    
                    addOrderNode(id, itemsHead, total);
                }
                line = "";
            } 
             else 
            {
                line = line + ch;
            }
        }
        
        // Process last line if exists
        if (stringLength(line) > 0) 
        {
            int id;
            float total;
            int firstSpace = -1;
            int secondSpace = -1;
            
            for (int i = 0; i < stringLength(line); i++) 
            {
                if (line[i] == ' ') 
                {
                    firstSpace = i;
                    break;
                }
            }
            
            for (int i = firstSpace + 1; i < stringLength(line); i++) 
            {
                if (line[i] == ' ') 
                {
                    secondSpace = i;
                    break;
                }
            }
            
            string idStr = "";
            for (int i = 0; i < firstSpace; i++) 
            {
                idStr = idStr + line[i];
            }
            id = stringToInt(idStr);
            
            string totalStr = "";
            for (int i = firstSpace + 1; i < secondSpace; i++) 
            {
                totalStr = totalStr + line[i];
            }
            total = stringToFloat(totalStr);
            
            OrderItemNode* itemsHead = NULL;
            OrderItemNode* itemsTail = NULL;
            
            int pos = secondSpace + 1;
            while (pos < stringLength(line)) 
            {
                int colonPos = -1;
                int commaPos = -1;
                
                for (int i = pos; i < stringLength(line); i++) 
                {
                    if (line[i] == ':') 
                    {
                        colonPos = i;
                        break;
                    }
                }
                
                if (colonPos == -1)
                 break;
                
                for (int i = colonPos; i < stringLength(line); i++) 
                {
                    if (line[i] == ',')
                     {
                        commaPos = i;
                        break;
                     }
                }
                
                string itemName = "";
                for (int i = pos; i < colonPos; i++) 
                {
                    itemName = itemName + line[i];
                }
                
                string priceStr = "";
                if (commaPos == -1) 
                {
                    for (int i = colonPos + 1; i < stringLength(line); i++)
                     {
                        priceStr = priceStr + line[i];
                     }
                    pos = stringLength(line);
                } 
                else 
                {
                    for (int i = colonPos + 1; i < commaPos; i++) 
                    {
                        priceStr = priceStr + line[i];
                    }
                    pos = commaPos + 2;
                }
                
                float itemPrice = stringToFloat(priceStr);
                
                OrderItemNode* newItem = new OrderItemNode(itemName, itemPrice);
                if (!itemsHead) 
                {
                    itemsHead = itemsTail = newItem;
                } 
                else
                 {
                    itemsTail->next = newItem;
                    itemsTail = newItem;
                 }
            }
            
            addOrderNode(id, itemsHead, total);
        }
        
        fin.close();
    }
};


// BILL STACK
class BillNode 
{
 public:
    string name;
    float price;
    BillNode* next;

    BillNode(const string& n, float p)
     {
        name = n;
        price = p;
        next = NULL;
     }
};

class BillStack 
{
    BillNode* top;
 public:
    BillStack() 
    { 
     top = NULL; 
    }

    void addItemToBill(const string& name, float price) 
    {
        BillNode* n = new BillNode(name, price);
        n->next = top;
         top = n;
    }

    void removeLastItem() 
    {
        if (!top) 
        { 
         cout << YELLOW << "Bill Empty!\n" << RESET; 
         return; 
        }
        BillNode* d = top;
         top = top->next; 
         delete d;
    }

    float calculateTotal() 
    {
        float total = 0;
        BillNode* t = top;
        while (t) 
        {
         total += t->price; 
         t = t->next;
        }
        return total;
    }

    void displayBill() 
    {
        if (!top) 
        { 
         cout << YELLOW << "Bill Empty!\n" << RESET; 
         return; 
        }
        cout << MAGENTA << "\n========= BILL =========\n" << RESET;
        BillNode* t = top;
        int itemNumber = 1;
        while (t) 
        { 
            cout << CYAN << itemNumber << ". " << RESET
                 << GREEN << t->name << RESET << " | " 
                 << YELLOW << "Rs." << t->price << RESET << endl; 
            t = t->next;
            itemNumber++;
        }
        cout << MAGENTA << "=======================================================\n" << RESET;
        cout << BOLD << CYAN << "Total: Rs." << calculateTotal() << RESET << endl;
        cout << MAGENTA << "=======================================================\n" << RESET;
    }

    void saveBillToFile() 
    {
        ofstream fout("bill.txt");
        BillNode* t = top;
        while (t) 
        { 
         fout << t->name << " " << t->price << endl;
         t = t->next; 
        }
        fout << "Total " << calculateTotal();
        fout.close();
    }
    
    void clearBill() 
    {
        while (top) 
        {
            BillNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
};


// TABLE MANAGEMENT
class TableManagement 
{
    int tables[10];
    string customer[10];

 public:
    TableManagement()
     {
        for (int i = 0; i < 10; i++) 
        { 
          tables[i] = 0; customer[i] = ""; 
        }
     }

    void reserveTable(int tableNo) 
    {
        if (tableNo < 1 || tableNo > 10) 
        { 
            cout << RED << "Invalid table number!\n" << RESET; 
            return; 
        }
        if (tables[tableNo - 1] == 1) 
        { 
            cout << YELLOW << "Table already reserved by " << customer[tableNo-1] << "!\n" << RESET; 
            return; 
        }

        string name;
        cout << CYAN << "Enter customer name: " << RESET; 
        cin.ignore();
        
        name = "";
        while (true) 
        {
            char ch = cin.get();
            if (ch == '\n') 
             break;
            name = name + ch;
        }

        tables[tableNo - 1] = 1;
        customer[tableNo - 1] = name;
        cout << GREEN << " Table " << tableNo << " reserved successfully for " << name << ".\n" << RESET;
    }

    void freeTable(int tableNo) 
    {
        if (tableNo < 1 || tableNo > 10) 
        { 
            cout << RED << "Invalid table number!\n" << RESET; 
            return; 
        }
        if (tables[tableNo - 1] == 0) 
        { 
            cout << YELLOW << "Table is already free!\n" << RESET; 
            return; 
        }
        tables[tableNo - 1] = 0;
        customer[tableNo - 1] = "";
        cout << GREEN << "Table " << tableNo << " is now free.\n" << RESET;
    }

    void showAvailableTable() 
    {
        cout << CYAN << "Available tables: " << RESET;
        bool any = false;
        for (int i = 0; i < 10; i++) 
        {
            if (tables[i] == 0) 
            { 
                cout << GREEN << (i + 1) << " " << RESET; 
                any = true; 
            }
        }
        if (!any) 
        cout << YELLOW << "None" << RESET;
        cout << endl;
    }

    void cancelReservation(int tableNo) 
    {
        if (tableNo < 1 || tableNo > 10) 
        { 
            cout << RED << "Invalid table number!\n" << RESET; 
            return; 
        }
        if (tables[tableNo - 1] == 0) 
        { 
            cout << YELLOW << "Table is already free!\n" << RESET; 
            return; 
        }
        cout << RED << " Reservation for " << customer[tableNo-1] << " cancelled.\n" << RESET;
        tables[tableNo - 1] = 0;
        customer[tableNo - 1] = "";
    }

    void reservationWaste() 
    {
        cout << CYAN << "Reserved tables: " << RESET;
        bool any = false;
        for (int i = 0; i < 10; i++) 
        {
            if (tables[i] == 1) 
            { 
                cout << YELLOW << (i + 1) << " (" << customer[i] << ") " << RESET; 
                any = true; 
            }
        }
        if (!any) 
        cout << YELLOW << "None" << RESET;
        cout << endl;
    }
};


// FILE FUNCTIONS FOR MENU
void saveMenuToFile(Menu* menus)
 {
    ofstream fout("menu.txt");
    for (int c = 0; c < 5; c++) 
    {
        MenuNode* t = menus[c].getHead();
        while (t)
         {
            fout << c << " " << t->id << " " << t->price << endl;
            fout << t->name << endl;
            t = t->next;
         }
    }
    fout.close();
 }

void loadMenuFromFile(Menu* menus) 
{
    ifstream fin("menu.txt");
    if (!fin)
     return;

    string line1 = "";
    string line2 = "";
    
    while (true) 
    {
        
        line1 = "";
        while (true) 
        {
            char ch = fin.get();
            if (fin.eof() || ch == '\n' || ch == '\r') 
            break;
            line1 = line1 + ch;
        }
        
        if (line1 == "" || fin.eof())
         break;
        
        // Read second line (item name)
        line2 = "";
        while (true) 
        {
            char ch = fin.get();
            if (fin.eof() || ch == '\n' || ch == '\r') 
             break;
             line2 = line2 + ch;
        }
        
        // Parse first line: "category id price"
        int space1 = -1, space2 = -1;
        for (int i = 0; i < stringLength(line1); i++) 
        {
            if (line1[i] == ' ') 
            {
                if (space1 == -1) 
                 space1 = i;
                else space2 = i;
            }
        }
        
        if (space1 == -1 || space2 == -1) 
         continue;
        
        string catStr = "";
        for (int i = 0; i < space1; i++) 
        {
            catStr = catStr + line1[i];
        }
        
        string idStr = "";
        for (int i = space1 + 1; i < space2; i++) 
        {
            idStr = idStr + line1[i];
        }
        
        string priceStr = "";
        for (int i = space2 + 1; i < stringLength(line1); i++) 
        {
            priceStr = priceStr + line1[i];
        }
        
        int cat = stringToInt(catStr);
        int id = stringToInt(idStr);
        float price = stringToFloat(priceStr);
        
        // Trim the name
        string name = stringTrim(line2);
        
        if (stringLength(name) > 0) 
        {
            menus[cat].addMenuItem(id, name, price);
        }
        
        if (fin.eof())
         break;
    }
    fin.close();
}


// INITIALIZE DEFAULT MENU (CORRECTED SPELLING)

void initializeDefaultMenu(Menu* menus) 
{
    menus[0].addMenuItem(1, "Fried Rice", 350);
    menus[0].addMenuItem(2, "Chicken Manchurian", 450);
    menus[0].addMenuItem(3, "Chow Mein", 300);
    menus[0].addMenuItem(4, "Hot & Sour Soup", 200);
    menus[0].addMenuItem(5, "Spring Rolls", 250);
    
    menus[1].addMenuItem(1, "Chicken Biryani", 500);
    menus[1].addMenuItem(2, "Chicken Karahi", 800);
    menus[1].addMenuItem(3, "Haleem", 400);  
    menus[1].addMenuItem(4, "Nihari", 600);
    menus[1].addMenuItem(5, "Seekh Kabab", 350);
    
    menus[2].addMenuItem(1, "Pizza Margherita", 900);
    menus[2].addMenuItem(2, "Spaghetti Carbonara", 700);
    menus[2].addMenuItem(3, "Lasagna", 800);
    menus[2].addMenuItem(4, "Fettuccine Alfredo", 750);
    menus[2].addMenuItem(5, "Garlic Bread", 400);
    
    menus[3].addMenuItem(1, "Zinger Burger", 300);
    menus[3].addMenuItem(2, "French Fries", 200);
    menus[3].addMenuItem(3, "Club Sandwich", 250);
    menus[3].addMenuItem(4, "Chicken Shawarma", 350);  
    menus[3].addMenuItem(5, "Chicken Nuggets", 300);
    
    menus[4].addMenuItem(1, "Mineral Water", 100);
    menus[4].addMenuItem(2, "Fresh Lime", 200);
    menus[4].addMenuItem(3, "Coca Cola", 150);
    menus[4].addMenuItem(4, "Green Tea", 120);
    menus[4].addMenuItem(5, "Coffee", 180);
    
    saveMenuToFile(menus);
    cout << GREEN << " Default menu created with 5 items in each category!\n" << RESET;
}


// DISPLAY BANNER

void displayBanner() 
{
    cout << MAGENTA;
    cout << "=========================================================\n";
    cout << "" << BOLD << CYAN << "RESTAURANT MANAGEMENT SYSTEM" << RESET << MAGENTA<<"\n";
    cout << "==========================================================\n";
    cout << RESET;
}


  void displayMainMenu()
 {
    cout << "\n" << CYAN << BOLD << "MAIN MENU:\n" << RESET;
    cout << YELLOW << "1. " << RESET << "Display Menu\n";
    cout << YELLOW << "2. " << RESET << "Add Menu Item\n";
    cout << YELLOW << "3. " << RESET << "Remove Menu Item\n";
    cout << YELLOW << "4. " << RESET << "Update Menu Item\n";
    cout << YELLOW << "5. " << RESET << "Search Menu Item\n";
    cout << YELLOW << "6. " << RESET << "Take Order\n";
    cout << YELLOW << "7. " << RESET << "Serve Order\n";
    cout << YELLOW << "8. " << RESET << "Cancel Order\n";
    cout << YELLOW << "9. " << RESET << "Display Pending Orders\n";
    cout << YELLOW << "10. " << RESET << "Add Item to Bill\n";
    cout << YELLOW << "11. " << RESET << "Display Bill\n";
    cout << YELLOW << "12. " << RESET << "Save Bill\n";
    cout << YELLOW << "13. " << RESET << "Reserve Table\n";
    cout << YELLOW << "14. " << RESET << "Free Table\n";
    cout << YELLOW << "15. " << RESET << "Show Available Table\n";
    cout << YELLOW << "16. " << RESET << "Cancel Table Reservation\n";
    cout << YELLOW << "17. " << RESET << "Show Reserved Tables\n";
    cout << YELLOW << "0. " << RED << "Exit\n" << RESET;
    cout << MAGENTA << "====================================================\n" << RESET;
 }



void displayAllMenuItems(Menu* menus, string* cat) 
{
    cout << MAGENTA << "\n===================== FULL MENU ====================\n" << RESET;
    for (int i = 0; i < 5; i++) 
    {
        cout << BOLD << BLUE << "\n=====" << cat[i] << " ====\n" << RESET;
        menus[i].displayMenuItem();
    }
    cout << MAGENTA << "======================================================\n" << RESET;
}

// CUSTOM SPLIT FUNCTION 

void splitString(string input, string items[], int &count) 
{
    count = 0;
    int len = stringLength(input);
    int start = 0;
    
    for (int i = 0; i <= len; i++) 
    {
        if (i == len || input[i] == ',') 
        {
            string item = "";
            for (int j = start; j < i; j++) 
            {
                item = item + input[j];
            }
            
            item = stringTrim(item);
            if (stringLength(item) > 0) 
            {
                items[count] = item;
                count++;
            }
            start = i + 1;
        }
    }
}


// READ STRING INPUT

string readStringInput() 
{
    string input = "";
    
    while (true) 
    {
        char ch = cin.get();
        if (ch == '\n')
         break;
        input = input + ch;
    }
    
    return input;
}
// SEARCH ITEM IN ALL CATEGORIES

MenuNode* searchItemInAllCategories(Menu* menus, string itemName) 
{
    string searchName = toLower(stringTrim(itemName));
    
    for (int i = 0; i < 5; i++) 
    {
        MenuNode* t = menus[i].getHead();
        while (t) 
        {
            if (stringCompare(toLower(t->name), searchName)) 
            {
                return t;
            }
            t = t->next;
        }
    }
    return NULL;
}


// CHECK IF STRING CONTAINS "DONE"

bool containsDone(string input) 
{
    string inputLower = toLower(input);
    int len = stringLength(inputLower);
    
    for (int i = 0; i <= len - 4; i++) 
    {
        if (inputLower[i] == 'd' && 
            inputLower[i+1] == 'o' && 
            inputLower[i+2] == 'n' && 
            inputLower[i+3] == 'e') 
            {
             return true;
            }
    }
    return false;
}


int main() 
{
    Menu menus[5];
    OrderQueue orders;
    BillStack bill;
    TableManagement tables;
    string cat[5] =
     {
      "Chinese","Desi","Italian","FastFood","Drinks"
     
     };

    // Check if menu file exists and load it
    ifstream fin("menu.txt");
    if (!fin) 
    {
        initializeDefaultMenu(menus);
    } 
    else 
    {
        fin.close();
        loadMenuFromFile(menus);
        
        bool hasItems = false;
        for (int i = 0; i < 5; i++) 
        {
            if (menus[i].getHead() != NULL) 
            {
                hasItems = true;
                break;
            }
        }
        
        if (!hasItems) 
        {
            initializeDefaultMenu(menus);
        }
    }
    
    orders.loadOrderFromFile();

    int choice;
    while (true) 
    {
        system("clear || cls");
        displayBanner();
        displayMainMenu();
        
        cout << CYAN << "Enter your choice: " << RESET;
        cin >> choice;

        if (choice == 1) 
        {
            displayAllMenuItems(menus, cat);
        }
        else if (choice == 2) 
        {
            cout << MAGENTA << "\n============ADD MENU ITEM ==========\n" << RESET;
            int c, id; float price;
            string name; 
            for (int i = 0; i < 5; i++) 
            cout << YELLOW << i << ". " << cat[i] << RESET << endl;
            cout << CYAN << "Category: " << RESET; 
             cin >> c;
            cout << CYAN << "ID: " << RESET;
             cin >> id;
            cout << CYAN << "Name: " << RESET;
             cin.ignore();
            name = readStringInput();
            cout << CYAN << "Price: " << RESET; 
             cin >> price;
            menus[c].addMenuItem(id, name, price);
             saveMenuToFile(menus);
            cout << GREEN << " Menu item added successfully!\n" << RESET;
        }
        else if (choice == 3) 
        {
            cout << MAGENTA << "\n========== REMOVE MENU ITEM ===========\n" << RESET;
            int c, id;
            for (int i = 0; i < 5; i++) 
            
            cout << YELLOW << i << ". " << cat[i] << RESET << endl;
            cout << CYAN << "Category: " << RESET;
              cin >> c;
            cout << CYAN << "Item ID: " << RESET; 
             cin >> id;
            
            if (menus[c].removeMenuItem(id)) 
            {
                cout << GREEN << " Item Removed!\n" << RESET;
                 saveMenuToFile(menus);
            }
            else 
             cout << RED << "Item not found!\n" << RESET;
        }
        else if (choice == 4) 
        {
            cout << MAGENTA << "\n========== UPDATE MENU ITEM ===========\n" << RESET;
            int c, id; 
            float price; 
            string name;
            for (int i = 0; i < 5; i++) 
            cout << YELLOW << i << ". " << cat[i] << RESET << endl;
            cout << CYAN << "Category: " << RESET; 
             cin >> c;
            cout << CYAN << "ID: " << RESET; 
             cin >> id;
            cout << CYAN << "New Name: " << RESET;
             cin.ignore();
            name = readStringInput();
            cout << CYAN << "New Price: " << RESET; 
             cin >> price;
            if (menus[c].updateMenuItem(id, name, price)) 
            {
                cout << GREEN << " Item Updated!\n" << RESET;
                saveMenuToFile(menus);
            }
            else 
             cout << RED << "Item not found!\n" << RESET;
        }
        else if (choice == 5) 
        {
            cout << MAGENTA << "\n==========SEARCH MENU ITEM ==========\n" << RESET;
            int c; 
            string name;
            for (int i = 0; i < 5; i++) 
            cout << YELLOW << i << ". " << cat[i] << RESET << endl;
            cout << CYAN << "Category: " << RESET; 
             cin >> c;
            cout << CYAN << "Item Name: " << RESET;
             cin.ignore();
            name = readStringInput();
             menus[c].searchMenuItem(name);
        }
        else if (choice == 6) 
        {
            cout << MAGENTA << "\n========== TAKE ORDER ==========\n" << RESET;
            int id;
            cout << CYAN << "Order ID: " << RESET; 
             cin >> id;
            
            displayAllMenuItems(menus, cat);
            
            OrderItemNode* itemsHead = NULL;
            OrderItemNode* itemsTail = NULL;
            float total = 0;
            
            cout << MAGENTA << "\n =========== ADD ITEMS TO ORDER ========== \n" << RESET;
            cout << YELLOW << "Enter items one by one. Type 'done' when finished.\n" << RESET;
            cout << YELLOW << "You can enter multiple items separated by COMMAS ONLY.\n" << RESET;
            cout << YELLOW << "Example: fried rice, haleem, coca cola\n" << RESET;
            
            cin.ignore(); 
            
            while (true)
             {
                cout << CYAN << "Enter item name(s) (or 'done' to finish): " << RESET;
                string input = readStringInput();
                
                input = stringTrim(input);
                
                if (stringCompare(toLower(input), "done")) 
                {
                    break;
                }
                
                // Check if input contains "done" mixed with items
                if (containsDone(input)) 
                {
                    cout << RED << "Error: Please enter 'done' separately, not with items.\n" << RESET;
                     continue;
                }
                
                string items[20];
                int itemCount = 0;
                splitString(input, items, itemCount);
                
                if (itemCount == 0) 
                {
                    cout << YELLOW << "No valid items entered. Please try again.\n" << RESET;
                     continue;
                }
                
                bool allItemsFound = true;
                for (int i = 0; i < itemCount; i++) 
                {
                    string itemName = items[i];
                    itemName = stringTrim(itemName);
                    
                    if (stringLength(itemName) == 0) 
                     continue;
                    
                    MenuNode* foundItem = searchItemInAllCategories(menus, itemName);
                    
                    if (foundItem == NULL) 
                    {
                        cout << RED << "Item '" << itemName << "' not found in menu. Please try again.\n" << RESET;
                         allItemsFound = false;
                         break;
                    }
                    
                    OrderItemNode* newItem = new OrderItemNode(foundItem->name, foundItem->price);
                    if (!itemsHead) 
                    {
                        itemsHead = itemsTail = newItem;
                    } 
                    else 
                    {
                        itemsTail->next = newItem;
                        itemsTail = newItem;
                    }
                    
                    bill.addItemToBill(foundItem->name, foundItem->price);
                    total += foundItem->price;
                    
                    cout << GREEN << " Added '" << foundItem->name << "' (Rs." << foundItem->price << ") to order.\n" << RESET;
                }
                
                if (!allItemsFound) 
                {
                    // Clean up items that were added
                    OrderItemNode* temp = itemsHead;
                    while (temp) 
                    {
                        OrderItemNode* nextTemp = temp->next;
                        delete temp;
                        temp = nextTemp;
                    }
                    itemsHead = itemsTail = NULL;
                    total = 0;
                    
                    bill.clearBill();
                    
                    continue;
                }
                
                cout << YELLOW << "Current total: Rs." << total << "\n" << RESET;
            }
            
            if (itemsHead) 
            {
                orders.takeOrder(id, itemsHead, total);
                orders.saveOrderToFile();
                cout << GREEN << "Order saved successfully!\n" << RESET;
            } else 
            {
                cout << YELLOW << "No items added to order. Order cancelled.\n" << RESET;
            }
        }
        else if (choice == 7) 
        {
            cout << MAGENTA << "\n========== SERVE ORDER ==========\n" << RESET;
             orders.serveOrder();
             orders.saveOrderToFile();
        }
        else if (choice == 8) 
        {
            cout << MAGENTA << "\n========== CANCEL ORDER ==========\n" << RESET;
            int id; cout << CYAN << "Order ID to cancel: " << RESET; 
             cin >> id;
             orders.cancelOrder(id);
             orders.saveOrderToFile();
        }
        else if (choice == 9) 
         orders.displayPendingOrder();
        else if (choice == 10) 
        {
            cout << MAGENTA << "\n========== ADD ITEM TO BILL ==========\n" << RESET;
             string name;
             float price;
             cout << CYAN << "Item Name: " << RESET;
             cin.ignore();
             name = readStringInput();
             cout << CYAN << "Price: " << RESET;
               cin >> price;
             bill.addItemToBill(name, price);
             cout << GREEN << " Item added to bill!\n" << RESET;
        }
         else if (choice == 11) 
          bill.displayBill();
         else if (choice == 12)
         {
            bill.saveBillToFile();
            cout << GREEN << " Bill saved to file!\n" << RESET;
         }
        else if (choice == 13) 
        {
            cout << MAGENTA << "\n========== RESERVE TABLE ==========\n" << RESET;
            int t; cout << CYAN << "Table No to reserve (1-10): " << RESET;
             cin >> t;
             tables.reserveTable(t);
        }
        else if (choice == 14) 
        {
            cout << MAGENTA << "\n========== FREE TABLE ==========\n" << RESET;
            int t; 
            cout << CYAN << "Table No to free (1-10): " << RESET; 
             cin >> t;
             tables.freeTable(t);
        }
        else if (choice == 15) 
        {
            cout << MAGENTA << "\n========== AVAILABLE TABLES ==========\n" << RESET;
            tables.showAvailableTable();
        }
        else if (choice == 16) 
        {
            cout << MAGENTA << "\n========== CANCEL RESERVATION ==========\n" << RESET;
            int t; cout << CYAN << "Table No to cancel reservation (1-10): " << RESET; 
             cin >> t;
            tables.cancelReservation(t);
        }
        else if (choice == 17) 
        {
            cout << MAGENTA <<"\n========== RESERVED TABLES ==========\n" << RESET;
             tables.reservationWaste();
        }
        else if (choice == 0) 
        {
            saveMenuToFile(menus);
            orders.saveOrderToFile();
            cout << MAGENTA << "\n=====================================================\n" << RESET;
            cout << RED << BOLD << "Thank you for using Restaurant Management System!\n" << RESET;
            cout << GREEN << "Data saved successfully. Goodbye! \n" << RESET;
            cout << MAGENTA << "=======================================================\n" << RESET;
            break;
        }
        else 
        {
            cout << RED << "Invalid Choice! Please try again.\n" << RESET;
        }
        
         cout << "\n" << YELLOW << "Press Enter to continue..." << RESET;
         cin.ignore();
         cin.get();
    }

    return 0;
}