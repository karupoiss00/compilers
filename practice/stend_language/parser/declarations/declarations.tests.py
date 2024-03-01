from parser.declarations.declarations import declarations
from lexer.lexer import *
from lexer.token_type import TokenType

tests = [
    ('''
VAR 
    String id := 'A'
RAV
''', [
    [TokenType.VAR, "VAR"], [TokenType.STRING_TYPE, "String"], [TokenType.IDENTIFIER, "id"], 
    [TokenType.ASSIGN, ":="], [TokenType.CHAR, "'A'"], [TokenType.RAV, "RAV"]
], True),

('''
CONST 
    String id := 'A'; 
    Int id := "AB"; 
    Float id := 1.0;
    Boolean id := 100;
    Char id := 1
NOC
VAR
    String id:='A';
    Int id:="AB"; 
    Float id:=1.0;
    Boolean id:=100;
    Char id:=1
RAV 
''', [
    [TokenType.CONST, "CONST"], [TokenType.STRING_TYPE, "String"], [TokenType.IDENTIFIER, "id"], [TokenType.ASSIGN, ":="], 
    [TokenType.CHAR, "'A'"], [TokenType.SEMICOLON, ";"], [TokenType.INT_TYPE, "Int"], [TokenType.IDENTIFIER, "id"], 
    [TokenType.ASSIGN, ":="], [TokenType.STRING, '"AB"'], [TokenType.SEMICOLON, ";"], [TokenType.FLOAT_TYPE, "Float"], 
    [TokenType.IDENTIFIER, "id"], [TokenType.ASSIGN, ":="], [TokenType.FLOAT, "1.0"], [TokenType.SEMICOLON, ";"], 
    [TokenType.BOOLEAN_TYPE, "Boolean"], [TokenType.IDENTIFIER, "id"], [TokenType.ASSIGN, ":="], [TokenType.NUMBER, "100"], 
    [TokenType.SEMICOLON, ";"], [TokenType.CHAR_TYPE, "Char"], [TokenType.IDENTIFIER, "id"], [TokenType.ASSIGN, ":="], 
    [TokenType.NUMBER, "1"], [TokenType.NOC, "NOC"], [TokenType.VAR, "VAR"], [TokenType.STRING_TYPE, "String"], [TokenType.IDENTIFIER, "id"], 
    [TokenType.ASSIGN, ":="], [TokenType.CHAR, "'A'"], [TokenType.SEMICOLON, ";"], [TokenType.INT_TYPE, "Int"], [TokenType.IDENTIFIER, "id"], 
    [TokenType.ASSIGN, ":="], [TokenType.STRING, '"AB"'], [TokenType.SEMICOLON, ";"], [TokenType.FLOAT_TYPE, "Float"], 
    [TokenType.IDENTIFIER, "id"], [TokenType.ASSIGN, ":="], [TokenType.FLOAT, "1.0"], [TokenType.SEMICOLON, ";"], 
    [TokenType.BOOLEAN_TYPE, "Boolean"], [TokenType.IDENTIFIER, "id"], [TokenType.ASSIGN, ":="], [TokenType.NUMBER, "100"], 
    [TokenType.SEMICOLON, ";"], [TokenType.CHAR_TYPE, "Char"], [TokenType.IDENTIFIER, "id"], 
    [TokenType.ASSIGN, ":="], [TokenType.NUMBER, "1"],[TokenType.RAV, "RAV"],
], True),

('''
CONST 
RAV 
''', [
    [TokenType.CONST, "CONST"], [TokenType.RAV, "RAV"],
], False),

('''

''', [
    
], False)
]

for test_id, test_data in enumerate(tests):
    test, expected_token_list, should_be_valid = test_data
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
            print(f'\tGot: {result_token.__dict__}')
            continue
    
    tokenize(test)
    try:
        if declarations() == should_be_valid:
            print(f'{test_id + 1}:\tOK')
            continue
    except NoNextTokenException:
        pass
    print(f'{test_id + 1}:\tFAIL')

