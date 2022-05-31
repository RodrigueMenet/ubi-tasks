#include <iostream>
#include <filesystem>

#include "TaskFactory.h"
#include "TasksRunner.h"


int main(int argc, char** argv)
{
  try
  {
    const auto task_environment = UbiTasks::TaskFactory::CreateTask(argc, argv);
    if (!task_environment.IsValid)
    {
      return 1;
    }

    UbiTasks::TasksRunner runner(*task_environment.Task);

    runner.RunOnInputDir(task_environment.InputDir);

    while(runner.IsEmpty() == false)
    {
      if(const auto result = runner.PopResult(); result.IsValid)
      {
        std::cout << "##################################" << std::endl;
        std::cout << "[INPUT]: " << result.InputFilePath.filename() << std::endl << std::endl;
        std::cout << (result.ErrorTriggered ? "[ERROR]: " : "[OUTPUT]: ") << result.Output << std::endl;
        std::cout << "##################################" << std::endl << std::endl;
      }
      else
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    }
  }
  catch (const std::exception & ex)
  {
    std::cerr << "main caught exception : " << ex.what() << std::endl;
  }

  return 0;
}
