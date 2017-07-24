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

#ifndef __WEIGHTED_SEQUENCE_BUILDER_HPP__
#define __WEIGHTED_SEQUENCE_BUILDER_HPP__

#include <vector>

#include "../string_util.hpp"

namespace resembla {

template<typename SequenceTokenizer, typename WeightFunction>
class WeightedSequenceBuilder
{
public:
    struct token_type
    {
        typename SequenceTokenizer::token_type token;
        double weight;
    };

    using sequence_type = std::vector<token_type>;

    WeightedSequenceBuilder(const SequenceTokenizer tokenizer = SequenceTokenizer(), const WeightFunction weight_func = WeightFunction()): 
        tokenizer(tokenizer), weight_func(weight_func) {}

    sequence_type build(const string_type& text, bool is_original = false) const
    {
        sequence_type ws;
        auto s = tokenizer.build(text, is_original);
        for(size_t i = 0; i < s.size(); ++i){
            ws.push_back({s[i], weight_func(s[i], is_original, s.size(), i)});
        }
        return ws;
    }

    string_type buildIndexingText(const string_type& text) const
    {
        return tokenizer.buildIndexingText(text);
    }

protected:
    SequenceTokenizer tokenizer;
    WeightFunction weight_func;
};

}
#endif
