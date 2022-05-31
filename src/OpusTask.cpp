#include "OpusTask.h"
#include "opus.h"

#include <filesystem>
#include <fstream>


namespace UbiTasks
{
  constexpr size_t FRAME_SIZE = 960;
  constexpr auto SAMPLE_RATE = 48000;
  constexpr auto CHANNELS = 2;
  
  OpusTask::OpusTask(std::filesystem::path outputFolder, OpusMode mode)
    : mOutputFolder(std::move(outputFolder))
      , mOpusMode(mode)
  {
    create_directories(mOutputFolder);

    int opus_application = 0;
    switch(mOpusMode)
    {
      case OpusMode::Audio:
        opus_application = OPUS_APPLICATION_AUDIO;
        break;
      case OpusMode::LowDelay:
        opus_application = OPUS_APPLICATION_RESTRICTED_LOWDELAY;
        break;
      case OpusMode::VoIP:
        opus_application = OPUS_APPLICATION_VOIP;
        break;
    }
    
    int error = 0;
    mOpusEncoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, opus_application, &error);
    if(error != OPUS_OK)
    {
      throw std::runtime_error{"Opus Error creating encoder: " + std::string(opus_strerror(error))};
    }
  }


  std::string OpusTask::Execute(std::istream& is, const std::filesystem::path& inputFilePath)
  {
    // check to be extended to any supported entry format
    if(inputFilePath.extension() != ".raw")
    {
      throw std::runtime_error{"Unexpected input file extension ; waiting for .raw ; got '" + inputFilePath.extension().string() + "'"};
    }
    const auto output_file_path = GetOutputPath(inputFilePath);
    std::ofstream os(output_file_path);

    // to be moved into stdx::file::size() homemade helper
    is.seekg(0, std::ios::end);
    auto input_length = static_cast<size_t>(is.tellg());
    is.seekg(0, std::ios::beg);


    while(input_length > 0)
    {
      char input_data[FRAME_SIZE * CHANNELS * sizeof(int16_t)]; // input file are fixed to signed 16-bit PCM raw files
      uint8_t output_data[FRAME_SIZE * CHANNELS];
      
      // reading a frame from the input file
      is.read(input_data, sizeof(input_data));

      const auto read_size = is.gcount();

      if(read_size == 0)
      {
        break;
      }

      // remaining reading size
      input_length -= read_size;
      
      opus_int32 encoded_size;
      {
        // encoding the opus raw data to the desired audio application
        std::unique_lock shield(mEncoderMutex); // protect the encoder as it is might be changed
        encoded_size = opus_encode(mOpusEncoder, reinterpret_cast<const opus_int16*>(input_data), FRAME_SIZE, output_data, sizeof(output_data));
      }

      if(encoded_size < 0)
      {
        throw std::runtime_error{"Opus Error decoding input: " + std::string(opus_strerror(encoded_size))};
      }

      // write the encoded stream to the output file
      os.write(reinterpret_cast<char*>(output_data), encoded_size);
    }
    
    return " Conversion to " + output_file_path.filename().string() + " OK ";
  }


  OpusTask::~OpusTask()
  {
    opus_encoder_destroy(mOpusEncoder);
  }


  std::filesystem::path OpusTask::GetOutputPath(const std::filesystem::path& inputFilePath) const
  {
    std::filesystem::path output_path(mOutputFolder);
    output_path /= inputFilePath.filename();
    
    switch(mOpusMode)
    {
      case OpusMode::Audio:
        output_path.replace_extension("audio");
        break;
      case OpusMode::LowDelay:
        output_path.replace_extension("lowdelay");
        break;
      case OpusMode::VoIP:
        output_path.replace_extension("voip");
        break;
    }
    return output_path;
  }
}
