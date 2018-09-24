#ifndef BIGNUM_H
#define BIGNUM_H
#include<iostream>
#include<string>
using namespace std;
class BigNum{
private:
	int sign;
	string bigx;
public:
	BigNum();
	BigNum(const BigNum & f);
	friend int str_to_arr(const string & bigx,int b[],int len);
	friend int cmp(int a[],int b[],int len);
	friend void sub(int x[],int y[],int c[],int bigger, int len);
	friend void add(int x[],int y[],int c[]);
	friend void cross(int x[],int y[],int c[],int lenx,int leny);
	int div(int x[],int y[],int c[],int lenx,int leny);
	friend BigNum operator-(const BigNum&);
	friend BigNum operator+(const BigNum &p,const BigNum &f);
	friend BigNum operator-(const BigNum &p,const BigNum &f);
	friend BigNum operator*(const BigNum &p,const BigNum &f);
	friend BigNum operator/(const BigNum &p,const BigNum &f);
	friend istream & operator>>(istream &, BigNum &);
	friend ostream & operator<<(ostream &,const BigNum &);
};
#endif 
