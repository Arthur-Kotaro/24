#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "main2.h"

int main()
{
    std::string name;
    person_struct tmp;
    std::time_t sec = std::time(nullptr);
    std::tm today_struct = * std::localtime(&sec);
    tmp.date_of_birth = * std::localtime(&sec);
    std::vector<person_struct> persons_vec;
    std::vector<unsigned int> next_birthday_index;
    do
    {
        std::cout << "Enter name or \"end\" to stop input: ";
        std::getline(std::cin, name);
        if (name == "end") break;
        else
        {
            tmp.name = name;
            std::cout << "Enter " << name << "\'s date of birth in format yyyy/mm/dd: ";
            std::cin >> std::get_time(&tmp.date_of_birth, "%y/%m/%d");
            std::getchar();
            persons_vec.push_back(tmp);
        }
    } while (true);
    for (unsigned int i = 0; i < persons_vec.size(); i++)
    {
        if (persons_vec[i].date_of_birth.tm_mon < today_struct.tm_mon || ( (persons_vec[i].date_of_birth.tm_mon == today_struct.tm_mon) && persons_vec[i].date_of_birth.tm_mday < today_struct.tm_mday ))
            continue; //ignore those birthdays that have already passed in this year     
        else if (next_birthday_index.empty())
        {
            next_birthday_index.push_back(i);
            continue;
        } //save index of first random upcoming birthday
        else if (persons_vec[next_birthday_index[0]].date_of_birth.tm_mon > persons_vec[i].date_of_birth.tm_mon || ( (persons_vec[next_birthday_index[0]].date_of_birth.tm_mon == persons_vec[i].date_of_birth.tm_mon) && persons_vec[next_birthday_index[0]].date_of_birth.tm_mday > persons_vec[i].date_of_birth.tm_mday ))
        {
            next_birthday_index.clear();
            next_birthday_index.push_back(i);
        } //save index of more closed date
        else if((persons_vec[i].date_of_birth.tm_mon == persons_vec[next_birthday_index[0]].date_of_birth.tm_mon) && (persons_vec[i].date_of_birth.tm_mday == persons_vec[next_birthday_index[0]].date_of_birth.tm_mday))
        {
            next_birthday_index.push_back(i);
        } //coincidence of dates
    }
    if (next_birthday_index.size() == 1)
        std::cout << "The next celebrant is " << persons_vec[next_birthday_index[0]].name << ". Birthday date is " << std::put_time(&persons_vec[next_birthday_index[0]].date_of_birth, "%d.%m.%Y") << std::endl;
    else if (next_birthday_index.size() > 1)
    {
        std::cout << "Wow! Some people celebrate their birthday in the same day! They are: ";
        for (unsigned int i = 0; i < next_birthday_index.size(); i++)
        {
            std::cout  << persons_vec[next_birthday_index[i]].name;
            if (i == (next_birthday_index.size() - 1))
                std::cout  << ".\n";
            else
                std::cout  << ", ";
        }
        std::cout << "Their birthday is in " << std::put_time(&persons_vec[next_birthday_index[0]].date_of_birth, "%d.%m.%Y") << std::endl;
    } else {
        std::cout << "There are no birthdays in this year.\n";
    }
	return 0;
}
