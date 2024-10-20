//
// Created by au9u5t on 24-10-11.
//

#ifndef ARINGQUSEMAKEFILE_AUGUSTENCRYPTION_H
#define ARINGQUSEMAKEFILE_AUGUSTENCRYPTION_H

#include <string>
#include <vector>

namespace augustEncryption
{

    std::vector<int> create_reverse_custom_base64_lookup();

    std::string encode(const std::string &input);

    std::string decode(const std::string &encoded);

}
#endif // ARINGQUSEMAKEFILE_AUGUSTENCRYPTION_H
