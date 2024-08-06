#include <iostream>
using namespace std;

class Polynomial{
    public:
        Polynomial();
        Polynomial Add();
        Polynomial Mult();
        float Eval(float f);
    private:
        Term *termArray;
        int capacity;
        int terms;
};
class Polynomial;
class Term{
    friend Polynomial;
    private:
        float coef;
        int exp;
};
int main(){

}
