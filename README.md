# Huffman Encode and Decode

A huffman encode and decode program implemented in C++.

## Requirements

- GNU g++, make
- CMake version 3.0 or higher

## Build

Do the following commands:

```shell
$mkdir build && cd build
$cmake ../ -DCMAKE_BUILD_TYPE=Release
#if you'd like to debug this program,please set TYPE as "Debug"
$make
```

## Run

```shell
$comp <filename> <compressed file name> #to compress file
$extr <filename> <extracted file name> #to extract file
```

- Data Set：<https://en.wikibooks.org/wiki/Special:Random>
