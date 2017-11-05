#ifndef JVMVISITOR_HEADER
#define JVMVISITOR_HEADER
/* You might want to change the above name. */

#include <Absyn.hpp>
#include <map>
#include "Result.hpp"

class JvmVisitor : public Visitor {
    Result currentResult;
public:
    const Result& getCurrentResult() const;

private:
    std::map<std::string, int> vars;
    int varCount = 1;
public:
    void visitProgram(Program *p);

    void visitStmt(Stmt *p);

    void visitExp(Exp *p);

    void visitProg(Prog *p);

    void visitSAss(SAss *p);

    void visitSExp(SExp *p);

    void visitExpAdd(ExpAdd *p);

    void visitExpSub(ExpSub *p);

    void visitExpMul(ExpMul *p);

    void visitExpDiv(ExpDiv *p);

    void visitExpLit(ExpLit *p);

    void visitExpVar(ExpVar *p);

    void visitListStmt(ListStmt *p);

    void visitInteger(Integer x);

    void visitIdent(Ident x);

    std::pair<Result, Result> visitTwoOp(Exp* e1, Exp* e2);

    int findVar(Ident x);

    std::vector<std::string> compile(Visitable *v);
};


#endif
