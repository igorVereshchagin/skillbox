#include <iostream>
#include <string>

std::string getIpToken(std::string str, int n);
bool checkIpToken(std::string str);

int main()
{
    std::string str;
    std::cout << "Input an IP-address: " << std::endl;
    std::getline(std::cin, str);
    bool good = true;
    for (int i = 1; good && i <= 4; i++)
        good = checkIpToken(getIpToken(str, i));
    std::cout << (good ? "Yes" : "No") << std::endl;
    return 0;
}

std::string getIpToken(std::string str, int n)
{
    int tokenStartPos = 0;
    int tokenSize = 0;
    int i = 0;
    for (int t = 0; t < n; t++)
    {
        tokenStartPos = i;
        while (i < str.length())
        {
            if (str[i++] == '.')
                break;
        }
        tokenSize = i - tokenStartPos - (i == str.length() ? 0 : 1);
    }
    return str.substr(tokenStartPos, tokenSize);
}

bool checkIpToken(std::string str)
{
    if (str.length() < 1 || str.length() > 3)
        return false;
    if (str.length() > 1 && str[0] == '0')
        return false;
    int n = 0;
    int m = 1;
    for (int i = str.length() - 1; i >= 0; i--, m *= 10)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
        else
            n += m * ((int)str[i] - '0');
    }
    if (n > 255)
        return false;
    return true;
}