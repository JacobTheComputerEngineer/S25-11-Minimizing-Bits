# S25-11 Minimizing Bits for Communication ECE 4805/6 Virginia Tech

### Members: Richard Martinez, Kylan Montgomery, Nate Sawitzki, Jacob Ramirez, Michael Volkman
### Sponsor: Jeremy Werner, DOT&E
### Subject Matter Expert: Yaling Yang
### Mentor: Joe Adams

In remote environments, limited bandwidth and low data rates often hinder the effective use of digital communication infrastructure. To address this challenge, we have developed an innovative encoding scheme that optimizes bit efficiency while preserving message readability. The potential use cases include military field operations and commercial scenarios where efficient and reliable point-to-point communication is critical.

## Build Instructions

Please follow these instructions to build the executable for S25-11.

1) Clone this repo:

You could use https or ssh.
Make sure your current working directory is this folder.

```
git clone https://github.com/JacobTheComputerEngineer/S25-11-Minimizing-Bits.git
```

Also, consider disabling automatic line endings when touched by Git.
(This is not mandatory, just a time saver)

```
git config --local core.autocrlf false
```

2) Build the docker image:

This may take a few minutes and should only need to be done once
(unless the dockerfile changes).

```
docker build . -t s25-11
```

3) Instantiate a container:

Run this command in this directory.
Consider putting this into an alias because it is quite long.

```
docker run --rm -it --mount type=bind,src=$PWD,dst=/mnt s25-11
```

You should now be inside the docker container file system.

4) Make a build directory and use CMake:

```
mkdir build
cd build
cmake ..
cmake --build .
```

5) Run the executables:

There should now be two binaries in the build directory

```
./erl          # The main erl binary
./unittests    # Unittests for erl
```

To use the erl binary, please use the following syntax:

```
./erl <INPUT FILE> <DICTIONARY FILE> <OUTPUT FILE>
```

The file extension of the input file will determine if the encoder or decoder process is executed.
For example:

```
./erl message.txt dictionary.txt encoded.erl    # Encoder
./erl encoded.erl dictionary.txt decoded.txt    # Decoder
```

It is critical that both the encoder and decoder have access to the same dictionary file.
Otherwise, the outputs will not be human-readable.

To run the unittests binary, simply execute it directly:

```
./unittests
-------------------
All tests passed.
```

Observe that all the tests pass.

6) Be aware of the following build options:

There are several CMake targets added for convenience.
These can be included or excluded in any combination.

```
cmake -DSTRICT=True -DTIDY=True -DMEMORY=True -DCOVERAGE=True ..
```

STRICT enables the compiler in strict mode. Warnings are considered errors.\
TIDY enables the clang-tidy code checker.\
MEMORY enables the valgrind memory leak checker.\
COVERAGE enables the lcov code coverage checker.

There is also a FULL target that will enable everything.

```
cmake -DFULL=True ..
```

To use any of these targets, build using cmake then invoke it as shown below.

```
cmake -DFULL=True ..
cmake --build .                       # Strict compiler used here

cmake --build . --target memory       # Run valgrind memory test
cmake --build . --target tidy         # Run code style checker
cmake --build . --target coverage     # Run code coverage check
```

7) Generate code documenation:

In the source directory, run:

```
doxygen Doxyfile
```

This will generate HTML documentation of the source code to the `./docs/html/` directory.
The main page can then be viewed offline at `./docs/html/index.html`.

8) Exit the container

You can exit the docker container command line interface at any time:

```
exit
```
