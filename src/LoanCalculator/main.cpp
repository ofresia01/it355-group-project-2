#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Loan.h"
#include <limits>
using namespace std;

/*
Doesn't directly manipulate buffers in a way that could cause overflow. Conforms to CWE-121.
Properly checks and limits array accesses, ensuring they don't exceed the array size, prevent out-of-bounds reads. Conforms to CWE-125.
Properly validates array indexes to prevent out-of-bounds accesses. Conforms to CWE-129.
Doesn't perform conversions between signed and unsigned types in a way that could lead to errors due to differing sizes. Conforms to CWE-196.
The sizeof() operator references the size of the object rather than the pointer. Ensuring correct size is determined Conforms to CWE-467.
Ensures that bitwise operations stay within the bounds of integer primitives, preventing incorrect bitwise shifts. Conforms to CWE-1335.
Classes aren't cloneable, preventing sensitive data leakage. Conforms to CWE-498.
Pointers are initialized before dereferencing them, avoiding NULL pointer dereference issues. Conforms to CWE-476.
Public methods return copies or immutable views of private data structures, preventing direct access to sensitive information. Conforms to CWE-495.

Ensures that user input is properly validated and sanitized before any write operations are performed. Conforms to CWE-123.
Properly manages buffer accesses and ensures that no index or pointer to the buffer references a left-hand-side out-of-bounds location. Conforms to CWE-124.
Handles parsed messages/structures with variable length attributes appropriately. Conforms to CWE-130.
Restricts all access to an item after it has been deallocated. Conforms to CWE-416
Ensures that any memory is only able to be freed once. Conforms to CWE-415.
Ensures that resources are released only once. Conforms to CWE-1341.
*/

// Clears the console screen
void clearConsole()
{
    cout << "\033[2J\033[1;1H";
}

// Pauses and waits for user input to continue
void anythingToContinue()
{
    cout << "\nPress enter to continue...";
    cin.clear();                                                   // Clear any error flags
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining characters in the buffer
    cin.get();                                                     // Wait for user to press enter
}

// Converts string input to integer
int convertInput(string inString)
{
    int output;
    try
    {
        output = stoi(inString);
    }
    catch(std::invalid_argument const& e)
    {
        return -1; // Return -1 if conversion fails
    }
    catch(std::out_of_range const& e)
    {
        return -1; // Return -1 if conversion result is out of range
    }

    return output;
    
}

// Converts string input to double
double convertInputToDouble(string inString)
{
    double output;
    try
    {
        output = stod(inString);
    }
    catch(std::invalid_argument const& e)
    {
        return -1; // Return -1 if conversion fails
    }
    catch(std::out_of_range const& e)
    {
        return -1;  // Return -1 if conversion result is out of range
    }

    return output;
}

int main()
{
    clearConsole();
    cout << "Welcome to your loan calculator." << endl;

    // Open file to read existing loan holders
    ifstream infile;
    infile.open("LoanHolders.txt");
    string line;

    // Vector to store existing loan holders and loans
    vector<Person> people;
    vector<Loan> loans;

    // Read existing loan holders from file
    while (getline(infile, line))
    {
        istringstream iss(line);
        string name;
        int age;
        getline(iss, name, ',') >> age;
        Person person(name, age);
        people.push_back(person);
    }
    infile.close();

    // Display current loan holders
    cout << "Current Loan Holders:" << endl;
    for (const auto &person : people)
    {
        cout << "Name: " << person.getName() << endl;
        cout << "Age: " << person.getAge() << endl;
        cout << endl;
    }
    anythingToContinue();

    int choice;
    string input;
    // Main menu loop
    do
    {
        clearConsole();
        // Display menu options
        cout << "Please select your choice:\n1: Create a new loanholder\n2: Create a new loan\n3: Print loan information\n4: Make a loan payment\n5: Exit" << endl;
        cout << "Enter your choice here: ";
        cin >> input;
        choice = convertInput(input);

        // Process user choice
        switch (choice)
        {
        case 1:
        {
            // Creating a new loan holder
            clearConsole();
            cout << "Current Action: Creating a new loan holder" << endl;
            cout << "Please enter loan holder's age: ";
            int age;
            string name;
            cin >> input;
            age = convertInput(input);
            if (age < 0 || age > 100)
            {
                // Validate age input
                while (age > 100 || age <= 0)
                {
                    cout << "You have entered an invalid age. Please enter a valid age(1-99) here: ";
                    cin >> input;
                    age = convertInput(input);
                }
            }
            if (age < 18 && age >= 0)
            {
                // Inform user about age restriction
                cout << "We do not allow minors to take on loans. Our apologies." << endl;
                anythingToContinue();
            }
            else
            {
                // Get name of new loan holder
                cin.ignore();
                cout << "Please enter loan holder's name here: ";
                getline(cin, name);
            }
            // Create new Person object and add to vector
            Person person(name, age);
            people.push_back(person);
            break;
        }
        case 2:
        {
            // Creating a new loan
            clearConsole();
            cout << "Current Action: Creating a new loan" << endl;
            cin.ignore();
            cout << "Please enter name loan will be stored under: ";
            string name;
            bool validPerson = false;
            getline(cin, name);
            for (const auto &person : people)
            {
                if (name == person.getName())
                {
                    validPerson = true;
                    // Choose loan type
                    cout << "Please enter type of loan you would like to create.\n1: Personal Loan\n2: Car Loan\n3: House Loan\n4: Business Loan" << endl;
                    cout << "Please enter your choice here: ";
                    int loanChoice;
                    cin >> input;
                    loanChoice = convertInput(input);
                    
                    while (loanChoice < 1 || loanChoice > 4)
                    {
                        cout << "Invalid choice, please enter a valid choice.\nEnter your choice here: ";
                        cin >> input;
                        loanChoice = convertInput(input);
                    }
                    cout << "Please enter the total loan amount you'd like to have: $";
                    double totalAmount;
                    cin >> input;
                    totalAmount = convertInputToDouble(input);
                    while (totalAmount < 0)
                    {
                        cout << "Invalid loan amount. Please enter a valid loan amount: $";
                        cin >> input;
                        totalAmount = convertInputToDouble(input);
                    }
                    cout << "Please enter how long you'd like the term date to be in years: ";
                    double termLength;
                    cin >> input;
                    termLength = convertInputToDouble(input);
                    while (termLength < 0)
                    {
                        cout << "Invalid term length. Please enter a valid term length: ";
                        cin >> input;
                        termLength = convertInputToDouble(input);
                    }

                    // Create new loan object based on user choice
                    if (loanChoice == 1)
                    {
                        Loan loan(person, totalAmount, "4/24/24", termLength);
                        loans.push_back(loan);
                    }
                    if (loanChoice == 2)
                    {
                        CarLoan loan(person, totalAmount, "4/24/24", termLength);
                        loans.push_back(loan);
                    }
                    if (loanChoice == 3)
                    {
                        HouseLoan loan(person, totalAmount, "4/24/24", termLength);
                        loans.push_back(loan);
                    }
                    if (loanChoice == 4)
                    {
                        BusinessLoan loan(person, totalAmount, "4/24/24", termLength);
                        loans.push_back(loan);
                    }

                    cout << "Loan created successfully." << endl;
                }
            }

            if (!validPerson)
            {
                cout << "No loanholders under that name exist." << endl;
            }
            anythingToContinue();
            break;
        }
        case 3:
        {
            // Print loan information for a given loan holder
            clearConsole();
            cout << "Current Action: Printing loan information" << endl;
            cin.ignore();
            cout << "Please enter loan holder's name to display loans: ";
            string name;
            bool validName = false;
            getline(cin, name);
            for (const auto &person : people)
            {
                if (name == person.getName())
                {
                    validName = true;
                    cout << "Displaying all loans under " << name << endl;
                    for (const auto &loan : loans)
                    {
                        if (loan.getName() == name)
                        {
                            loan.print();
                        }
                    }
                }
            }

            if (!validName)
            {
                cout << "No loanholders under that name exist." << endl;
            }
            anythingToContinue();
            break;
        }
        case 4:
        {
            clearConsole();
            cout<<"Current Action: Make a loan payment"<<endl;
            cin.ignore();
            cout<<"Please select whether you will be making a scheduled payment or an unscheduled payment\n1: Scheduled payment\n2: Unscheduled payment"<<endl;
            cout<<"Enter your choice here: ";
            int paymentType;
            cin >> input;
            paymentType = convertInput(input);
            while(paymentType != 1 && paymentType != 2)
            {
                cout<<"Invalid choice. Please enter a valid choice here: ";
                cin >> input;
                paymentType = convertInput(input);
            }
            string name;
            cin.ignore();
            cout<<"Please enter loanholder's name for payment: ";
            bool validName = false;
            getline(cin, name);
            for (const auto &person : people)
            {
                if (name == person.getName())
                {
                    validName = true;
                    int numOfLoans = 0;
                    cout << "Displaying all loans under " << name << endl;
                    for (const auto &loan : loans)
                    {
                        if (loan.getName() == name)
                        {
                            numOfLoans++;
                            cout<<"Loan number "<<numOfLoans<<":"<<endl;
                            loan.print();
                        }
                    }
                    cout<<"Please select loan you wish to make a payment for."<<endl;
                    cout<<"Enter loan number here: ";
                    cin >> input;
                    int loanNumber = convertInput(input);
                    while(loanNumber <= 0 || loanNumber > numOfLoans)
                    {
                        cout<<"Invalid loan number. Please enter a valid loan number here: ";
                        cin >> input;
                        loanNumber = convertInput(input);
                    }

                    numOfLoans = 0;
                    for(auto &loan : loans)
                    {
                        if(loan.getName() == name)
                        {
                            numOfLoans++;
                            if(numOfLoans == loanNumber)
                            {
                                if(paymentType == 1)
                                {
                                    loan.scheduledPayment();
                                    cout<<"Payment successful."<<endl;
                                }
                                else if(paymentType == 2)
                                {
                                    cout<<"Please enter amount you would like to pay: ";
                                    cin >> input;
                                    double amountToPay = convertInputToDouble(input);
                                    while(amountToPay < 0)
                                    {
                                        cout<<"Invalid amount. Please enter a valid amount here: ";
                                        cin >> input;
                                        amountToPay = convertInputToDouble(input);
                                    }
                                    loan.makePayment(amountToPay);
                                }
                            }
                        }
                    }
                }
            }

            if (!validName)
            {
                cout << "No loanholders under that name exist." << endl;
            }
            anythingToContinue();
            break;
        }
        case 5:
        {
            // Exit program
            clearConsole();
            cout << "Thank you for using our loan calculator. Goodbye!" << endl;
            break;
        }
        default:
        {
            // Invalid choice
            cout << "\nInvalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
    }
    } while (choice != 5);

    return 0;
}