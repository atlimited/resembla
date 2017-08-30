/*
Resembla: Word-based Japanese similar sentence search library
https://github.com/tuem/resembla

Copyright 2017 Takashi Uemura

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <string>

#include <unicode/normalizer2.h>

#include "string_util.hpp"

namespace resembla {

class SymbolNormalizer
{
public:
    SymbolNormalizer(const std::string& nrm_dir, const std::string& nrm_name,
        const std::string& predefined_nrm_name, bool to_lower = false);
    virtual ~SymbolNormalizer();

    bool available() const;
    string_type operator()(const string_type& input) const;

protected:
    const Normalizer2* normalizer_resembla;
    const Normalizer2* normalizer_nfkc;
    bool to_lower;
};

}
