#include "compressor.h"
#include <zlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>

void compressChunk(const std::vector<char>& input, std::vector<char>& output, int compressionLevel) {
    uLongf outputSize = compressBound(input.size());
    output.resize(outputSize);
    compress2(reinterpret_cast<Bytef*>(output.data()), &outputSize, reinterpret_cast<const Bytef*>(input.data()), input.size(), compressionLevel);
    output.resize(outputSize);
}

void Compressor::compress(const std::string& inputFile, const std::string& outputFile, int compressionLevel) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    const size_t chunkSize = 1024 * 1024; // 1 MB
    std::vector<std::thread> threads;
    std::vector<std::vector<char>> compressedChunks;

    while (!inFile.eof()) {
        std::vector<char> buffer(chunkSize);
        inFile.read(buffer.data(), chunkSize);
        buffer.resize(inFile.gcount());

        compressedChunks.emplace_back();
        threads.emplace_back(compressChunk, std::ref(buffer), std::ref(compressedChunks.back()), compressionLevel);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (const auto& chunk : compressedChunks) {
        outFile.write(chunk.data(), chunk.size());
    }
}