#include <iostream>
#include <string>

bool checkNumber(std::string srtNumber);
std::string getIntegerPart(std::string str);
std::string getFractionalPart(std::string str);
int compareInteger(std::string int1, std::string int2, bool neg1, bool neg2); //0: equal, 1:int1, -1:int2
int compareFractional(std::string frac1, std::string frac2, bool neg);//0: equal, 1:frac1, -1:frac2
char getFracSafe(std::string frac, int i);
char getIntSafe(std::string integer, int i, int len); // x1 = 1 -> len = 1, x2 = 123 -> len = 3, x1.len => 3, x1 = 001, x1[0 .. 2] = {'0', '0', '1'}
bool isNegative(std::string integer);

int main()
{
    std::string strNumber1, strNumber2;
    bool good;
    do
    {
        std::cout << "Input 2 numbers:" << std::endl;
        std::cin >> strNumber1 >> strNumber2;
        good = checkNumber(strNumber1) && checkNumber(strNumber2);
        if (!good)
            std::cout << "Invalid input, try again" << std::endl;
    }while(!good);
    std::string int1 = getIntegerPart(strNumber1);
    std::string int2 = getIntegerPart(strNumber2);
    std::string frac1 = getFractionalPart(strNumber1);
    std::string frac2 = getFractionalPart(strNumber2);
    bool neg1 = isNegative(int1);
    bool neg2 = isNegative(int2);
    int res = compareInteger(int1, int2, neg1, neg2);
    if (0 == res)
        res = compareFractional(frac1, frac2, neg1);
    std::cout << (0 == res ? "Equal" : (1 == res ? "More" : "Less")) << std::endl;
    return 0;
}

int compareInteger(std::string int1, std::string int2, bool neg1, bool neg2)
{
    int ret = 0;
    int len = int1.length() > int2.length() ? int1.length() : int2.length();
    int more;
    if (neg1 ^ neg2)
        return neg1 ? -1 : 1;
    else
        more = neg1 ? -1 : 1;
    for (int i = 0; ret == 0 && i < len; i++)
    {
        char c1 = getIntSafe(int1, i, len);
        char c2 = getIntSafe(int2, i, len);
        if (c1 > c2)
            ret = more;
        else if (c2 > c1)
            ret = -more;
    }
    return ret;
}

int compareFractional(std::string frac1, std::string frac2, bool neg)
{
    int ret = 0;
    int len = frac1.length() > frac2.length() ? frac1.length() : frac2.length();
    int more = neg ? -1 : 1;
    for (int i = 0; ret == 0 && i < len; i++)
    {
        char c1 = getFracSafe(frac1, i);
        char c2 = getFracSafe(frac2, i);
        if (c1 > c2)
            ret = more;
        else if (c2 > c1)
            ret = -more;
    }
    return ret;
}

std::string getIntegerPart(std::string str)
{
    std::string ret = str;
    std::string::size_type dotPosition = str.find('.');
    if (dotPosition != std::string::npos)
        ret = str.substr(0, dotPosition);
    return ret;
}

std::string getFractionalPart(std::string str)
{
    std::string ret = "";
    std::string::size_type dotPosition = str.find('.');
    if (dotPosition != std::string::npos)
        ret = str.substr(dotPosition + 1, str.length());
    return ret;
}

char getFracSafe(std::string frac, int i)
{
    if (i < frac.length())
        return frac[i];
    else
        return '0';
}

char getIntSafe(std::string integer, int i, int len)
{
    if ((len - i) <= integer.length())
        return integer[integer.length() + i - len];
    else
        return ((integer.length() > 0) && (integer[0] == '-')) ? '-':'0';
}

bool checkNumber(std::string strNumber)
{
    int len = strNumber.length();
    bool good = true;
    for (int i = 0; good && i < len; i++)
    {
        if (!((strNumber[i] >= '0' && strNumber[i] <= '9') || strNumber[i] == '.' || (i == 0 && strNumber[i] == '-')))
            good = false;
    }
    return good;
}
bool isNegative(std::string integer)
{
    bool neg = false;
    if (integer.length() > 0 && integer[0] == '-')
        neg = true;
    return neg;
}