
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void error (std::string s)
{
  throw std::runtime_error (s);
}

struct Token {
	char kind;
	double value;
	std::string name;
	Token(char ch) :kind(ch), value(0) { } // Token for operators or functions - ch = operator
	Token(char ch, double val) :kind(ch), value(val) { } // Token for numbers - ch = 8, value = floating point number
    Token(char ch, std::string n) :kind(ch), name(n) {} // Token for variables ch = name (constant), name = variable name
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }
	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char);
};


const int k = 1000;
const char let = 'L';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqrt_key = 's';
const char power_key = 'p';
const char quit_key = 'q';
const std::string quit = "exit";
const std::string declkey = "#";
const std::string square_root = "sqrt";
const std::string power = "pow";


Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	std::cin >> ch;
	switch (ch) {
    case '#':
        return Token(let); // Return Token for declaration keyword;
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
    case ',':
		return Token(ch); // Return Token for operator
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	std::cin.unget();
	double val;
	std::cin >> val;
	return Token(number, val); // Return Token for floating point number
	}
	default:
		if (isalpha(ch)) {
			std::string s;
			s += ch;
			while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			std::cin.unget();
            if (s == square_root) return Token(sqrt_key); // Return Token for sqrt function
            if (s == power) return Token(power_key); // Return Token for pow function
            if (s == quit) return Token(quit_key); // Return Token for quitting program;
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (std::cin >> ch)
		if (ch == c) return;
}

struct Variable {
	std::string name;
	double value;
	Variable(std::string n, double v) :name(n), value(v) { }
};

std::vector<Variable> names;

double get_value(std::string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
    std::string err_msg = "get: undefined name " + s;
	error(err_msg);
}

void set_value(std::string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
    std::string err_msg = "set: undefined name " + s;
	error(err_msg);
}

bool is_declared(std::string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double square_root_fn()
{
    Token t = ts.get();
    switch(t.kind){
        case '(':
        {
            double d = expression();
            if (d <= 0) {
                error("can not get square root of number less than or equal to 0");
            }

            Token t2 = ts.get();
            if (t2.kind != ')') error("')' expected");
            return sqrt(d);
        }
    }
}

int power_fn()
{
    Token t = ts.get();
    switch(t.kind){
        case '(':
        {
            double d = expression();
            Token t2 = ts.get();
            char ch;
            int i;
            if (t2.kind != ',') error("pow takes two arguments");
            
            std::cin >> i;
            double res = d;
            for(int n = 0; n < (i-1); n++){
                res *= d;
            }
            Token t3 = ts.get();
            if (t3.kind != ')') error("')' expected");
            return res;
        }
        default:
		    error("function: 'pow' takes two arguments: pow(double x, int i)");
    }
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	    t = ts.get();
	    if (t.kind != ')') error("')' expected");
        return d;
	}
	case '-':
		return - primary();
	case number:
		return t.value;
	case name:
    {
        Token t2 = ts.get();
        if (t2.kind == '=') {
            double d = expression();
            set_value(t.name, d);
            return get_value(t.name);
        }
        ts.unget(t2);
        return get_value(t.name);
    }
    case sqrt_key:
        return square_root_fn();
    case power_key:
        return power_fn();
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// declaring a variable
double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	std::string name = t.name;
    std::string err_msg = name + " declared twice";
	if (is_declared(name)) error(err_msg);
	Token t2 = ts.get();
	if (t2.kind != '='){
        err_msg = "= missing in declaration of " + name;
        error(err_msg);
    }
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}


double assignment(std::string name)
{
    double d = expression();
    set_value(name, d);
    return d;
}

// statement - either declaration
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const std::string prompt = "> ";
const std::string result = "= ";

void calculate()
{
	while (std::cin) {
        try {
            std::cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get();
            if (t.kind == quit_key) return;
            ts.unget(t);
            std::cout << result << statement() << '\n';
        }
        catch (std::runtime_error& e) {
            std::cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
}

int main()
{

    try {
        calculate();
        return 0;
    }
    catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << '\n';
        char c;
        while (std::cin >> c && c != ';');
        return 1;
    }
    catch (...) {
        std::cerr << "exception\n";
        char c;
        while (std::cin >> c && c != ';');
        return 2;
    }

}