# C++ Engineer - Test task

Thank you for applying to Ubisoft. An important early step in our interview process is a take-home assignment. We feel
like completing this assignment will give us a better chance to learn about you than a traditional whiteboard session,
and you’ll be better positioned to show your strengths.

The goal of this assignment is to understand your C++ skills, what is your approach to dealing with constraints and
ambiguity of the real world while optimizing your solution, as well as introduce you to the technical problems of game
streaming. You are expected to make a variety of assumptions from the information given to you and clearly document them
in your project README.

## Task

We ask you to create a command-line tool which can launch a pre-defined task on every file in a directory. The aim of
this tool is to be able to spread repetitive work across the different units of the CPU. Each task outputs a string,
here are the possible tasks:

* Compute an CRC32 checksum, printing the sum into the std output.
* Encode a raw audio PCM stream with the opus encoder (the output is a file created with the encoded audio stream data).

The tool should take a directory path as its input and execute the task on every file in the input directory. It should
be possible to run the tasks concurrently. It’s up to you to decide how exactly to parallelize them. Please make sure
you explain your approach and reasoning in the README file.

For a faster bootstrap, we provide a skeleton for the project, giving you:

* A standard CMake toolchain for MSVC
* A pre-built version of opusenc and opus built with MSVC for x64 with MT runtime
* The header-only cxxopts library to easily parse the command-line
* A quick implementation of the CRC32 algorithm

You are free to reshape everything to your liking, it is just a way to start faster. Also, if you don’t have an MSVC
environment, you can change it, but we will judge the work on a Windows machine in any case.

**Important**: your goal is to focus on the runner and the ability to talk to other APIs, so feel free to cut corner and
have reasonable expectation. For instance, you can assume a fixed audio format for inputs (e.g., 16-bit signed int PCM).

Here are the minimal command line options it can support:

* `-i` – input directory path
* `-t` – the type of task to execute (opus / hash)
* `-o` – (opus only) output directory path
* `-m` – (opus only) opus mode (voip, audio or lowdelay)
* `-s` – (hash only) the CRC32 seed

## Expectations

* Code is thread-safe and stable.
* Using at least C++14 standard.
* Usage of STL (boost should not be necessary).
* Extensibility to other kinds of tasks or other arguments to send to the tasks.
* Good code structure and organization.

We’ll give extra points to

* Well-articulated assumptions and explanations of how you designed the tool.
* History of commits to illustrate the incremental progress on the implementation.
* Maintainability of your solution.

## Submission

Please use git and submit your solution with a link to a private repo on GitHub
(also, add lpetit-ubi account as a collaborator to your repo).

Before sending an email with your submission, please take a minute and answer the following questions adding answers to
your project README file.

* How long did it take you to complete this assignment?
* What would you do if you had more time?
* What is your feedback on the assignment?

We hope this task will be a flexible way to show your skills and you’ll enjoy it. We will ask you to restrict yourself
to 4 to 5 hours. If you want to continue after that, you’re free to do so, but we will ask you to provide the commit
number that you had after 5 hours.

Some references

* `Opus`. The opus encoding is a way to compress an audio stream used in a variety of applications, especially in VoIP
  usages. The core encoding project is available here https://github.com/xiph/opus <br>
  However, we additionally provide https://github.com/xiph/libopusenc which can produce opus streams in an ogg container
  directly.
* `PCM`. A PCM audio stream is a stream of values representing the sound wave at a fixed sampling rate (usually 44100Hz
  or 48000Hz). In technical terms, it can be either an integer bound between INT_MIN and INT_MAX (typically 16-bit). Or
  it can be a float bound between –1.0 and 1.0. A frame is one sample per channel. In the case of stereo audio, it
  consists of two samples. It is possible to produce raw PCM streams using softwares like Audacity (file->export->other
  uncompressed->RAW).

Good luck!

The game streaming team @ Ubisoft.