#include <iostream>
#include <string>
using namespace std;

class Bank_Account{
protected: 
	string name;
	int number;
	double balance;
	bool freezed;
public: 
	Bank_Account(string xname, int xnumber);
	Bank_Account(string xname, int xnumber, double xbalance, bool xfreezed);
	Bank_Account(const Bank_Account & x);
	~Bank_Account();
	void Print();
	bool Deposit(double x);
	virtual bool Withdraw(double x);
	void Freeze();
	void Activate();
};

class Credit:public Bank_Account{
private:
	double fee;
	double debt;
public:
	Credit(string xname, int xnumber);
	Credit(string xname, int xnumber, double xbalance, bool xfreezed, double xfee, double xdebt);
	~Credit();
	Credit(const Credit & x);
	bool Withdraw(double x);
	void ChangeFee(double x);
	void ChangeDebt(double x);
};

Bank_Account::Bank_Account(string xname, int xnumber){
	name=xname;
	number=xnumber;
	freezed=false;
}

Bank_Account::Bank_Account(string xname, int xnumber, double xbalance, bool xfreezed){
	name=xname;
	number=xnumber;
	balance=xbalance;
	freezed=xfreezed;
}

Bank_Account::Bank_Account(const Bank_Account & x){
	name=x.name;
	number=x.number;
	balance=x.balance;
	freezed=x.freezed;
}

Bank_Account::~Bank_Account(){
	name="0";
	number=0;
	balance=0;
	freezed=false;
}

void Bank_Account::Print(){
	cout<<"Balance: "<<balance<<"\n";
}

bool Bank_Account::Deposit(double x){
	if (freezed==true)
		return false;
	else{
		balance+=x;
		return true;
	}
}

bool Bank_Account::Withdraw(double x){
	cout<<"Bank Account\n";
	if (freezed==true || x>balance)
		return false;
	else{
		balance-=x;
		return true;
	}
}

void Bank_Account::Freeze(){
	freezed=true;
}

void Bank_Account::Activate(){
	freezed=false;
}

Credit::Credit(string xname, int xnumber):Bank_Account(xname, xnumber){
	fee=0;
	debt=0;
}

Credit::Credit(string xname, int xnumber, double xbalance, bool xfreezed, double xfee, double xdebt):Bank_Account(xname, xnumber, xbalance, xfreezed){
	fee=xfee;
	debt=xdebt;
}

Credit::~Credit(){
	fee=0;
	debt=0;
}

Credit::Credit(const Credit & x):Bank_Account(x){
	name=x.name;
	number=x.number;
	balance=x.balance;
	freezed=x.freezed;
	fee=x.fee;
	debt=x.debt;
}

bool Credit::Withdraw(double x){
	cout<<"Credit\n";
	if (freezed==true || x>(balance+debt))
		return false;
	else{
		if (x>balance)
			balance-=((x-balance)*fee/100);
		balance-=x;
		return true;
	}
}

void Credit::ChangeFee(double x){
	fee=x;
	cout<<"Warning! Fee was changed to: "<<fee<<"\n";
}

void Credit::ChangeDebt(double x){
	debt=x;
	cout<<"Warning! Maximum debt was changed to: "<<debt<<"\n";
}

int main(){
	Credit a("John", 123, 1234, false, 10, 10000);
	Credit b=a;
	Bank_Account * y;
	y=&a;
	y -> Withdraw(1235);
	y -> Print();
	b.ChangeDebt(100000);
	b.Deposit(1111);
	b.Withdraw(3000);
	b.Print();
	return 0;
}
