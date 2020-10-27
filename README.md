# Clean Code Contest 2020

Welcome to clean code contest 2020! A default project is already created with a preset docker environment.
Below software stacks are prepared in this docker image:
- GCC 9.3 (full C++17 support)
- CMake 3.16.3
- Boost C++ library (1.71.0)
- GDB 9.1
- Bash 5.0
- Valgrind 3.15
- CppCheck 1.9
- Google Test/Google Mock 

## Build and CI/CD
Gitlab CI automation is already set for this repository, so **any commit** would trigger prebuilt pipleines automatically, and you can check those jobs' status from gitlab page
- Build
- Unit test
- Quality check including cppcheck/sanitizer check/valgrind memory check 

>Please do NOT change the .gitlab-ci.yml file.

>**For university students:**
>The access to gitlab is not available for non-NOKIA users. The results will be sent in other ways.

### CMake Targets and Sample Commands - for Starters
A default CMakeLists.txt is prepared so you can follow traditional CMake configure/generate/build workflow

```bash
mkdir bld
cmake ../
make help
```

Various configurations are also provided so you can pass in additional command line arguments and optional parameters to `cmake` command. For exmaple `cmake -DENABLE_CPPCHECK=1 ../` would integrate `cppcheck` automatically in build procedure.

Supported options
- Pass in `-DCMAKE_BUILD_TYPE=Sanitizer` to enable sanitizer checkers during build procedure.
- Pass in `-DENABLE_VALGRIND=1 -DCMAKE_BUILD_TYPE=Debug` to enable debug build with valgrind check enabled.
- Pass in `-DENABLE_CPPCHECK=1` to enable cppcheck.

> It is always recommended to use out-of-source build so you can have as many build directories as you like, with each of them reserving dedicated build dependencies and intermediate build artifacts.

#### Default Build Targets

1. Just issue the `make` command in your binary directory then both the executable and test binary file will be created.
2. Use `make test` command to run all tests.
3. Use `make ut` to build and run all unit tests in verbose mode.
4. Use `make it` to build and run all integration tests.

> Under the hood, ctest tool is used to organize all test cases.

#### Valgrind memory check
You have to pass in `Debug` as `CMAKE_BUILD_TYPE` and enable valgrind by `-DENABLE_VALGRIND=1` so debug symbols are available when errors are reported.

To run valgrind check, just use `make memcheck` command.

### Working with provided CMake framework
Follow the comments as provided in `CMakeLists.txt` when you add more files or complicated structures

- Add new include directories to project search path by `include_directories(dir1 dir2 ...)`, by default this assumes current working directory from top level of the project.
- Add additional source files to `srcs` list by explictly list each new files on by one. Default working directory is project top directory.
- Add test files similarly like source files.

You can also add new files that can be shared between test build and target build, see more details from CMake official documentation.

## Local Environment Setup

There are two different approaches to get started:
- Docker based development: also check the VSCode docker extension if you program with VSCode
- Virtual machine based environment: easier if you have no docker access

### Docker Based Environment
If you'd like to setup a local development environment, the easiest way is to start with prebuilt docker image (if you have a Linux machine with root access).

1. Make sure you have `docker` installed on your Linux box (virtual machine is okay).
2. Run `./bootstrap.sh` command which would pull the images and prepare everything for you, **you need to have `sudo` enabled**.
3. Once everything is set, you shall be prompted to the container environment and current directory is mounted to `/ccc2020` directory.

> Docker image is stored on dockerhub, you may need to setup proxy to access dockerhub. Check dockerhub documentation for more details.

#### Image Details - Advanced Users only
See below docker image source
``` Dockerfile
FROM ubuntu:latest
RUN apt-get update
RUN apt-get -y install build-essential gcc

ENV TZ=Etc/UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get -y install googletest google-mock cppcheck valgrind
RUN apt-get -y install cpputest libcpputest-dev
RUN apt-get -y install cmake 

RUN apt-get -y install libboost-all-dev

# We have to install googletest manually
RUN cd /usr/src/googletest && cmake . && cmake --build . --target install
```

### Virtual Machine Based Environment
There is also a prebuilt virtual machine created (Ubuntu 20.04.1 LTS based) that prepares almost everything for you. You can download it from the link in mail of contest committee.
