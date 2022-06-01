# Task Runner Tech Test

## INTRODUCTION

All the instructions are in the [assignment file](./ASSIGNMENT.md).

Following chapters are here as an answer to the assignment.

## HOW TO BUILD

MSVC-CMake approach have been kept. Just open the git-versioned cmake folder with your visual studio IDE and build it.

Only *x64-Debug* configuration is supported for demo shortcut purpose.

## HOW TO RUN

Once built, you can find ubi_tasks generated executable under out/build/x64-Debug folder

You can run it by following the usage below

Usage:
  Ubi-Tasks [OPTION...]
  
  	-i, --input arg   MANDATORY -- input directory path
  	-t, --type arg    MANDATORY -- the type of task to execute (opus / hash)
  	-o, --output arg  (opus only) output directory path (default:
	                    ./OPUS_OUTPUT)
  	-m, --mode arg    (opus only) opus mode (voip, audio or lowdelay) (default:
        	            audio)
  	-s, --seed arg    (hash only) the CRC32 seed (default: 0)
  	-h, --help        Print usage


Anyway, usage appears if you do not provide mandatory parameters

## MADE ASSUMPTIONS

* Parallelisation have only be done within a unique task		
* I guess the whole purpose would be to achieve this scenario:
	1. Do a crc32 on a file
	2. Encode it
	3. Send it + Computed CRC
	4. Decode it
	5. Check CRC on decoded file
		

## QUESTION ANSWERS

* Parallelization approach and why?
	* Used async / future pattern ; to launch several tasks in parallel and can wait easily for each result

* How long did it take you to complete this assignment?
	* 1h for the environment setup / documentation
	* 1h for architecture
	* 0.5h for crc32 task
	* 1.5h for opus task
	* 1h for options
	--> 5h

* What would you do if you had more time?
	* About project organization
		* I would have created a unit test project, to be able to at least do non-regression tests, 
		with more time planned I would have started by this, instead of that, I used the ubi tasks project as unit test / sandbox in a first step
		* I would have set "warning treat as error" option on, to avoid any easy to detect issue
	* About development improvement
		* I would have introduce loading status as a percentage of each task running in parallel
		* Add a logging system
		* Use coroutines / string generator to share results between the main (UI) and the runner
		* More input to Opus encoding (currently limited to *big-endian 16-bit signed int 48KHz Stereo PCM*)
		* Would use cxxopts::results to make more generic any ITask parameter usage
	* About project further steps		
		* Could be enlarged to to run several tasks by
			* capturing several -t options with cxxopts
			* doing several tasks on the -i directory by extending the task runner / task factory
		* adding sending / decoding / check CRC task
		* extending directory to network locations

* What is your feedback on the assignment?
	* Really enjoyed discovering opus & cxxopts lib! Thanks for that!
	* Could help to have quick samples as input for both tasks






