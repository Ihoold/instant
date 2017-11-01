/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "JvmVisitor.hpp"


void JvmVisitor::visitProgram(Program *t) {} //abstract class
void JvmVisitor::visitStmt(Stmt *t) {} //abstract class
void JvmVisitor::visitExp(Exp *t) {} //abstract class

void JvmVisitor::visitProg(Prog *prog) {
    /* Code For Prog Goes Here */

    prog->liststmt_->accept(this);

}

void JvmVisitor::visitSAss(SAss *sass) {
    /* Code For SAss Goes Here */

    visitIdent(sass->ident_);
    sass->exp_->accept(this);

}

void JvmVisitor::visitSExp(SExp *sexp) {
    /* Code For SExp Goes Here */

    sexp->exp_->accept(this);

}

void JvmVisitor::visitExpAdd(ExpAdd *expadd) {
    /* Code For ExpAdd Goes Here */

    expadd->exp_1->accept(this);
    expadd->exp_2->accept(this);

}

void JvmVisitor::visitExpSub(ExpSub *expsub) {
    /* Code For ExpSub Goes Here */

    expsub->exp_1->accept(this);
    expsub->exp_2->accept(this);

}

void JvmVisitor::visitExpMul(ExpMul *expmul) {
    /* Code For ExpMul Goes Here */

    expmul->exp_1->accept(this);
    expmul->exp_2->accept(this);

}

void JvmVisitor::visitExpDiv(ExpDiv *expdiv) {
    /* Code For ExpDiv Goes Here */

    expdiv->exp_1->accept(this);
    expdiv->exp_2->accept(this);

}

void JvmVisitor::visitExpLit(ExpLit *explit) {
    /* Code For ExpLit Goes Here */

    visitInteger(explit->integer_);

}

void JvmVisitor::visitExpVar(ExpVar *expvar) {
    /* Code For ExpVar Goes Here */

    visitIdent(expvar->ident_);

}


void JvmVisitor::visitListStmt(ListStmt *liststmt) {
    for (auto& el : *liststmt) {
        el->accept(this);
    }
}


void JvmVisitor::visitInteger(Integer x) {
    /* Code for Integer Goes Here */
}

void JvmVisitor::visitIdent(Ident x) {

    /* Code for Ident Goes Here */
}



