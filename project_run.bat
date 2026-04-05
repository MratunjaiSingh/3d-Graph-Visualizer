@echo off
cls
echo ---------------------------------------------------
echo  Compiling 3D Graph Visualizer...
echo ---------------------------------------------------

:: Hum root directory se compile kar rahe hain
:: -I. ka matlab hai ki current folder ko bhi search path mein rakho
g++ Example/main.cpp src/VisualGraphDSA.cpp -o main.exe -I. -IInclude -L. -lfreeglut -lopengl32 -lglu32

:: Check if compilation was successful
if %errorlevel% equ 0 (
    echo  Compilation Success! Launching...
    echo ---------------------------------------------------
    main.exe
) else (
    echo 
     Compilation Failed! Check the errors above.
    pause
)

