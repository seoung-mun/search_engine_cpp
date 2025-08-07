#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <set>

class SearchEngine {
public:
    
    SearchEngine();
    
    void index_documents(const std::string& folder_path);
    // 폴더 경로를 받아서 그 안의 모든 파일을 인덱싱하는 함수

    std::set<std::string> search(const std::string& query);
    // 검색어를 받아서 해당하는 문서 경로 집합을 반환하는 함수
    void index_document(const std::string& file_path);
    // 단일 문서를 인덱싱하는 함수
    void index_files(const std::vector<std::string>& file_paths);
    // 여러 파일을 인덱싱하는 함수

    
private:
    std::map<std::string, std::set<std::string>> inverted_index;
    // 역색인: 단어 -> 해당 단어가 포함된 문서 경로 집합

    std::vector<std::string> tokenize(const std::string& text);
    // 텍스트를 단어 단위로 분리하는 헬퍼 함수

    void index_single_file(const std::string& file_path);
    // 단일 파일을 인덱싱하는 헬퍼 함수 (구현 필요)
};

#endif 