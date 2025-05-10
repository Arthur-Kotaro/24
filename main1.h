enum status_en
{
    go_on,
    finished
};
struct task_struct
{
    std::string name;
    status_en status;
    std::time_t start_time;
    std::time_t finish_time;
};

void finish_task(std::vector<task_struct> & tasks_vec);
void make_task(std::vector<task_struct> & tasks_vec);
void show_status(std::vector<task_struct> & tasks_vec);
