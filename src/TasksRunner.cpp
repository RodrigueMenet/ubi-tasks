#include "TasksRunner.h"

#include <fstream>
#include <iostream>
#include <thread>


namespace UbiTasks
{
  namespace fs = std::filesystem;


  void TasksRunner::RunOnInputDir(fs::path dir)
  {
    for(const auto& entry : fs::directory_iterator(dir))
    {
      if(entry.is_regular_file())
      {
        std::unique_lock shield(mMutex);
        mTasks[entry.path().string()] = std::async([entry]
        {
          std::this_thread::sleep_for(std::chrono::seconds(rand() % 3));
          std::ifstream is(entry.path());
          std::stringstream ss;
          ss << is.rdbuf();
          return ss.str();
        });
      }
    }
  }


  bool TasksRunner::IsEmpty()
  {
    std::unique_lock shield(mMutex);
    return mTasks.empty();
  }


  TaskResult TasksRunner::PopResult()
  {
    for(auto& task : mTasks)
    {
      if(task.second.valid() && task.second.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
      {
        TaskResult result{true, task.first, task.second.get()};
        {
          std::unique_lock shield(mMutex);
          mTasks.erase(task.first);
        }
        return result;
      }
    }
    return {false};
  }
}
