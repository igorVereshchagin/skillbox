#include <iostream>

bool checkLog(std::string& high, std::string& mid, std::string& low);
int getXCount(std::string& high, std::string& mid, std::string& low);
int getOCount(std::string& high, std::string& mid, std::string& low);

char getSymbolByPos(int x, int y, std::string& high, std::string& mid, std::string& low);

char checkLineWinner(int lineN, std::string& high, std::string& mid, std::string& low);
// lineN:              3 4 5   6        7
//       0 ------      | | |    \      /
//       1 ------      | | |     \    /
//       2 ------      | | |      \  /


int main()
{
    std::string highLine, midLine, lowLine;
    std::cout << "Input game log:" << std::endl;
    std::cin >> highLine >> midLine >> lowLine;

    bool good = checkLog(highLine, midLine, lowLine);
    int numX = getXCount(highLine, midLine, lowLine);
    int numO = getOCount(highLine, midLine, lowLine);
    if (good && (numO > numX))
        good = false;
    char winner = '\0';
    char lineWinner;
    for (int i = 0; good && i < 8; i++)
    {
        lineWinner = checkLineWinner(i, highLine, midLine, lowLine);
        if (lineWinner != '\0')
        {
            if (winner != '\0')
                good = false;
            else
                winner = lineWinner;
        }
    }
    if (good && ((winner == 'X' && (numO >= numX)) || (winner == 'O' && (numO != numX))))
        good = false;

    if (good)
        std::cout << (winner == '\0' ? "Nobody" : (winner == 'X' ? "Petya won" : "Vanya won")) << std::endl;
    else
        std::cout << "Incorrect" << std::endl;
    return 0;
}

bool checkLog(std::string& high, std::string& mid, std::string& low)
{
    if (high.length() != 3 || mid.length() != 3 || low.length() != 3)
        return false;
    for (int i = 0; i < 3; i++)
    {
        if (high[i] != 'O' && high[i] != 'X' && high[i] != '.')
            return false;
        if (mid[i] != 'O' && mid[i] != 'X' && mid[i] != '.')
            return false;
        if (low[i] != 'O' && low[i] != 'X' && low[i] != '.')
            return false;
    }
    return true;
}

int getXCount(std::string& high, std::string& mid, std::string& low)
{
    int cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (high[i] == 'X') cnt++;
        if (mid [i] == 'X') cnt++;
        if (low [i] == 'X') cnt++;
    }
    return cnt;
}

int getOCount(std::string& high, std::string& mid, std::string& low)
{
    int cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (high[i] == 'O') cnt++;
        if (mid [i] == 'O') cnt++;
        if (low [i] == 'O') cnt++;
    }
    return cnt;
}

char checkLineWinner(int lineN, std::string& high, std::string& mid, std::string& low)
{
    char winner = '\0';
    std::string line;
    int x0, y0, dx, dy;
    if (lineN >= 0 && lineN <= 2)
    {
        x0 = 0;
        y0 = lineN;
        dy = 0;
        dx = 1;
    }
    else if (lineN >= 3 && lineN <= 5)
    {
        y0 = 0;
        x0 = lineN - 3;
        dx = 0;
        dy = 1;
    }
    else if (lineN == 6)
    {
        x0 = 0;
        y0 = 0;
        dx = 1;
        dy = 1;
    }
    else if (lineN == 7)
    {
        x0 = 2;
        y0 = 0;
        dx = -1;
        dy = 1;
    }
    else
        return '\0';
    for (int i = 0, x = x0, y = y0; i < 3; i++, x += dx, y += dy)
        line.append(1, getSymbolByPos(x, y, high, mid, low));
    if ((line[0] == line[1]) && (line[0] == line[2]))
        winner = line[0];
    return winner;
}

char getSymbolByPos(int x, int y, std::string& high, std::string& mid, std::string& low)
{
    if (x >= 0 && x < 3 && y >= 0 && y < 3)
    {
        if (y == 0)
            return high[x];
        else if (y == 1)
            return mid[x];
        else // (y == 2)
            return low[x];
    }
    else
        return '\0';
}