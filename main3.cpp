#include <iostream>
#include <ctime>
#include <iomanip>

int main()
{
    std::time_t sec;
    std::tm target;
    std::cout << "Enter time period in format mm:ss : ";
    std::cin >> std::get_time(&target, "%M:%S");
    while (target.tm_sec != 0 || target.tm_min > 0)
    {
        sec = std::time(nullptr);
        while (sec == std::time(nullptr)) {}
        target.tm_sec--;
        std::cout << std::put_time(&target, "%M:%S") << std::endl;
        if(target.tm_min > 0 &&  target.tm_sec == 0)
        {
            target.tm_sec = 60;
            target.tm_min--;
        }
}
    std::cout << "DING! DING! DING!";
    return 0;
}