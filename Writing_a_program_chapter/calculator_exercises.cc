#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


void error (std::string s)
{
  throw std::runtime_error (s);
}


class Token{
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};


class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back (putback() is defined elsewhere)
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};


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
    case 'x':
        exit(0);
        break;    // for "quit"
    case '=':    // for "print"
    case '(': case ')': case '{': case '}': case '!': case '+': case '-': case '*': case '/':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        std::cin.putback(ch);         // put digit back into the input stream
        double val;
        std::cin >> val;              // read a floating-point number
        return Token('8', val);   // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}


Token_stream ts;    
double expression();    // declaration so that primary() can call expression()
double my_factorial(double n);


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
    case '8':
        return t.value;
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
double my_factorial(double n){
    int res = n;
    if(n < 2 && n >= 0) return 1;
    for(int i = res-1; i > 0; i--){
        res*=i;
    }
    return res;
}

int main()
{   
    std::cout << "Welcome to our simple calculator.\nPlease enter expressions using floating-point numbers.\n";
    std::cout << "Press 'x' to quit and = to print the expression.\n";
    double val;
try
{
    while (std::cin) {
        Token t = ts.get();
        if (t.kind == '=')
            std::cout << "=" << val << '\n';
        else
            ts.putback(t);
        val = expression();
    }
}
catch (std::exception& e) {
    std::cerr << "error: " << e.what() << '\n';

    return 1;
}
catch (...) {
    std::cerr << "Oops: unknown exception!\n";

    return 2;
}

}

//------------------------------------------------------------------------------
