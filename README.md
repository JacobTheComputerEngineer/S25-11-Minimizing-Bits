# S25-11 Minimizing Bits for Communication ECE 4805/6 Virginia Tech

### Members: Richard Martinez, Kylan Montgomery, Nate Sawitzki, Jacob Ramirez, Michael Volkman
### Sponsor: Dr. Jeremy Werner, DOT&E
### Subject Matter Expert: Dr. Yaling Yang
### Mentor: Dr. Joe Adams

In remote environments, limited bandwidth and low data rates often hinder the effective use of digital communication infrastructure. To address this challenge, we have developed an innovative encoding scheme that optimizes bit efficiency while preserving message readability. The potential use cases include military field operations and commercial scenarios where efficient and reliable point-to-point communication is critical.

## Build Instructions

Please follow these instructions to build the executable for S25-11.

1) Clone this repo (or otherwise download it):

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
(unless the dockerfile changes). Again, make sure your current working directory is this folder.

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

The dictionary file can be swapped out for any text file that contains 8192 words each on its own line 
(see provided files for example).
The S25-11 team has provided a curated default English dictionary that has been designed to work
best on average for a given English message (defaultdictionary.txt). 
Having more domain knowledge about the distribution of words in a message would allow
for the dictionary to become more efficient.

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
cd /mnt/build
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

If the tidy or coverage script fails to run as expected, try using dos2unix:

```
cd /mnt/scripts
dos2unix *.sh
```

For the memory test, you should see the following output:

```
cd /mnt/build
cmake -DMEMORY=True ..
cmake --build .
cmake --build . --target memory
-------------------
All heap blocks were freed -- no leaks are possible
```

For the tidy test, you should see the following output:

```
cd /mnt/build
cmake -DTIDY=True ..
cmake --build .
cmake --build . --target tidy
-------------------
-- Running clang-tidy on *.cpp
...
```
No explicit warnings should be generated. Any suppressed warnings in the form `X warnings generated.` can be safely ignored.

For the coverage test, the coverage rate will be printed to the console:

```
cd /mnt/build
cmake -DCOVERAGE=True ..
cmake --build .
cmake --build . --target coverage
-------------------
Overall coverage rate:
  lines......: 93.2% (613 of 658 lines)
  functions..: 90.2% (55 of 61 functions)
```

This information will also be summarized in an offline HTML format.
The main page can be viewed offline at `./build/Coverage_Report/index.html`.

7) Run the integration test

In the build directory after compiling the binaries, there is a Python integration test.
This test file will run the encoder and decoder for a given input file.
The console output is checked to ensure the proper format.
Then, the final decoded message is compared to the original to ensure they have roughly the same contents.

```
cd /mnt/build
python3 ./integration_test.py
-------------------
Ran 1 test

OK
```

Observe that the integration test passed.

8) Generate code documenation:

In the source directory, run:

```
cd /mnt/
doxygen Doxyfile
```

This will generate HTML documentation of the source code to the `./docs/html/` directory.
The main page can then be viewed offline at `./docs/html/index.html`.

9) Exit the container

You can exit the docker container command line interface at any time:

```
exit
```
