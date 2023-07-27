#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


void error (std::string s)
{
  throw std::runtime_error (s);
}

class Token {
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
    Token_stream();
    Token get();
    void putback(Token t);
private:
    bool full {false};
    Token buffer;
};

Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if(full){
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;

    switch(ch){
        case ';': // print
        case 'q': // quit
        case '(': case ')': case '+': case '-': case '*': case '/':
        return Token{ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            std::cin.putback(ch);
            double val;
            return Token{'8', val};
        }
        default:
            error("Bad token");
    }
}

Token_stream ts;
double expression();
double term();
double primary();


double primary()
{
    Token t = ts.get();
    switch(t.kind){
        case '(':
            {
                double d = expression();
                t = ts.get();
                if(t.kind != ')') error("')' expected");
                return d;
            }
        case '8':
            return t.value;
        default:
            error("primary expected");
    }
}


double term()
{
    double left = primary();
    Token t = ts.get();
    while(true){
        switch(t.kind){
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {    double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }                
            default:
                ts.putback(t);
                return left;
        }
    }
}


double expression()
{
    double left = term();
    Token t = ts.get();
    while(true){
        switch(t.kind){
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

int main()
{
    try {
        double val = 0;
        while (std::cin){
            Token t = ts.get();
            if(t.kind == 'q') break;
            if(t.kind == ';'){
                std::cout << "=" << val << '\n';
            } else {
                ts.putback(t);
            }
            val = expression();
        }
    }
    catch (std::exception& e){
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch(...){
        std::cerr << "unknown exception \n";
        return 2;
    }
}