#pragma once

#include "ITask.h"


namespace UbiTasks
{
  struct TaskEnvironment
  {
    bool IsValid;
    std::unique_ptr<ITask> Task;
    std::filesystem::path InputDir;
  };


  struct TaskFactory
  {
    /// @brief create task with given parameters
    static TaskEnvironment CreateTask(int argc, char** argv);
  };
}
