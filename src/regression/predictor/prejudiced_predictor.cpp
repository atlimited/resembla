/*
Resembla
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

#include "prejudiced_predictor.hpp"

namespace resembla {

const std::string PrejudicedPredictor::DEFAULT_KEY = "base_similarity";

PrejudicedPredictor::PrejudicedPredictor(const std::string& key):
    name(key), key(key)
{}

PrejudicedPredictor::PrejudicedPredictor(const std::string& name, const std::string& key):
    name(name), key(key)
{}

PrejudicedPredictor::output_type PrejudicedPredictor::operator()(const input_type& x) const
{
    return x.at(key);
}

}
