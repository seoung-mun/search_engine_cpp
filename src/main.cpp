// main.cpp

#include <iostream>
#include <string>
#include <vector>
#include "SearchEngine.h" // SearchEngine.h의 상대 경로를 올바르게 지정

// main 함수: 프로그램의 시작점
int main() {
    // SearchEngine 클래스 객체 생성
    SearchEngine engine;
    
    // 데이터 파일이 있는 폴더 경로
    // 프로젝트 루트(cpp_dev)를 기준으로 상대 경로를 지정합니다.
    std::string data_folder_path = "search_engine/data";

    // 색인화할 파일 목록을 수동으로 전달
    std::vector<std::string> file_paths = {
        data_folder_path + "/doc1.txt",
        data_folder_path + "/doc2.txt",
        data_folder_path + "/doc3.txt",
        data_folder_path + "/doc4.txt",
        data_folder_path + "/doc5.txt"
    };

    std::cout << "문서 색인화를 시작합니다..." << std::endl;
    // 각 파일을 하나씩 색인화
    for (const std::string& path : file_paths) {
        engine.index_files(file_paths);
    }
    std::cout << "색인화가 완료되었습니다." << std::endl;
    
    // 사용자에게 검색어를 입력받고 검색 시작
    std::string query;
    std::cout << "\n검색할 단어를 입력하세요 (종료: 'quit'): ";
    std::getline(std::cin, query);

    while (query != "quit") {
        std::set<std::string> results = engine.search(query);

        if (results.empty()) {
            std::cout << "'" << query << "'(을)를 포함하는 문서가 없습니다." << std::endl;
        } else {
            std::cout << "'" << query << "'(을)를 포함하는 문서 목록:" << std::endl;
            for (const std::string& doc_path : results) {
                std::cout << "- " << doc_path << std::endl;
            }
        }
        
        std::cout << "\n검색할 단어를 입력하세요 (종료: 'quit'): ";
        std::getline(std::cin, query);
    }
    
    std::cout << "프로그램을 종료합니다." << std::endl;
    return 0;
}