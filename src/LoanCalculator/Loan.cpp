#include "Loan.h"
#include <iostream>
using namespace std;

Loan::Loan(Person loanHolder, double totalLoan, string startDate, double length, double interest)
    : person(loanHolder), totalAmount(totalLoan), currentlyOwed(totalLoan), loanStartDate(startDate), termLength(length), interestRate(interest) {}

void Loan::makePayment(double amount)
{
    if(totalAmount > amount)
    {
        amount = floor(amount * 100) / 100;
        this->totalAmount = this->totalAmount - amount;
        cout << "Payment of $ " << amount << " made by " << this->person.getName() << endl;
    }
    else
    {
        double amountPayed = this->totalAmount;
        this->totalAmount = 0;
        cout << "Payment of $ " << amountPayed << " made by " << this->person.getName() << endl;
    } 
}

double Loan::calculateInterest(string typeOfInterest)
{
    if(typeOfInterest.compare("Total Interest") || typeOfInterest.compare("total interest"))
    {
        return this->totalAmount * this->interestRate / 100;
    }
    else if(typeOfInterest.compare("Interest Left") || typeOfInterest.compare("interest left"))
    {
        return this->currentlyOwed * this->interestRate / 100;
    }
    else
    {
        cout<<"Invalid loan calculation."<<endl;
        return 0.0;
    }
}

void Loan::scheduledPayment()
{
    double monthlyPayment = this->totalAmount * ((this->interestRate / 12) * pow((1 + (this->interestRate / 12)), (this->termLength * 12))) / (pow((1 + (this->interestRate / 12)), (this->termLength * 12)) - 1);
    monthlyPayment = floor(monthlyPayment * 100) / 100;
    double biweeklyPayment = monthlyPayment / 2;
    biweeklyPayment = floor(biweeklyPayment * 100) / 100;

    double amountToInterest = (biweeklyPayment * this->interestRate) / 100;
    amountToInterest = floor(amountToInterest * 100) / 100;
    double amountToPrincipal = biweeklyPayment - amountToInterest;

    this->totalAmount = this->totalAmount - amountToPrincipal;    
}

double Loan::getRemainingAmount()
{
    return currentlyOwed;
}

void Loan::print() const
{
    cout<<"Loan Holder: "<<person.getName()<<endl;
    cout<<"Total Loan Amount: "<<this->totalAmount<<endl;
    cout<<"Term Length: "<<this->termLength<<" Years"<<endl;
    cout<<"Interest Rate: "<<this->interestRate<<endl;
    cout<<"Amount Left to Pay: "<<this->currentlyOwed<<endl;
}

string Loan::getName() const
{
    return this->person.getName();
}

void CarLoan::print() const
{
    cout<<"Type of Loan: Car Loan"<<endl;
    Loan::print();
}

void HouseLoan::print() const
{
    cout<<"Type of Loan: House Loan"<<endl;
    Loan::print();
}

void BusinessLoan::print() const
{
    cout<<"Type of Loan: Business Loan"<<endl;
    Loan::print();
}