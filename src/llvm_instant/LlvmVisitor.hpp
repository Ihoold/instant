#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor {
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

    void visitChar(Char x);

    void visitDouble(Double x);

    void visitString(String x);

    void visitIdent(Ident x);

};


#endif
