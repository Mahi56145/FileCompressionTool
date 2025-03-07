#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>

class Compressor {
public:
    void compress(const std::string& inputFile, const std::string& outputFile, int compressionLevel);
};

#endif // COMPRESSOR_H