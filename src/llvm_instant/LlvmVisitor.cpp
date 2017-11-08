/*** BNFC-Generated Visitor Design Pattern LlvmVisitor. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include <iostream>
#include "LlvmVisitor.hpp"

std::string LlvmVisitor::getFreeId() {
    return "%i" + std::to_string(idCount++);
}

std::vector<std::string> LlvmVisitor::compile(Visitable* v) {
    v->accept(this);
    return code;
}

void LlvmVisitor::visitProgram(Program *t) {} //abstract class
void LlvmVisitor::visitStmt(Stmt *t) {} //abstract class
void LlvmVisitor::visitExp(Exp *t) {} //abstract class

void LlvmVisitor::visitProg(Prog *prog) {
    code.emplace_back("declare void @printInt(i32)");
    code.emplace_back("define i32 @main() {");
    prog->liststmt_->accept(this);
    code.emplace_back("ret i32 0");
    code.emplace_back("}");
}

void LlvmVisitor::visitSAss(SAss *sass) {
    sass->exp_->accept(this);
    auto ptrName = genPtrName(sass->ident_);
    if (vars.find(sass->ident_) == vars.end()) {
        code.emplace_back(ptrName + " = alloca i32");
    }

    code.emplace_back("store i32 " + currentResutlt + ", i32* " + ptrName);
    vars.insert(sass->ident_);
}

void LlvmVisitor::visitSExp(SExp *sexp) {
    sexp->exp_->accept(this);
    code.emplace_back("call void @printInt(i32 " + currentResutlt + ")");
}

void LlvmVisitor::visitTwoOp(Exp* e1, Exp* e2, const std::string& op) {
    e1->accept(this);
    std::string arguments = this->currentResutlt + ", ";
    e2->accept(this);
    arguments += this->currentResutlt;

    currentResutlt = getFreeId();
    code.emplace_back(currentResutlt + " = " + op + arguments);
}

std::string LlvmVisitor::genPtrName(const std::string& var) {
    return "%ptr_" + var;
}

void LlvmVisitor::visitExpAdd(ExpAdd *exp) {
    visitTwoOp(exp->exp_1, exp->exp_2, "add i32 ");
}

void LlvmVisitor::visitExpSub(ExpSub *exp) {
    visitTwoOp(exp->exp_1, exp->exp_2, "sub i32 ");
}

void LlvmVisitor::visitExpMul(ExpMul *exp) {
    visitTwoOp(exp->exp_1, exp->exp_2, "mul i32 ");
}

void LlvmVisitor::visitExpDiv(ExpDiv *exp) {
    visitTwoOp(exp->exp_1, exp->exp_2, "udiv i32 ");
}

void LlvmVisitor::visitExpLit(ExpLit *explit) {
    visitInteger(explit->integer_);
}

void LlvmVisitor::visitExpVar(ExpVar *expvar) {
    if (vars.find(expvar->ident_) != vars.end()) {
        currentResutlt = getFreeId();
        code.emplace_back(currentResutlt + " = load i32, i32* " + genPtrName(expvar->ident_));
    } else {
        std::cerr << expvar->ident_ << std::endl;
        std::cerr << "Using undeclared variable!" << std::endl;
        exit(-3);
    }
}


void LlvmVisitor::visitListStmt(ListStmt *liststmt) {
    for (auto& stmt : *liststmt)
        stmt->accept(this);
}


void LlvmVisitor::visitInteger(Integer x) {
    currentResutlt = std::to_string(x);
}

void LlvmVisitor::visitIdent(Ident x) {
    // unused
}
