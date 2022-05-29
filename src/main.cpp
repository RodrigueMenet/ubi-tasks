#include <iostream>

#include "Crc32Task.h"
#include "TasksRunner.h"

int main()
{
  UbiTasks::Crc32Task crc32_task(3);

  //std::stringstream ss("Test");
  //std::cout << crc32_task.Execute(ss) << std::endl;
  //return 1;
  UbiTasks::TasksRunner runner(crc32_task);

  runner.RunOnInputDir(std::filesystem::current_path());

  while (runner.IsEmpty() == false)
  {
    if (const auto result = runner.PopResult(); result.IsValid == true)
    {
      std::cout << "##################################" << std::endl;
      std::cout << "#" << result.InputFilePath << std::endl;
      std::cout << "##################################" << std::endl << std::endl;
      std::cout << result.Output << std::endl << std::endl;
    }
    else
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  } 
  
  return 0;
}
