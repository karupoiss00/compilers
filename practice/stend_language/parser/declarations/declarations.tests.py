from parser.declarations.declarations import declarations
from lexer.lexer import *

tests = [
    ('''
VAR 
    String id := 'A'
RAV
''', [
    [VAR, "VAR"], [STRING_TYPE, "String"], [IDENTIFIER, "id"], [ASSIGN, ":="], [CHAR, "'A'"], [RAV, "RAV"]
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
    [CONST, "CONST"], [STRING_TYPE, "String"], [IDENTIFIER, "id"], [ASSIGN, ":="], 
    [CHAR, "'A'"], [SEMICOLON, ";"], [INT_TYPE, "Int"], [IDENTIFIER, "id"], [ASSIGN, ":="], [STRING, '"AB"'], 
    [SEMICOLON, ";"], [FLOAT_TYPE, "Float"], [IDENTIFIER, "id"], [ASSIGN, ":="], [FLOAT, "1.0"], [SEMICOLON, ";"], 
    [BOOLEAN_TYPE, "Boolean"], [IDENTIFIER, "id"], [ASSIGN, ":="], [NUMBER, "100"], [SEMICOLON, ";"], [CHAR_TYPE, "Char"], [IDENTIFIER, "id"], 
    [ASSIGN, ":="], [NUMBER, "1"], [NOC, "NOC"],
    [VAR, "VAR"], [STRING_TYPE, "String"], [IDENTIFIER, "id"], [ASSIGN, ":="], 
    [CHAR, "'A'"], [SEMICOLON, ";"], [INT_TYPE, "Int"], [IDENTIFIER, "id"], [ASSIGN, ":="], [STRING, '"AB"'], 
    [SEMICOLON, ";"], [FLOAT_TYPE, "Float"], [IDENTIFIER, "id"], [ASSIGN, ":="], [FLOAT, "1.0"], [SEMICOLON, ";"], 
    [BOOLEAN_TYPE, "Boolean"], [IDENTIFIER, "id"], [ASSIGN, ":="], [NUMBER, "100"], [SEMICOLON, ";"], [CHAR_TYPE, "Char"], [IDENTIFIER, "id"], 
    [ASSIGN, ":="], [NUMBER, "1"],[RAV, "RAV"],
], True),

('''
CONST 
RAV 
''', [
    [CONST, "CONST"], [RAV, "RAV"],
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

