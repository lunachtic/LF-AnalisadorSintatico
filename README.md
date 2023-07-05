# LF-AnalisadorSintatico
## Analisador sintático de sub-conjunto da linguagem C 

Escrever uma gramática e um analisador sintático descendente recursivo que reconheça o subconjunto da linguagem C abaixo:

1. Declarações e referências a variáveis int, long int, long long int, float, char e double com possibilidade do modificador unsigned, bem como arrays e pointers para as mesmas.

2. Declarações e chamadas de funções.

3. Expressões: Com a lista de operadores aritméticos, bitwise, relacionais e lógicos em C relacionados abaixo. A gramática deve implementar a precedência e associatividade dos operadores:

        Troca de Sinal: - 
            Aritméticos: +, -, *, /, %
            Relacionais: >, <, ==, !=, >=, <=
            Bitwise: &, |, ^, >>, <<, ~
            Lógicos: &&, || , !
            De atribuição: =, +=, -=, *=, /=, %=, >>=, <<=
            Vírgula

        Comandos :
            while
            do-while
            for
            if
            comando composto (grupos de comandos agrupados com chaves)
            comando-expressão.

Obs: O analisador pode ser implementado manualmente ou com o auxílio da ferramenta ParsingEdu. Em caso de erro sintático o analisador pode encerrar a análise, obrigatoriamente emitindo uma mensagem informando em que linha e coluna ocorreu o erro, qual era o token esperado e qual foi o token encontrado.

Obs: Pode ser utilizada como referência a gramática em https://www.lysator.liu.se/c/ANSI-C-grammar-y.html.

## Utilização:

O arquivo main.c faz a leitura do arquivo texto input.txt e retorna se a estrutura sintatica foi reconhecida, lexemas e estruturas fora do que foi definido anteriormente resultarão em um erro na execucão do probrama.
