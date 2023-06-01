#pragma once
#include <iostream>
#include <cmath>

namespace std
{
  class Complex
  {
  	long double a, b;
  
  	long double whole, fractional;
  	bool sign;
  
  	void rlEngine(const char[], size_t, size_t, int);
    
  public:
  	Complex ();
  
  	Complex (long double, long double);
  
  	void operator++ ();
  
  	void operator++ (int);
  
  	void operator-- ();
  
  	void operator-- (int);
  
  	Complex operator- ();
  
  	Complex operator+ (Complex) const;
  
  	template <class T>
  	Complex operator+ (T) const;
  
  	template <class T>
  	friend Complex operator+ (T, Complex);
  
  	Complex operator- (Complex) const;
  
  	template <class T>
  	Complex operator- (T) const;
  
  	template <class T>
  	friend Complex operator- (T, Complex);
  
  	Complex operator* (Complex) const;
  
  	template <class T>
  	Complex operator* (T) const;
  
  	template <class T>
  	friend Complex operator* (T, Complex);
  
  	Complex operator/ (Complex) const;
  
  	template <class T>
  	Complex operator/ (T) const;
  
  	template <class T>
  	friend Complex operator/ (T, Complex);
  
  	bool operator== (Complex) const;
  
  	bool operator!= (Complex) const;
  
  	operator bool () const;
  
  	template <class T>
  	operator T () const;
  
  	friend std::ostream& operator<< (std::ostream&, Complex);
  
  	friend std::istream& operator>> (std::istream&, Complex&);
  };
}

void std::Complex::rlEngine(const char buff[], size_t i=0, size_t len=256, int q=1)
{
	if (!i)
	{
	whole = 0; fractional = 0; sign = false;
	}
	
	if (!(i < len))
		return;
	
	switch (q)
	{
    case 1:
      if (buff[i] == '.')
        rlEngine(buff, i + 1, len, q=2);
      if (buff[i] >= 48 && buff[i] <= 57)
      {
        whole = buff[i] - 48;
        a = whole;
        rlEngine(buff, i + 1, len, q=3);
      }
      if (buff[i] == '+' || buff[i] == '-')
      {
        sign = false;
        if (buff[i] == '-')
          sign = true;
        rlEngine(buff, i + 1, len, q=4);
      }
      if (buff[i] == 'j')
      {
        whole = 1; fractional = 0;
        rlEngine(buff, i + 1, len, q=7);
      }
      return;
    case 2:
      if (buff[i] >= 48 && buff[i] <= 57)
      {
        fractional = fractional * 10 + buff[i] - 48;
        long double temp = fractional;
        while (static_cast<unsigned long long>(temp))
          temp /= 10;
        a = (sign ? -1 : 1) * (whole + temp);
        rlEngine(buff, i + 1, len, q=2);
      }
      if (buff[i] == '+' || buff[i] == '-')
      {
        whole = 0; fractional = 0;
        sign = false;
        if (buff[i] == '-')
          sign = true;
        rlEngine(buff, i + 1, len, q=5);
      }
      if (buff[i] == 'j')
      {
        b = a; a = 0;
        rlEngine(buff, i + 1, len, q=7);
      }
      return;
    case 3:
      if (buff[i] == '.')
        rlEngine(buff, i + 1, len, q=2);
      if (buff[i] == '+' || buff[i] == '-')
      {
        whole = 0;
        sign = false;
        if (buff[i] == '-')
          sign = true;
        rlEngine(buff, i + 1, len, q=5);
      }
      if (buff[i] >= 48 && buff[i] <= 57)
      {
        whole = whole * 10 + (sign ? -1 : 1) * (buff[i] - 48);
        a = whole;
        rlEngine(buff, i + 1, len, q=3);
      }
      if (buff[i] == 'j')
      {
        b = a; a = 0;
        rlEngine(buff, i + 1, len, q=7);	
      }
      return;
    case 4:
      if (buff[i] == '+' || buff[i] == '-')
      {
        whole = 0;
        sign = false;
        if (buff[i] == '-')
        sign = true;
        rlEngine(buff, i + 1, len, q=5);
      }
      if (buff[i] == '.')
        rlEngine(buff, i + 1, len, q=6);
      if (buff[i] == 'j')
      {
        b = a; a = 0;
        rlEngine(buff, i + 1, len, q=7);
      }
      if (buff[i] >= 48 && buff[i] <= 57)
      {
        whole = whole * 10 + (sign ? -1 : 1) * (buff[i] - 48);
        a = whole;
        rlEngine(buff, i + 1, len, q=4);
      }
      return;
    case 5:
      if (buff[i] == 'j')
        rlEngine(buff, i + 1, len, q=7);
      if (buff[i] == '.')
      {
        fractional = 0;
        rlEngine(buff, i + 1, len, q=8);
      }
      if (buff[i] >= 48 && buff[i] <= 57)
      {
        whole = whole * 10 + (sign ? -1 : 1) * (buff[i] - 48);
        rlEngine(buff, i + 1, len, q=5);
      }
      return;
    case 6:
      if (buff[i] == '+' || buff[i] == '-')
        rlEngine(buff, i + 1, len, q=5);
      if (buff[i] == 'j')
      {
        b = a;
        a = 0;
        whole = 0; fractional = 0;
        rlEngine(buff, i + 1, len, q=7);
      }
      if (buff[i] >= 48 && buff[i] <= 57)
      {
        fractional = fractional * 10 + buff[i] - 48;
        long double temp = fractional;
        while (static_cast<unsigned long long>(temp))
          temp /= 10;
        a = (sign ? -1 : 1) * (whole + temp);
        rlEngine(buff, i + 1, len, q=6);
      }
      return;
    case 7:
      while (static_cast<unsigned long long>(fractional))
        fractional /= 10;
      b = whole + (sign ? -1 : 1) * fractional;
      return;
    case 8:
      if (buff[i] == 'j')
        rlEngine(buff, i + 1, len, q=7);
      if (buff[i] >= 48 && buff[i] <= 57)
      {
        fractional = fractional * 10 + buff[i] - 48;
        rlEngine(buff, i + 1, len, q=8);
      }
      return;
	}
}

std::Complex::Complex () {}

std::Complex::Complex (long double r, long double i=0) : a(r), b(i) {}

void std::Complex::operator++ ()
{
	a++;
}

void std::Complex::operator++ (int)
{
	++a;
}

void std::Complex::operator-- ()
{
	a--;
}

void std::Complex::operator-- (int)
{
	--a;
}

std::Complex std::Complex::operator- ()
{
	return {-a, -b};
}

std::Complex std::Complex::operator+ (Complex r)
{
	return {a + r.a, b + r.b};
}

template <class T>
std::Complex std::Complex::operator+ (T r)
{
	return {a + r, b};
}

template <class T>
std::Complex operator+ (T l, Complex r)
{
	return {l + r.a, r.b};
}

std::Complex std::Complex::operator- (Complex r)
{
	return {a - r.a, b - r.b};
}

template <class T>
std::Complex std::Complex::operator- (T r)
{
	return {a - r, b};
}

template <class T>
std::Complex operator- (T l, Complex c)
{
	return {l - c.a, c.b};
}

std::Complex std::Complex::operator* (Complex r)
{
	return {a * r.a - b * r.b, a * r.b + b * r.a};
}

template <class T>
std::Complex std::Complex::operator* (T r)
{
	return {a * r, b * r};
}

template <class T>
std::Complex operator* (T l, Complex r)
{
	return {l * r.a, l * r.b};
}

std::Complex std::Complex::operator/ (Complex r)
{
	return {(a * r.a - b * r.b)/(r.a * r.a + r.b * r.b), (a * r.b + b * r.a)/(r.a * r.a + r.b * r.b)};
}

template <class T>
std::Complex std::Complex::operator/ (T r)
{
	return {a / r, b / r};
}

template <class T>
std::Complex operator/ (T l, Complex r)
{
	return {l * r.a / (r.a * r.a + r.b * r.b), l * r.b / (r.a * r.a + r.b * r.b)};
}

bool std::Complex::operator== (Complex c)
{
	if (a == c.a && b == c.b)
		return true;
	return false;
}

bool std::Complex::operator!= (Complex c)
{
	if (a != c.a && b != c.b)
		return true;
	return false;
}

std::Complex::operator bool ()
{
	if (a || b)
		return true;
	return false;
}

template <class T>
std::Complex::operator T ()
{
	return T(a);
}

std::ostream& operator<< (std::ostream& obuff, Complex c)
{
	if (!c.a && !c.b)
	{
		obuff << 0;
		return obuff;
	}

	if (std::isinf(c.a) && c.b || std::isinf(c.b) && c.a)
	{
		obuff << "inf";
		return obuff;
	}
	if ((std::isinf(c.a) && c.a < 0) || (!c.a && std::isinf(c.b) && c.b < 0))
	{
		obuff << "-inf";
		return obuff;
	}
	else if ((!c.b && std::isinf(c.a) && c.a > 0) || (!c.a && std::isinf(c.b) && c.b > 0))
	{
		obuff << "inf";
		return obuff;
	}
	if (std::isnan(c.a) || std::isnan(c.b))
	{
		obuff << "nan";
		return obuff;
	}
		
	bool flag = false;

	if (c.a && c.b)
	{
		obuff << '(';
		flag = true;
	}
		
	if (c.a)
		obuff << c.a;

	if (c.b)
	{
		if (c.b > 0 && c.a)
			obuff << '+';
		obuff << c.b << 'j';
	}

	if (flag)
		obuff << ')';
	
	return obuff;
}

std::istream& operator>> (std::istream& ibuff, Complex& c)
{
	char buff[256];
	
	c.a = 0; c.b = 0;
	ibuff >> buff;
	
	c.rlEngine(buff);

	return ibuff;
}

std::Complex operator""_j (long double i)
{
	return {0, i};
}

std::Complex operator""_j (unsigned long long i)
{
	return {0, static_cast<long double>(i)};
}
