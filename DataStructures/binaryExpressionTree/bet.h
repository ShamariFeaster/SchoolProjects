#ifndef _BET_H_
#define _BET_H_

#include <string>
#include <map>
using namespace std;

class BET
{
    struct BinaryNode
    {
        string element;
        BinaryNode * left;
        BinaryNode * right;
    };
    public:
        BET();
        BET(const string postfix);
        BET(const BET&);
        ~BET();
        bool buildFromPostfix(const string postfix);
        const BET & operator= (const BET &);
        void printInfixExpression();
        bool empty();


    private:
        BinaryNode * root;
        map<string, int> operators;
        void printInfixExpression(BinaryNode *n);
        void makeEmpty(BinaryNode* &t);
        BinaryNode * clone(BinaryNode *t) const;
        void init();


    friend string traverse(BinaryNode * &n, int precedence);

};

#include "bet.cpp"
#endif