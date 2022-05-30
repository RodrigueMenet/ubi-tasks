#include "OpusTask.h"

#include <filesystem>
#include <fstream>


namespace UbiTasks
{
  OpusTask::OpusTask(std::string outputFolder, OpusMode mode)
    : mOutputFolder(std::move(outputFolder))
      , mOpusMode(mode)
  {
    std::filesystem::create_directories(mOutputFolder);
  }


  std::string OpusTask::Execute(const std::istream& is, const std::string& inputFilePath)
  {
    const auto output_file_path = GetOutputPath(inputFilePath);
    std::ofstream os(output_file_path);
    os << is.rdbuf();

    std::stringstream ss;
    ss << inputFilePath << " converted to " << output_file_path;
    return ss.str();
  }


  std::string OpusTask::GetOutputPath(const std::string& inputFilePath) const
  {
    const std::filesystem::path input_path(inputFilePath);
    std::filesystem::path output_path(mOutputFolder);
    output_path /= input_path.filename();

    switch(mOpusMode)
    {
      case OpusMode::Audio:
        output_path += ".audio";
        break;
      case OpusMode::LowDelay:
        output_path += ".lowdelay";
        break;
      case OpusMode::VoIP:
        output_path += ".voip";
        break;
    }
    return output_path.string();
  }
}
