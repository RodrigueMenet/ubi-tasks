#include "Crc32Task.h"
#include <fstream>
#include <sstream>

#include "crc32.h"


namespace UbiTasks
{
  Crc32Task::Crc32Task(uint32_t seed)
    : mSeed(seed)
  {
  }


  std::string Crc32Task::Execute(std::istream& is, const std::filesystem::path& filePath)
  {
    std::stringstream ss;
    ss << is.rdbuf();
    const auto crc_input = ss.str();

    ss.str("");
    ss << "CRC32 = 0x" << std::hex << crc32(mSeed, crc_input.c_str(), crc_input.size());

    return ss.str();
  }
}
