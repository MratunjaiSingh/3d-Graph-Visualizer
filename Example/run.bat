@echo off
g++ main.cpp ../src/VisualGraphDSA.cpp -o myProject.exe -I../Include -lfreeglut -lglew32 -lopengl32 -lglu32
if %errorlevel% neq 0 (
    echo Compilation Failed!
    pause
    exit /b
)
echo Compilation Success! Running Project...
myProject.exe
pause