#include "bet.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <utility>

//STAND ALONE HELPER FUNCTIONS
//puts a space-separated expression into a vector of tokens
void tokenize(vector<string> &output, string input)
{
    string buffer;
    for(int x = 0; x < input.size(); x++)
    {
        if(isspace(input[x]) == 0)
        {
            buffer += input[x];
        }
        else
        {
            output.push_back(buffer);
            buffer = "";
        }

        if( x == (input.size()-1) && buffer.compare("") != 0 )
            output.push_back(buffer);
    }
}

//used to test for the precence of operators in a string
bool any_operators(string str)
{
    bool is_alpha = false;
    for(int x = 0; x < str.size(); x++)
    {
        if(!isalnum(str[x]))
        {
            is_alpha = true;
            break;
        }
    }
    return is_alpha;
}

//recursive friend function function used in BET::printInfixExpression(BinaryNode *n)
string traverse(BET::BinaryNode * &n, int precedence)
{
    map<string, int> operators;
    operators["("] = 3;
    operators[")"] = 3;
    operators["/"] = 2;
    operators["*"] = 2;
    operators["+"] = 1;
    operators["-"] = 1;
    string ans;
    if(n != NULL)
    {
        if(operators.count(n->element) < 1)
        {
            return n->element;
        }
        else
        {   //recursions happens here
            ans = traverse(n->left, operators[n->element])
                + " " +  n->element + " " + traverse(n->right, operators[n->element]);

            if(operators[n->element] <= precedence)
            {
                ans = "( " + ans + " )";
            }
        }
    }
    return ans;
}
//-------------------------------------------------------
//MEMBER FUNCTIONS
void BET::init()
{
    root = NULL;
    operators["("] = 3;
    operators[")"] = 3;
    operators["/"] = 2;
    operators["*"] = 2;
    operators["+"] = 1;
    operators["-"] = 1;
}

BET::BET()
{
    init();
}

BET::BET(const string postfix)
{
    init();
    if(!buildFromPostfix(postfix))
        makeEmpty(root);
}

BET::BET(const BET& orig)
{
    init();
    *this = orig;
}

const BET & BET::operator= (const BET & lhs)
{
    makeEmpty(root);
    root = clone(lhs.root);
 }

BET::~BET()
{
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string postfix)
{
    //if tree exists,erase it
    makeEmpty(root);

    //if ther are no operators, make operand node and return
    if(!any_operators(postfix))
    {
        root = new BinaryNode;
        root->element = postfix;
        root->left = NULL;
        root->right = NULL;
        return true;
    }

    vector<string> v;
    tokenize(v, postfix);
    stack<BinaryNode *> s;
    string op;

    for (int x = 0; x < v.size(); x++)
    {
        op = v[x];
        if(operators.count(op) < 1)
        {
            BinaryNode * a = new BinaryNode;
            a->element = op;
            a->left = NULL;
            a->right = NULL;
            s.push(a);
        } else
        {
            if(s.size() < 2) //aborting improperly structured postfix expression
            {
                makeEmpty(root); //clear aborted tree
                return false;
            }

            root = new BinaryNode;
            root->element = op;
            root->right = s.top();
            s.pop();
            root->left = s.top();
            s.pop();
            s.push(root);
        }

    }
    if(s.size() > 1) //aborting improperly structured postfix expression
    {
        makeEmpty(root); //clear aborted tree
        return false;
    }
    else
        return true;
}

void BET::printInfixExpression()
{
    if(!empty())
        printInfixExpression(root);
}


bool BET::empty()
{
    if(root == NULL)
        return true;
    else
      return false;
}


//----------------------------------------------------
void BET::printInfixExpression(BinaryNode *n)
{
    string answer;
    if(!empty())
    {   //traverse() is a recursive function
        answer = traverse(n, operators[n->element] );
        if(any_operators(answer))
            answer = answer.substr(1, answer.length() - 2);
        cout << answer << endl;;
    }
}
void BET::makeEmpty(BinaryNode* &t)
{
    if(t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}
BET::BinaryNode * BET::clone(BinaryNode *t) const
{
    if(t == NULL)
        return NULL;
    else
    {
        BinaryNode * b = new BinaryNode();
        b->element = t->element;
        b->left = clone(t->left);
        b->right = clone(t->right);
        return b;
    }

}

