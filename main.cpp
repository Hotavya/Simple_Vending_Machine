/*================================================
 11/01/19
 This program simulates a simple vending machine
 that sells chips, candy and soda. The user enters
 a number of quarters and then selects an option
 from the list of snacks availabe. If the money is
 adequate for the transaction, the item is dispensed
 otherwise the money is returned. The program keeps
 running until the user enter N. Closing info for
 the items is displayed as the program ends.
 =================================================*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#pragma warning(disable:4996)

using namespace std;

class Snack
{
    
private:
    string name;
    double price;
    int quantity;
    int itemsSold;
    string *ptr;
    
public:
    //DEFAULT CONSTRUCTOR
    Snack ()
    {
        name = " ";
        price = 0.00;
        quantity = 0;
        itemsSold = 0;
        ptr = nullptr;
    }
    
    //OVERLOADED CONSTRUCTOR
    Snack ( string n, double p, int q, int s = 0 )
    {
        name = n;
        price = p;
        quantity = q;
        itemsSold = s;
        ptr = new string [q];
    }
    
    //DESTRUCTOR
    ~Snack ()
    {
        cout <<"Closing info for " << name << endl;
        cout << quantity <<" in stock" << endl;
        cout << itemsSold <<" sold for a profit of $"
        << itemsSold * price << endl;
        cout << endl;
        if(itemsSold > 0){
            cout<<"Transactions occurred at: \n";
            for(int i =0; i< itemsSold; i++){
                cout<<ptr[i];
                cout<<endl;
            }
        }
        else
            cout<<endl;
        cout << endl;
        delete [] ptr;
        
    }
    
    /*================================================
     This function receives a double that representing
     the amount of money entered. It dispenses the item
     & returns true if the money is appropriate for
     transaction. If the money is not sufficient or
     the items are not in stock, then it displays
     message accordingly and returns false to the
     calling function.
     ================================================*/
    
    bool buyItem(double &moneyEntered)
    {
        if (moneyEntered >= price && quantity >= 1)
        {
            moneyEntered -= price;
            quantity -= 1;
            itemsSold += 1;
            cout <<"Item has been dispensed below" << endl;
            return true;
        }
        else if (quantity < 1)
        {
            cout <<"Error: Item is sold-out!" << endl;
            return false;
        }
        else
        {
            cout <<"Money Entered is not sufficient for transaction\n";
            return false;
        }
    }
    
    string getCurrentTime()
    {
        time_t t = time(0);
        struct tm ts;
        char buff[10];
        ts = *localtime(&t);
        strftime(buff, sizeof(buff), "%X", &ts);
        return buff;
    }
    
    //ACCESSOR AND MUTATOR FUNCTIONS
   void setName (string n)
    { name = n;}
   string getName () const
    { return name;}
    
   void setPrice (double p)
    { price = p;}
    double getPrice () const
    { return price;}
    
    void setQuantity (int q)
    { quantity = q;
      ptr = new string [q];}
    int getQuantity () const
    { return quantity;}
    
    int getitemsSold () const
    { return itemsSold;}
    
    string *getptr () const
    { return ptr;}
    
    
};

void displayVendingMachine(const Snack [], int);
int getQuarters();
void userBuyItem(Snack [], int);
bool promptToContinue();

int main ()
{
    cout << fixed << setprecision (2);
    const int ARR_SIZE = 3;
    Snack array [ARR_SIZE] = {Snack (),
                              Snack ("Candy", 1.25, 5),
                              Snack ("Soda", 1.00, 2)
                              };
    
    
    array [0].setName("Chips");
    array [0].setPrice (1.75);
    array [0].setQuantity (3);
    
    userBuyItem(array, ARR_SIZE);
    
    return 0;
}

/*==========================================
 This function displays the vending machine's
 contents in a formatted fashion. It accepts
 the array of snack objects and the number of
 elements in it. Function does not return
 anything.
============================================*/

void displayVendingMachine(const Snack array[], int size)
{
    cout <<"Welcome to the vending machine!\n" << endl;
    cout <<"Item #" <<"       " <<"Item Name" <<"       "
    <<"Price" <<"       " <<"# in - stock" << endl;
    
    cout <<"------------------------------------------------------" << endl;
    
    cout<<"1."<<setw(16)<<array[0].getName()<<setw(15);
    cout<<array[0].getPrice()<<setw(9)<<array[0].getQuantity()<<endl;
    cout<<"2."<<setw(16)<<array[1].getName()<<setw(15);
    cout<<array[1].getPrice()<<setw(9)<<array[1].getQuantity()<<endl;
    cout<<"3."<<setw(15)<<array[2].getName()<<setw(16);
    cout<<array[2].getPrice()<<setw(9)<<array[2].getQuantity()<<endl;
    
}

/*=======================================
 This function uses input validaiton and
 prompts the user to enter a number of
 quarters. Once a valid number is entered,
 an int value is returned.
 =========================================*/

int getQuarters()
{
    int quarters = 0;
 
    cout << endl;
    cout <<"Enter a number of quarters: ";
    cin >> quarters;
    cout << endl;
    
    while (quarters < 1)
    {
        cout <<"Please enter a number greater than 0" << endl;
        cout <<"Enter a number of quarters: ";
        cin >> quarters;
        
    }
    
    return quarters;
    
}

/*============================================
 This function accepts the array of snack
 objects and its size. It displays the vending
 machine and prompts the user to enter a number
 of quarters. The user is then prompted to enter
 a snack choice and the item is dispensed if the
 entered money is sufficient. It also displays
 a message if change is returned. The function
 does not return anything.
 =============================================*/

void userBuyItem(Snack array[], int size)
{
    bool choice;
    do
    {
        int num = 0;
        int index = 0;
    
        displayVendingMachine(array, size);
        int quarters = getQuarters();
        double amount = (quarters / 4) + ((quarters % 4 ) * 0.25);
    
        cout <<"Amount Entered: $" << amount << endl << endl;
    
        cout <<"Enter a number between 1 and 3 to make your selection: ";
        cin >> num;
        cout << endl;
    
        while (num < 1 || num > 3)
        {
            cout <<"Please enter a number between 1 and 3 to "
            << "make your selection: ";
            cin >> num;
        }
    
        bool a = array[num-1].buyItem(amount);
        
        if (a == true)
        {
            index = array[num-1].getitemsSold() - 1;
            array[num-1].getptr()[index] =
            array[num-1].getCurrentTime();
        }
    
        if (amount > 0)
            cout <<"$" << amount <<" dispensed below" << endl;
    
        choice = promptToContinue();
    } while (choice == true);
    
}

/*=====================================
This function asks the user if they wish
 to continue the program. It returns true
 if the user enters Y or y otherwise,
 returns false.
 ======================================*/

bool promptToContinue()
{
    char choice;
    bool a;

    cout << endl;
    cout << "Continue (Y/N): ";
    
    do
    {
        cin >> choice;
        cin.ignore();
        cout << endl;
        
        if (choice == 'y' || choice == 'Y')
            a = true;
        else if (choice == 'n' || choice == 'N')
            a = false;
        else
        {
            cout <<"Please enter a valid choice: " << endl;
        }
            
    } while (toupper (choice) != 'Y' && toupper (choice) != 'N');
    
    return a;

}

/******************************SAMPLE RUN*************************************
 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.             Chips               1.75        3
 2.             Candy              1.25        5
 3.             Soda                1.00        2

 Enter a number of quarters: -9

 Please enter a number greater than 0
 Enter a number of quarters: -6
 Please enter a number greater than 0
 Enter a number of quarters: -5
 Please enter a number greater than 0
 Enter a number of quarters: 0
 Please enter a number greater than 0
 Enter a number of quarters: 8
 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 9

 Please enter a number between 1 and 3 to make your selection: 7
 Please enter a number between 1 and 3 to make your selection: 9
 Please enter a number between 1 and 3 to make your selection: 3
 Item has been dispensed below
 $1.00 dispensed below

 Continue (Y/N): l

 Please enter a valid choice:
 k

 Please enter a valid choice:
 l

 Please enter a valid choice:
 j

 Please enter a valid choice:
 y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.             Chips                1.75        3
 2.             Candy               1.25        5
 3.             Soda                 1.00        1

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 3

 Item has been dispensed below
 $1.00 dispensed below

 Continue (Y/N): y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.             Chips               1.75        3
 2.             Candy              1.25        5
 3.             Soda                1.00        0

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 3

 Error: Item is sold-out!
 $2.00 dispensed below

 Continue (Y/N): y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.             Chips               1.75        3
 2.             Candy              1.25        5
 3.             Soda                1.00        0

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 3

 Error: Item is sold-out!
 $2.00 dispensed below

 Continue (Y/N): y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.             Chips               1.75        3
 2.             Candy              1.25        5
 3.             Soda                1.00        0

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 2

 Item has been dispensed below
 $0.75 dispensed below

 Continue (Y/N): y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.              Chips               1.75        3
 2.              Candy              1.25        4
 3.              Soda                1.00        0

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 1

 Item has been dispensed below
 $0.25 dispensed below

 Continue (Y/N): y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.             Chips               1.75         2
 2.             Candy              1.25         4
 3.             Soda                1.00         0

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 1

 Item has been dispensed below
 $0.25 dispensed below

 Continue (Y/N): y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.             Chips               1.75        1
 2.             Candy              1.25        4
 3.             Soda                1.00        0

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 1

 Item has been dispensed below
 $0.25 dispensed below

 Continue (Y/N): y

 Welcome to the vending machine!

 Item #       Item Name       Price       # in - stock
 ------------------------------------------------------
 1.              Chips               1.75        0
 2.              Candy              1.25        4
 3.              Soda                1.00        0

 Enter a number of quarters: 8

 Amount Entered: $2.00

 Enter a number between 1 and 3 to make your selection: 1

 Error: Item is sold-out!
 $2.00 dispensed below

 Continue (Y/N): n

 Closing info for Soda
 0 in stock
 2 sold for a profit of $2.00

 Transactions occurred at:
 20:53:33
 20:54:00

 Closing info for Candy
 4 in stock
 1 sold for a profit of $1.25

 Transactions occurred at:
 20:54:26

 Closing info for Chips
 0 in stock
 3 sold for a profit of $5.25

 Transactions occurred at:
 20:54:45
 20:54:50
 20:54:57

 Program ended with exit code: 0
 
*****************************************************************************************/
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

