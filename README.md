# S25-11-Minimizing-Bits

TODO: Fill out this file with more information

## Build Instructions

Please follow these instructions to build the WIP version of erl for S25-11.\
Written by Richard Martinez

1) Clone this repo:

You could use https or ssh.
Make sure your current working directory is this folder.

```
> git clone https://github.com/JacobTheComputerEngineer/S25-11-Minimizing-Bits.git
```

Also, make sure to disable automatic line endings when touched by Git.
(This is not mandatory, just a time saver)

```
> git config --local core.autocrlf false
```

2) Build the docker image:

This may take a few minutes and should only need to be done once
(unless the dockerfile changes).

```
> docker build . -t s25-11
```

3) Instantiate a container:

Run this command in this directory.
I like to put this into an alias because it is quite long.

```
> docker run --rm -it --mount type=bind,src=$PWD,dst=/mnt s25-11
```

You should now be inside the docker container file system.

4) Make a build directory and use CMake:

```
> mkdir build
> cd build
> cmake ..
> cmake --build .
```

5) Run the executables:

There should now be two binaries in the build directory

```
> ./erl          # The main erl binary
> ./unittests    # Unittests for erl
```

6) Be aware of the following options:

There are several CMake targets I added for convenience.
These can be included or excluded in any combination.
If you want me to add another target or are having an issue, let me know.
Maybe one for integration testing?

```
> cmake -DSTRICT=True -DTIDY=True -DMEMORY=True -DCOVERAGE=True ..
```

STRICT enables the compiler in strict mode. Warnings are considered errors.\
TIDY enables the clang-tidy code checker.\
MEMORY enables the valgrind memory leak checker.\
COVERAGE enables the lcov code coverage checker.

There is also a FULL target that will enable everything.

```
> cmake -DFULL=True ..
```

To use any of these targets, build using cmake then invoke it as shown below.

```
> cmake -DMEMORY=True ..
> cmake --build .

> cmake --build . --target memory
OR
> make memory
```
