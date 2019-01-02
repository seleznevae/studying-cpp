#include <iostream>
#include <string_view>

/**
 *  The code below is a copy of https://www.fluentcpp.com/2019/01/01/todo_before-clean-codebase-2019/
 */

constexpr int current_build_year() {
   constexpr std::string_view date{ __DATE__ };
   constexpr std::string_view year = date.substr(date.find_last_of(' ') + 1);
   return (year[0] - '0') * 1000 + (year[1] - '0') * 100
        + (year[2] - '0') * 10 + (year[3] - '0');
}

int main()
{
    std::cerr << "Format of __DATE__: " << __DATE__ << std::endl;
    constexpr int current_compilation_year = current_build_year();
    std::cerr << "Current build year: " << current_compilation_year << std::endl;

    // Uncomment to force compile time error
    //static_assert(current_build_year() < 2019, "Happy New Year 2019!");
    return 0;
}