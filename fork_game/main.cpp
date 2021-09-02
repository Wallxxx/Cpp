#include "menu.h"

using namespace std;

int main()
{
	system("clear");
    Menu test;
    test.showMenu();
    Window pws;
    pws.makeScreen();
    vector<size_t> data;
    string word = test.getWord();
    char choise = 1;
    char step = '0';
    while (true)
    {
        size_t check = data.size();
        pws.showScreen(step);
        if (step == '6')
        {
            cout << "You lose.\nWord: " << word << endl;
            break;
        }
        pws.showWord(word, data);
        if (data.size() == word.length())
        {
            cout << "\nYou won!\n";
            break;
        }
        cout << "\nGuess the letter: ";

        pws.setInputMode(true);

        choise = static_cast<char>(getchar());

        pws.setInputMode(false);
        for (size_t i = 0; i < word.length(); i++)
        {
            bool isNew = true;
            if (word[i] == choise)
            {
                for (size_t q = 0; q < data.size(); q++)
                {
                    if (data[q] == i) isNew = false;
                }
                if (isNew) data.push_back(i);
                else check++;
            }
        }
        if (data.size() == check) step++;
    }
    return 0;
}
