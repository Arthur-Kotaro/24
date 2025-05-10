#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include "main1.h"

int main()
{
    std::vector<task_struct> tasks_vec;
    std::string input_str;
    std::cout<< "Enter command \"begin\" to start new task, \"end\" to finish the task. Enter command \"status\" to show info or \"exit\" to stop.\n";
    do
    {
	    std::cout << "Command: ";
        std::cin >> input_str;
	    if(input_str == "begin")
	    {
		    if(!tasks_vec.empty())
			    finish_task(tasks_vec);
		    make_task(tasks_vec);
	    }
	    else if(input_str == "end") finish_task(tasks_vec);
	    else if(input_str == "status") show_status(tasks_vec);
	    else if(input_str == "exit")
	    {
		    std::cout<< "\n*********************\nTasks tracker stoped.\n*********************\n";
		    break;
	    }
	    else std::cout<< "Incorrect input. Try again.\n";
    } while (true);
    return 0;
}


void finish_task(std::vector<task_struct> & tasks_vec)
{
    if(tasks_vec[tasks_vec.size()-1].status == go_on)
    {
        tasks_vec[tasks_vec.size()-1].status = finished; 
		tasks_vec[tasks_vec.size()-1].finish_time  = std::time(nullptr);
    }
}


void make_task(std::vector<task_struct> & tasks_vec)
{
    task_struct tmp_task;
    std::cout<< "Enter name of task: ";
    std::getchar();
    std::getline(std::cin, tmp_task.name);
    tmp_task.status = go_on;
    tmp_task.start_time = std::time(nullptr);
    tasks_vec.push_back(tmp_task);
}


void show_status(std::vector<task_struct> & tasks_vec)
{
	std::time_t dif_time;
	std::tm* tmp_strct;
	long unsigned int i = 0;
	bool contin_flag = false;
	if(0 < tasks_vec.size() && tasks_vec[i].status == finished)
		std::cout << "\n********************\nFinished tasks list:\n********************\n\n";
	for(i = 0; i < tasks_vec.size(); i++)
	{
		if(tasks_vec[i].status == finished)
		{
			tmp_strct = std::localtime(&tasks_vec[i].start_time);
			std::cout << i+1 << ". " << tasks_vec[i].name << ": started in " << std::put_time(tmp_strct, "%d/%m/%Y %H:%M") << ", duration: ";
			dif_time = tasks_vec[i].finish_time - tasks_vec[i].start_time;
			int hours = dif_time / 3600;
			int minutes = (dif_time - (hours * 3600)) / 60;
			int seconds = (dif_time - (hours * 3600 + minutes * 60));
			std::cout << hours <<" hours " << minutes << " minutes " << seconds << " seconds.\n";
		}
		else
		{
			contin_flag = true;
			break;
		}	    
	}
	if(contin_flag && i == tasks_vec.size()-1)
	{
		tmp_strct = std::localtime(&tasks_vec[i].start_time);
		std::cout << "Current task is " << tasks_vec[i].name << ". It started in " << std::put_time(tmp_strct, "%d/%m/%Y %H:%M") << "\n";
	}
}
