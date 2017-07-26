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

#ifndef __FEATURE_EXTRACTOR_HPP__
#define __FEATURE_EXTRACTOR_HPP__

#include <unordered_map>
#include <memory>
#include <initializer_list>

#include <resembla/string_util.hpp>
#include <resembla/resembla_interface.hpp>

#include "../feature.hpp"

namespace resembla {

class FeatureExtractor
{
public:
    using string_type = resembla::string_type;
    using return_type = StringFeatureMap;

    static const char FEATURE_DELIMITER;
    static const char KEYVALUE_DELIMITER;

    struct Function
    {
        virtual Feature::text_type operator()(const string_type& text) const = 0;
    };

    template<class F>
    struct StringToStringFunction: public Function
    {
        StringToStringFunction(){}
        StringToStringFunction(F f): f(f){}

        Feature::text_type operator()(const string_type& text) const
        {
            return Feature::toText(f(text));
        }

    private:
        const F f;
    };

    FeatureExtractor(const std::string base_similarity_key = "base_similarity");

    void append(Feature::key_type key, std::shared_ptr<Function> func);

    // load features of corpus texts
    return_type operator()(const std::string& raw_text, const std::string& raw_features) const;
    // extract features from corpus text using already loaded features
    return_type operator()(const ResemblaInterface::response_type& data, const return_type& given_features) const;
    // extract features from unknown text
    return_type operator()(const string_type& text) const;

protected:
    const std::string base_similarity_key;

    std::unordered_map<Feature::key_type, std::shared_ptr<Function>> functions;
};

}
#endif