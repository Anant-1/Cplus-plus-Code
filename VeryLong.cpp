#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

const int sz = 100000;

class VeryLong 
{
private:
    char vlstr[sz];
    int vlen;
    VeryLong mult_digit(int);
    VeryLong mult10(VeryLong);
public:
    VeryLong() : vlen(0)
    { vlstr[0] = (char)NULL; }
    VeryLong (const char str[sz])
    { 
        strcpy(vlstr, str); 
        vlen = strlen(str);
    }
    VeryLong(const unsigned long n)
    {    
        ltoa(n, vlstr, 10);
        strrev(vlstr);
        vlen = strlen(vlstr);
    }

    void putvl() const;
    void getvl();
    VeryLong operator + (const VeryLong);
    VeryLong operator * (const VeryLong);
};

void VeryLong::putvl() const
{
    char tmp[sz];
    strcpy(tmp, vlstr);
    cout << strrev(tmp);
}

void VeryLong::getvl()
{
    cin >> vlstr;
    vlen = strlen(vlstr);
    strrev(vlstr);
}

VeryLong VeryLong::operator+(const VeryLong v)
{
    char tmp[sz];
    int maxlen = (vlen > v.vlen) ? vlen : v.vlen;

    int carry = 0, i;

    for(i = 0; i < maxlen; i++)
    {
        int d1 = (i > vlen - 1) ? 0 : (vlstr[i] - '0');
        int d2 = (i > v.vlen - 1) ? 0 : (v.vlstr[i] - '0');

        int digit_sum = d1 + d2 + carry;

        if(digit_sum >= 10)
        { digit_sum -= 10; carry = 1; }

        else
            carry = 0;

        tmp[i] = digit_sum + '0';    

    }

    if(carry == 1)
    { tmp[i++] = '1'; }
    tmp[i] = (char)NULL;
    return VeryLong(tmp);
}

VeryLong VeryLong::operator*(const VeryLong v)
{
    VeryLong pprod;
    VeryLong tmpsum;
    int digit;
    for(int i = 0; i < v.vlen; i++)
    {
        digit = v.vlstr[i] - '0';
        pprod = mult_digit(digit);
        for(int k = 0; k < i; k++)
            pprod = mult10(pprod);
        tmpsum = tmpsum + pprod;
    }
    return tmpsum;
}

VeryLong VeryLong::mult10(VeryLong v)
{
    char tmp[sz];
    for(int i =v.vlen - 1; i >= 0; i--)
        tmp[i + 1] = v.vlstr[i];
    tmp[0] = '0';
    tmp[v.vlen + 1] = (char)NULL;
    return VeryLong(tmp);
}

VeryLong VeryLong::mult_digit(int d2)
{
    char tmp[sz];
    int i, carry = 0;

    for(i = 0; i < vlen; i++)
    {
        int d1 = vlstr[i] - '0';
        int digi_prod = d1 * d2;

        digi_prod += carry;

        if(digi_prod >= 10)
        {
            carry = digi_prod / 10;
            digi_prod -= carry * 10;
        }
        else
            carry = 0;
        tmp[i] = digi_prod + '0';
    }

    if(carry != 0)
    {
        tmp[i++] = carry + '0';
    }
    tmp[i] = (char)NULL;
    return VeryLong(tmp);
}

int main()
{
    //Used as sum of big numbers

    VeryLong n1;
    VeryLong n2;
    cout << "Enter n1 : ";
    n1.getvl();
    cout << "Enter n2 : ";
    n2.getvl();
    VeryLong sum, prod;
    sum = n1 + n2;
    cout << "Sum : "; sum.putvl();

    //Used as sum of big numbers

    prod = n1 * n2;
    cout << "\nProd : ";prod.putvl();    
    getch();

    //Used as Factorial for big numbers

    int num;
    cout << "Enter the number : ";
    cin >> num;

    VeryLong fact = 1;

    for(int i = 2; i <= num; i++)
    {
        fact = fact * i;
    }
    fact.putvl();


    return 0;
}-