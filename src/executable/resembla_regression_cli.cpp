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

#include <iostream>
#include <string>
#include <random>
#include <memory>

#include <resembla/resembla_util.hpp>

#include "paramset.hpp"

#include "regression/regression_util.hpp"

using namespace resembla;

int main(int argc, char* argv[])
{
    init_locale();

    paramset::definitions defs = {
        {"resembla_measure", STR(weighted_word_edit_distance), {"resembla", "measure"}, "measure", 'm', "measure for scoring"},
        {"resembla_threshold", 0.2, {"resembla", "threshold"}, "threshold", 't', "measure for scoring"},
        {"resembla_max_reranking_num", 1000, {"resembla", "max_reranking_num"}, "max-reranking-num", 'r', "max number of reranking texts in Resembla"},
        {"simstring_measure_str", "cosine", {"simstring", "measure"}, "simstring-measure", 's', "SimString measure"},
        {"simstring_threshold", 0.2, {"simstring", "threshold"}, "simstring-threshold", 'T', "SimString threshold"},
        {"ed_simstring_threshold", -1, {"edit_distance", "simstring_threshold"}, "ed-simstring-threshold", 0, "SimString threshold for edit distance"},
        {"ed_max_reranking_num", -1, {"edit_distance", "max_reranking_num"}, "ed-max-reranking-num", 0, "max number of reranking texts for edit distance"},
        {"ed_base_weight", 1L, {"edit_distance", "base_weight"}, "ed-base-weight", 0, "base weight for edit distance"},
        {"wwed_simstring_threshold", -1, {"weighted_word_edit_distance", "simstring_threshold"}, "wwed-simstring-threshold", 0, "SimString threshold for weighted word edit distance"},
        {"wwed_max_reranking_num", -1, {"weighted_word_edit_distance", "max_reranking_num"}, "wwed-max-reranking-num", 0, "max number of reranking texts for weighted word edit distance"},
        {"wwed_mecab_options", "", {"weighted_word_edit_distance", "mecab_options"}, "wwed-mecab-options", 0, "MeCab options for weighted word edit distance"},
        {"wwed_base_weight", 1L, {"weighted_word_edit_distance", "base_weight"}, "wwed-base-weight", 0, "base weight for weighted word edit distance"},
        {"wwed_delete_insert_ratio", 10L, {"weighted_word_edit_distance", "delete_insert_ratio"}, "wwed-del-ins-ratio", 0, "cost ratio of deletion and insertion for weighted word edit distance"},
        {"wwed_noun_coefficient", 10L, {"weighted_word_edit_distance", "noun_coefficient"}, "wwed-noun-coefficient", 0, "coefficient of nouns for weighted word edit distance"},
        {"wwed_verb_coefficient", 10L, {"weighted_word_edit_distance", "verb_coefficient"}, "wwed-verb-coefficient", 0, "coefficient of verbs for weighted word edit distance"},
        {"wwed_adj_coefficient", 5L, {"weighted_word_edit_distance", "adj_coefficient"}, "wwed-adj-coefficient", 0, "coefficient of adjectives for weighted word edit distance"},
        {"wwed_ensemble_weight", 0.5, {"weighted_word_edit_distance", "ensemble_weight"}, "wwed-ensemble-weight", 0, "weight coefficient for weighted word edit distance in ensemble mode"},
        {"wped_simstring_threshold", -1, {"weighted_pronunciation_edit_distance", "simstring_threshold"}, "wped-simstring-threshold", 0, "SimString threshold for weighted pronunciation edit distance"},
        {"wped_max_reranking_num", -1, {"weighted_pronunciation_edit_distance", "max_reranking_num"}, "wped-max-reranking-num", 0, "max number of reranking texts for weighted pronunciation edit distance"},
        {"wped_mecab_options", "", {"weighted_pronunciation_edit_distance", "mecab_options"}, "wped-mecab-options", 0, "MeCab options for weighted pronunciation edit distance"},
        {"wped_mecab_feature_pos", 7, {"weighted_pronunciation_edit_distance", "mecab_feature_pos"}, "wped-mecab-feature-pos", 0, "Position of pronunciation in feature for weighted pronunciation edit distance"},
        {"wped_mecab_pronunciation_of_marks", "", {"weighted_pronunciation_edit_distance", "mecab_pronunciation_of_marks"}, "wped-mecab-pronunciation-of-marks", 0, "pronunciation in MeCab features when input is a mark"},
        {"wped_base_weight", 1L, {"weighted_pronunciation_edit_distance", "base_weight"}, "wped-base-weight", 0, "base weight for weighted pronunciation edit distance"},
        {"wped_delete_insert_ratio", 10L, {"weighted_pronunciation_edit_distance", "delete_insert_ratio"}, "wped-del-ins-ratio", 0, "cost ratio of deletion and insertion for weighted pronunciation edit distance"},
        {"wped_ensemble_weight", 0.5, {"weighted_pronunciation_edit_distance", "ensemble_weight"}, "wped-ensemble-weight", 0, "weight coefficient for weighted pronunciation edit distance in ensemble mode"},
        {"wred_simstring_threshold", -1, {"weighted_romaji_edit_distance", "simstring_threshold"}, "wred-simstring-threshold", 0, "SimString threshold for weighted romaji edit distance"},
        {"wred_max_reranking_num", -1, {"weighted_romaji_edit_distance", "max_reranking_num"}, "wred-max-reranking-num", 0, "max number of reranking texts for weighted romaji edit distance"},
        {"wred_mecab_options", "", {"weighted_romaji_edit_distance", "mecab_options"}, "wred-mecab-options", 0, "MeCab options for weighted romaji edit distance"},
        {"wred_mecab_feature_pos", 7, {"weighted_romaji_edit_distance", "mecab_feature_pos"}, "wred-mecab-feature-pos", 0, "Position of pronunciation in feature for weighted romaji edit distance"},
        {"wred_mecab_pronunciation_of_marks", "", {"weighted_romaji_edit_distance", "mecab_pronunciation_of_marks"}, "wred-mecab-pronunciation-of-marks", 0, "pronunciation in MeCab features when input is a mark"},
        {"wred_base_weight", 1L, {"weighted_romaji_edit_distance", "base_weight"}, "wred-base-weight", 0, "base weight for weighted romaji edit distance"},
        {"wred_delete_insert_ratio", 10L, {"weighted_romaji_edit_distance", "delete_insert_ratio"}, "wred-del-ins-ratio", 0, "cost ratio of deletion and insertion for weighted romaji edit distance"},
        {"wred_uppercase_coefficient", 1L, {"weighted_romaji_edit_distance", "uppercase_coefficient"}, "wred-uppercase-coefficient", 0, "coefficient for uppercase letters for weighted romaji edit distance"},
        {"wred_lowercase_coefficient", 1L, {"weighted_romaji_edit_distance", "lowercase_coefficient"}, "wred-lowercase-coefficient", 0, "coefficient for lowercase letters for weighted romaji edit distance"},
        {"wred_vowel_coefficient", 1L, {"weighted_romaji_edit_distance", "vowel_coefficient"}, "wred-vowel-coefficient", 0, "coefficient for vowels for weighted romaji edit distance"},
        {"wred_consonant_coefficient", 1L, {"weighted_romaji_edit_distance", "consonant_coefficient"}, "wred-consonant-coefficient", 0, "coefficient for consonants for weighted romaji edit distance"},
        {"wred_case_mismatch_cost", 1L, {"weighted_romaji_edit_distance", "case_mismatch_cost"}, "wred-case-mismatch-cost", 0, "cost to replace case mismatches for weighted romaji edit distance"},
        {"wred_similar_letter_cost", 1L, {"weighted_romaji_edit_distance", "similar_letter_cost"}, "wred-similar-letter-cost", 0, "cost to replace similar letters for weighted romaji edit distance"},
        {"wred_ensemble_weight", 0.5, {"weighted_romaji_edit_distance", "ensemble_weight"}, "wred-ensemble-weight", 0, "weight coefficient for weighted romaji edit distance in ensemble mode"},
        {"svr_max_candidate", 2000, {"svr", "max_candidate"}, "svr-max-candidate", 0, "max number of candidates for support vector regression"},
        {"svr_features_path", "features.tsv", {"svr", "features_path"}, "svr-features-path", 0, "feature definition file for support vector regression"},
        {"svr_patterns_home", ".", {"svr", "patterns_home"}, "svr-patterns-home", 0, "directory for pattern files for regular expression-based feature extractors"},
        {"svr_model_path", "model", {"svr", "model_path"}, "svr-model-path", 0, "LibSVM model file"},
        {"svr_corpus_features_path", "", {"svr", "corpus_features_path"}, "svr-corpus-features-path", 0, "metadata file for input corpus"},
        {"corpus_path", "", {"common", "corpus_path"}},
        {"varbose", false, {"common", "varbose"}, "varbose", 'v', "show more information"},
        {"conf_path", "", "config", 'c', "config file path"}
    };
    paramset::manager pm(defs);

    try{
        pm.load(argc, argv, "config");

        std::string corpus_path = read_value_with_rest(pm, "corpus_path", ""); // must not be empty

        const int resembla_max_response = 1;
        double resembla_threshold = pm["resembla_threshold"];

        if(pm.get<bool>("varbose")){
            double default_simstring_threshold = pm["simstring_threshold"];
            double wwed_simstring_threshold = pm.get<double>("wwed_simstring_threshold") != -1 ?
                pm.get<double>("wwed_simstring_threshold") : default_simstring_threshold;
            double wped_simstring_threshold = pm.get<double>("wped_simstring_threshold") != -1 ?
                pm.get<double>("wped_simstring_threshold") : default_simstring_threshold;
            double wred_simstring_threshold = pm.get<double>("wred_simstring_threshold") != -1 ?
                pm.get<double>("wred_simstring_threshold") : default_simstring_threshold;

            int default_max_reranking_num = pm["resembla_max_reranking_num"];
            int wwed_max_reranking_num = pm.get<int>("wwed_max_reranking_num") != -1 ?
                pm.get<int>("wwed_max_reranking_num") : default_max_reranking_num;
            int wped_max_reranking_num = pm.get<int>("wped_max_reranking_num") != -1 ?
                pm.get<int>("wped_max_reranking_num") : default_max_reranking_num;
            int wred_max_reranking_num = pm.get<int>("wred_max_reranking_num") != -1 ?
                pm.get<int>("wred_max_reranking_num") : default_max_reranking_num;

            std::cerr << "Configurations:" << std::endl;
            std::cerr << "  Common:" << std::endl;
            std::cerr << "    corpus_path=" << corpus_path << std::endl;
            std::cerr << "  SimString:" << std::endl;
            std::cerr << "    measure=" << pm.get<std::string>("simstring_measure_str") << std::endl;
            std::cerr << "    threshold=" << default_simstring_threshold << std::endl;
            std::cerr << "  SVR:" << std::endl;
            std::cerr << "    model_path=" << pm.get<std::string>("svr_model_path") << std::endl;
            std::cerr << "  Resembla:" << std::endl;
            std::cerr << "    measure=" << pm.get<std::string>("resembla_measure") << std::endl;
            std::cerr << "    threshold=" << pm.get<double>("resembla_threshold") << std::endl;
            std::cerr << "    max_reranking_num=" << default_max_reranking_num << std::endl;
            std::cerr << "  Weighted word edit distance:" << std::endl;
            std::cerr << "    simstring_threshold=" << wwed_simstring_threshold << std::endl;
            std::cerr << "    max_reranking_num=" << wwed_max_reranking_num << std::endl;
            std::cerr << "    mecab_options=" << pm.get<std::string>("wwed_mecab_options") << std::endl;
            std::cerr << "    base_weight=" << pm.get<double>("wwed_base_weight") << std::endl;
            std::cerr << "    delete_insert_ratio=" << pm.get<double>("wwed_delete_insert_ratio") << std::endl;
            std::cerr << "    noun_coefficient=" << pm.get<double>("wwed_noun_coefficient") << std::endl;
            std::cerr << "    verb_coefficient=" << pm.get<double>("wwed_verb_coefficient") << std::endl;
            std::cerr << "    adj_coefficient=" << pm.get<double>("wwed_adj_coefficient") << std::endl;
            std::cerr << "    ensemble_weight=" << pm.get<double>("wwed_ensemble_weight") << std::endl;
            std::cerr << "  Weighted Pronunciation edit distance:" << std::endl;
            std::cerr << "    simstring_threshold=" << wped_simstring_threshold << std::endl;
            std::cerr << "    max_reranking_num=" << wped_max_reranking_num << std::endl;
            std::cerr << "    mecab_options=" << pm.get<std::string>("wped_mecab_options") << std::endl;
            std::cerr << "    mecab_feature_pos=" << pm.get<int>("wped_mecab_feature_pos") << std::endl;
            std::cerr << "    mecab_pronunciation_of_marks=" << pm.get<std::string>("wped_mecab_pronunciation_of_marks") << std::endl;
            std::cerr << "    base_weight=" << pm.get<double>("wped_base_weight") << std::endl;
            std::cerr << "    delete_insert_ratio=" << pm.get<double>("wped_delete_insert_ratio") << std::endl;
            std::cerr << "    ensemble_weight=" << pm.get<double>("wped_ensemble_weight") << std::endl;
            std::cerr << "  Weighted romaji edit distance:" << std::endl;
            std::cerr << "    simstring_threshold=" << wred_simstring_threshold << std::endl;
            std::cerr << "    max_reranking_num=" << wred_max_reranking_num << std::endl;
            std::cerr << "    mecab_options=" << pm.get<std::string>("wred_mecab_options") << std::endl;
            std::cerr << "    mecab_feature_pos=" << pm.get<int>("wred_mecab_feature_pos") << std::endl;
            std::cerr << "    mecab_pronunciation_of_marks=" << pm.get<std::string>("wred_mecab_pronunciation_of_marks") << std::endl;
            std::cerr << "    base_weight=" << pm.get<double>("wred_base_weight") << std::endl;
            std::cerr << "    delete_insert_ratio=" << pm.get<double>("wred_delete_insert_ratio") << std::endl;
            std::cerr << "    uppercase_coefficient=" << pm.get<double>("wred_uppercase_coefficient") << std::endl;
            std::cerr << "    lowercase_coefficient=" << pm.get<double>("wred_lowercase_coefficient") << std::endl;
            std::cerr << "    vowel_coefficient=" << pm.get<double>("wred_vowel_coefficient") << std::endl;
            std::cerr << "    consonant_coefficient=" << pm.get<double>("wred_consonant_coefficient") << std::endl;
            std::cerr << "    case_mismatch_cost=" << pm.get<double>("wred_case_mismatch_cost") << std::endl;
            std::cerr << "    similar_letter_cost=" << pm.get<double>("wred_similar_letter_cost") << std::endl;
            std::cerr << "    ensemble_weight=" << pm.get<double>("wred_ensemble_weight") << std::endl;
        }

        auto resembla_ensemble = construct_resembla_ensemble(corpus_path, pm);
        auto resembla = construct_regression_resembla(resembla_ensemble, pm);

        while(true){
            std::wstring input;
            std::wcin >> input;
            if(input == L"exit" || input == L"quit" || input == L"bye"){
                break;
            }
            auto result = resembla->getSimilarTexts(input, resembla_max_response, resembla_threshold);
            if(result.empty()){
                std::wcout << L"Not found." << std::endl;
            }
            else{
                std::wcout << L"best: text=" << result[0].text << L", score=" << result[0].score << std::endl;
            }
        }
    }
    catch(const paramset::exception& e){
        std::cerr << "error: " << e.what() << std::endl;
        exit(1);
    }

    return 0;
}