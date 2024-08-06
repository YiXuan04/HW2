#include <iostream>
#include <math.h>
using namespace std;
class Term;
class Polynomial{
    public:
        Polynomial();
        Polynomial Add(Polynomial& other);
        Polynomial Mult(Polynomial& other);
        float Eval(float f);
        friend istream& operator>>(istream& input,Polynomial& Poly);
        friend ostream& operator<<(ostream& output,Polynomial& Poly);
    private:
        Term *termArray;
        int capacity;
        int terms;
        void newTerm(float coef,int exp);
};
class Polynomial;
class Term{
    friend Polynomial;
    friend istream& operator>>(istream& input,Polynomial& Poly);
    friend ostream& operator<<(ostream& output,Polynomial& Poly);
    private:
        float coef;
        int exp;
};
Polynomial::Polynomial():capacity(10),terms(0){
    termArray=new Term[capacity];
}
void Polynomial::newTerm(float coef,int exp){
    if(terms==capacity){
        capacity*=2;
        Term* temp=new Term[capacity];
        for(int i=0;i<terms;i++){
            temp[i]=termArray[i];
        }
        delete[] termArray;
        termArray=temp;
    }
    termArray[terms].coef=coef;
    termArray[terms++].exp=exp;
}
Polynomial Polynomial::Add(Polynomial& other){
    Polynomial result;
    int aPos=0,bPos=0;
    while(aPos<terms&&bPos<other.terms){
        if(termArray[aPos].exp==other.termArray[bPos].exp){
            float sum=termArray[aPos].coef+other.termArray[bPos].coef;
            if(sum) result.newTerm(sum,termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp>other.termArray[bPos].exp){
            result.newTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
        else{
            result.newTerm(other.termArray[bPos].coef,other.termArray[bPos].exp);
            bPos++;
        }
    }
    for(;aPos<terms;aPos++){
        result.newTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<terms;bPos++){
        result.newTerm(other.termArray[bPos].coef,other.termArray[bPos].exp);
    }
    return result;
}
Polynomial Polynomial::Mult(Polynomial& other){
    Polynomial result;
    Polynomial temp;
    for(int i=0;i<terms;i++){
        for(int j=0;j<other.terms;j++){
            temp.newTerm(termArray[i].coef*other.termArray[j].coef,termArray[i].exp+other.termArray[j].exp);
        }
    }
    for(int i=0;i<temp.terms;i++){
        bool found=false;
        for(int j=0;j<result.terms;j++){
            if (result.termArray[j].exp == temp.termArray[i].exp) {
                result.termArray[j].coef += temp.termArray[i].coef;
                found = true;
                break;
            }
        }
        if(!found){
            result.newTerm(temp.termArray[i].coef,temp.termArray[i].exp);
        }
    }
    return result;
}
float Polynomial::Eval(float f){
    float result=0;
    for(int i=0;i<terms;i++){
        result+=termArray[i].coef*pow(f,termArray[i].exp);
    }
    return result;
}
istream& operator>>(istream& input,Polynomial& Poly){
    int num;
    cout<<"Enter the number of terms: ";
    input>>num;
    for(int i=0;i<num;i++){
        float coef;
        int exp;
        cout<<"Enter coefficient and exponent: ";
        input>>coef>>exp;
        Poly.newTerm(coef,exp);
    }
    return input;
}
ostream& operator<<(ostream& output,Polynomial& Poly){
    for(int i=0;i<Poly.terms;i++){
        if(i>0 && Poly.termArray[i].coef >0){
            output<<" + ";
        }
        output<<Poly.termArray[i].coef<<"x^"<<Poly.termArray[i].exp;
    }
    return output;
}
int main(){
    Polynomial p1, p2;
    cout << "Enter polynomial p1:\n";
    cin >> p1;
    cout << "Enter polynomial p2:\n";
    cin >> p2;
    cout << "Polynomial p1: " << p1 << endl;
    cout << "Polynomial p2: " << p2 << endl;
    Polynomial p3 = p1.Add(p2);
    cout << "Polynomial p1 + p2: " << p3 << endl;
    Polynomial p4 = p1.Mult(p2);
    cout << "Polynomial p1 * p2: " << p4 << endl;\
    float value;
    cout << "Enter a value to evaluate p1: ";
    cin >> value;
    cout << "p1(" << value << ") = " << p1.Eval(value) << endl;

    return 0;
}