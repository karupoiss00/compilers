import sys; sys.path.append("../..") # To access lexer module without IDE

from lexer.lexer import *

tests = [
    ('''
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
''', [
    [2, "CONST"], [6, "String"], [27, "id"], [25, ":="], [29, "123"], [26, ";"], [7, "Int"], [27, "id"],
    [25, ":="], [29, "123"], [26, ";"], [8, "Float"], [27, "id"], [25, ":="], [28, "1.23"], [26, ";"], [9, "Boolean"],
    [27, "id"], [25, ":="], [28, "1.24"], [26, ";"], [10, "Char"], [27, "id"], [25, ":="], [29, "123"], [3, "NOC"],
    [4, "VAR"], [7, "Int"], [27, "id"], [25, ":="], [29, "123"], [5, "RAV"],
]),

('''
CONST 
    String id := 'A'; 
    Int id := "AB"; 
    Float id := 1.0;
    Boolean id := 100;
    Char id := 1
NOC
VAR
    String id:='A';;
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
    [CHAR, "'A'"], [SEMICOLON, ";"], [SEMICOLON, ";"], [INT_TYPE, "Int"], [IDENTIFIER, "id"], [ASSIGN, ":="], [STRING, '"AB"'], 
    [SEMICOLON, ";"], [FLOAT_TYPE, "Float"], [IDENTIFIER, "id"], [ASSIGN, ":="], [FLOAT, "1.0"], [SEMICOLON, ";"], 
    [BOOLEAN_TYPE, "Boolean"], [IDENTIFIER, "id"], [ASSIGN, ":="], [NUMBER, "100"], [SEMICOLON, ";"], [CHAR_TYPE, "Char"], [IDENTIFIER, "id"], 
    [ASSIGN, ":="], [NUMBER, "1"],[RAV, "RAV"],
]),

('''
CONST 
RAV 
''', [
    [CONST, "CONST"], [RAV, "RAV"],
]),

('''

''', [
    
])
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
            print(f'\tGot: {result_token.__dict__}')
            continue

    print(f'{test_id + 1}:\tOK')