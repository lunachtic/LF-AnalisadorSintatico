#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TK_IDENTIFIER,
    TK_INT,
    TK_FLOAT,
    TK_CHAR,
    TK_DOUBLE,
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
    TK_DIVIDE_EQUAL,
    TK_MODULO_EQUAL,
    TK_STRUCT_ARROW,
    TK_LOGICAL_AND,
    TK_LOGICAL_OR,
    TK_BITWISE_AND,
    TK_BITWISE_OR,
    TK_BITWISE_XOR,
    TK_BITWISE_NOT,
    TK_BITWISE_LSHIFT,
    TK_BITWISE_RSHIFT,
    TK_BITWISE_AND_EQUAL,
    TK_BITWISE_OR_EQUAL,
    TK_BITWISE_XOR_EQUAL,
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
    TK_TILDE,
    TK_EOF
} TokenN;

typedef struct
{
    TokenN Token;
    char type[30];
    char lexeme[50];
    int line;
    int column;
} Token;

Token getNextToken(FILE *inputFile, int *line, int *column)
{
    Token token;
    memset(token.lexeme, 0, sizeof(token.lexeme));
    memset(token.type, 0, sizeof(token.type));
    char c = fgetc(inputFile);
    while (isspace(c) || c == '\n')
    {
        if (c == '\n')
        {
            *line = (*line) + 1;
            *column = 1;
            c = ' ';
        }
        else
        {
            c = getc(inputFile);
        }
    }
    token.line = *line;
    token.column = *column;
    token.lexeme[0] = c;
    if (isalpha(c) || c == '_')
    {
        int i = 0;
        while (isalnum(c) || c == '_')
        {
            token.lexeme[i] = c;
            c = getc(inputFile);
            if (c == '\n')
            {
                *line = (*line) + 1;
                *column = 0;
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
            *column = (*column) + 1;
            strcpy(token.type, "TK_INT");
            token.Token=TK_INT;
        }
        else if (strncmp(token.lexeme, "float", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_FLOAT");
            token.Token=TK_FLOAT;
        }
        else if (strncmp(token.lexeme, "char", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_CHAR");
            token.Token=TK_CHAR;
        }
        else if (strncmp(token.lexeme, "double", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DOUBLE");
            token.Token=TK_DOUBLE;
        }
        else if (strncmp(token.lexeme, "struct", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_STRUCT");
            token.Token=TK_STRUCT;
        }
        else if (strncmp(token.lexeme, "typedef", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_TYPEDEF");
            token.Token=TK_TYPEDEF;
        }
        else if (strncmp(token.lexeme, "while", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_WHILE");
            token.Token=TK_WHILE;
        }
        else if (strncmp(token.lexeme, "do", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DO");
            token.Token=TK_DO;
        }
        else if (strncmp(token.lexeme, "for", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_FOR");
            token.Token=TK_FOR;
        }
        else if (strncmp(token.lexeme, "if", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_IF");
            token.Token=TK_IF;
        }
        else if (strncmp(token.lexeme, "else", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_ELSE");
            token.Token=TK_ELSE;
        }
        else if (strncmp(token.lexeme, "switch", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_SWITCH");
            token.Token=TK_SWITCH;
        }
        else if (strncmp(token.lexeme, "case", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_CASE");
            token.Token=TK_CASE;
        }
        else if (strncmp(token.lexeme, "continue", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_CONTINUE");
            token.Token=TK_CONTINUE;
        }
        else if (strncmp(token.lexeme, "break", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BREAK");
            token.Token=TK_BREAK;
        }
        else if (strncmp(token.lexeme, "default", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DEFAULT");
            token.Token=TK_DEFAULT;
        }
        else if (strncmp(token.lexeme, "void", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_VOID");
            token.Token=TK_VOID;
        }
        else if (strncmp(token.lexeme, "return", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_RETURN");
            token.Token=TK_RETURN;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_IDENTIFIER");
            token.Token=TK_IDENTIFIER;
        }
    }
    else if (isdigit(c))
    {
        int i = 0;
        while (isdigit(c))
        {
            token.lexeme[i] = c;
            c = getc(inputFile);
            if (c == '\n')
            {
                *line = (*line) + 1;
                *column = 0;
            }
            i++;
        }
        token.lexeme[i] = '\0';
        if (c != '\n' && c != ' ')
        {
            ungetc(c, inputFile);
        }
        *column = (*column) + 1;
        strcpy(token.type, "TK_INT");
        token.Token=TK_INT;
    }
    else if (c == '+')
    {
        c = getc(inputFile);
        if (c == '+')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_PLUS");
            token.Token=TK_PLUS;
            token.lexeme[1] = c;
        }
        else if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_PLUS_EQUAL");
            token.Token=TK_PLUS_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_PLUS_PLUS");
            token.Token=TK_PLUS_PLUS;
            ungetc(c, inputFile);
        }  
    }
    else if (c == '-')
    {
        c = getc(inputFile);
        if (c == '-')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_MINUS_MINUS");
            token.Token=TK_MINUS_MINUS;
            token.lexeme[1] = c;
        }else if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_MINUS_EQUAL");
            token.Token=TK_MINUS_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_MINUS");
            token.Token=TK_MINUS;
            ungetc(c, inputFile);
        } 
    }
    else if (c == '*')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_MULTIPLY_EQUAL");
            token.Token=TK_MULTIPLY_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_MULTIPLY");
            token.Token=TK_MULTIPLY;
            ungetc(c, inputFile);
        } 
    }
    else if (c == '/')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DIVIDE_EQUAL");
            token.Token=TK_DIVIDE_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DIVIDE");
            token.Token=TK_DIVIDE;
            ungetc(c, inputFile);
        } 
    }
    else if (c == '%')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_MODULO_EQUAL");
            token.Token=TK_MODULO_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_MODULO");
            token.Token=TK_MODULO;
            ungetc(c, inputFile);
        } 
    }
    else if (c == '=')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_EQUAL");
            token.Token=TK_EQUAL;
            token.lexeme[1] = c;
        }
        else if (c == '>')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_STRUCT_ARROW");
            token.Token=TK_STRUCT_ARROW;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_ASSIGN");
            token.Token=TK_ASSIGN;
            ungetc(c, inputFile);
        }
    }
    else if (c == '<')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LESS_EQUAL");
            token.Token=TK_LESS_EQUAL;
            token.lexeme[1] = c;
        }
        else if (c == '<')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_LSHIFT");
            token.Token=TK_BITWISE_LSHIFT;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LESS");
            token.Token=TK_LESS;
            ungetc(c, inputFile);
        }
    }
    else if (c == '>')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_GREATER_EQUAL");
            token.Token=TK_GREATER_EQUAL;
            token.lexeme[1] = c;
        }
        else if (c == '>')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_RSHIFT");
            token.Token=TK_BITWISE_RSHIFT;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_GREATER");
            token.Token=TK_GREATER;
            ungetc(c, inputFile);
        }
    }
    else if (c == '!')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_NOT_EQUAL");
            token.Token=TK_NOT_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_NOT");
            token.Token=TK_BITWISE_NOT;
            ungetc(c, inputFile);
        }
    }
    else if (c == '&')
    {
        c = getc(inputFile);
        if (c == '&')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LOGICAL_AND");
            token.Token=TK_LOGICAL_AND;
            token.lexeme[1] = c;
        }
        else if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_AND_EQUAL");
            token.Token=TK_BITWISE_AND_EQUAL;
            token.lexeme[1] = c;
        }
        else {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_AND");
            token.Token=TK_BITWISE_AND;
            ungetc(c, inputFile);
        }
    }
    else if (c == '|')
    {
        c = getc(inputFile);
        if (c == '|')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LOGICAL_OR");
            token.Token=TK_LOGICAL_OR;
            token.lexeme[1] = c;
        }
        else if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_OR_EQUAL");
            token.Token=TK_BITWISE_OR_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_OR");
            token.Token=TK_BITWISE_OR;
            ungetc(c, inputFile);
        }
    }
    else if (c == '^')
    {
         c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_XOR_EQUAL");
            token.Token=TK_BITWISE_XOR_EQUAL;
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_XOR");
             token.Token=TK_BITWISE_XOR;
            ungetc(c, inputFile);
        }
        
    }
    else if (c == '(')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_LPAREN");
        token.Token=TK_LPAREN;
    }
    else if (c == ')')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_RPAREN");
        token.Token=TK_RPAREN;
    }
    else if (c == '{')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_LBRACE");
        token.Token=TK_LBRACE;
    }
    else if (c == '}')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_RBRACE");
        token.Token=TK_RBRACE;
    }
    else if (c == '[')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_LBRACKET");
        token.Token=TK_LBRACKET;
    }
    else if (c == ']')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_RBRACKET");
        token.Token=TK_RBRACKET;
    }
    else if (c == ';')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_SEMICOLON");
        token.Token=TK_SEMICOLON;
    }
    else if (c == '~')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_TILDE");
        token.Token=TK_TILDE;
    }
    else if (c == '.')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_DOT");
        token.Token=TK_DOT;
    }
    else if (c == ':')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_TWO_DOT");
        token.Token=TK_TWO_DOT;
    }
    else if (c == ',')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_COMMA");
        token.Token=TK_COMMA;
    }
    else if (c == EOF)
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_EOF");
        token.Token=TK_EOF;
        token.lexeme[0]='|';
        token.lexeme[1]='n';
        
    }
    else
    {
        // Error handling for unrecognized characters
        printf("Error: Unrecognized character '%c' at line %d, column %d\n", c, *line, *column);
        *column = (*column) + 1;
        strcpy(token.type, "TK_EOF");
        token.Token=TK_EOF;
    }
    return token;
}

const char* getTokenName(TokenN Token) {
    switch (Token) {
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
        case TK_BITWISE_NOT:
            return "Bitwise NOT";
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
        case TK_TILDE:
            return "Tilde";
    }
    return "Unknown";
}

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening input or output file.\n");
        return 1;
    }

    // Token token;
    // int lineCount = 1, columnCount = 1;
    // int tokenCount = 0;
    // printf("| Linha          | Coluna        | Lexeme        | Token\n");
    // printf("|----------------|---------------|---------------|-----------------\n");
    // fprintf(outputFile,"| Linha          | Coluna        | Lexeme        | Token\n");
    // fprintf(outputFile,"|----------------|---------------|---------------|-----------------\n");
    // do
    // {
    //     token = getNextToken(inputFile, &lineCount, &columnCount);
    //     printf("| %-14d | %-13d | %-13s | %s\n", token.line, token.column, token.lexeme, token.type);
    //     fprintf(outputFile, "| %-14d | %-13d | %-13s | %s\n", token.line, token.column, token.lexeme, token.type);
    //     tokenCount++;
    // } while (strcmp(token.type, "TK_EOF") != 0);
    // printf("|----------------|---------------|---------------|-----------------\n");
    // printf("|Total tokens:   | %-13d |               |\n", tokenCount);
    // printf("|----------------|---------------|               |\n");
        // fprintf(outputFile,"|----------------|---------------|---------------|-----------------\n");
    // fprintf(outputFile,"|Total tokens:   | %-13d |               |\n", tokenCount);
    // fprintf(outputFile,"|----------------|---------------|               |\n");

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
