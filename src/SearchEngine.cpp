#include "SearchEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype> 

// 생성자
SearchEngine::SearchEngine() {}


void SearchEngine::index_documents(const std::string& folder_path) {
    std::cout << "Indexing documents from " << folder_path << std::endl;
}

std::set<std::string> SearchEngine::search(const std::string& query) {
    // 1. 검색어를 소문자로 변환하여 전처리
    std::string processed_query = query;
    std::transform(processed_query.begin(), processed_query.end(), processed_query.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // 2. 역색인에서 검색어에 해당하는 문서 목록을 찾아서 반환
    auto it = inverted_index.find(processed_query);
    if (it != inverted_index.end()) {
        return it->second; // 문서 경로 집합(set) 반환
    } else {
        return {}; // 결과가 없으면 빈 집합(set) 반환
    }
}


std::vector<std::string> SearchEngine::tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;
    
    // 1. 공백을 기준으로 단어를 분리 (토큰화)
    while (ss >> word) {
        // 2. 간단한 전처리: 소문자로 변환 및 구두점 제거
        std::string cleaned_word;
        for (char ch : word) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                cleaned_word += std::tolower(static_cast<unsigned char>(ch));
            }
        }
        
        if (!cleaned_word.empty()) {
            tokens.push_back(cleaned_word);
        }
    }
    return tokens;
}

void SearchEngine::index_single_file(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string file_content = buffer.str();
    
    // 1. 파일 내용을 단어들로 토큰화
    std::vector<std::string> words = tokenize(file_content);

    // 2. 각 단어를 역색인에 추가
    for (const std::string& word : words) {
        // map에 단어가 없으면 새로운 set이 자동으로 생성됨
        inverted_index[word].insert(file_path);
    }

    std::cout << "Indexed file: " << file_path << std::endl;
}