#include <iostream>
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include <fstream>

using namespace std;
using namespace clang::tooling;
using namespace llvm;
static llvm::cl::OptionCategory MyToolCategory("global-detect options");

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

StatementMatcher GlobalVarMatcher = declRefExpr(
	to(
		functionDecl().bind("funcDecl")
	) // to
).bind("globalReference");


class Global_Printer : public MatchFinder::MatchCallback {
public:

	virtual void run(const MatchFinder::MatchResult& Result)
	{
		FunctionDecl const* func_decl =
			Result.Nodes.getNodeAs<FunctionDecl>("function");
		Expr const* g_var = Result.Nodes.getNodeAs<Expr>("globalReference");
		auto const* var = Result.Nodes.getNodeAs<FunctionDecl>("funcDecl");
		if (var) {
			/*
			DeclarationNameInfo NameInfo = func_decl->getNameInfo();
			DeclarationName Name = NameInfo.getName();
			*/
			auto parent = var->getParent();
			if (parent) {
				cout << "Parent: " << parent->getDeclKindName() << endl << "\t";
			}

			cout << "函数名：" << ((Decl*)var)->getDeclKindName() << " - " <<
				var->getNameAsString() << endl;

			

			//Name2.dump();
		}
	}
};

int main(int argc, const char** argv) {
	CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
	ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
	Global_Printer GvarPrinter;
	MatchFinder Finder;
	Finder.addMatcher(GlobalVarMatcher, &GvarPrinter);
	Tool.run(newFrontendActionFactory(&Finder).get());
	Finder.~MatchFinder();
	return 0;
}