# C++ File Compression and Decompression Application

*COMPANY*: CODTECH IT SOLUTIONS

*NAME*: MAHIPAL

*INTERN ID*:CT08PBA

*DOMAIN*: C++ PROGRAMMING

*DURATION*: 4 WEEKS

*MENTOR*: NEELA SANTHOSH


## Overview
This project is a C++ application that provides functionalities for compressing and decompressing files using multithreading to optimize performance. The application features a command-line interface for user interaction and demonstrates significant performance gains when handling large files.

## Project Structure
```
cpp-compression-app
├── src
│   ├── main.cpp
│   ├── compression
│   │   ├── compressor.cpp
│   │   └── compressor.h
│   ├── decompression
│   │   ├── decompressor.cpp
│   │   └── decompressor.h
│   ├── frontend
│   │   ├── ui.cpp
│   │   └── ui.h
│   └── utils
│       ├── file_utils.cpp
│       └── file_utils.h
├── CMakeLists.txt
└── README.md
```

## Features
- **Multithreaded Compression**: Utilizes multiple threads to compress files, significantly reducing processing time for large datasets.
- **Multithreaded Decompression**: Similar to compression, decompression is optimized for performance using multithreading.
- **User Interface**: A simple command-line interface allows users to easily compress and decompress files.

## Building the Application
To build the application, follow these steps:

1. Ensure you have CMake installed on your system.
2. Open a terminal and navigate to the project directory.
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   make
   ```

## Running the Application
After building the application, you can run it from the build directory:
```
./cpp-compression-app
```

## Performance Demonstration
To demonstrate the performance gains achieved through multithreading, you can use the following steps:

1. Prepare a large file (e.g., a text file or binary file) for testing.
2. Use the application to compress the file and note the time taken.
3. Decompress the file and again note the time taken.
4. Compare the performance with a single-threaded implementation (if available) to see the improvements.

## Conclusion
This C++ application showcases the power of multithreading in file compression and decompression tasks, providing users with a fast and efficient tool for managing their files.

Output:

![Image](https://github.com/user-attachments/assets/b4e82d96-80fa-4228-8975-023467510361)
