#include <iostream>
#include <string>

std::string encrypt_caesar(std::string str, int key);
std::string decrypt_caesar(std::string str, int key);

int main()
{
    std::string str;
    std::string enc_str;
    std::cout << "Input a string: ";
    std::getline(std::cin, str);
    int key;
    std::cout << "Input a key: ";
    std::cin >> key;
    enc_str = encrypt_caesar(str, key);
    std::cout << enc_str << std::endl;
    std::cout << decrypt_caesar(enc_str, key) << std::endl;
    return 0;
}

std::string encrypt_caesar(std::string str, int key)
{
    std::string ret = "";
    int alphabet_size = 'z' + 1 - 'a';
    key = key % alphabet_size;
    for (int i = 0; i < str.length(); i++)
    {
        int c = str[i];
        if (c >= 'a' && c <= 'z')
        {
            c += key;
            if (c < 'a')
                c += alphabet_size;
            else if (c > 'z')
                c -= alphabet_size;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c += key;
            if (c < 'A')
                c += alphabet_size;
            else if (c > 'Z')
                c -= alphabet_size;
        }

        ret.append((const char*)&c, 1);
    }
    return ret;
}

std::string decrypt_caesar(std::string str, int key)
{
    return encrypt_caesar(str, -key);
}