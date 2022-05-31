#include "TasksRunner.h"

#include <fstream>
#include <iostream>
#include <thread>


namespace UbiTasks
{
  namespace fs = std::filesystem;


  TasksRunner::TasksRunner(ITask& task)
    : mTask(task)
  {
  }


  void TasksRunner::RunOnInputDir(fs::path dir)
  {
    for(const auto& entry : fs::directory_iterator(dir))
    {
      if(entry.is_regular_file())
      {
        std::unique_lock shield(mMutex);
        mAsyncTasks[entry.path().string()] = std::async([entry, this]
        {
          std::ifstream is(entry.path(), std::ios::binary);
          return mTask.Execute(is, entry.path().string());
        });
      }
    }
  }


  bool TasksRunner::IsEmpty()
  {
    std::unique_lock shield(mMutex);
    return mAsyncTasks.empty();
  }


  TaskResult TasksRunner::PopResult()
  {
    for(auto& task : mAsyncTasks)
    {
      if(task.second.valid() && task.second.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
      {
        TaskResult result{true, false, task.first};
        
        try
        {
          result.Output = task.second.get();
        }
        catch(const std::exception& ex)
        {
          result.ErrorTriggered = true;
          result.Output = ex.what();
        }

        {
          std::unique_lock shield(mMutex);
          mAsyncTasks.erase(task.first);
        }
        return result;
      }
    }
    return {false, false, "", ""};
  }
}
