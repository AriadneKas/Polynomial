#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include "Rangepoohls2.hpp"

using namespace std;

Polynomial::Term::Term(int exp,int coeff,Term *n)
{
  exponent=exp;
  coefficient=coeff;

  next=n;
}

Polynomial::Polynomial():the_front(nullptr){}

Polynomial::Polynomial(const Polynomial &p):the_front(nullptr)
{ 
  copy(p);
}

Polynomial::~Polynomial()
{
  purge();
}

void Polynomial::push_front(const int &x,const int &y)
{
  Term *n=new Term(x,y,the_front);
  the_front=n;
}
void Polynomial::copy(const Polynomial &p)
{ 
  Term *the_back;
  for(Term *t=p.the_front; t!=nullptr; t=t->next){
    Term *n=new Term(t->exponent,t->coefficient,nullptr);
    if(the_front!=nullptr) the_back->next=n;
    else the_front=n;
    the_back=n;
  }  
}

void Polynomial::purge()
{
  Term *t=the_front;
  
  while(t!=nullptr){
    Term *p=t;
    t=t->next;
    delete p;
  }
}

Polynomial & Polynomial::operator = (const Polynomial &p)
{
  if(this==&p) return *this;
  
  purge();
  the_front=nullptr;

  copy(p);

  return *this;
}

void Polynomial::addTerm(int exp, int coeff)
{
  assert(coeff!=0);
  if(the_front==nullptr) push_front(exp,coeff);
  else if(the_front->exponent==exp && the_front->coefficient+coeff==0){
    Term* n=the_front;
    the_front=the_front->next;
    delete n;
  }
  else
   for(Term *t=the_front;t!=nullptr;t=t->next){
     if(t->next!=nullptr && t->next->coefficient+coeff==0 && t->next->exponent==exp){
       Term*n=t->next;
       t->next=n->next;
       delete n;
       break;
     }
     else if(t->exponent==exp){
       t->coefficient+=coeff;
       break;
     }
     else if(exp>t->exponent && t==the_front){
       push_front(exp,coeff);
       break;
     }
     else if(exp<t->exponent && t->next==nullptr){
       Term *n=new Term(exp,coeff,nullptr);
       t->next=n;
       break;
     }
     else if(exp<t->exponent && exp>t->next->exponent){
       Term *n=new Term(exp,coeff,t->next);
       t->next=n;
       break;
     }
  }
}

double Polynomial::evaluate(double x)
{
  double result=0;

  for(Term *t=the_front;t!=nullptr;t=t->next){
    double e=pow(x,t->exponent);
    result+=t->coefficient*e;
  }
  return result;
}

Polynomial operator + (const Polynomial &a,const Polynomial &b)
{
  Polynomial result;
  result.copy(b);

  for(Polynomial::Term *ta=a.the_front;ta!=nullptr;ta=ta->next){
    result.addTerm(ta->exponent,ta->coefficient);
  }
  
  return result; 
}

Polynomial operator * (const Polynomial &a,const Polynomial &b){
  Polynomial result;

  for(Polynomial::Term *ta=a.the_front;ta!=nullptr;ta=ta->next)
    for(Polynomial::Term *tb=b.the_front;tb!=nullptr;tb=tb->next)
      result.addTerm(ta->exponent+tb->exponent,ta->coefficient*tb->coefficient);

  return result;
}

ostream & operator << (ostream &out,const Polynomial &p){
  if(p.the_front==nullptr)out << "0";
  else
   for(Polynomial::Term *t=p.the_front;t!=nullptr;t=t->next){
     if(t->exponent>1 && t->coefficient==1) out << "+ " << "x^" << t->exponent;
     else if(t->exponent>1 && t->coefficient>0) out << "+ " << t->coefficient << "x^" << t->exponent;
     else if(t->exponent>1 && t->coefficient==-1) out << "- " << "x^" << t->exponent;
     else if(t->exponent>1 && t->coefficient<0) {int c=abs(t->coefficient); out << "- " << c << "x^" << t->exponent;}
     else if(t->exponent==1 && t->coefficient==1) out << "+ " << "x"; 
     else if(t->exponent==1 && t->coefficient>1) out << "+ " << t->coefficient << "x";     
     else if(t->exponent==1 && t->coefficient==-1) out << "- " << "x";
     else if(t->exponent==1 && t->coefficient<0) {int c=abs(t->coefficient); out << "- " << c << "x";}
     else if(t->exponent==0 && t->coefficient>0) out << "+ " <<t->coefficient;
     else if(t->exponent==0 && t->coefficient<0) {int c=abs(t->coefficient); out << "- " <<c;}

     if(t->next!=nullptr) out << " ";
   }
  return out;
}
