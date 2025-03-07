#include "decompressor.h"
#include <zlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>

void decompressChunk(const std::vector<char>& input, std::vector<char>& output) {
    uLongf outputSize = input.size() * 4; // Estimate decompressed size
    output.resize(outputSize);
    uncompress(reinterpret_cast<Bytef*>(output.data()), &outputSize, reinterpret_cast<const Bytef*>(input.data()), input.size());
    output.resize(outputSize);
}

void Decompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    const size_t chunkSize = 1024 * 1024; // 1 MB
    std::vector<std::thread> threads;
    std::vector<std::vector<char>> decompressedChunks;

    while (!inFile.eof()) {
        std::vector<char> buffer(chunkSize);
        inFile.read(buffer.data(), chunkSize);
        buffer.resize(inFile.gcount());

        decompressedChunks.emplace_back();
        threads.emplace_back(decompressChunk, std::ref(buffer), std::ref(decompressedChunks.back()));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (const auto& chunk : decompressedChunks) {
        outFile.write(chunk.data(), chunk.size());
    }
}