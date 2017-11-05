/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include <iostream>
#include <unordered_set>
#include "JvmVisitor.hpp"

const int ILOAD_LIMIT = 3;
const int ISTORE_LIMIT = 3;
const int CONST_LIMIT = 5;
const int BIPUSH_LIMIT = 127;
const int SIPUSH_LIMIT = 32767;


void JvmVisitor::visitProgram(Program *t) {} //abstract class
void JvmVisitor::visitStmt(Stmt *t) {} //abstract class
void JvmVisitor::visitExp(Exp *t) {} //abstract class

std::vector<std::string> JvmVisitor::compile(Visitable* v) {
    v->accept(this);
    return currentResult.getCode();
}

void JvmVisitor::visitProg(Prog *prog) {
    std::vector<std::string> commands{
            ".method public static main([Ljava/lang/String;)V",
    };
    Result res(commands, 0);
    prog->liststmt_->accept(this);
    res.setStackSize(currentResult.getStackSize());
    res.addCommand(".limit stack " + std::to_string(res.getStackSize()));
    res.addCommand(".limit locals " + std::to_string(varCount));

    res.concatCode(currentResult.getCode());

    res.addCommand("return");
    res.addCommand(".end method");
    currentResult = res;
}

void JvmVisitor::visitSAss(SAss *sass) {
    int i = findVar(sass->ident_);
    sass->exp_->accept(this);

    std::string command;
    if (i < 0) {
        i = varCount++;
        vars[sass->ident_] = i;
    }

    if (i <= ISTORE_LIMIT) {
        command = "istore_" + std::to_string(i);
    } else {
        command = "istore " + std::to_string(i);
    }

    currentResult.addCommand(command);
}

void JvmVisitor::visitSExp(SExp *sexp) {
    sexp->exp_->accept(this);
    std::vector<std::string> commands {"getstatic java/lang/System/out Ljava/io/PrintStream;"};
    Result printExpRes(commands, 1);
    if (currentResult.getStackSize() > 1) {
        currentResult.concatCode(printExpRes.getCode());
        currentResult.addCommand("swap");
    } else {
        printExpRes.concatCode(currentResult.getCode());
        currentResult = printExpRes;
        currentResult.setStackSize(2);
    }
    currentResult.addCommand("invokevirtual java/io/PrintStream/println(I)V");
}

std::pair<Result, Result> JvmVisitor::visitTwoOp(Exp *e1, Exp *e2) {
    e1->accept(this);
    auto res1 = currentResult;
    e2->accept(this);
    auto res2 = currentResult;

    return std::make_pair(res1, res2);
}

void JvmVisitor::visitExpAdd(ExpAdd *expadd) {
    auto resPair = visitTwoOp(expadd->exp_1, expadd->exp_2);

    // Do calculations with bigger stack first.
    if (resPair.first.getStackSize() >= resPair.second.getStackSize()) {
        currentResult = resPair.first;
        currentResult.concatCode(resPair.second.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.second.getStackSize() + 1));
    } else {
        currentResult = resPair.second;
        currentResult.concatCode(resPair.first.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.first.getStackSize() + 1));
    }

    currentResult.addCommand("iadd");
}

void JvmVisitor::visitExpSub(ExpSub *expsub) {
    auto resPair = visitTwoOp(expsub->exp_1, expsub->exp_2);

    // Do calculations with bigger stack first.
    if (resPair.first.getStackSize() >= resPair.second.getStackSize()) {
        currentResult = resPair.first;
        currentResult.concatCode(resPair.second.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.second.getStackSize() + 1));
    } else {
        currentResult = resPair.second;
        currentResult.concatCode(resPair.first.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.first.getStackSize() + 1));
        currentResult.addCommand("swap");
    }

    currentResult.addCommand("isub");

}

void JvmVisitor::visitExpMul(ExpMul *expmul) {
    auto resPair = visitTwoOp(expmul->exp_1, expmul->exp_2);

    // Do calculations with bigger stack first.
    if (resPair.first.getStackSize() >= resPair.second.getStackSize()) {
        currentResult = resPair.first;
        currentResult.concatCode(resPair.second.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.second.getStackSize() + 1));
    } else {
        currentResult = resPair.second;
        currentResult.concatCode(resPair.first.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.first.getStackSize() + 1));
    }

    currentResult.addCommand("imul");
}

void JvmVisitor::visitExpDiv(ExpDiv *expdiv) {
    auto resPair = visitTwoOp(expdiv->exp_1, expdiv->exp_2);

    // Do calculations with bigger stack first.
    if (resPair.first.getStackSize() >= resPair.second.getStackSize()) {
        currentResult = resPair.first;
        currentResult.concatCode(resPair.second.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.second.getStackSize() + 1));
    } else {
        currentResult = resPair.second;
        currentResult.concatCode(resPair.first.getCode());
        currentResult.setStackSize(std::max(currentResult.getStackSize(), resPair.first.getStackSize() + 1));
        currentResult.addCommand("swap");
    }

    currentResult.addCommand("idiv");
}

void JvmVisitor::visitExpLit(ExpLit *explit) {
    visitInteger(explit->integer_);
}

void JvmVisitor::visitExpVar(ExpVar *expvar) {
    int i = findVar(expvar->ident_);
    std::string command;

    if(i <= 0) {
        std::cerr << "Using undeclared variable!" << std::endl;
        exit(-3);
    } else if (i <= ILOAD_LIMIT) {
        command = "iload_" + std::to_string(i);
    } else {
        command = "iload " + std::to_string(i);
    }

    std::vector<std::string> commands {command};
    this->currentResult = Result(commands, 1);
}


void JvmVisitor::visitListStmt(ListStmt *liststmt) {
    Result res;
    for (auto& el : *liststmt) {
        el->accept(this);
        res.concatCode(currentResult.getCode());
        res.setStackSize(std::max(res.getStackSize(), currentResult.getStackSize()));
    }
    currentResult = res;
}


void JvmVisitor::visitInteger(Integer x) {
    std::string command;
    if (x < 0) {
        std::cerr << "Netgative values not supported." << std::endl;
        std::exit(-1);
    } else if (x <= CONST_LIMIT) {
        command = "iconst_" + std::to_string(x);
    } else if (x <= BIPUSH_LIMIT) {
        command = "bipush " + std::to_string(x);
    } else if (x <= SIPUSH_LIMIT) {
        command = "sipush " + std::to_string(x);
    } else {
        command = "ldc " + std::to_string(x);
    }
    std::vector<std::string> commands {command};
    this->currentResult = Result(commands, 1);
}

int JvmVisitor::findVar(Ident x) {
    auto it = vars.find(x);
    if (it == vars.end())
        return -1;
    return vars[x];
}

void JvmVisitor::visitIdent(Ident x) {
    // unused
}
