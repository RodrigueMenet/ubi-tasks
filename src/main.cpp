#include <iostream>
#include "TasksRunner.h"

int main()
{
  UbiTasks::TasksRunner runner;

  runner.RunOnInputDir(std::filesystem::current_path());

  while (runner.IsEmpty() == false)
  {
    if (const auto result = runner.PopResult(); result.IsValid == true)
    {
      std::cout << "##################################" << std::endl;
      std::cout << "#" << result.InputFilePath << std::endl;
      std::cout << "##################################" << std::endl << std::endl;
      std::cout << "#" << result.Output << std::endl << std::endl;
    }
  } 
  
  return 0;
}
