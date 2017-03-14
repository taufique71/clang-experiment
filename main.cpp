/* Compilation command: g++ main.cpp -lclang -o analyzer */

#include <iostream>
#include <string>
#include <cstring>
#include <clang-c/Index.h>
using namespace std;

std::string getCursorSpelling( CXCursor cursor ){
    CXString cursorSpelling = clang_getCursorSpelling( cursor );
    std::string result      = clang_getCString( cursorSpelling );
    clang_disposeString( cursorSpelling );
    return result;
}

CXChildVisitResult functionVisitor(CXCursor cursor, CXCursor parent, CXClientData clientData){
    CXSourceLocation location = clang_getCursorLocation( cursor );
    if( clang_Location_isFromMainFile( location ) == 0){
        return CXChildVisit_Continue;
    }
    else{
        CXCursorKind kind = clang_getCursorKind( cursor );
        if( kind == CXCursorKind::CXCursor_StructDecl || kind == CXCursorKind::CXCursor_UnionDecl || kind == CXCursorKind::CXCursor_ClassDecl ){
            return CXChildVisit_Continue;
        }
        else{
            if(kind == CXCursorKind::CXCursor_FunctionDecl){
                std::string spelling = getCursorSpelling( cursor );
                cout << spelling << endl;
            }
            return CXChildVisit_Recurse;
        }
    }
}

CXChildVisitResult varDeclVisitor(CXCursor cursor, CXCursor parent, CXClientData clientData){
    CXSourceLocation location = clang_getCursorLocation( cursor );
    if( clang_Location_isFromMainFile( location ) == 0){
        return CXChildVisit_Continue;
    }
    else{
        CXCursorKind kind = clang_getCursorKind( cursor );
        if( kind == CXCursorKind::CXCursor_StructDecl || kind == CXCursorKind::CXCursor_UnionDecl || kind == CXCursorKind::CXCursor_ClassDecl ){
            return CXChildVisit_Continue;
        }
        else{
            if(kind == CXCursorKind::CXCursor_VarDecl || kind == CXCursorKind::CXCursor_ParmDecl){
                std::string spelling = getCursorSpelling( cursor );
                cout << spelling << endl;
            }
            return CXChildVisit_Recurse;
        }
    }
}

int main(int argc, char** argv){
    CXIndex index = clang_createIndex(0, 0);
    printf("Going to parse %s file\n", argv[1]);
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        argv[1],
        nullptr,
        0,
        nullptr,
        0,
        CXTranslationUnit_None
    );
    if(unit == nullptr){
        printf("Unable to parse given file\n");
    }
    else{
        CXCursor cursor = clang_getTranslationUnitCursor( unit );
        int choice;
        printf("Which list you want the program to print? Enter your choice:\n");
        printf("Option 0: Variable list\n");
        printf("Option 1: Function list\n");
        scanf("%d", &choice);
        switch(choice){
            case 0:
                /* Visit all variable declarations */
                clang_visitChildren( cursor, varDeclVisitor, nullptr );
                break;
            case 1:
                /* Visit all function declarations */
                clang_visitChildren( cursor, functionVisitor, nullptr );
                break;
        }

    }

    clang_disposeTranslationUnit( unit );
    clang_disposeIndex( index );
    return 0;
}
