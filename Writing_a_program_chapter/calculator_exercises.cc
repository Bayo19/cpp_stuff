#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

const char number = '8';
const char quit = 'q';
const char print = '=';
const char name = 'a';
const char let = 'L';
const std::string result = "= ";
const std::string declkey = "let";


void error (std::string s)
{
  throw std::runtime_error (s);
}


class Token{
public:
    char kind;        // what kind of token
    double value; 
    std::string name;    // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
    Token(char ch, std::string n)
        :kind(ch), name(n) {} // ch refers to token for variable and name refers to variables name
};


class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back (putback() is defined elsewhere)
    void ignore(char c);
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};



class Variable {
public:
    std::string name;
    double value;
    Variable(std::string this_name, double this_val)
        :name(this_name), value(this_val) {};
};

std::vector<Variable> var_table;


// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}


void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}



Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;    

    switch (ch) {
    case quit:
        exit(0);
        break;
    case print:
    case '(': case ')': case '{': case '}': case '!': case '+': case '-': case '*': case '/': case '%':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        std::cin.putback(ch);         // put digit back into the input stream
        double val;
        std::cin >> val;
        return Token(number, val); 
    }
    default:
        if(isalpha(ch)) {
            std::string s;
            s += ch;
            while(std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
            std::cin.putback(ch);
            if(s == declkey) return Token(let);
            return Token(name, s);
        }
        error("Bad token");
    }
}


void Token_stream::ignore(char c)
{
    if(full && c == buffer.kind){
        full = false;
        return;
    }

    char ch = 0;
    while(std::cin >> ch){
        if(ch == c) return;
    }
}



Token_stream ts;    
double expression();    // declaration so that primary() can call expression()
double my_factorial(double n);

double get_value(std::string s)
{   
    for (const Variable& v: var_table)
    {
        if(v.name == s) return v.value;
    }
    error("get: undefined variable ");
}


void set_value(std::string s, double d)
{
    for(Variable& v: var_table)
    {
        if(v.name == s){
            v.value = d;
            return;
        }
    }
    error("set: undefined variable");
}

bool is_declared(std::string var)
{
    for(const Variable& v: var_table)
    {
        if(v.name == var) return true;
    }
    return false;

}


double define_name(std::string var, double val)
{
    if(is_declared(var)){
        std::string error_message = var + " is declared already";
        error(error_message);
    }

    var_table.push_back(Variable(var, val));
    return val;
}


double declaration()
    // assume we have seen "let"
    // handle: name = expression
    // declare a variable called "name" with the initial value set to "expression"
{
    Token t = ts.get();
    if(t.kind != name){
        error("name expected in declaration");
    }
    std::string var_name = t.name;

    Token t2 = ts.get();
    if(t2.kind != '='){
        std::string error_message = "= missing in declation of " + var_name;
        error(error_message);
    }

    double d = expression();
    define_name(var_name, d);
    return d;
}


double statement()
{
    Token t = ts.get();
    switch(t.kind){
        case let:
            return declaration();
        default:
        ts.putback(t);
        return expression();
    }
}


void clean_up_mess()
{
    ts.ignore(print);
}


// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    Token factorial_t = ts.get();
    // check for presence of factorial operator '!'
    switch(factorial_t.kind) {
        case '!':
        return my_factorial(t.value);
        default:
        ts.putback(factorial_t); // put char back if not '!'
    }

    switch (t.kind) {
    case '(': case '{':    // handle '(' expression ')'
    {   if(t.kind == '('){
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        
        if(t.kind == '{'){
            double d = expression();
            t = ts.get();
            if(t.kind != '}') error("'}' expected");
            return d;
        }
    }
    case number:
        return t.value;
    case '-':
        return - primary();
    case '+':
        return primary();
    break;
    default:
        error("primary expected");
    }
}


// deal with *, /
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left = fmod(left, d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}


// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}


// get factorial of n
double my_factorial(double n)
{
    int res = n;
    if(n < 2 && n >= 0) return 1;
    for(int i = res-1; i > 0; i--){
        res*=i;
    }
    return res;
}


void calculate()
{
    std::cout << "Welcome to our simple calculator.\nPlease enter expressions using floating-point numbers.\n";
    std::cout << "Press 'x' to quit and = to print the expression.\n";
    double val;
    while (std::cin) {
        try {
            Token t = ts.get();
            while(t.kind == print) t = ts.get();
            if(t.kind == quit) return;
            ts.putback(t);
            std::cout << result << statement() << '\n';
        }
        catch (std::exception& e) {
            std::cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
}


int main()
{   

try
{
    calculate();
    return 0;
}
catch (std::runtime_error& e) {
    std::cerr << "error: " << e.what() << '\n';
    std::cout << "Please enter the character ~ to exit\n";

    for (char ch; std::cin >> ch;){
        if(ch =='~') return 1;
    }
    return 1;
}
catch (...) {
    std::cerr << "Oops: unknown exception!\n";

    return 2;
}

}

