#include <iostream>
#include <clang-c/Index.h>
using namespace std;

int main(){
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        "header.hpp", nullptr, 0,
        nullptr, 0,
        CXTranslationUnit_None
    );
    if(unit == nullptr){
        cerr << "Unable to parse translation unit" << endl;
    }
    else{
        cout << "Parsed translation unit" << endl;
    }

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
    return 0;
}
