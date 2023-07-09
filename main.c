#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum{
    TK_IDENTIFIER,
    TK_INT,
    TK_FLOAT,
    TK_CHAR,
    TK_DOUBLE,
    TK_LONG,
    TK_UNSIGNED,
    TK_STRUCT,
    TK_PLUS,
    TK_MINUS,
    TK_MULTIPLY,
    TK_DIVIDE,
    TK_MODULO,
    TK_ASSIGN,
    TK_EQUAL,
    TK_NOT_EQUAL,
    TK_LESS,
    TK_LESS_EQUAL,
    TK_GREATER,
    TK_GREATER_EQUAL,
    TK_PLUS_PLUS,
    TK_PLUS_EQUAL,
    TK_MINUS_MINUS,
    TK_MINUS_EQUAL,
    TK_MULTIPLY_EQUAL,
    TK_BITWISE_LSHIFT_EQUAL,
    TK_BITWISE_RSHIFT_EQUAL,
    TK_DIVIDE_EQUAL,
    TK_MODULO_EQUAL,
    TK_STRUCT_ARROW,
    TK_LOGICAL_AND,
    TK_LOGICAL_OR,
    TK_LOGICAL_NOT,
    TK_BITWISE_AND,
    TK_BITWISE_OR,
    TK_BITWISE_XOR,
    TK_BITWISE_LSHIFT,
    TK_BITWISE_RSHIFT,
    TK_BITWISE_AND_EQUAL,
    TK_BITWISE_OR_EQUAL,
    TK_BITWISE_XOR_EQUAL,
    TK_TYPE_SPECIFIER,
    TK_UNARY_OPERATOR,
    TK_PRIMARY_EXPRESSION,
    TK_RETURN,
    TK_IF,
    TK_ELSE,
    TK_WHILE,
    TK_DO,
    TK_FOR,
    TK_TYPEDEF,
    TK_SWITCH,
    TK_CASE,
    TK_CONTINUE,
    TK_BREAK,
    TK_DEFAULT,
    TK_VOID,
    TK_LBRACKET,
    TK_RBRACKET,
    TK_LPAREN,
    TK_RPAREN,
    TK_LBRACE,
    TK_RBRACE,
    TK_DOT,
    TK_TWO_DOT,
    TK_SEMICOLON,
    TK_COMMA,
    TK_BITWISE_NOT,
    TK_TILDE,
    TK_EOF
} TokenN;

typedef struct
{
    TokenN current_token;
    char type[30];
    char lexeme[50];
    int line;
    int column;
} Token;

FILE *inputFile;
FILE *outputFile;
int tokenCount = 0;
TokenN tkWait, tkSave;
Token token;

// Funções Gramatica
int program();
int declarator();
int declaration_list();
int declaration_list_line();
int declaration();
int init_declarator_list();
int init_declarator_list_line();
int init_declarator();
int initializer();
int initializer_list();
int initializer_list_line();
int pointer();
int declaration_specifiers();
int unary_expression();
int unary_operator();
int type_specifier();
int translation_unit();
int translation_unit_line();
int external_declaration();
int function_definition();
int direct_declarator();
int direct_declarator_line();
int constant_expression();
int and_expression();
int and_expression_line();
int equality_expression();
int equality_expression_line();
int relational_expression();
int relational_expression_line();
int shift_expression();
int shift_expression_line();
int additive_expression();
int additive_expression_line();
int multiplicative_expression();
int multiplicative_expression_line();
int postfix_expression();
int postfix_expression_line();
int primary_expression();
int expression();
int expression_line();
int assignment_expression();
int assignment_operator();
int parameter_list();
int parameter_list_line();
int parameter_declaration();
int identifier_list();
int identifier_list_line();
int logical_or_expression();
int logical_or_expression_line();
int logical_and_expression();
int logical_and_expression_line();
int inclusive_or_expression();
int selection_statement();
int iteration_statement();
int jump_statement();
int inclusive_or_expression_line();
int exclusive_or_expression();
int exclusive_or_expression_line();
int compound_statement();
int argument_expression_list();
int argument_expression_list_line();
int declaration_or_statement_list();
int declaration_or_statement_list_line();
int statement_list();
int statement_list_line();
int statement();
int labeled_statement();
int expression_statement();

int getNextToken()
{
    memset(token.lexeme, 0, sizeof(token.lexeme));
    memset(token.type, 0, sizeof(token.type));
    char c = fgetc(inputFile);
    if (c == '\t')
    {
        token.column += 4;
    }
    else
    {
        token.column++;
    }
    while (isspace(c) || c == '\n')
    {
        if (c == '\n')
        {
            token.line = (token.line) + 1;
            token.column = 1;
            c = ' ';
        }
        else
        {
            c = getc(inputFile);
            if (c == '\t')
            {
                token.column += 4;
            }
            else
            {
                token.column++;
            }
        }
    }
    token.lexeme[0] = c;
    if (isalpha(c) || c == '_')
    {
        int i = 0;
        while (isalnum(c) || c == '_')
        {
            token.lexeme[i] = c;
            c = getc(inputFile);
            token.column++;
            if (c == '\n')
            {
                token.line = (token.line) + 1;
                token.column = 0;
            }
            i++;
        }
        token.lexeme[i] = '\0';
        if (c != '\n' && c != ' ')
        {
            ungetc(c, inputFile);
        }

        if (strncmp(token.lexeme, "int", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_INT\n");
            token.current_token = TK_INT;
        }
        else if (strncmp(token.lexeme, "float", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_FLOAT\n");
            token.current_token = TK_FLOAT;
        }
        else if (strncmp(token.lexeme, "char", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_CHAR\n");
            token.current_token = TK_CHAR;
        }
        else if (strncmp(token.lexeme, "double", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_DOUBLE\n");
            token.current_token = TK_DOUBLE;
        }
        else if (strncmp(token.lexeme, "long", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_LONG\n");
            token.current_token = TK_LONG;
        }
        else if (strncmp(token.lexeme, "unsigned", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_UNSIGNED\n");
            token.current_token = TK_UNSIGNED;
        }
        else if (strncmp(token.lexeme, "struct", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_STRUCT\n");
            token.current_token = TK_STRUCT;
        }
        else if (strncmp(token.lexeme, "typedef", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_TYPEDEF\n");
            token.current_token = TK_TYPEDEF;
        }
        else if (strncmp(token.lexeme, "while", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_WHILE\n");
            token.current_token = TK_WHILE;
        }
        else if (strncmp(token.lexeme, "do", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_DO\n");
            token.current_token = TK_DO;
        }
        else if (strncmp(token.lexeme, "for", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_FOR\n");
            token.current_token = TK_FOR;
        }
        else if (strncmp(token.lexeme, "if", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_IF\n");
            token.current_token = TK_IF;
        }
        else if (strncmp(token.lexeme, "else", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_ELSE\n");
            token.current_token = TK_ELSE;
        }
        else if (strncmp(token.lexeme, "switch", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_SWITCH\n");
            token.current_token = TK_SWITCH;
        }
        else if (strncmp(token.lexeme, "case", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_CASE\n");
            token.current_token = TK_CASE;
        }
        else if (strncmp(token.lexeme, "continue", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_CONTINUE\n");
            token.current_token = TK_CONTINUE;
        }
        else if (strncmp(token.lexeme, "break", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BREAK\n");
            token.current_token = TK_BREAK;
        }
        else if (strncmp(token.lexeme, "default", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_DEFAULT\n");
            token.current_token = TK_DEFAULT;
        }
        else if (strncmp(token.lexeme, "void", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_VOID\n");
            token.current_token = TK_VOID;
        }
        else if (strncmp(token.lexeme, "return", strlen(token.lexeme)) == 0)
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_RETURN\n");
            token.current_token = TK_RETURN;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_IDENTIFIER\n");
            token.current_token = TK_IDENTIFIER;
        }
    }
    else if (isdigit(c))
    {
        int i = 0;
        while (isdigit(c))
        {
            token.lexeme[i] = c;
            c = getc(inputFile);
            token.column++;
            if (c == '\n')
            {
                token.line = (token.line) + 1;
                token.column = 0;
            }
            i++;
        }
        token.lexeme[i] = '\0';
        if (c != '\n' && c != ' ')
        {
            ungetc(c, inputFile);
        }
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_INT\n");
        token.current_token = TK_INT;
    }
    else if (c == '+')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '+')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_PLUS_PLUS\n");
            token.current_token = TK_PLUS;
            token.lexeme[1] = c;
        }
        else if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_PLUS_EQUAL\n");
            token.current_token = TK_PLUS_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_PLUS\n");
            token.current_token = TK_PLUS_PLUS;
            ungetc(c, inputFile);
        }
    }
    else if (c == '-')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '-')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_MINUS_MINUS\n");
            token.current_token = TK_MINUS_MINUS;
            token.lexeme[1] = c;
        }
        else if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_MINUS_EQUAL\n");
            token.current_token = TK_MINUS_EQUAL;
            token.lexeme[1] = c;
        }
        else if (c == '>')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_STRUCT_ARROW\n");
            token.current_token = TK_STRUCT_ARROW;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_MINUS\n");
            token.current_token = TK_MINUS;
            ungetc(c, inputFile);
        }
    }
    else if (c == '*')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_MULTIPLY_EQUAL\n");
            token.current_token = TK_MULTIPLY_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_MULTIPLY\n");
            token.current_token = TK_MULTIPLY;
            ungetc(c, inputFile);
        }
    }
    else if (c == '/')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_DIVIDE_EQUAL\n");
            token.current_token = TK_DIVIDE_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_DIVIDE\n");
            token.current_token = TK_DIVIDE;
            ungetc(c, inputFile);
        }
    }
    else if (c == '%')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_MODULO_EQUAL\n");
            token.current_token = TK_MODULO_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_MODULO\n");
            token.current_token = TK_MODULO;
            ungetc(c, inputFile);
        }
    }
    else if (c == '=')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_EQUAL\n");
            token.current_token = TK_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_ASSIGN\n");
            token.current_token = TK_ASSIGN;
            ungetc(c, inputFile);
        }
    }
    else if (c == '<')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_LESS_EQUAL\n");
            token.current_token = TK_LESS_EQUAL;
            token.lexeme[1] = c;
        }
        else if (c == '<')
        {

            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_LSHIFT\n");
            token.current_token = TK_BITWISE_LSHIFT;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_LESS\n");
            token.current_token = TK_LESS;
            ungetc(c, inputFile);
        }
    }
    else if (c == '>')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_GREATER_EQUAL\n");
            token.current_token = TK_GREATER_EQUAL;
            token.lexeme[1] = c;
        }
        else if (c == '>')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_RSHIFT\n");
            token.current_token = TK_BITWISE_RSHIFT;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_GREATER\n");
            token.current_token = TK_GREATER;
            ungetc(c, inputFile);
        }
    }
    else if (c == '!')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_NOT_EQUAL\n");
            token.current_token = TK_NOT_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_LOGICAL_NOT\n");
            token.current_token = TK_LOGICAL_NOT;
            ungetc(c, inputFile);
        }
    }
    else if (c == '&')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '&')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_LOGICAL_AND\n");
            token.current_token = TK_LOGICAL_AND;
            token.lexeme[1] = c;
        }
        else if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_AND_EQUAL\n");
            token.current_token = TK_BITWISE_AND_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_AND\n");
            token.current_token = TK_BITWISE_AND;
            ungetc(c, inputFile);
        }
    }
    else if (c == '|')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '|')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_LOGICAL_OR\n");
            token.current_token = TK_LOGICAL_OR;
            token.lexeme[1] = c;
        }
        else if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_OR_EQUAL\n");
            token.current_token = TK_BITWISE_OR_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_OR\n");
            token.current_token = TK_BITWISE_OR;
            ungetc(c, inputFile);
        }
    }
    else if (c == '^')
    {
        c = getc(inputFile);
        token.column++;
        if (c == '=')
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_XOR_EQUAL\n");
            token.current_token = TK_BITWISE_XOR_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            token.column = (token.column) + 1;
            strcpy(token.type, "TK_BITWISE_XOR\n");
            token.current_token = TK_BITWISE_XOR;
            ungetc(c, inputFile);
        }
    }
    else if (c == '(')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_LPAREN\n");
        token.current_token = TK_LPAREN;
    }
    else if (c == ')')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_RPAREN\n");
        token.current_token = TK_RPAREN;
    }
    else if (c == '{')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_LBRACE\n");
        token.current_token = TK_LBRACE;
    }
    else if (c == '}')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_RBRACE\n");
        token.current_token = TK_RBRACE;
    }
    else if (c == '[')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_LBRACKET\n");
        token.current_token = TK_LBRACKET;
    }
    else if (c == ']')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_RBRACKET\n");
        token.current_token = TK_RBRACKET;
    }
    else if (c == ';')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_SEMICOLON\n");
        token.current_token = TK_SEMICOLON;
    }
    else if (c == '~')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_BITWISE_NOT\n");
        token.current_token = TK_BITWISE_NOT;
    }
    else if (c == '~')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_TILDE\n");
        token.current_token = TK_TILDE;
    }
    else if (c == '.')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_DOT\n");
        token.current_token = TK_DOT;
    }
    else if (c == ':')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_TWO_DOT\n");
        token.current_token = TK_TWO_DOT;
    }
    else if (c == ',')
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_COMMA\n");
        token.current_token = TK_COMMA;
    }
    else if (c == EOF)
    {
        token.column = (token.column) + 1;
        strcpy(token.type, "TK_EOF\n");
        token.current_token = TK_EOF;
        token.lexeme[0] = '|';
        token.lexeme[1] = 'n';
    }
    else
    {
        // Error handling for unrecognized characters
        printf("Error: Unrecognized character '%c' at line %d, column %d\n", c, token.line, token.column);
        token.column = (token.column) + 1;
        strcpy(token.type, "expectedToken\n");
        token.current_token = TK_EOF;
    }
    
    tokenCount++;
    return token.current_token;
}

long getPosi()
{
    return ftell(inputFile);
}

void restartPosi(long posiSave, int TK_SAVE)
{
    fseek(inputFile, posiSave, SEEK_SET);
    token.current_token = TK_SAVE;
}

// Função principal para iniciar o analisador sintático
int program(){
    getNextToken();
	if (translation_unit()) return 1;
	return 0;
}

int translation_unit() {
	if (external_declaration()) {
		if (translation_unit_line()) return 1;
		return 0;
	}
	return 0;
}

int translation_unit_line() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (external_declaration()) {
		if (translation_unit_line()) return 1;
		return 0;
	}
	restartPosi(posiFile, tkSave);
	return 1;
}

int external_declaration() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (function_definition()) return 1;
	restartPosi(posiFile, tkSave);
	if (declaration()) return 1;
	return 0;
}

int function_definition() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (declaration_specifiers()) {
		if (declarator()) {
			long posiFile2 = getPosi();
			int tkSave2 = token.current_token;
			if (declaration_list()) {
				if (compound_statement()) return 1;
				return 0;
			}
			restartPosi(posiFile2, tkSave2);
			if (compound_statement()) return 1;
			return 0;
		}
		return 0;
	}
	restartPosi(posiFile, tkSave);
	if (declarator()) {
		long posiFile2 = getPosi();
		int tkSave2 = token.current_token;
		if (declaration_list()) {
			if (compound_statement()) return 1;
			return 0;
		}
		restartPosi(posiFile2, tkSave2);
		if (compound_statement()) return 1;
		return 0;
	}
	return 0;
}

int declaration_specifiers() {
	if (type_specifier()) {
		if (declaration_specifiers()) return 1;
		return 1;
	}
	return 0;
}

int type_specifier() {
	if (token.current_token == TK_INT) { getNextToken(); return 1; }
	if (token.current_token == TK_LONG) { getNextToken(); return 1; }
	if (token.current_token == TK_FLOAT) { getNextToken(); return 1; }
	if (token.current_token == TK_CHAR) { getNextToken(); return 1; }
	if (token.current_token == TK_DOUBLE) { getNextToken(); return 1; }
	if (token.current_token == TK_UNSIGNED) { getNextToken(); return 1; }
	tkWait = TK_TYPE_SPECIFIER;
	return 0;
}

int declarator() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (pointer()) {
		if (direct_declarator()) return 1;
		return 0;
	}
	restartPosi(posiFile, tkSave);
	if (direct_declarator()) return 1;
	return 0;
}

int pointer() {
	if (token.current_token == TK_MULTIPLY) {
		getNextToken();
		if (pointer()) return 1;
		return 1;
	}
	return 0;
}

int direct_declarator() {
	if (token.current_token == TK_IDENTIFIER) {
		getNextToken();
		if (direct_declarator_line()) return 1;
		return 0;
	}
	if (token.current_token == TK_LPAREN) {
		getNextToken();
		if (declarator()) {
			if (token.current_token == TK_RPAREN) {
				getNextToken();
				if (direct_declarator_line()) return  1;
				return 0;
			}
			return 0;
		}
		return 0;
	}
	tkWait = TK_IDENTIFIER;
	return 0;
}

int direct_declarator_line() {
	if (token.current_token == TK_LBRACKET) {
		getNextToken();
		long posiFile = getPosi();
		int tkSave = token.current_token;
		if (constant_expression()) {
			if (token.current_token == TK_RBRACKET) {
				getNextToken();
				if (direct_declarator_line()) return 1;
				return 0;
			}
			return 0;
		}
		restartPosi(posiFile, tkSave);
		if (token.current_token == TK_RBRACKET) {
			getNextToken();
			if (direct_declarator_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_LPAREN) {
		getNextToken();
		long posiFile = getPosi();
		int tkSave = token.current_token;
		if (parameter_list()) {
			if (token.current_token == TK_RPAREN) {
				getNextToken();
				if (direct_declarator_line()) return 1;
				return 0;
			}
			return 0;
		}
		restartPosi(posiFile, tkSave);
		if (identifier_list()) {
			if (token.current_token == TK_RPAREN) {
				getNextToken();
				if (direct_declarator_line()) return 1;
				return 0;
			}
			return 0;
		}
		restartPosi(posiFile, tkSave);
		if (token.current_token == TK_RPAREN) {
			getNextToken();
			if (direct_declarator_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int constant_expression() {
	if (logical_or_expression()) return 1;
	return 0;
}

int logical_or_expression() {
	if (logical_and_expression()) {
		if (logical_or_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int logical_or_expression_line() {
	if (token.current_token == TK_LOGICAL_OR) {
		getNextToken();
		if (logical_and_expression()) {
			if (logical_or_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int logical_and_expression() {
	if (inclusive_or_expression()) {
		if (logical_and_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int logical_and_expression_line() {
	if (token.current_token == TK_LOGICAL_AND) {
		getNextToken();
		if (inclusive_or_expression()) {
			if (logical_and_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int inclusive_or_expression() {
	if (exclusive_or_expression()) {
		if (inclusive_or_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int inclusive_or_expression_line() {
	if (token.current_token == TK_BITWISE_OR) {
		getNextToken();
		if (exclusive_or_expression()) {
			if (inclusive_or_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int exclusive_or_expression() {
	if (and_expression()) {
		if (exclusive_or_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int exclusive_or_expression_line() {
	if (token.current_token == TK_BITWISE_XOR) {
		getNextToken();
		if (and_expression()) {
			if (exclusive_or_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int and_expression() {
	if (equality_expression()) {
		if (and_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int and_expression_line() {
	if (token.current_token == TK_BITWISE_AND) {
		getNextToken();
		if (equality_expression()) {
			if (and_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int equality_expression() {
	if (relational_expression()) {
		if (equality_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int equality_expression_line() {
	if (token.current_token == TK_EQUAL) {
		getNextToken();
		if (relational_expression()) {
			if (equality_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_NOT_EQUAL) {
		getNextToken();
		if (relational_expression()) {
			if (equality_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int relational_expression() {
	if (shift_expression()) {
		if (relational_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int relational_expression_line() {
	if (token.current_token == TK_LESS) {
		getNextToken();
		if (shift_expression()) {
			if (relational_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_GREATER) {
		getNextToken();
		if (shift_expression()) {
			if (relational_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_LESS_EQUAL) {
		getNextToken();
		if (shift_expression()) {
			if (relational_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_GREATER_EQUAL) {
		getNextToken();
		if (shift_expression()) {
			if (relational_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int shift_expression() {
	if (additive_expression()) {
		if (shift_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int shift_expression_line() {
	if (token.current_token == TK_BITWISE_RSHIFT) {
		getNextToken();
		if (additive_expression()) {
			if (shift_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_BITWISE_LSHIFT) {
		getNextToken();
		if (additive_expression()) {
			if (shift_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int additive_expression() {
	if (multiplicative_expression()) {
		if (additive_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int additive_expression_line() {
	if (token.current_token == TK_PLUS) {
		getNextToken();
		if (multiplicative_expression()) {
			if (additive_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_MINUS) {
		getNextToken();
		if (multiplicative_expression()) {
			if (additive_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int multiplicative_expression() {
	if (unary_expression()) {
		if (multiplicative_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int multiplicative_expression_line() {
	if (token.current_token == TK_MULTIPLY) {
		getNextToken();
		if (unary_expression()) {
			if (multiplicative_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_DIVIDE) {
		getNextToken();
		if (unary_expression()) {
			if (multiplicative_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_MODULO) {
		getNextToken();
		if (unary_expression()) {
			if (multiplicative_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int unary_expression() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (postfix_expression()) return 1;
	restartPosi(posiFile, tkSave);
	if (token.current_token == TK_PLUS_PLUS) {
		getNextToken();
		if (unary_expression()) return 1;
		return 0;
	}
	if (token.current_token == TK_MINUS_MINUS) {
		getNextToken();
		if (unary_expression()) return 1;
		return 0;
	}
	if (unary_operator()) {
		if (unary_expression()) return 1;
		return 0;
	}
	return 0;
}

int unary_operator() {
	if (token.current_token == TK_BITWISE_AND) { getNextToken(); return 1; }
	if (token.current_token == TK_MULTIPLY) { getNextToken(); return 1; }
	if (token.current_token == TK_PLUS) { getNextToken(); return 1; }
	if (token.current_token == TK_MINUS) { getNextToken(); return 1; }
	if (token.current_token == TK_TILDE) { getNextToken(); return 1; }
	if (token.current_token == TK_BITWISE_NOT) { getNextToken(); return 1; }
	tkWait = TK_UNARY_OPERATOR;
	return 0;
}

int postfix_expression() {
	if (primary_expression()) {
		if (postfix_expression_line()) return 1;
		return 0;
	}
	return 0;
}

int postfix_expression_line() {
	if (token.current_token == TK_LBRACKET) {
		getNextToken();
		if (expression()) {
			if (token.current_token == TK_RBRACKET) {
				getNextToken();
				if (postfix_expression_line()) return 1;
				return 0;
			}
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_LPAREN) {
		getNextToken();
		if (token.current_token == TK_RPAREN) {
			getNextToken();
			if (postfix_expression_line()) return 1;
			return 0;
		}
		if (argument_expression_list()) {
			if (token.current_token == TK_RPAREN) {
				getNextToken();
				if (postfix_expression_line()) return 1;
				return 0;
			}
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_DOT) {
		getNextToken();
		if (token.current_token == TK_IDENTIFIER) {
			getNextToken();
			if (postfix_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_STRUCT_ARROW) {
		getNextToken();
		if (token.current_token == TK_IDENTIFIER) {
			getNextToken();
			if (postfix_expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_PLUS_PLUS) {
		getNextToken();
		if (postfix_expression_line()) return 1;
		return 0;
	}
	if (token.current_token == TK_MINUS_MINUS) {
		getNextToken();
		if (postfix_expression_line()) return 1;
		return 0;
	}
	return 1;
}

int primary_expression() {
	if (token.current_token == TK_IDENTIFIER) { getNextToken(); return 1; }
	if (token.current_token == TK_INT) { getNextToken(); return 1; }
	if (token.current_token == TK_LPAREN) {
		getNextToken();
		if (expression()) {
			if (token.current_token == TK_RPAREN) {
				getNextToken();
				return 1;
			}
			return 0;
		}
		return 0;
	}
	tkWait = TK_PRIMARY_EXPRESSION;
	return 0;
}

int expression() {
	if (assignment_expression()) {
		if (expression_line()) return 1;
		return 0;
	}
	return 0;
}

int expression_line() {
	if (token.current_token == TK_COMMA) {
		getNextToken();
		if (assignment_expression()) {
			if (expression_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int assignment_expression() {
	if (logical_or_expression()) {
		long posiFile = getPosi();
		int tkSave = token.current_token;
		if (assignment_operator()) {
			if (assignment_expression()) return 1;
			return 0;
		}
		restartPosi(posiFile, tkSave);
		return 1;
	}
	return 0;
}

int assignment_operator() {
	if (token.current_token == TK_ASSIGN) { getNextToken(); return 1; }
	if (token.current_token == TK_MULTIPLY_EQUAL) { getNextToken(); return 1; }
	if (token.current_token == TK_DIVIDE_EQUAL) { getNextToken(); return 1; }
	if (token.current_token == TK_MODULO_EQUAL) { getNextToken(); return 1; }
	if (token.current_token == TK_PLUS_EQUAL) { getNextToken(); return 1; }
	if (token.current_token == TK_MINUS_EQUAL) { getNextToken(); return 1; }
	if (token.current_token == TK_BITWISE_LSHIFT_EQUAL) { getNextToken(); return 1; }
	if (token.current_token == TK_BITWISE_RSHIFT_EQUAL) { getNextToken(); return 1; }
	tkWait = TK_ASSIGN;
	return 0;
}

int parameter_list() {
	if (parameter_declaration()) {
		if (parameter_list_line()) return 1;
		return 0;
	}
	return 0;
}

int parameter_list_line() {
	if (token.current_token == TK_COMMA) {
		getNextToken();
		if (parameter_declaration()) {
			if (parameter_list_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int parameter_declaration() {
	if (declaration_specifiers()) {
		if (declarator()) return 1;
		return 1;
	}
	return 0;
}

int identifier_list() {
	if (token.current_token == TK_IDENTIFIER) {
		getNextToken();
		if (identifier_list_line()) return 1;
		return 0;
	}
	tkWait = TK_IDENTIFIER;
	return 0;
}

int identifier_list_line() {
	if (token.current_token == TK_COMMA) {
		getNextToken();
		if (token.current_token == TK_IDENTIFIER) {
			getNextToken();
			if (identifier_list_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int declaration_list() {
	if (declaration()) {
		if (declaration_list_line()) return 1;
		return 0;
	}
	return 0;
}

int declaration_list_line() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (declaration()) {
		if (declaration_list_line()) return 1;
		return 0;
	}
	restartPosi(posiFile, tkSave);
	return 1;
}

int declaration() {
	if (declaration_specifiers()) {
		if (token.current_token == TK_SEMICOLON) {
			getNextToken();
			return 1;
		}
		if (init_declarator_list()) {
			if (token.current_token == TK_SEMICOLON) {
				getNextToken();
				return 1;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}

int init_declarator_list() {
	if (init_declarator()) {
		if (init_declarator_list_line()) return 1;
		return 0;
	}
	return 0;
}

int init_declarator_list_line() {
	if (token.current_token == TK_COMMA) {
		getNextToken();
		if (init_declarator()) {
			if (init_declarator_list_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int init_declarator() {
	if (declarator()) {
		if (token.current_token == TK_ASSIGN) {
			getNextToken();
			if (initializer()) return 1;
			return 0;
		}
		return 1;
	}
	return 0;
}

int initializer() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (assignment_expression()) return 1;
	restartPosi(posiFile, tkSave);
	if (token.current_token == TK_LBRACE) {
		getNextToken();
		if (initializer_list()) {
			if (token.current_token == TK_RBRACE) {
				getNextToken();
				return 1;
			}
			if (token.current_token == TK_COMMA) {
				getNextToken();
				if (token.current_token == TK_RBRACE) {
					getNextToken();
					return 1;
				}
				return 0;
			}
			return 0;
		}
		return 0;
	}
	tkWait = TK_LBRACE;
	return 0;
}

int initializer_list() {
	if (initializer()) {
		if (initializer_list_line()) return 1;
		return 0;
	}
	return 0;
}

int initializer_list_line() {
	if (token.current_token == TK_COMMA) {
		getNextToken();
		if (initializer()) {
			if (initializer_list_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

int compound_statement() {
	if (token.current_token == TK_LBRACE) {
		getNextToken();
		long posiFile = getPosi();
		int tkSave = token.current_token;
		if (token.current_token == TK_RBRACE) { getNextToken(); return 1; }
		if (declaration_or_statement_list()) {
			if (token.current_token == TK_RBRACE)	{ getNextToken(); return 1; }
			return 0;
		}
		return 0;
	}
	tkWait = TK_LBRACE;
	return 0;
}

int declaration_or_statement_list() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (declaration_list()) {
		if (declaration_or_statement_list_line()) return 1;
		return 0;
	}
	restartPosi(posiFile, tkSave);
	if (statement_list()) {
		if (declaration_or_statement_list_line()) return 1;
		return 0;
	}
	return 0;
}

int declaration_or_statement_list_line() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (declaration_list()) {
		if (declaration_or_statement_list_line()) return 1;
		return 0;
	}
	restartPosi(posiFile, tkSave);
	if (statement_list()) {
		if (declaration_or_statement_list_line()) return 1;
		return 0;
	}
	restartPosi(posiFile, tkSave);
	return 1;
}

int statement_list() {
	if (statement()) {
		if (statement_list_line()) return 1;
		return 0;
	}
	return 0;
}

int statement_list_line() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (statement()) {
		if (statement_list_line()) return 1;
		return 0;
	}
	restartPosi(posiFile, tkSave);
	return 1;
}

int statement() {
	long posiFile = getPosi();
	int tkSave = token.current_token;
	if (labeled_statement()) return 1;
	restartPosi(posiFile, tkSave);
	if (compound_statement()) return 1;
	restartPosi(posiFile, tkSave);
	if (expression_statement()) return 1;
	restartPosi(posiFile, tkSave);
	if (selection_statement()) return 1;
	restartPosi(posiFile, tkSave);
	if (iteration_statement()) return 1;
	restartPosi(posiFile, tkSave);
	if (jump_statement()) return 1;
	return 0;
}

int labeled_statement() {
	if (token.current_token == TK_IDENTIFIER) {
		getNextToken();
		if (token.current_token == TK_TWO_DOT) {
			getNextToken();
			if (statement()) return 1;
			return 0;
		}
		tkWait = TK_TWO_DOT;
		return 0;
	}
	if (token.current_token == TK_CASE) {
		getNextToken();
		if (constant_expression()) {
			if (token.current_token == TK_TWO_DOT) {
				getNextToken();
				if (statement()) return 1;
				return 0;
			}
			tkWait = TK_TWO_DOT;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_DEFAULT) {
		getNextToken();
		if (token.current_token == TK_TWO_DOT) {
			getNextToken();
			if (statement()) return 1;
			return 0;
		}
		tkWait = TK_TWO_DOT;
		return 0;
	}
	return 0;
}

int expression_statement() {
	if (token.current_token == TK_SEMICOLON) { getNextToken(); return 1; }
	if (expression()) {
		if (token.current_token == TK_SEMICOLON) { getNextToken(); return 1; }
		tkWait = TK_SEMICOLON;
		return 0;
	}
	tkWait = TK_SEMICOLON;
	return 0;
}

int selection_statement() {
	if (token.current_token == TK_IF) {
		getNextToken();
		if (token.current_token == TK_LPAREN) {
			getNextToken();
			if (expression()) {
				if (token.current_token == TK_RPAREN) {
					getNextToken();
					long posiFile = getPosi();
					int tkSave = token.current_token;
					if (statement()) return 1;
					restartPosi(posiFile, tkSave);
					if (token.current_token == TK_ELSE) {
						getNextToken();
						if (statement()) return 1;
						return 0;
					}
					tkWait = TK_ELSE;
					return 0;
				}
				tkWait = TK_RPAREN;
				return 0;
			}
			return 0;
		}
		tkWait = TK_LPAREN;
		return 0;
	}
	if (token.current_token == TK_SWITCH) {
		getNextToken();
		if (token.current_token == TK_LPAREN) {
			getNextToken();
			if (expression()) {
				if (token.current_token == TK_RPAREN) {
					getNextToken();
					if (statement()) return 1;
					return 0;
				}
				tkWait = TK_RPAREN;
				return 0;
			}
			return 0;
		}
		tkWait = TK_LPAREN;
		return 0;
	}
	return 0;
}

int iteration_statement() {
	if (token.current_token == TK_WHILE) {
		getNextToken();
		if (token.current_token == TK_LPAREN) {
			getNextToken();
			if (expression()) {
				if (token.current_token == TK_RPAREN) {
					getNextToken();
					if (statement()) return 1;
					return 0;
				}
				tkWait = TK_RPAREN;
				return 0;
			}
			return 0;
		}
		tkWait = TK_LPAREN;
		return 0;
	}
	if (token.current_token == TK_DO) {
		getNextToken();
		if (statement()) {
			if (token.current_token == TK_WHILE) {
				getNextToken();
				if (token.current_token == TK_LPAREN) {
					getNextToken();
					if (expression()) {
						if (token.current_token == TK_RPAREN) {
							getNextToken();
							if (token.current_token == TK_SEMICOLON) {
								getNextToken();
								return 1;
							}
							tkWait = TK_SEMICOLON;
							return 0;
						}
						tkWait = TK_RPAREN;
						return 0;
					}
					return 0;
				}
				tkWait = TK_LPAREN;
				return 0;
			}
			tkWait = TK_WHILE;
			return 0;
		}
		return 0;
	}
	if (token.current_token == TK_FOR) {
		getNextToken();
		if (token.current_token == TK_LPAREN) {
			getNextToken();
			if (expression_statement()) {
				if (expression_statement()) {
					if (token.current_token == TK_RPAREN) {
						getNextToken();
						if (statement()) return 1;
						return 0;
					}
					if (expression()) {
						if (token.current_token == TK_RPAREN) {
							getNextToken();
							if (statement()) return 1;
							return 0;
						}
						tkWait = TK_RPAREN;
						return 0;
					}
					tkWait = TK_RPAREN;
					return 0;
				}
				return 0;
			}
			return 0;
		}
		tkWait = TK_LPAREN;
		return 0;
	}
	return 0;
}

int jump_statement() {
	if (token.current_token == TK_BREAK) {
		getNextToken();
		if (token.current_token == TK_SEMICOLON) {
			getNextToken();
			return 1;
		}
		tkWait = TK_SEMICOLON;
		return 0;
	}
	if (token.current_token == TK_RETURN) {
		getNextToken();
		if (token.current_token == TK_SEMICOLON) {
			getNextToken();
			return 1;
		}
		if (expression()) {
			if (token.current_token == TK_SEMICOLON) {
				getNextToken();
				return 1;
			}
			tkWait = TK_SEMICOLON;
			return 0;
		}
		tkWait = TK_SEMICOLON;
		return 0;
	}
	return 0;
}

int argument_expression_list() {
	if (assignment_expression()) {
		if (argument_expression_list_line()) return 1;
		return 0;
	}
	return 0;
}

int argument_expression_list_line() {
	if (token.current_token == TK_COMMA) {
		getNextToken();
		if (assignment_expression()) {
			if (argument_expression_list_line()) return 1;
			return 0;
		}
		return 0;
	}
	return 1;
}

const char *getTokenName(TokenN Token)
{
    switch (Token)
    {
    case TK_IDENTIFIER:
        return "Identifier";
    case TK_INT:
        return "Int";
    case TK_FLOAT:
        return "Float";
    case TK_CHAR:
        return "Char";
    case TK_DOUBLE:
        return "Double";
    case TK_STRUCT:
        return "Struct";
    case TK_TYPEDEF:
        return "Typedef";
    case TK_LBRACKET:
        return "Left Bracket";
    case TK_RBRACKET:
        return "Right Bracket";
    case TK_PLUS:
        return "Plus";
    case TK_MINUS:
        return "Minus";
    case TK_MULTIPLY:
        return "Multiply";
    case TK_DIVIDE:
        return "Divide";
    case TK_MODULO:
        return "Modulo";
    case TK_BITWISE_AND:
        return "Bitwise AND";
    case TK_BITWISE_LSHIFT:
        return "Bitwise Left Shift";
    case TK_BITWISE_RSHIFT:
        return "Bitwise Right Shift";
    case TK_LOGICAL_NOT:
        return "LOGICAL NOT";
    case TK_BITWISE_AND_EQUAL:
        return "Bitwise AND Equal";
    case TK_BITWISE_OR:
        return "Bitwise OR";
    case TK_BITWISE_OR_EQUAL:
        return "Bitwise OR Equal";
    case TK_BITWISE_XOR:
        return "Bitwise XOR";
    case TK_BITWISE_XOR_EQUAL:
        return "Bitwise XOR Equal";
    case TK_LESS:
        return "Less Than";
    case TK_LESS_EQUAL:
        return "Less Than or Equal";
    case TK_GREATER:
        return "Greater Than";
    case TK_GREATER_EQUAL:
        return "Greater Than or Equal";
    case TK_EQUAL:
        return "Equal";
    case TK_NOT_EQUAL:
        return "Not Equal";
    case TK_ASSIGN:
        return "ASSIGN";
    case TK_LOGICAL_AND:
        return "Logical AND";
    case TK_LOGICAL_OR:
        return "Logical OR";
    case TK_WHILE:
        return "While";
    case TK_DO:
        return "Do";
    case TK_FOR:
        return "For";
    case TK_IF:
        return "If";
    case TK_ELSE:
        return "Else";
    case TK_SWITCH:
        return "Switch";
    case TK_CASE:
        return "Case";
    case TK_BREAK:
        return "Break";
    case TK_CONTINUE:
        return "Continue";
    case TK_DEFAULT:
        return "Default";
    case TK_VOID:
        return "Void";
    case TK_RETURN:
        return "Return";
    case TK_EOF:
        return "End of File";
    case TK_PLUS_PLUS:
        return "Plus Plus";
    case TK_PLUS_EQUAL:
        return "Plus Equal";
    case TK_MINUS_MINUS:
        return "Minus Minus";
    case TK_MINUS_EQUAL:
        return "Minus Equal";
    case TK_STRUCT_ARROW:
        return "Struct Arrow";
    case TK_MULTIPLY_EQUAL:
        return "Multiply Equal";
    case TK_DIVIDE_EQUAL:
        return "Divide Equal";
    case TK_MODULO_EQUAL:
        return "Modulo Equal";
    case TK_LPAREN:
        return "Left Parenthesis";
    case TK_RPAREN:
        return "Right Parenthesis";
    case TK_LBRACE:
        return "Left Brace";
    case TK_RBRACE:
        return "Right Brace";
    case TK_COMMA:
        return "Comma";
    case TK_SEMICOLON:
        return "Semicolon";
    case TK_DOT:
        return "Dot";
    case TK_TWO_DOT:
        return "Two Dots";
    case TK_BITWISE_NOT:
        return "BITWISE NOT";
    case TK_TILDE:
        return "Tilde";
    }
    return "Unknown";
}

int main(){
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL){
        printf("Error opening input or output file.\n\n");
        return 1;
    }
    token.column = 0;
    tokenCount = 0;

    program() ? printf("|Reconhecido.    |\n") : printf("|Nao Reconhecido.|\n");
    printf("|----------------|---------------\n\n");
    printf("|Total tokens:   | %-13d \n", tokenCount);
    printf("|----------------|---------------\n\n");
    fclose(inputFile);
    return 0;
}
