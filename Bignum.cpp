#include<iostream>
#include<sstream>
#include"0516305.h"
#define MAX 40000
using namespace std;
BigNum::BigNum(){
	sign = 1;
}
BigNum::BigNum(const BigNum &f)
{
	bigx = f.bigx;
	sign = f.sign;
}
int str_to_arr(const string & bigx,int b[],int len)
{
	if(bigx[0] == '-')
	{
		for(int k = (40000-1);k > (40000-len-1);k--)
		{
			b[k] = bigx[len-(40000-k)+1] - 48;
		}
	}
	else
	{
		for(int k = (40000-1);k > (40000-len-1);k--)
		{
			b[k] = bigx[len-(40000-k)] - 48;
		}
	}
}
int cmp(int a[],int b[],int len)
{
	int i;
	for(i = 0;i < len;i++)
	{
		if(a[i] > b[i])
		{
			return 1;
		}
		else if(a[i] < b[i])
		{
			return -1;
		}
	}
	return 0;
}
void add(int x[],int y[],int c[])
{
	int i;
	for(i = 0;i < 40000;i++)
	{
		c[i] = x[i] + y[i];
	}
	for(i = 39999;i > 0;i--)
	{
		c[i-1] = c[i-1] + (c[i]/10);
		c[i] = c[i]%10;
	}
}
void sub(int x[],int y[],int c[],int bigger,int len)
{
	int i;
	if(bigger >= 0)
	{
		for(i = 0;i < len;i++)
		{
			c[i] = x[i] - y[i];
		}
	}
	else
	{
		for(i = 0;i < len;i++)
		{
			c[i] = y[i] - x[i];
		}
	}
	for(i = (len-1);i > 0;i--)
	{
		if(c[i] < 0)
		{
			c[i-1]--;
			c[i] = c[i] + 10;
		}
	}
}
void cross(int x[],int y[],int c[],int lenx,int leny)
{
	int i,j;
	for(i = 39999;i >= (40000-lenx);i--)
	{
		for(j = 39999;j >= (40000-leny);j--)
		{
			c[i+j-39999] = c[i+j-39999] + (x[i] * y[j]);
		}
	}
	for(i = 39999;i > 0;i--)
	{
		c[i-1] = c[i-1] + (c[i]/10);
		c[i] = c[i]%10;
	}
}
int div(int x[],int y[],int c[],int lenx,int leny)
{
	int i = 0,k,j = 0,h;
	int *a,*divi,*r,*b;
	a = new int[leny+1];
	divi = new int[leny+1];
	r = new int[leny+1];
	for(k = 0;k < (leny+1);k++)
	{
		divi[k] = 0;
	}
	if(r == NULL || a == NULL || divi == NULL)
	{
		cout << "error!";
		exit(1);
	}
	if(lenx < leny)
	{
		return 1;
	}
	for(i = 0;i < leny;i++)
	{
		divi[i+1] = y[40000-leny+i];
	}
	for(h = lenx+1;h > leny;h--)
	{
		
		i = 0;
		for(k = 0;k < (leny+1);k++)
		{
			a[k] = 0;
			r[k] = 0;
		}
		for(k = 0;k < (leny+1);k++)
		{
			a[k] = x[40000-h+k];
		}
		if(cmp(a,divi,leny+1) >= 0)
		{
			sub(a,divi,r,1,leny+1);
			i++;
		}
		while(cmp(r,divi,leny+1) >= 0)
		{
			int k;
			for(k = 0;k < leny+1;k++)
			{
				r[k] = r[k] - divi[k];
			}
			for(k = (leny);k > 0;k--)
			{
				if(r[k] < 0)
				{
					r[k-1]--;
					r[k] = r[k] + 10;
				}
			}
			i++;
		}
		c[j] = i;
		j++;
		if(i != 0)
		{
			for(k = 0;k < (leny+1);k++)
			{
				x[40000-h+k] = r[k];
			}	
		} 
	}
	delete []a;
	delete []r;
	delete []divi;
	return j;
}
//負號 
BigNum operator-(const BigNum &p)
{
	BigNum v;
	v = p;
	v.sign = -p.sign;
	if(v.bigx[0] == '-')
	{
		v.bigx.erase(0,1);        //消負號 
	}
	return v;
}
//加號 
BigNum operator+(const BigNum &p,const BigNum &f)
{
	BigNum v,p1,f1;
	p1 = p;
	f1 = f;
	int *a,*b,*c,k,lenp = p1.bigx.length(),lenf = f1.bigx.length(),signp = p1.sign,signf = f1.sign;
	a = new int[40000];
	b = new int[40000];
	c = new int[40000];
	for(int i = 0;i < 40000;i++)
	{
		c[i] = 0;
		b[i] = 0;
		a[i] = 0;
	}
	stringstream ss;
	if(p1.bigx[0] == '-')
	{
		p1.sign = -1;
		signp = -1;
		lenp = p1.bigx.length() - 1;
	}
	if(f1.bigx[0] == '-')
	{
		f1.sign = -1;
		signf = -1;
		lenf = f1.bigx.length() - 1;
	}
	str_to_arr(p1.bigx,b,lenp);
	str_to_arr(f1.bigx,c,lenf);
	if(signp > 0 && signf < 0)                 //正加負 
	{
		v = p1 - (-f1);
	}
	else if(signp < 0 && signf > 0)          //負加正 
	{
		v = f1 - (-p1);
	}
	else 
	{
		int i = 0;
		add(b,c,a);
		for(i = 0;i < MAX;i++)
		{
			if(a[i] != 0)
			{
				break;
			}
		}
		if(signp < 0 && signf < 0)          //負加負，把東西丟回string 
		{
			v.sign = -1;
			for(int z = i;z < MAX;z++)
			{
				ss << a[z];
				if(i == 39999)
				{
					i = 39999;
					break;
				}
			}
		}
		else
		{
			v.sign = 1;
			for(int z = i;z < MAX;z++)
			{
				ss << a[z];
				if(i == 39999)
				{
					i = 39999;
					break;
				}
			}
		}
		ss >> v.bigx;
	}
	return v;
}
//減號 
BigNum operator-(const BigNum &p,const BigNum &f)
{
	BigNum v,p1,f1;
	p1 = p;
	f1 = f;
	stringstream ss;
	int *a,*b,*c,lenp = p1.bigx.length(),lenf = f1.bigx.length(),signp = p1.sign,signf = f1.sign;
	a = new int[40000];
	b = new int[40000];
	c = new int[40000];
	for(int i = 0;i < 40000;i++)
	{
		c[i] = 0;
		b[i] = 0;
	}
	for(int i = 0;i < 40000;i++)
	{
		a[i] = 0;
	}
	if(p1.bigx[0] == '-')
	{
		p1.sign = -1;
		signp = -1;
		lenp = p1.bigx.length() - 1;
	}
	if(f1.bigx[0] == '-')
	{
		f1.sign = -1;
		signf = -1;
		lenf = f1.bigx.length() - 1;
	}
	str_to_arr(p1.bigx,b,lenp);
	str_to_arr(f1.bigx,c,lenf);
	if(signp < 0 && signf > 0)         //負減正 
	{
		v = (-p1) + f1;
		v.sign = -1;
	}
	else if(signp > 0 && signf < 0)  //正減負
	{
		v = p1 + (-f1);
		v.sign = 1;	
	}
	else
	{
		if(signp < 0 && signf < 0)
		{
			v.sign = cmp(c,b,40000);
			sub(c,b,a,v.sign,40000);
		}
		else
		{
			v.sign = cmp(b,c,40000);
			sub(b,c,a,v.sign,40000);
		}
		int i = 0;
		for(i = 0;i < 40000;i++)
		{
			if(a[i] != 0)
			{
				break;
			}
			if(i == 39999)
			{
				i = 39999;
				break;
			}
		}
		for(int z = i;z < 40000;z++)
		{
			ss << a[z];
		}
		ss >> v.bigx;
	}
	return v;
}
//乘 
BigNum operator*(const BigNum & p,const BigNum & f)
{
	BigNum v,p1,f1;
	p1 = p;
	f1 = f;
	stringstream ss;
	int *a,*b,*c,lenp = p1.bigx.length(),lenf = f1.bigx.length(),signp = p1.sign,signf = f1.sign;
	a = new int[40000];
	b = new int[40000];
	c = new int[40000];
	for(int i = 0;i < 40000;i++)
	{
		c[i] = 0;
		b[i] = 0;
		a[i] = 0;
	}
	if(p1.bigx[0] == '-')
	{
		p1.sign = -1;
		signp = -1;
		lenp = p1.bigx.length() - 1;
	}
	if(f.bigx[0] == '-')
	{
		f1.sign = -1;
		signf = -1;
		lenf = f1.bigx.length() - 1;
	}
	str_to_arr(p1.bigx,b,lenp);
	str_to_arr(f1.bigx,c,lenf);
	if(signp == signf)
	{
		v.sign = 1;
	}
	else
	{
		v.sign = -1;
	}
	cross(b,c,a,lenp,lenf);
	int i = 0;
	for(i = 0;i < 40000;i++)
	{
		if(a[i] != 0)
		{
			break;
		}
		if(i == 39999)
		{
			i = 39999;
			break;
		}
	}
	for(int z = i;z < 40000;z++)
	{
		ss << a[z];
	}
	ss >> v.bigx;
	return v;
}
//除
BigNum operator/(const BigNum & p,const BigNum & f)
{
	BigNum v,p1,f1;
	p1 = p;
	f1 = f;
	stringstream ss;
	int *a,*b,*c,lenp = p1.bigx.length(),lenf = f1.bigx.length(),signp = p1.sign,signf = f1.sign;
	a = new int[40000];
	b = new int[40000];
	c = new int[40000];
	for(int i = 0;i < 40000;i++)
	{
		c[i] = 0;
		b[i] = 0;
		a[i] = 0;
	}
	if(p1.bigx[0] == '-')
	{
		p1.sign = -1;
		signp = -1;
		lenp = p1.bigx.length() - 1;
	}
	if(f.bigx[0] == '-')
	{
		f1.sign = -1;
		signf = -1;
		lenf = f1.bigx.length() - 1;
	}
	str_to_arr(p1.bigx,b,lenp);
	str_to_arr(f1.bigx,c,lenf);
	if(signp == signf)
	{
		v.sign = 1;
	}
	else
	{
		v.sign = -1;
	}
	int j = 0;
	j = div(b,c,a,lenp,lenf);
	int i = 0;
	for(i = 0;i < j;i++)
	{
		if(a[i] != 0)
		{
			break;
		}
		if(i == (j-1))
		{
			i = j-1;
			break;
		}
	}
	for(int z = i;z < j;z++)
	{
		ss << a[z];
	}
	ss >> v.bigx;
	return v;
} 
istream & operator>>(istream &s,BigNum &v)
{
	s >> v.bigx;
	return s;
}
ostream & operator<<(ostream &s,const BigNum &v)
{
	int i,k;
	if(v.sign < 0 && v.bigx[0] != 48)
	{
		s << '-';
	}
	for(i = 0;i < v.bigx.length();i++)
	{
		if(v.bigx[i] >= 48 && v.bigx[i] < 58)
		{
			s << (v.bigx[i] - 48);
		}
	}
	return s;
}
