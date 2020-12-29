@echo off
:start
rand
Greedy_algorithm_op+MKL
1

fc 1.out 2.out
if errorlevel == 1 pause
:end
goto start