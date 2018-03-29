#include "ClangSACheckers.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h"
#include <iostream>

using namespace clang;
using namespace ento;

namespace {
    class globalVarChecker
        : public Checker< check::PreStmt<BinaryOperator> ,check::PreCall> {
        mutable std::unique_ptr<BuiltinBug> BT;

    public:
        void checkPreStmt(const BinaryOperator *B, CheckerContext &C) const;
		void checkPreCall(const CallEvent &Call, CheckerContext &C) const;
    };
}

void globalVarChecker::checkPreStmt(const BinaryOperator *B, CheckerContext &C) const
{
	//std::cout << "global preStmt\n";
	//FILE * fp = fopen("globSTMT.txt", "a+");
	//fprintf(fp, "%u %u\n", st.getRawEncoding(), ed.getRawEncoding());
	//fclose(fp);
	return;
}

void globalVarChecker::checkPreCall(const CallEvent &Call, CheckerContext &C) const 
{
	const IdentifierInfo *ID = Call.getCalleeIdentifier();
	if (ID == NULL) {
		return;
	}
	SourceRange range = Call.getSourceRange();
	
	auto st = range.getBegin();
	SourceManager &SourceMgr = C.getSourceManager();

	//std::cout << st.printToString(SourceMgr);

	FILE * fp = fopen("log.txt", "a+");
	fprintf(fp, "%s %u %u\n", ID->getName(), SourceMgr.getSpellingLineNumber(st));
	fclose(fp);

	return;
}

void ento::registerglobalVarChecker(CheckerManager &mgr) {
  mgr.registerChecker<globalVarChecker>();
}