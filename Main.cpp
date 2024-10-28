#include <iostream>;
#include "ConsoleManager.h";
#include "GameManager.h";

using namespace std;

int main()
{
    FullScreen();
    HideCursor();
    srand(time(NULL));
    Game();
    return 0;
}
