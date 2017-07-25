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

#ifndef __REAL_FEATURE_AGGREGATOR_HPP__
#define __REAL_FEATURE_AGGREGATOR_HPP__

#include "feature_aggregator.hpp"

namespace resembla {

struct RealFeatureAggregatorImpl
{
    Feature::real_type operator()(Feature::real_type a, Feature::real_type b) const;
};
using RealFeatureAggregator = FeatureAggregator::StringsToRealFunction<RealFeatureAggregatorImpl>;

}
#endif