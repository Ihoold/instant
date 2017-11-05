#ifndef LLVM_VISITOR_HEADER
#define LLVM_VISITOR_HEADER
/* You might want to change the above name. */

#include "Absyn.hpp"

#include <unordered_set>


class LlvmVisitor : public Visitor {
    std::string currentResutlt;
    std::vector<std::string> code;
    std::unordered_set<std::string> vars;
    int idCount = 0;
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

    std::string getFreeId();

    void visitTwoOp(Exp *e1, Exp *e2, const std::string& op);

    std::string genPtrName(const std::string& var);

    std::vector<std::string> compile(Visitable *v);
};


#endif
