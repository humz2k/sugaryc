import sys
import os
import subprocess
sys.path = [os.path.abspath(os.path.join(os.path.dirname( __file__ ), '..'))] + sys.path

def print_log(log,msg):
    if log:
        print(msg)

def find_compiler(log=False):
    # Prefered compiler
    preferred_compiler = 'g++'

    # Check if the user has set an environment variable
    compiler_env = os.getenv('SGCC_CXX')
    if compiler_env:
        print_log(log,"SGCC_CXX set to " + compiler_env)
        return compiler_env

    # List of compilers to check
    compilers = ['g++', 'clang++', 'c++']

    # Check each compiler to see if it's available
    for compiler in compilers:
        try:
            # Check if compiler is in PATH and get its version
            subprocess.run([compiler, '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
            print_log(log,f"Found compiler: {compiler}")
            return compiler
        except (subprocess.CalledProcessError, FileNotFoundError):
            continue

    print("No C++ compiler found. Please install a C++ compiler (preferable g++).")
    exit()
    return None