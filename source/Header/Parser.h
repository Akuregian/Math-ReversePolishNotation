#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Lexer.h"

// Parser will take in a string and use Lexer.h to Generate Tokens, then structure these tokens into a Tree
class Parser {
    public:
        Parser(std::string, bool pt);
        ~Parser();
        // Reverse Polish Notation
        void OperatorPrecedenceParse();

    private:
        int _position;
        // Stores all the parsed Tokens
        std::deque<SyntaxToken>  _tokensArr;
        // The Output Array in Reverse Polish Notation
        std::deque<SyntaxToken> ReversePolishNotation;
        // Temporariliy Holds Operator Tokens to Later be popped off the stack
        std::stack<SyntaxToken> tempStack;
        bool _printTree;
};


class Node
{
    public:
        Node() { left = nullptr; right = nullptr;}
        SyntaxToken root;
        Node *left;
        Node *right;
};

class Trunk {
    public:
        Trunk(Trunk *prev, std::string str) : previous(prev), _str(str) {};
        Trunk *previous;
        std::string _str;
};


class BinaryTree : public Node {
    public:
        BinaryTree(std::deque<SyntaxToken> RPN) : reversePolarNotation(RPN){};
        BinaryTree(const Node& n) { root = n.root;
                                    left = n.left;
                                    right = n.right; };
        void ParseIntoTree();
        Node* Leaf(SyntaxToken Root);
        Node* SubTree(SyntaxToken Root, Node* Left, Node* Right);
        void printStack();
        double Evaluate(Node*);
        void PrintTree(Node*, Trunk*, bool);

        Node* GrabTopNode() { return nodes.top(); };
    private:
        std::deque<SyntaxToken> reversePolarNotation;
        std::stack<Node*> nodes;

};


#endif