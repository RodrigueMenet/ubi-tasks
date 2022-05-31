#pragma once

#include "ITask.h"


namespace UbiTasks
{
  struct Crc32Task : ITask
  {
    Crc32Task(uint32_t seed);
    std::string Execute(std::istream & is, const std::filesystem::path & filePath) override;

  private:
    const uint32_t mSeed;
  };
}
