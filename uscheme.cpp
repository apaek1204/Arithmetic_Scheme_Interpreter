// uscheme.cpp

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>

using namespace std;

// Globals ---------------------------------------------------------------------

bool BATCH = false;
bool DEBUG = false;

// Structures ------------------------------------------------------------------

struct Node {
    Node(string value, Node *left=nullptr, Node *right=nullptr);
    ~Node();

    string value;
    Node * left;
    Node * right;

    friend ostream &operator<<(ostream &os, const Node &n);
};
Node::Node(string value, Node *left, Node *right){
    this->value = value;
    this->left = left;
    this->right = right;
}

Node::~Node(){
    delete left;
    delete right;
    left = nullptr;
    right = nullptr;
}
ostream &operator<<(ostream &os, const Node &n) {
    
    os << "(";
    if(n.left|| n.right){
        os << "Node: value=" << n.value <<", left="<< *n.left << ", right="<< *n.right;
    }
    else{
        os << "Node: value=" << n.value;
    }
    os << ")";
    return os;
}



// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    char c1=s.peek();
    string token;
    //skip whitespace
    while(isspace(c1)){
        c1=s.get();
        c1 = s.peek();
    }
    //check next char
    if(!isdigit(c1)){
        token = s.get();
    }
    else{
        token = s.get();
        while(isdigit(s.peek())){
            token += s.get();
        }
    }
    return token;
}

Node *parse_expression(istream &s) {
    string token = parse_token(s);
    Node *left=nullptr;
    Node *right=nullptr;
    if(token=="" || token==")"){
        return nullptr;
    }
    if(token == "("){
        token = parse_token(s);
        left = parse_expression(s);
        if(left){
            right = parse_expression(s);
        }
        if(right){
            parse_token(s);
        }
    }
    return new Node(token, left, right);
}

// Interpreter -----------------------------------------------------------------

int convert(string s){
    int ans=0;
    for(unsigned i=0; i<s.size(); i++){
        ans = ans*10;
        int temp = s[i]-'0';
        ans = ans + temp;
    }
    return ans;
}
void evaluate_r(const Node *n, stack<int> &s) { 
    if(n==nullptr){
        return;
    }
    evaluate_r(n->right, s);
    evaluate_r(n->left, s);

    if(isdigit(n->value[0])){
        s.push(convert(n->value));
    }
    else{
        
        int a= s.top();
        s.pop();
        int b = s.top();
        s.pop();
        if(n->value == "+"){
            s.push(a+b);
        }
        else if(n->value == "-"){
            s.push(a-b);
        }
        else if(n->value == "*"){
            s.push(a*b);
        }
        else{
            s.push(a/b);
        }
    }
}

int evaluate(const Node *n) {
    stack<int> s;
    evaluate_r(n,s);
    return s.top();
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    string line;
    int c;

    while ((c = getopt(argc, argv, "bdh")) != -1) {
        switch (c) {
            case 'b': BATCH = true; break;
            case 'd': DEBUG = true; break;
            default:
                cerr << "usage: " << argv[0] << endl;
                cerr << "    -b Batch mode (disable prompt)"   << endl;
                cerr << "    -d Debug mode (display messages)" << endl;
                return 1;
        }
    }

    while (!cin.eof()) {
        if (!BATCH) {
            cout << ">>> ";
            cout.flush();
        }

        if (!getline(cin, line)) {
            break;
        }

        if (DEBUG) { cout << "LINE: " << line << endl; }

        stringstream s(line);
        Node *n = parse_expression(s);
        if (DEBUG) { cout << "TREE: " << *n << endl; }

        cout << evaluate(n) << endl;

        delete n;
    }

    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
