#pragma once

#include <filesystem>
#include <string>

namespace UbiTasks
{
  struct ITask
  {
    virtual ~ITask() = default;
    virtual std::string Execute(std::istream &, const std::filesystem::path & inputFilePath) = 0;
  };
}
