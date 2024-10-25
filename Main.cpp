#include <iostream>;
#include "ConsoleManager.cpp";
#include "GameManager.cpp";

using namespace std;


int main()
{
    fullsc();
    HideCursor();
    srand(time(NULL));
    cout << "\033[40m";
    Game();
    return 0;
}
