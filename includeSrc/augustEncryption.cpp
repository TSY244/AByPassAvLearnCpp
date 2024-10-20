//
// Created by au9u5t on 24-10-11.
//

#include "../include/augustEncryption.h"

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

    std::string encode(const std::string &input)
    {
        static const std::vector<int> reverse_custom_base64_lookup = create_reverse_custom_base64_lookup();
        std::string encoded;
        int val = 0, valb = -6;
        for (unsigned char c : input)
        {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0)
            {
                encoded.push_back(custom_base64_chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6)
        {
            encoded.push_back(custom_base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
            if (encoded.size() % 4 == 3)
            {
                encoded.push_back('`');
            }
            else if (encoded.size() % 4 == 2)
            {
                encoded.push_back('`');
                encoded.push_back('|');
            }
        }
        return encoded;
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