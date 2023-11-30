import os
import sys
import platform
import subprocess

project_root = os.path.dirname(os.path.abspath(__file__))+"\\..\\"
script_py387 = os.path.join(project_root,"include\\python","")
sys.path.append(script_py387)
import py387



import subprocess

# 定义CMake脚本内容
cmake_script = """
cmake_minimum_required(VERSION 3.12)

project(YourProjectName)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定使用的编译器为Clang
set(CMAKE_CXX_COMPILER "clang++")

# 指定使用的标准库为libc++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# 添加你的源文件
add_executable(YourExecutable main.cpp)
"""

# 将CMake脚本写入文件
with open("CMakeLists.txt", "w") as cmake_file:
    cmake_file.write(cmake_script)

# 使用subprocess运行CMake命令
subprocess.run(["cmake", "."], check=True)
subprocess.run(["make"], check=True)



'''
msys2_clang_command = [
    "C:/msys64/clang64.exe",
    "clang",
    "-o", 
    "C:/Users/k34ub/source/DevKit/tests/test_clang.exe",
    "C:/Users/k34ub/source/DevKit/tests/test_clang.cpp",
    ]
subprocess.run(msys2_clang_command, shell=True)
'''


#print('System name : ',os.name)
#print('Platform name : ',platform.system())

