# ECE 4806 S25-11 dockerfile
# Adapted from ECE 3574
# Version: 1
# Date: Jan 30 2025

FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV ECE3574_REFERENCE_ENV="Y"

RUN apt-get update && apt-get upgrade
RUN apt-get -y install build-essential coreutils cmake
RUN apt-get -y install python3-pip python3-dev
RUN apt-get -y install valgrind lcov doxygen
RUN apt-get -y install clang clang-tidy
RUN apt-get -y install dos2unix
RUN apt-get -y install libicu-dev pkg-config

RUN pip3 install gcovr pexpect

WORKDIR /mnt

