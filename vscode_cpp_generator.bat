@echo off
echo:
set /p project_folder_name="Enter the name of the new project: "
set /p project_folder_path="Enter the path where the new project will be created: "

set full_project_path=%project_folder_path%\%project_folder_name%

echo:
echo The full project path is: %full_project_path%
echo:

: Creating the folder of the project.
mkdir %full_project_path%

: Copy all folders
: /E - Copy subdirectories, including any empty ones.
: /H - Copy files with hidden and system file attributes.
: /C - Continue copying even if an error occurs.
: /I - If in doubt, always assume the destination is a folder. e.g. when the destination does not exist.
xcopy ".vscode" %full_project_path%\".vscode" /E /H /C /I
xcopy "build" %full_project_path%\"build" /E /H /C /I
xcopy "src" %full_project_path%\"src" /E /H /C /I

: Copy all files
copy ".clang-format" %full_project_path%\".clang-format"
copy "CMakeLists.txt" %full_project_path%\"CMakeLists.txt"

call BatchSubstitute.bat "zero" %project_folder_name% %full_project_path%\CMakeLists.txt>%full_project_path%\CMakeLists2.txt
del %full_project_path%\CMakeLists.txt
rename %full_project_path%\CMakeLists2.txt CMakeLists.txt

call BatchSubstitute.bat "zero" %project_folder_name% %full_project_path%\.vscode\launch.json>%full_project_path%\.vscode\launch2.json
del %full_project_path%\.vscode\launch.json
rename %full_project_path%\.vscode\launch2.json launch.json

del %full_project_path%\build\dummy_file.txt
