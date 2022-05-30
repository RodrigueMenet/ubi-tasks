#include <iostream>
#include <filesystem>

#include "Crc32Task.h"
#include "OpusTask.h"
#include "TasksRunner.h"

int main()
{
  //UbiTasks::Crc32Task crc32_task(3);

  //std::stringstream ss("Test");
  //std::cout << crc32_task.Execute(ss) << std::endl;
  //return 1;

  UbiTasks::OpusTask opus_task((std::filesystem::current_path() / "opus_result").string(), UbiTasks::OpusMode::LowDelay);
  UbiTasks::TasksRunner runner(opus_task);

  runner.RunOnInputDir(std::filesystem::current_path());

  while (runner.IsEmpty() == false)
  {
    if (const auto result = runner.PopResult(); result.IsValid == true)
    {
      std::cout << "##################################" << std::endl;
      std::cout << result.Output << std::endl << std::endl;
      std::cout << "##################################" << std::endl << std::endl;
    }
    else
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  } 
  
  return 0;
}
