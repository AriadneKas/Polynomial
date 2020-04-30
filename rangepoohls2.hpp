#include <iostream>

using namespace std;

class Polynomial{
protected:
  class Term{
  protected:
    int exponent;
    int coefficient;
    Term* next;
    Term(int exp,int coeff,Term *n);
    friend class Polynomial;
    friend Polynomial operator + (const Polynomial &a,const Polynomial &b);
    friend Polynomial operator * (const Polynomial &a,const Polynomial &b);
    friend ostream & operator << (ostream &out,const Polynomial &p);
  };

public:
  Polynomial():the_front(nullptr);
  Polynomial(const Polynomial &p);
  ~Polynomial();

  void push_back(const int &x,const int &y);
  void push_front(const int &x,const int &y);
  
  void copy(const Polynomial &p);
  void purge();

  Polynomial & operator = (const Polynomial &p);

  void addTerm(int exp,int coeff);
  double evaluate(double x);
  
  friend Polynomial operator + (const Polynomial &a,const Polynomial &b);
  friend Polynomial operator * (const Polynomial &a,const Polynomial &b);

  friend ostream & operator << (ostream &out,const Polynomial &p);
    
private:
  Term *the_front;
};
