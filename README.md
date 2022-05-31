# Task Runner Tech Test

## INTRODUCTION

All the instructions are in the [assignment file](./ASSIGNMENT.md).

Following chapters are here as an answer to the assignment.

## HOW TO BUILD

MSVC-CMake approach have been kept. Just open the git-versioned cmake folder with your visual studio IDE and build it.

Only *x64-Debug* configuration is supported for demo shortcut purpose.

## HOW TO RUN

Once built, you can find ubi_tasks generated executable under out/build/x64-Debug folder

You can run it with following commands

__[to complete]__

Anyway, usage appears if you do not provide expected parameters

## QUESTIONS ANSWERS

* Parallelization approach and why?
	* Used async / future pattern ; to launch several tasks in parallel and can wait easily for each result

* How long did it take you to complete this assignment?
	* __[to complete]__

* What would you do if you had more time?
	* About project organization
		* I would have created a unit test project, to be able to at least do non-regression tests, 
		with more time planned I would have started by this, instead of that, I used the ubi tasks project as unit test / sandbox in a first step
		* I would have set "warning treat as error" option on, to avoid any easy to detect issue
	* About development improvement
		* I would have introduce loading status as a percentage of each task running in parallel
		* Add a logging system
		* Use coroutines / string generator to share results between the main (UI) and the runner
		* More input to Opus encoding (currently limited to 16-bit signed int PCM)

* What is your feedback on the assignment?
	* __[to complete]__






