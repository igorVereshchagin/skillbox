#include <iostream>
#include <string>

std::string getPrefix(std::string str);
std::string getDomain(std::string str);
bool checkPrefix(std::string prefix);
bool checkDomain(std::string domain);

int main()
{
    std::string str;
    std::cout << "Input email address: " << std::endl;
    std::cin >> str;
    std::string prefix = getPrefix(str);
    std::string domain = getDomain(str);
    std::cout << ((checkPrefix(prefix) && checkDomain(domain)) ? "Yes" : "No") << std::endl;
    return 0;
}

std::string getPrefix(std::string str)
{
    std::string ret = "";
    std::string::size_type atSignPosition = str.find('@');
    if (atSignPosition != std::string::npos)
        ret = str.substr(0, atSignPosition);
    return ret;
}
std::string getDomain(std::string str)
{
    std::string ret = "";
    std::string::size_type atSignPosition = str.find('@');
    if (atSignPosition != std::string::npos)
        ret = str.substr(atSignPosition + 1, str.length());
    return ret;
}

bool checkPrefix(std::string prefix)
{
    bool good = true;
    if (prefix.length() < 1 || prefix.length() > 64)
        good = false;
    if (good && (prefix[0] == '.' || prefix[prefix.length() - 1] == '.'))
        good = false;
    if (good)
    {
        std::string prefixSymbols = "!#$%&'*+-/=?^_`{|}~.";
        for (int i = 0; good && i < prefix.length(); i++)
        {
            bool found = false;
            if ((prefix[i] >= 'a' && prefix[i] <= 'z') || (prefix[i] >= 'A' && prefix[i] <= 'Z') || (prefix[i] >= '0' && prefix[i] <= '9'))
                found = true;
            else
                for (int j = 0; j < prefixSymbols.length(); j++)
                {
                    if (prefix[i] == prefixSymbols[j])
                    {
                        found = true;
                        break;
                    }
                }
            if (!found)
                good = false;
            else if (prefix[i] == '.' && prefix[i - 1] == '.')
                good = false;
        }
    }
    return good;
}

bool checkDomain(std::string domain)
{
    bool good = true;
    if (domain.length() < 1 || domain.length() > 64)
        good = false;
    if (good && (domain[0] == '.' || domain[domain.length() - 1] == '.'))
        good = false;
    if (good)
    {
        std::string prefixSymbols = "-.";
        for (int i = 0; good && i < domain.length(); i++)
        {
            bool found = false;
            if ((domain[i] >= 'a' && domain[i] <= 'z') || (domain[i] >= 'A' && domain[i] <= 'Z') || (domain[i] >= '0' && domain[i] <= '9'))
                found = true;
            else
                for (int j = 0; j < prefixSymbols.length(); j++)
                {
                    if (domain[i] == prefixSymbols[j])
                    {
                        found = true;
                        break;
                    }
                }
            if (!found)
                good = false;
            else if (domain[i] == '.' && domain[i - 1] == '.')
                good = false;
        }
    }
    return good;
}
