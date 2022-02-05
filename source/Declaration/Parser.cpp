#include "../Header/Parser.h"

void Details(Node* tree) {
    std::cout << "Root: " << tree->root._value << " Left: " << tree->left << " Right: " << tree->right << "" << std::endl;
}

void BinaryTree::printStack()
{
    for (std::stack<Node*> dump = nodes; !dump.empty(); dump.pop())
        dump.top()->root._value;

    std::cout << "(" << nodes.size() << " elements)\n";
}

//Adds all the Tokens to _tokensList, if its not a WhiteSpace or Bad Token
Parser::Parser(std::string text, bool printTree)
{
    _position = 0;

    // Perform a Lexer Analysis on the text being Passed in
    Lexer *lexer = new Lexer(text);

    // Init a List to Store Tokens
    std::deque<SyntaxToken> tokenList;

    // store the current token
    SyntaxToken token;

    // loop
    while (true)
    {
        // Grab The Token
        token = lexer->NextToken();
        // Ensure its not the EndOfFileToken
        if (token.returnToken() == EndOfFileToken) { break; }
        //     // If The Token is not a WhiteSpace or Bad Token then Push that Token back to the List
        if (token.returnToken() != WhiteSpaceToken && token.returnToken() != BadToken)
        {
            tokenList.push_back(token);
        }
    }
    

    // Assign to private Var _tokensLists
    _tokensArr = tokenList;

    // Re-orders tokens into Reverse Polish Notation
    OperatorPrecedenceParse();

    // Takes that RPN and contructs a Tree
    BinaryTree *binarytree = new BinaryTree(ReversePolishNotation);

    // Parse into Tree
    binarytree->ParseIntoTree();
    // Grab Tree
    Node *tree = binarytree->GrabTopNode();

    // Evaluate
    std::cout << binarytree->Evaluate(tree) << std::endl;

    if(printTree){
        // Print Tree
        binarytree->PrintTree(tree, nullptr, false);
    }


    delete lexer;
   // delete binarytree;
};

Parser::~Parser(){
}

// Parses the tokens into Reverse Polish Notation i.e. 1 + 2 --> 1 2 +
void Parser::OperatorPrecedenceParse()
{
    while (_tokensArr.size() > 0)
    {
        // Read The First Token and Remove from _tokensArray
        SyntaxToken curr = _tokensArr.front();

        _tokensArr.pop_front();
        // If NumberToken, Push to outputArray
        if (curr.returnToken() == NumberToken || curr.returnToken() == X_VariableToken || curr.returnToken() == Y_VariableToken)
        {
            ReversePolishNotation.push_back(curr);
        }
        //If the Token is a Function, then push to operator stack
        else if (curr.returnToken() == FunctionToken)
        {
            tempStack.push(curr);
        }
        //If the Token is an Operator, then check precedence then push to stack
        else if (curr.returnToken() == AddToken || curr.returnToken() == SubToken ||
            curr.returnToken() == MulToken || curr.returnToken() == DivToken || curr.returnToken() == PowerToken)
        {
            // while !stack.empty(), top.Precedence > curr.pecedence, isleftAssociative, and isnot Left Parthesis
            while (!tempStack.empty() && 
                  (tempStack.top()._Precedence > curr._Precedence || tempStack.top()._Precedence == curr._Precedence && curr._associativity == "Left" )
                    && (tempStack.top().returnToken() != LeftParathesisToken))
            {
                SyntaxToken popped = tempStack.top();
                tempStack.pop();
                ReversePolishNotation.push_back(popped);
            }
            tempStack.push(curr);
        }
        // If Token Left Parathesis
        else if(curr.returnToken() == LeftParathesisToken) {

            tempStack.push(curr);

        }
        // If Token Right Parthesis
        else if(curr.returnToken() ==  RightParathesisToken) {
            while(tempStack.top().returnToken() != LeftParathesisToken){
                SyntaxToken popped = tempStack.top();
                tempStack.pop();
                ReversePolishNotation.push_back(popped);

            }
            // If there is Left Parenthesis, pop and discard
            if(tempStack.top().returnToken() == LeftParathesisToken) {

                tempStack.pop();

            }
          //  if(tempStack.top().returnToken() == FunctionToken) {
          //      SyntaxToken popped = tempStack.top();
          //      tempStack.pop();
          //      ReversePolishNotation.push_back(popped);
          //  }
        }

    }
    if(_tokensArr.empty()) {
        while(!tempStack.empty()) {
            SyntaxToken popped = tempStack.top();
            tempStack.pop();
            ReversePolishNotation.push_back(popped);
        }
    }

    for(auto i : ReversePolishNotation){
        std::cout << i._text << " ";
    }
    std::cout << std::endl;

}


void ShowTrunk(Trunk *p){
    if(p->previous == nullptr){
        return;
    }
    ShowTrunk(p->previous);
    std::cout << p->_str;
}


void BinaryTree::ParseIntoTree()
{
       while (reversePolarNotation.size() > 0)
    {
        // Read The First Token and Remove from _tokensArray
        SyntaxToken curr = reversePolarNotation.front();

        reversePolarNotation.pop_front();
        // If NumberToken, Push to outputArray
        if (curr.returnToken() == NumberToken || curr.returnToken() == X_VariableToken || curr.returnToken() == Y_VariableToken)
        {
           Node *node = BinaryTree::Leaf(curr);
           nodes.push(node);
        }
        //If the Token is a Function, then push to operator stack
        else if (curr.returnToken() == FunctionToken)
        {
           Node *node = BinaryTree::Leaf(curr);
           std::cout << "Function Pushed" << std::endl;
           nodes.push(node);
        }
        //If the Token is an Operator, then check precedence then push to stack
        else if (curr.returnToken() == AddToken || curr.returnToken() == SubToken ||
            curr.returnToken() == MulToken || curr.returnToken() == DivToken || curr.returnToken() == PowerToken)
        {
            Node *subTree = new Node();
            while(nodes.size() > 0) {
                Node *right = nodes.top();
                nodes.pop();

                Node *left = nodes.top();
                nodes.pop();
                subTree = BinaryTree::SubTree(curr, left, right);
                break;
            }
            nodes.push(subTree);

            //printStack();
        }
    }
}


Node* BinaryTree::Leaf(SyntaxToken nodetoken)
{
    Node *node = new Node();
    node->root = nodetoken;
    node->left = nullptr;
    node->right = nullptr;
    return node;
};


Node* BinaryTree::SubTree(SyntaxToken nodetoken, Node *left, Node *right)
{
    Node *subTree = new Node();
    subTree->root = nodetoken;
    subTree->left = left;
    subTree->right = right;
    return subTree;
};


double BinaryTree::Evaluate(Node *node){
    // ensure tree is not empty
    if(node == nullptr){ throw std::string("Error"); };

    // Check if Left and Right is nullptr
    if(node->left == nullptr && node->right == nullptr){
        return node->root._value;
    }
    // Grab Right First
    double right_value = Evaluate(node->right);
    double left_value = Evaluate(node->left);

    if(node->root._text == "+"){
        return left_value + right_value; 
    } 
    if(node->root._text == "-") {
        return left_value - right_value; 
    }
    if(node->root._text == "*") {
        return left_value * right_value; 
    }
    if(node->root._text == "/") {
        return left_value / right_value; 
    }
    if(node->root._text == "^") {
        double constant = left_value;
        double exponent = right_value;
        double results = 1;
        while(exponent != 0){
            results *= constant;
            exponent--;
        }
        return results;
    }
}

// Efficient Algorithm to print the Binary Tree Structure
// ** Tree is read From TOP to BOTTOM when printed too the terminal [RightNode [operator] LeftNode]
void BinaryTree::PrintTree(Node *tree, Trunk *prev, bool isLeft)
{
    // nodes.size() should only have 1 element inside, the tree.
    if (nodes.size() == 1)
    {
        // Return if the tree we want to construct is nullptr
        if (tree == nullptr){ return; }
        // store the previous string
        std::string prevString = "    ";
        // Create Trunk(Storage Container) to store PREVIOUS Trunk, Along with its string
        Trunk *trunk = new Trunk(prev, prevString); 
        // Print Left Side of Tree


        PrintTree(tree->left, trunk, true);

        //If prev is nullptr, print "---"
        if (!prev) { 
            trunk->_str = "———"; 
            std::cout << "\t";

        }
        // If isLeft is true
        else if (isLeft) {
            std::cout << "\t";
            trunk->_str = ".———";
            prevString = "    |";
        }
        else {
            std::cout << "\t";
            trunk->_str = "`———";
            prev->_str = prevString;
        }

        // ShowTrunk prints the previous Trunk's _str variable
        ShowTrunk(trunk);

        // Print the current trees root value
        std::cout << "[" << tree->root._text << "]" << std::endl;

        // if prev is not null, store the prevString into the prev->_str
        if (prev)
        {
            prev->_str = prevString;
            if(prevString == "    " && !prev->previous){
            std::cout << "|";
            }

        }
        trunk->_str = "|    |";

        PrintTree(tree->right, trunk, false);


        delete trunk;
    }
}
