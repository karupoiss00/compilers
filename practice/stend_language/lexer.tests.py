from lexer.lexer import tokenize, get_token, get_tokens_count
from lexer.token_type import TokenType

tests = [
    ('''
START 
CONST 
    String id := 123; 
    Int id := 123; 
    Float id := 1.23;
    Boolean id := 1.24;
    Char id := 123
NOC
VAR
    Int id := 123 
RAV 
{ 
    READ(id);
    FOR id := 5 TO 10 
    DO 
        id := 1;
        IF id > 0 THEN 
            id := 10
        ELSE 
            id := 0
        FI
    ROF; 
    id := 1; 
    ;;
    IF id > 0 
    THEN 
        id := 10;
        FOR id := 5 TO 10 
        DO 
            id := 1;
            IF id > 0 THEN 
                id := 10 
            ELSE 
                id := 0 
            FI
        ROF 
    ELSE 
        id := 0; 
        FOR id := 5 TO 10 
        DO 
            id := 1;
            IF id > 0 THEN 
                id := 10 
            ELSE 
                id := 0 
            FI
        ROF; 
        WHILE id < 5
        DO
            id := id + 1;
            READLINE(id);
            WHILE id < 5
            DO
                id := id + 1
            EL
        EL
    FI;

    WRITELINE(id + 1);
    WRITE(id + 2)
} 
FINISH
''', [
    [TokenType.START, "START"],
    [TokenType.CONST, "CONST"],
    [TokenType.STRING_TYPE, "String"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "123"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.INT_TYPE, "Int"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "123"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.FLOAT_TYPE, "Float"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.FLOAT, "1.23"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.BOOLEAN_TYPE, "Boolean"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.FLOAT, "1.24"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.CHAR_TYPE, "Char"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "123"],
    [TokenType.NOC, "NOC"],
    [TokenType.VAR, "VAR"],
    [TokenType.INT_TYPE, "Int"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "123"],
    [TokenType.RAV, "RAV"],
    [TokenType.LBRACE, "{"],
    [TokenType.READ, "READ"],
    [TokenType.LPAREN, "("],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.RPAREN, ")"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.FOR, "FOR"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "5"],
    [TokenType.TO, "TO"],
    [TokenType.NUMBER, "10"],
    [TokenType.DO, "DO"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "1"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.IF, "IF"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.GREATER_THAN, ">"],
    [TokenType.NUMBER, "0"],
    [TokenType.THEN, "THEN"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "10"],
    [TokenType.ELSE, "ELSE"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "0"],
    [TokenType.FI, "FI"],
    [TokenType.ROF, "ROF"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "1"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.IF, "IF"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.GREATER_THAN, ">"],
    [TokenType.NUMBER, "0"],
    [TokenType.THEN, "THEN"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "10"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.FOR, "FOR"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "5"],
    [TokenType.TO, "TO"],
    [TokenType.NUMBER, "10"],
    [TokenType.DO, "DO"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "1"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.IF, "IF"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.GREATER_THAN, ">"],
    [TokenType.NUMBER, "0"],
    [TokenType.THEN, "THEN"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "10"],
    [TokenType.ELSE, "ELSE"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "0"],
    [TokenType.FI, "FI"],
    [TokenType.ROF, "ROF"],
    [TokenType.ELSE, "ELSE"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "0"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.FOR, "FOR"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "5"],
    [TokenType.TO, "TO"],
    [TokenType.NUMBER, "10"],
    [TokenType.DO, "DO"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "1"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.IF, "IF"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.GREATER_THAN, ">"],
    [TokenType.NUMBER, "0"],
    [TokenType.THEN, "THEN"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "10"],
    [TokenType.ELSE, "ELSE"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.NUMBER, "0"],
    [TokenType.FI, "FI"],
    [TokenType.ROF, "ROF"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.WHILE, "WHILE"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.LESS_THAN, "<"],
    [TokenType.NUMBER, "5"],
    [TokenType.DO, "DO"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.PLUS, "+"],
    [TokenType.NUMBER, "1"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.READLINE, "READLINE"],
    [TokenType.LPAREN, "("],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.RPAREN, ")"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.WHILE, "WHILE"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.LESS_THAN, "<"],
    [TokenType.NUMBER, "5"],
    [TokenType.DO, "DO"],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.ASSIGN, ":="],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.PLUS, "+"],
    [TokenType.NUMBER, "1"],
    [TokenType.EL, "EL"],
    [TokenType.EL, "EL"],
    [TokenType.FI, "FI"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.WRITELINE, "WRITELINE"],
    [TokenType.LPAREN, "("],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.PLUS, "+"],
    [TokenType.NUMBER, "1"],
    [TokenType.RPAREN, ")"],
    [TokenType.SEMICOLON, ";"],
    [TokenType.WRITE, "WRITE"],
    [TokenType.LPAREN, "("],
    [TokenType.IDENTIFIER, "id"],
    [TokenType.PLUS, "+"],
    [TokenType.NUMBER, "2"],
    [TokenType.RPAREN, ")"],
    [TokenType.RBRACE, "}"],
    [TokenType.FINISH, "FINISH"]
]),
('''
START } FINISH
''', [
    [TokenType.START, "START"],
    [TokenType.RBRACE, "}"],
    [TokenType.FINISH, "FINISH"]
]),
]

for test_id, test_data in enumerate(tests):
    test, expected_token_list = test_data
    tokenize(test)

    if len(expected_token_list) != get_tokens_count():
        raise Exception(f'''
    Tokens count does not match
    \tExpected: {len(expected_token_list)}
    \tGot: {get_tokens_count()}''')

    for token in expected_token_list:
        result_token = get_token()

        if result_token.id != token[0] or result_token.value != token[1]:
            print(f'{test_id + 1}:\tFAIL')
            print(f'\tExpected: {token}')
            print(f'\tGot: {result_token}')
            continue

    print(f'{test_id + 1}:\tOK')