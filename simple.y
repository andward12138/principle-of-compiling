%{
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

extern int yylex();
extern void yyerror(const char* s);
extern FILE* yyin;

map<string, int> Store_Identifier;
map<string, int> Store_String;
map<string, int> Store_Int;
int total_Count = 0;

// Global variables
int _curr_index = 0;
int _curr_T = 0;
string program_name = "";

// Utility functions
string ToString(int a) {
    if (a == 0) return "0";
    string ret = "";
    while (a > 0) {
        char temp = (char)(a % 10 + '0');
        ret = temp + ret;
        a /= 10;
    }
    return ret;
}

int ToInt(string a) {
    int ret = 0;
    for(int i = 0; i < a.length(); i++) {
        if (a[i] >= '0' && a[i] <= '9') {
            ret = ret * 10 + a[i] - '0';
        }
    }
    return ret;
}

// Quaternion structure
struct Quaternion {
    string v1, v2, v3, v4;
    int index;
    Quaternion(int _index, string _v1 = "-", string _v2 = "-", string _v3 = "-", string _v4 = "-") {
        index = _index;
        v1 = _v1;
        v2 = _v2;
        v3 = _v3;
        v4 = _v4;
    }
};

vector<Quaternion> Quaternions;

// E-state for boolean expressions
struct EState {
    int selfpos;
    int _true;
    int _false;
    bool isCorrect;
    EState* _trueList;
    EState* _falseList;
    
    EState(int _index) {
        selfpos = _index;
        _true = -1;
        _false = -1;
        _trueList = NULL;
        _falseList = NULL;
        isCorrect = false;
    }
    
    EState*& GetTlist() {
        if (_trueList == NULL)
            return _trueList;
        else
            return _trueList->GetTlist();
    }
    
    EState*& GetFlist() {
        if (_falseList == NULL)
            return _falseList;
        else
            return _falseList->GetFlist();
    }
    
    void backpatch_T(int exit) {
        _true = exit;
        if (selfpos > 0 && !isCorrect) {
            Quaternions[selfpos].v4 = ToString(exit);
        }
        if (_trueList == NULL)
            return;
        else
            _trueList->backpatch_T(exit);
    }
    
    void backpatch_F(int exit) {
        _false = exit;
        if (selfpos > 0 && !isCorrect) {
            Quaternions[selfpos].v4 = ToString(exit);
        }
        if (_falseList == NULL)
            return;
        else
            _falseList->backpatch_F(exit);
    }
};

// Control flow states
struct if_State {
    EState* E;
    int pos_ElseQ;
    if_State(EState* _temp) {
        E = _temp;
        pos_ElseQ = -1;
    }
    void backpatch_T(int exit) {
        E->backpatch_T(exit);
    }
    void backpatch_F(int exit) {
        E->backpatch_F(exit);
    }
};

struct while_State {
    int Enter;
    EState* E;
    void backpatch_T(int exit) {
        E->backpatch_T(exit);
    }
    void backpatch_F(int exit) {
        E->backpatch_F(exit);
    }
    while_State(EState* _temp, int _enter) {
        E = _temp;
        Enter = _enter;
    }
};

struct repeat_State {
    int Enter;
    EState* E;
    repeat_State(int _enter) {
        Enter = _enter;
        E = NULL;
    }
    void backpatch_T(int exit) {
        if (E) E->backpatch_T(exit);
    }
    void backpatch_F(int exit) {
        if (E) E->backpatch_F(exit);
    }
};

// Stacks for control flow
stack<if_State> if_stack;
stack<while_State> while_stack;
stack<repeat_State> repeat_stack;

// Storage for EStates
vector<EState*> e_Storage;

// Variable generators
string newTemp() {
    return "T" + ToString(++_curr_T);
}

void PrintQuaternions() {
    cout << "Generated Quaternions:" << endl;
    for (int i = 0; i < Quaternions.size(); i++) {
        cout << "(" << (i < 10 ? " " : "") << i << ")  (" << Quaternions[i].v1 << ", " 
             << Quaternions[i].v2 << ", " << Quaternions[i].v3 << ", " 
             << Quaternions[i].v4 << ")" << endl;
    }
}

void addQuaternion(string op, string arg1 = "-", string arg2 = "-", string result = "-") {
    Quaternions.push_back(Quaternion(_curr_index++, op, arg1, arg2, result));
}

%}

%union {
    char* str;
    struct {
        char* addr;
        void* estate;
    } expr;
    void* estate_ptr;
}

%token <str> IDENTIFIER NUMBER
%token AND ARRAY BEGIN_TOKEN TOKEN_BOOL CALL CASE TOKEN_CHAR CONSTANT DIM DO ELSE END FALSE_TOKEN
%token FOR IF TOKEN_INPUT INTEGER NOT OF OR OUTPUT PROCEDURE PROGRAM READ REAL REPEAT
%token SET STOP THEN TO TRUE_TOKEN UNTIL VAR WHILE WRITE
%token ASSIGN EQ NE LT LE GT GE PLUS MINUS MULTIPLY DIVIDE
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE SEMICOLON COLON COMMA DOT

%type <expr> expression term factor
%type <estate_ptr> condition
%type <str> assignment_target

%left OR
%left AND
%right NOT
%left EQ NE LT LE GT GE
%left PLUS MINUS
%left MULTIPLY DIVIDE

%start program

%%

program:
    PROGRAM IDENTIFIER SEMICOLON {
        program_name = string($2);
        free($2);
    } var_declarations compound_statement DOT {
        cout << "Program parsed successfully!" << endl;
        addQuaternion("sys");
        PrintQuaternions();
    }
    ;

var_declarations:
    /* empty */
    | VAR var_declaration_list
    ;

var_declaration_list:
    var_declaration
    | var_declaration_list var_declaration
    ;

var_declaration:
    identifier_list COLON type SEMICOLON
    ;

identifier_list:
    IDENTIFIER { free($1); }
    | identifier_list COMMA IDENTIFIER { free($3); }
    ;

type:
    INTEGER | REAL | TOKEN_BOOL | TOKEN_CHAR
    ;

compound_statement:
    BEGIN_TOKEN {
        // Add program quaternion at the beginning
        if (_curr_index == 0) {
            addQuaternion("program", program_name, "-", "-");
        }
    } statement_list END
    ;

statement_list:
    statement
    | statement_list SEMICOLON statement
    ;

statement:
    assignment_statement
    | compound_statement
    | if_statement
    | while_statement
    | repeat_statement
    | /* empty */
    ;

assignment_statement:
    assignment_target ASSIGN expression {
        addQuaternion(":=", $3.addr, "-", $1);
        free($1);
        free($3.addr);
    }
    ;

assignment_target:
    IDENTIFIER {
        $$ = strdup($1);
        free($1);
    }
    ;

if_statement:
    IF condition THEN {
        if_State new_if((EState*)$2);
        new_if.backpatch_T(_curr_index);
        if_stack.push(new_if);
    } statement else_part {
        if (!if_stack.empty()) {
            if_State& top_if = if_stack.top(); 

            if (top_if.pos_ElseQ == -1) { // No ELSE: 'IF condition THEN statement'
                int condition_false_target;
                if (!while_stack.empty() && program_name != "") { // Check program_name to ensure it's not during global var processing if any
                    condition_false_target = while_stack.top().Enter;
                } else {
                    condition_false_target = _curr_index;
                }
                top_if.backpatch_F(condition_false_target);
            } else { // Has ELSE: 'IF condition THEN statement ELSE statement'
                // top_if.pos_ElseQ is the quadruple for jumping from end of THEN over ELSE body
                int jump_over_else_target;
                if (!while_stack.empty() && program_name != "") {
                    jump_over_else_target = while_stack.top().Enter;
                } else {
                    jump_over_else_target = _curr_index; // _curr_index is after ELSE body
                }
                Quaternions[top_if.pos_ElseQ].v4 = ToString(jump_over_else_target);
            }
            if_stack.pop();
        }
    }
    ;

else_part:
    /* empty */
    | ELSE {
        if (!if_stack.empty()) {
            if_State& top_if = if_stack.top();
            top_if.pos_ElseQ = _curr_index;
            addQuaternion("j", "-", "-", "-1");
            top_if.backpatch_F(_curr_index);
        }
    } statement
    ;

while_statement:
    WHILE {
        while_stack.push(while_State(NULL, _curr_index));
    } condition DO {
        while_stack.top().E = (EState*)$3;
        while_stack.top().backpatch_T(_curr_index);
    } statement {
        addQuaternion("j", "-", "-", ToString(while_stack.top().Enter));
        
        // Determine the target for the FALSE exit of this while loop's condition.
        int false_target_addr;
        while_State this_while_attrs = while_stack.top(); 
        while_stack.pop(); // Temporarily pop current while to peek

        if (!while_stack.empty()) {
            // Nested while: false exit of current (inner) while jumps to start of OUTER while.
            false_target_addr = while_stack.top().Enter;
        } else {
            // Not nested (or outermost): false exit jumps to instruction after this loop's own jump-back.
            // _curr_index is already at this position (after the addQuaternion above).
            false_target_addr = _curr_index;
        }
        
        while_stack.push(this_while_attrs); // Restore stack before using its EState

        while_stack.top().E->backpatch_F(false_target_addr);
        while_stack.pop(); // Finally, pop this while_State.
    }
    ;

repeat_statement:
    REPEAT {
        repeat_State new_repeat(_curr_index);
        repeat_stack.push(new_repeat);
    } statement_list UNTIL condition {
        repeat_stack.top().E = (EState*)$5;
        repeat_stack.top().backpatch_F(repeat_stack.top().Enter);
        repeat_stack.top().backpatch_T(_curr_index);
        repeat_stack.pop();
    }
    ;

condition:
    expression EQ expression {
        // Create the main E-state container
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        // Create true jump (conditional jump)
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j=", $1.addr, $3.addr, "-1");
        p->_trueList = lastT;
        
        // Create false jump (unconditional jump)
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        $$ = (void*)p;
        free($1.addr);
        free($3.addr);
    }
    | expression NE expression {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j<>", $1.addr, $3.addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        $$ = (void*)p;
        free($1.addr);
        free($3.addr);
    }
    | expression LT expression {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j<", $1.addr, $3.addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        $$ = (void*)p;
        free($1.addr);
        free($3.addr);
    }
    | expression LE expression {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j<=", $1.addr, $3.addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        $$ = (void*)p;
        free($1.addr);
        free($3.addr);
    }
    | expression GT expression {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j>", $1.addr, $3.addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        $$ = (void*)p;
        free($1.addr);
        free($3.addr);
    }
    | expression GE expression {
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        EState* lastT = new EState(_curr_index);
        e_Storage.push_back(lastT);
        addQuaternion("j>=", $1.addr, $3.addr, "-1");
        p->_trueList = lastT;
        
        EState* lastF = new EState(_curr_index);
        e_Storage.push_back(lastF);
        addQuaternion("j", "-", "-", "-1");
        p->_falseList = lastF;
        
        $$ = (void*)p;
        free($1.addr);
        free($3.addr);
    }
    | condition AND {
        // For AND: backpatch first condition's true to current position
        EState* left = (EState*)$1;
        if (left->_trueList) {
            left->_trueList->isCorrect = true;
            Quaternions[left->_trueList->selfpos].v4 = ToString(_curr_index);
        }
    } condition {
        EState* left = (EState*)$1;
        EState* right = (EState*)$4;
        
        // Create new combined E-state
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        // For AND: true when both are true (use right's true)
        p->_trueList = right->_trueList;
        p->_true = right->_true;
        
        // For AND: false when either is false (chain false lists properly)
        p->_falseList = left->_falseList;
        if (left->_falseList) {
            EState* current = left->_falseList;
            while (current->_falseList != NULL) {
                current = current->_falseList;
            }
            current->_falseList = right->_falseList;
        } else {
            p->_falseList = right->_falseList;
        }
        p->_false = left->_false;
        
        $$ = (void*)p;
    }
    | condition OR {
        // For OR: backpatch first condition's false to current position  
        EState* left = (EState*)$1;
        if (left->_falseList) {
            left->_falseList->isCorrect = true;
            Quaternions[left->_falseList->selfpos].v4 = ToString(_curr_index);
        }
    } condition {
        EState* left = (EState*)$1;
        EState* right = (EState*)$4;
        
        // Create new combined E-state
        EState* p = new EState(-1);
        e_Storage.push_back(p);
        
        // For OR: true when either is true (chain true lists)
        p->_trueList = left->_trueList;
        if (left->_trueList && right->_trueList) {
            left->_trueList->_trueList = right->_trueList;
        } else if (!left->_trueList) {
            p->_trueList = right->_trueList;
        }
        p->_true = left->_true;
        
        // For OR: false when both are false (use right's false)
        p->_falseList = right->_falseList;
        p->_false = right->_false;
        
        $$ = (void*)p;
    }
    | NOT condition {
        EState* orig = (EState*)$2;
        EState* new_state = new EState(-1);
        e_Storage.push_back(new_state);
        
        // Swap true and false
        new_state->_true = orig->_false;
        new_state->_false = orig->_true;
        new_state->_trueList = orig->_falseList;
        new_state->_falseList = orig->_trueList;
        
        $$ = (void*)new_state;
    }
    | LPAREN condition RPAREN {
        $$ = $2;
    }
    ;

expression:
    expression PLUS term {
        string temp = newTemp();
        addQuaternion("+", $1.addr, $3.addr, temp);
        $$.addr = strdup(temp.c_str());
        $$.estate = NULL;
        free($1.addr);
        free($3.addr);
    }
    | expression MINUS term {
        string temp = newTemp();
        addQuaternion("-", $1.addr, $3.addr, temp);
        $$.addr = strdup(temp.c_str());
        $$.estate = NULL;
        free($1.addr);
        free($3.addr);
    }
    | term {
        $$ = $1;
    }
    ;

term:
    term MULTIPLY factor {
        string temp = newTemp();
        addQuaternion("*", $1.addr, $3.addr, temp);
        $$.addr = strdup(temp.c_str());
        $$.estate = NULL;
        free($1.addr);
        free($3.addr);
    }
    | term DIVIDE factor {
        string temp = newTemp();
        addQuaternion("/", $1.addr, $3.addr, temp);
        $$.addr = strdup(temp.c_str());
        $$.estate = NULL;
        free($1.addr);
        free($3.addr);
    }
    | factor {
        $$ = $1;
    }
    ;

factor:
    IDENTIFIER {
        $$.addr = strdup($1);
        $$.estate = NULL;
        free($1);
    }
    | NUMBER {
        $$.addr = strdup($1);
        $$.estate = NULL;
        free($1);
    }
    | LPAREN expression RPAREN {
        $$ = $2;
    }
    ;

%%

int main(int argc, char** argv) {
    // a) Output author's information
    cout << "姓名: 郑炜诗" << endl;
    cout << "班级: 计科二班" << endl;
    cout << "学号: 202330452392" << endl;
    cout << endl; // Add a blank line for separation

    // b) Request input test program name
    char filename[256];
    if (argc > 1) { // If filename is provided as command line argument
        strncpy(filename, argv[1], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0'; // Ensure null termination
    } else { // Otherwise, prompt user for filename
        cout << "请输入测试程序名 (例如 TEST4): ";
        cin.getline(filename, sizeof(filename));
    }

    yyin = fopen(filename, "r");
    if (!yyin) {
        cerr << "错误: 无法打开文件 " << filename << endl;
        return 1;
    }
    
    cout << "开始编译程序: " << filename << endl << endl;

    int result = yyparse();
    
    // Clean up allocated EStates
    for (auto* state : e_Storage) {
        delete state;
    }
    
    return result;
} 