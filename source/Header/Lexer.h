#ifndef TONESMATHMATICS_H
#define TONESMATHMATICS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <stack>

// Tokens for each index position of the equation, which is a string
enum Tokens
{
    LeftParathesisToken,
    RightParathesisToken,
    PowerToken,
    MulToken,
    DivToken,
    AddToken,
    SubToken,
    NumberToken,
    WhiteSpaceToken,
    X_VariableToken,
    Y_VariableToken,
    FunctionToken, 
    EndOfFileToken,
    BadToken,
};


// ----------------- The SyntaxToken at each Vert: (TypeOfToken, PositionInText, ParsedString) -----------------------
class SyntaxToken
{
public:
    SyntaxToken() {};
    SyntaxToken(Tokens token, int position, std::string text, int value, int precedence, std::string associativity)
        : _token(token), _position(position), _text(text), _value(value), _Precedence(precedence), _associativity(associativity) {};
    void Increment(){ _position++;};
    std::string TokenKindToString();
    int tokenValue(){ return _value; };
    Tokens returnToken() { return _token; };
    int getPosition() { return _position; };

    Tokens _token;
    int _position;
    int _value;
    std::string _text;
    std::string _associativity;
    int _Precedence;
};

//----------------Lexer class returns all the tokens for each vert of the equation -------------------
class Lexer
{
public:
    // Takes in a string and stores it in private var
    Lexer(std::string equation_string) : _equation_string(equation_string) { _position = 0; };
    // increments the position index, moving the index forward
    void NextPosition() { _position++; };
    // Returns the Current Character, at that _position
    char CurrentPosition();
    // Returns a syntaxToken of the current _position in the string
    SyntaxToken NextToken();

private:
    std::string _equation_string;
    int _position;
};


#endif