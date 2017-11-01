/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"



void Skeleton::visitProgram(Program* t) {} //abstract class
void Skeleton::visitStmt(Stmt* t) {} //abstract class
void Skeleton::visitExp(Exp* t) {} //abstract class

void Skeleton::visitProg(Prog *prog)
{
  /* Code For Prog Goes Here */

  prog->liststmt_->accept(this);

}

void Skeleton::visitSAss(SAss *sass)
{
  /* Code For SAss Goes Here */

  visitIdent(sass->ident_);
  sass->exp_->accept(this);

}

void Skeleton::visitSExp(SExp *sexp)
{
  /* Code For SExp Goes Here */

  sexp->exp_->accept(this);

}

void Skeleton::visitExpAdd(ExpAdd *expadd)
{
  /* Code For ExpAdd Goes Here */

  expadd->exp_1->accept(this);
  expadd->exp_2->accept(this);

}

void Skeleton::visitExpSub(ExpSub *expsub)
{
  /* Code For ExpSub Goes Here */

  expsub->exp_1->accept(this);
  expsub->exp_2->accept(this);

}

void Skeleton::visitExpMul(ExpMul *expmul)
{
  /* Code For ExpMul Goes Here */

  expmul->exp_1->accept(this);
  expmul->exp_2->accept(this);

}

void Skeleton::visitExpDiv(ExpDiv *expdiv)
{
  /* Code For ExpDiv Goes Here */

  expdiv->exp_1->accept(this);
  expdiv->exp_2->accept(this);

}

void Skeleton::visitExpLit(ExpLit *explit)
{
  /* Code For ExpLit Goes Here */

  visitInteger(explit->integer_);

}

void Skeleton::visitExpVar(ExpVar *expvar)
{
  /* Code For ExpVar Goes Here */

  visitIdent(expvar->ident_);

}


void Skeleton::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}



