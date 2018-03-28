#include "ClangSACheckers.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include <iostream>

using namespace clang;
using namespace ento;

namespace {
    class globalVarChecker
        : public Checker< check::PreStmt<BinaryOperator> > {
        mutable std::unique_ptr<BuiltinBug> BT;

    public:
        void checkPreStmt(const BinaryOperator *B, CheckerContext &C) const;
		void checkPostCall(const CallEvent &Call, CheckerContext &C) const;
		void checkASTDecl(const FunctionDecl *D,
			AnalysisManager &Mgr,
			BugReporter &BR) const;
    };
}

void globalVarChecker::checkPreStmt(const BinaryOperator *B, CheckerContext &C) const
{
	std::cout << "123456\n";
	return;
}

void globalVarChecker::checkPostCall(const CallEvent &Call, CheckerContext &C) const 
{
	FILE * fp = fopen("123.txt", "w");
	fclose(fp);
	return;
}

void globalVarChecker::checkASTDecl(const FunctionDecl *D,
	AnalysisManager &Mgr,
	BugReporter &BR) const
{
	std::cout << "AST\n";
	return;
}

void ento::registerglobalVarChecker(CheckerManager &mgr) {
  mgr.registerChecker<globalVarChecker>();
}