#include "window.h"

Window::~Window()
{

}

void Window::makeScreen()
{
    std::cout << "Loading... (step 0)\n";
    zero[0] = R"(|--------)";
    zero[1] = R"(||      |)";
    zero[2] = zero[1];
    zero[3] = R"(||      -)";
    zero[4] = R"(||)";
    zero[5] = R"(||)";
    zero[6] = R"(||)";
    zero[7] = R"(||)";
    zero[8] = R"(||)";
    zero[9] = R"(||)";
    zero[10] = R"(||)";
    zero[11] = zero[10];
    zero[12] = R"(||______________)";
    zero[13] = R"(|_______________|)";
    system("clear");

    std::cout << "Loading... (step 1)\n";
    one[0] = R"(|--------)";
    one[1] = R"(||      |)";
    one[2] = one[1];
    one[3] = R"(||      -)";
    one[4] = R"(||     / \)";
    one[5] = R"(||     \ /)";
    one[6] = R"(||)";
    one[7] = R"(||)";
    one[8] = R"(||)";
    one[9] = R"(||)";
    one[10] = R"(||)";
    one[11] = one[10];
    one[12] = R"(||______________)";
    one[13] = R"(|_______________|)";
    system("clear");

    std::cout << "Loading... (step 2)\n";
    two[0] = R"(|--------)";
    two[1] = R"(||      |)";
    two[2] = two[1];
    two[3] = R"(||      -)";
    two[4] = R"(||     / \)";
    two[5] = R"(||     \ /)";
    two[6] = R"(||     | |)";
    two[7] = R"(||     | |)";
    two[8] = R"(||)";
    two[9] = R"(||)";
    two[10] = R"(||)";
    two[11] = two[10];
    two[12] = R"(||______________)";
    two[13] = R"(|_______________|)";
    system("clear");

    std::cout << "Loading... (step 3)\n";
    three[0] = R"(|--------)";
    three[1] = R"(||      |)";
    three[2] = three[1];
    three[3] = R"(||      -)";
    three[4] = R"(||     / \)";
    three[5] = R"(||     \ /)";
    three[6] = R"(||   //| |)";
    three[7] = R"(||     | |)";
    three[8] = R"(||)";
    three[9] = R"(||)";
    three[10] = R"(||)";
    three[11] = three[10];
    three[12] = R"(||______________)";
    three[13] = R"(|_______________|)";
    system("clear");

    std::cout << "Loading... (step 4)\n";
    four[0] = R"(|--------)";
    four[1] = R"(||      |)";
    four[2] = four[1];
    four[3] = R"(||      -)";
    four[4] = R"(||     / \)";
    four[5] = R"(||     \ /)";
    four[6] = R"(||   //| |\\)";
    four[7] = R"(||     | |)";
    four[8] = R"(||)";
    four[9] = R"(||)";
    four[10] = R"(||)";
    four[11] = four[10];
    four[12] = R"(||______________)";
    four[13] = R"(|_______________|)";
    system("clear");

    std::cout << "Loading... (step 5)\n";
    five[0] = R"(|--------)";
    five[1] = R"(||      |)";
    five[2] = five[1];
    five[3] = R"(||      -)";
    five[4] = R"(||     / \)";
    five[5] = R"(||     \ /)";
    five[6] = R"(||   //| |\\)";
    five[7] = R"(||     | |)";
    five[8] = R"(||    //)";
    five[9] = R"(||   //)";
    five[10] = R"(||)";
    five[11] = five[10];
    five[12] = R"(||______________)";
    five[13] = R"(|_______________|)";
    system("clear");

    std::cout << "Loading... (step 6)\n";
    lose[0] = R"(|--------)";
    lose[1] = R"(||      |)";
    lose[2] = lose[1];
    lose[3] = R"(||      -)";
    lose[4] = R"(||     / \)";
    lose[5] = R"(||     \ /)";
    lose[6] = R"(||   //| |\\)";
    lose[7] = R"(||     | |)";
    lose[8] = R"(||    // \\)";
    lose[9] = R"(||   //   \\)";
    lose[10] = R"(||)";
    lose[11] = lose[10];
    lose[12] = R"(||______________)";
    lose[13] = R"(|_______________|)";
    system("clear");
}

void Window::showScreen(const char &step)
{
    system("clear");
    switch (step)
    {
    case '0':
        for (size_t i = 0; i < 14; i++) std::cout << zero[i] << std::endl;
        break;
    case '1':
        for (size_t i = 0; i < 14; i++) std::cout << one[i] << std::endl;
        break;
    case '2':
        for (size_t i = 0; i < 14; i++) std::cout << two[i] << std::endl;
        break;
    case '3':
        for (size_t i = 0; i < 14; i++) std::cout << three[i] << std::endl;
        break;
    case '4':
        for (size_t i = 0; i < 14; i++) std::cout << four[i] << std::endl;
        break;
    case '5':
        for (size_t i = 0; i < 14; i++) std::cout << five[i] << std::endl;
        break;
    case '6':
        for (size_t i = 0; i < 14; i++) std::cout << lose[i] << std::endl;
        break;
    }
}

void Window::showWord(const std::string &word, const std::vector<size_t> &data)
{
    std::cout << std::endl;
    std::cout << "---------------------------------\n";
    std::cout << "Word: ";
    bool isNew = false;
    for (size_t i = 0; i < word.size(); i++)
    {
        for (size_t q = 0; q < data.size(); q++)
        {
            if (data[q] == i)
            {
                std::cout << word[i] << " ";
                isNew = true;
                break;
            }
        }
        if (!isNew) std::cout << "_ ";
        isNew = false;
    }
}

void Window::setInputMode(bool OnOff)
{
    if (OnOff)
    {
        /*tcgetattr gets the parameters of the current terminal
        STDIN_FILENO will tell tcgetattr that it should write the settings
        of stdin to oldt*/
        tcgetattr( STDIN_FILENO, &oldt);
        /*now the settings will be copied*/
        newt = oldt;

        /*ICANON normally takes care that one line at a time will be processed
        that means it will return if it sees a "\n" or an EOF or an EOL*/
        newt.c_lflag &= ~(ICANON);

        /*Those new settings will be set to STDIN
        TCSANOW tells tcsetattr to change attributes immediately. */
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        /*restore the old settings*/
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}
