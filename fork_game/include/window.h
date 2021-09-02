#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <vector>
#include <termios.h>
#include <unistd.h>

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define BBLUE "\033[36m"
#define WHITE "\033[37m"

#define F_BLACK "\033[40m"
#define F_RED "\033[41m"
#define F_GREEN "\033[42m"
#define F_YELLOW "\033[43m"
#define F_BLUE "\033[44m"
#define F_PURPLE "\033[45m"
#define F_BBLUE "\033[46m"
#define F_WHITE "\033[47m"

#define L_BLACK "\033[90m"
#define L_RED "\033[91m"
#define L_GREEN "\033[92m"
#define L_YELLOW "\033[93m"
#define L_BLUE "\033[94m"
#define L_PURPLE "\033[95m"
#define L_BBLUE "\033[96m"
#define L_WHITE "\033[97m"

#define LF_BLACK "\033[100m"
#define LF_RED "\033[101m"
#define LF_GREEN "\033[102m"
#define LF_YELLOW "\033[103m"
#define LF_BLUE "\033[104m"
#define LF_PURPLE "\033[105m"
#define LF_BBLUE "\033[106m"
#define LF_WHITE "\033[107m"

#define UNDERLINE "\033[4m"

#define RESET "\033[0m"

class Window
{
public:
    Window() {}
    ~Window();
    void makeScreen();
    void showScreen(const char &step);
    void showWord(const std::string &word, const std::vector<size_t> &data);
    void setInputMode(bool OnOff);
private:
    std::string zero[14], one[14], two[14], three[14], four[14], five[14], lose[14];
    struct termios oldt, newt;
};
#endif // WINDOW_H
