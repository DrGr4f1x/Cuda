@ECHO OFF
REM This batch file generates a new Deep-Learning project for Visual Studio 2022.
REM It is expected that python.exe is on your path and is version 3.0 or above.
python.exe Programs\ProjectGen\MakeNewProject.py %1 %2