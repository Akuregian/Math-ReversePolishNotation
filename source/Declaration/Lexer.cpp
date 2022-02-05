#include "../Header/Lexer.h"

//-------------------------------- Helper Functions --------------------------------

int StringToInt(std::string str)
{
    std::stringstream stream(str);
    int holdValues = 0;
    stream >> holdValues;
    return holdValues;
}


// This is more of less for Debugging purposes
std::string ShowKind(Tokens toke)
{
    // if whitespace, return
    if(toke == WhiteSpaceToken) {
        return "WhiteSpaceToken";
    }

    switch(toke) {
        case(NumberToken):
            return "NumberToken";
        case(AddToken):
            return "AddToken";
        case(SubToken):
            return "SubToken";
        case(MulToken):
            return "MulToken";
        case(DivToken):
            return "DivToken";
        case(LeftParathesisToken):
            return "LeftParathesisToken";
        case(RightParathesisToken):
            return "RightParathesisToken";
        case(WhiteSpaceToken):
            return "WhiteSpaceToken";
        case(EndOfFileToken):
            return "EndOfFileToken";
        case(FunctionToken):
            return "FunctionToken";
        case(X_VariableToken):
            return "X_VariableToken";
        case(Y_VariableToken):
            return "Y_VariableToken";
        case(PowerToken):
            return "PowerToken";
        case(BadToken):
            return "BadToken";
        default:
            return "SOMEFUCKEDTOKEN";
    }
};

//--------------------------------- SyntaxToken Class ------------------------------

// This is more of less for Debugging purposes
std::string SyntaxToken::TokenKindToString()
{
    // if whitespace, return
    if(_token == WhiteSpaceToken) {
        return "WhiteSpaceToken";
    }

    switch(_token) {
        case(NumberToken):
            return "NumberToken";
        case(AddToken):
            return "AddToken";
        case(SubToken):
            return "SubToken";
        case(MulToken):
            return "MulToken";
        case(DivToken):
            return "DivToken";
        case(LeftParathesisToken):
            return "LeftParathesisToken";
        case(RightParathesisToken):
            return "RightParathesisToken";
        case(WhiteSpaceToken):
            return "WhiteSpaceToken";
        case(FunctionToken):
            return "FunctionToken";
        case(EndOfFileToken):
            return "EndOfFileToken";
        case(X_VariableToken):
            return "X_VariableToken";
        case(Y_VariableToken):
            return "Y_VariableToken";
        case(PowerToken):
            return "PowerToken";
        case(BadToken):
            return "BadToken";
        default:
            return "SOMEFUCKEDTOKEN";
    }
};

// ----------------------------------------- Lexer Class -------------------------------------------

// return the current charactor of the string equation
char Lexer::CurrentPosition()
{
    if (_position >= _equation_string.length() + 1)
    {
        std::cout << "Error, _position: " << _position << " is out of bounds, exiting" << std::endl;
        return '\0';
    }
    return _equation_string[_position];
};

// Traverses each index of the equation generating tokens
SyntaxToken Lexer::NextToken()
{
    // Make sure _position is not out of bounds of string
    if (_position >= _equation_string.length())
    {
        return SyntaxToken(EndOfFileToken, _position, "\0", 0, 0, "");
    }

    // check if the char is a digit
    if (std::isdigit(CurrentPosition()))
    {
        int currPos = _position;

        while (std::isdigit(CurrentPosition()))
        {
            NextPosition();
        }

        int dx = _position - currPos;
        std::string text = _equation_string.substr(currPos, dx);

        int value = StringToInt(text);
        return SyntaxToken(NumberToken, currPos, text, value, 0, "");
    }

    // check if the char is a whitespace
    if (std::isspace(CurrentPosition()))
    {
        int currPos = _position;

        while (std::isspace(CurrentPosition()))
        {
            NextPosition();
        }

        int dx = _position - currPos;
        std::string text = _equation_string.substr(currPos, dx);

        return SyntaxToken(WhiteSpaceToken, currPos, text, 0, 0, "");
    }

    // Check if its a Function: cos(), sin(), tan()
    std::string possibleFunction = _equation_string.substr(_position, 3);
    if (possibleFunction == "cos" || possibleFunction == "sin" || possibleFunction == "tan")
    {
        if (possibleFunction == "cos")
        {
            _position += 3;
            return SyntaxToken(FunctionToken, _position, "cos", 0, 0, "");
        }
        else if (possibleFunction == "sin")
        {
            _position += 3;
            return SyntaxToken(FunctionToken, _position, "sin", 0, 0, "");
        }
        else if (possibleFunction == "tan")
        {
            _position += 3;
            return SyntaxToken(FunctionToken, _position, "tan", 0, 0, "");
        }
        else {
            return SyntaxToken(BadToken, _position++, _equation_string.substr(_position - 1, 1), 0, 0, "");
        }
    }
    /* 
     [Operator]      [Associativity]
    Exponents - 4 --> "Right"
    Mulitplication - 3  --> "Left"
    Divition - 3 -->  "Left"
    Addition - 2 --> "Left"
    Subtraction - 2 --> "Left"
    */

    // Check if Charactor is one of the Tokens we want
    if (CurrentPosition() == '+')
    {
        return SyntaxToken(AddToken, _position++, "+", 0, 2, "Left");
    }
    else if (CurrentPosition() == '-')
    {
        return SyntaxToken(SubToken, _position++, "-", 0, 2, "Left");
    }
    else if (CurrentPosition() == '*')
    {
        return SyntaxToken(MulToken, _position++, "*", 0, 3, "Left");
    }
    else if (CurrentPosition() == '/')
    {
        return SyntaxToken(DivToken, _position++, "/", 0, 3, "Left");
    }
    else if (CurrentPosition() == '(')
    {
        return SyntaxToken((LeftParathesisToken), _position++, "(", 0, 0, "");
    }
    else if (CurrentPosition() == ')')
    {
        return SyntaxToken(RightParathesisToken, _position++, ")", 0, 0, "");
    }
    else if (CurrentPosition() == 'x')
    {
        return SyntaxToken(X_VariableToken, _position++, "x", 0, 0, "");
    }
    else if (CurrentPosition() == 'y')
    {
        return SyntaxToken(Y_VariableToken, _position++, "y", 0, 0, "");
    }
    else if (CurrentPosition() == '^')
    {
        return SyntaxToken(PowerToken, _position++, "^", 0, 4, "Right");
    }
    else
    {
        return SyntaxToken(BadToken, _position++, _equation_string.substr(_position - 1, 1), 0, 0, "");
    }
}

