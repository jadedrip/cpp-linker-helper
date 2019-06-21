cmake_minimum_required(VERSION 3.14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(LibClang REQUIRED)

set(LLVM_LINK_COMPONENTS
  Support
  )

ADD_EXECUTABLE(CSPlugin
  CSPlugin.cpp
)

target_link_libraries(CSPlugin
    clangAST
    clangBasic
	clangEdit
    clangDriver
    clangFormat
    clangLex
    clangParse
    clangSema
    clangFrontend
    clangTooling
    clangToolingCore
    clangRewrite
	clangAnalysis
	clangSerialization
    clangRewriteFrontend
	clangASTMatchers
	LLVMCore
	LLVMMC
	LLVMDemangle
	LLVMProfileData
	LLVMMCParser
	LLVMBitReader
	LLVMBinaryFormat
	LLVMOption
	LLVMSupport
	Version
)

if(UNIX)
  set(CLANGXX_LINK_OR_COPY create_symlink)
else()
  set(CLANGXX_LINK_OR_COPY copy)
endif()
