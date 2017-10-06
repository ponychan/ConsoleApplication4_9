// ConsoleApplication49.cpp: 定义控制台应用程序的入口点。
//4.9.cpp

#include "stdafx.h"
#include<iostream>
#include<cmath>
using namespace std;

//储蓄账户类-类名acount
class acount {
private:
	int id;													//账户-id
	double left;											//余额-left
	double rate;											//利率-rate
	int lastdate;											//上次变更余额的时间-lastdate
	double interest;										//利息-interest
	void record(int date, double amount);					//增加一条记录-函数record   amount交易金额
	double inter(int date)const {							//计算利息---------函数inter
		return interest + left*(date - lastdate);
	}
public:
	//构造函数*必须和类名一致
	acount(int date, int id, double rate);					//利息账号利率
	int getid() { return id; }								//获得账号
	double getinstrest() { return interest; }				//获得余额
	double getrate() { return rate; }						//获得利率
	void deposit(int date, double amount);					//存入现金
	void withdraw(int date, double amount);					//取出现金
	void settle(int date);									//每年结算利息
	void show();											//显示账户信息
};

//类的成员函数实现
//构造函数
acount::acount(int date, int id, double rate) :id(id), left(0), rate(rate), lastdate(date), interest(0) {
	cout << date << "\t#" << id << "\t" << " is created" << endl;
}
//增加一条记录
void acount::record(int date, double amount) {
	interest = inter(date);									//计算利息
	lastdate = date;										//保存日期用于下一次使用
	amount = floor(amount * 100 + 0.5) / 100;				//保留小数点后两位-算法假设小数点后有三位，乘100后小数点后第三位变成十分位，加0.5后取整相当于四舍五入，再除以100
	left += amount;
	cout << date << "\t#" << id << "\t" << amount << "\t" << left << endl;
}
//存入现金
void acount::deposit(int date, double amount) {
	record(date, amount);
}
//取出现金
void acount::withdraw(int date, double amount) {
	if (amount > left)
		cout << "error:not enough money" << endl;
	else
		record(date, -amount);
}
//每年一月一日结算利息
void acount::settle(int date) {
	double interest = inter(date)*rate / 365;
	if (interest != 0)
		record(date, interest);
	interest = 0;
}
//显示账户信息
void acount::show() {
	cout << "#" << id << "\tBalance: " << left;
}
int main()
{
	//建立几个账户
	acount sa0(1, 21325304, 0.015);
	acount sa1(1, 58320212, 0.015);
	//进行几次交易
	sa0.deposit(5, 5000);
	sa1.deposit(25, 10000);
	sa0.deposit(45, 5500);
	sa1.withdraw(60, 4000);

	//开户第90天到了银行的计息日，结算所有账户的年息
	sa0.settle(90);
	sa1.settle(90);

	//输出各个账户信息
	sa0.show();	cout << endl;
	sa1.show();	cout << endl;
	return 0;
}

