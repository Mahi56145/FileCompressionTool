#include "server.h"
#include "httplib.h"
#include "compression/compressor.h"
#include "decompression/decompressor.h"
#include "utils/file_utils.h"
#include <iostream>

void startServer() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(R"(
            <!DOCTYPE html>
            <html lang="en">
            <head>
                <meta charset="UTF-8">
                <title>Compression Web App</title>
                <link rel="stylesheet" href="/style.css">
            </head>
            <body>
                <h1>Compression Web App</h1>
                <form action="/compress" method="post" enctype="multipart/form-data">
                    <h2>Compress</h2>
                    <label for="inputFile">Input File:</label>
                    <input type="file" id="inputFile" name="inputFile"><br>
                    <label for="compressionLevel">Compression Level (1-9):</label>
                    <input type="number" id="compressionLevel" name="compressionLevel" min="1" max="9"><br>
                    <input type="submit" value="Compress">
                </form>
                <form action="/decompress" method="post" enctype="multipart/form-data">
                    <h2>Decompress</h2>
                    <label for="inputFile">Input File:</label>
                    <input type="file" id="inputFile" name="inputFile"><br>
                    <input type="submit" value="Decompress">
                </form>
            </body>
            </html>
        )", "text/html");
    });

    svr.Post("/compress", [](const httplib::Request& req, httplib::Response& res) {
        auto file = req.get_file_value("inputFile");
        std::string inputFile = "uploads/" + file.filename;
        std::string outputFile = "uploads/" + file.filename + "_compressed.bin";
        int compressionLevel = std::stoi(req.get_param_value("compressionLevel"));

        std::ofstream ofs(inputFile, std::ios::binary);
        ofs.write(file.content.c_str(), file.content.size());

        Compressor compressor;
        compressor.compress(inputFile, outputFile, compressionLevel);

        res.set_content("Compression successful! Download the file <a href=\"/" + outputFile + "\">here</a>.", "text/html");
    });

    svr.Post("/decompress", [](const httplib::Request& req, httplib::Response& res) {
        auto file = req.get_file_value("inputFile");
        std::string inputFile = "uploads/" + file.filename;
        std::string outputFile = "uploads/" + file.filename + "_decompressed.txt";

        std::ofstream ofs(inputFile, std::ios::binary);
        ofs.write(file.content.c_str(), file.content.size());

        Decompressor decompressor;
        decompressor.decompress(inputFile, outputFile);

        res.set_content("Decompression successful! Download the file <a href=\"/" + outputFile + "\">here</a>.", "text/html");
    });

    svr.set_mount_point("/", "./web");
    svr.listen("localhost", 8080);
}