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

#ifndef RESEMBLA_BASIC_RESEMBLA_HPP
#define RESEMBLA_BASIC_RESEMBLA_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <mutex>

#include <simstring/simstring.h>
#include <json.hpp>

#include "resembla_interface.hpp"
#include "csv_reader.hpp"
#include "eliminator.hpp"
#include "reranker.hpp"

namespace resembla {

template<typename Preprocessor, typename ScoreFunction>
class BasicResembla: public ResemblaInterface
{
public:
    BasicResembla(const std::string& db_path, const std::string& inverse_path,
            int simstring_measure, double simstring_threshold, size_t max_candidate,
            std::shared_ptr<Preprocessor> preprocess, std::shared_ptr<ScoreFunction> score_func,
            bool preprocess_corpus = true, size_t preprocessed_data_col = 3):
        simstring_measure(simstring_measure), simstring_threshold(simstring_threshold),
        max_candidate(max_candidate), reranker(),
        preprocess(preprocess), score_func(score_func), preprocess_corpus(preprocess_corpus)
    {
        db.open(db_path);

        for(const auto& columns: CsvReader<string_type>(inverse_path, 2)){
            const auto& indexed = columns[0];
            const auto& original = columns[1];

            const auto& p = inverse.insert(std::pair<string_type, std::vector<string_type>>(indexed, {original}));
            if(!p.second){
                p.first->second.push_back(original);
            }

            if(preprocess_corpus){
                if(preprocessed_data_col > 0 && preprocessed_data_col - 1 < columns.size() &&
                        !columns[preprocessed_data_col - 1].empty()){
                    nlohmann::json j = nlohmann::json::parse(
                            cast_string<std::string>(columns[preprocessed_data_col - 1]));
                    typename Preprocessor::output_type preprocessed = j;
                    preprocessed_corpus[original] = std::make_pair(original, preprocessed);
                }
                else{
                    preprocessed_corpus[original] = std::make_pair(original, (*preprocess)(original, true));
                }
            }
        }
    }

    std::vector<output_type> find(const string_type& query,
            double threshold = 0.0, size_t max_response = 0) const
    {
        string_type search_query = preprocess->index(query);

        // search from N-gram index
        std::vector<string_type> simstring_result;
        {
            std::lock_guard<std::mutex> lock(mutex_simstring);
            db.retrieve(search_query, simstring_measure, simstring_threshold,
                    std::back_inserter(simstring_result));
        }
        if(simstring_result.empty()){
            return {};
        }
        else if(simstring_result.size() > max_candidate){
            Eliminator<string_type> eliminate(search_query);
            eliminate(simstring_result, max_candidate);
        }

        std::vector<string_type> candidate_texts;
        for(const auto& i: simstring_result){
            if(i.empty()){
                continue;
            }
            const auto& j = inverse.at(i);
            std::copy(std::begin(j), std::end(j), std::back_inserter(candidate_texts));
        }

        return eval(query, candidate_texts, threshold, max_response);
    }

    std::vector<output_type> eval(const string_type& query, const std::vector<string_type>& candidates,
            double threshold = 0.0, size_t max_response = 0) const
    {
        // load preprocessed data if preprocessing is enabled. otherwise, process corpus texts on demand
        std::vector<WorkData> work;
        for(const auto& t: candidates){
            if(preprocess_corpus){
                const auto i = preprocessed_corpus.find(t);
                if(i != std::end(preprocessed_corpus)){
                    work.push_back(i->second);
                    continue;
                }
            }
            auto tabpos = t.find(column_delimiter<string_type::value_type>());
            work.push_back(std::make_pair(
                tabpos != string_type::npos ? t.substr(0, tabpos) : t,
                (*preprocess)(t, true)));
        }

        // execute reranking
        auto input_data = std::make_pair(query, (*preprocess)(query, false));
        std::vector<output_type> response;
        for(const auto& r: reranker.rerank(input_data, work.begin(), work.end(),
                *score_func, threshold, max_response)){
            response.push_back({r.first, score_func->name, r.second});
        }
        return response;
    }

protected:
    using WorkData = std::pair<string_type, typename Preprocessor::output_type>;

    mutable simstring::reader db;
    mutable std::mutex mutex_simstring;
    std::unordered_map<string_type, std::vector<string_type>> inverse;

    const int simstring_measure;
    const double simstring_threshold;
    const size_t max_candidate;
    const Reranker<string_type> reranker;

    const std::shared_ptr<Preprocessor> preprocess;
    const std::shared_ptr<ScoreFunction> score_func;

    const bool preprocess_corpus;
    std::unordered_map<string_type, WorkData> preprocessed_corpus;
};

}
#endif
