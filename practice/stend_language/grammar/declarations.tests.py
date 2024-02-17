from declarations import declarations
from lexer.temp_token_provider import set_tokens


tests = [
('''
CONST 
    String id := "test" ; 
    Int id := '123' ; 
    Float id := 1.23 ;
    Boolean id := 1.24 ;
    Char id := 'a'
NOC 
VAR 
    String id := "test"
RAV''', True),


('''
VAR 
    String id := "test"'
RAV''', True),


('''
VAR 
    String id
RAV''', True),


('''
VAR 
    String id
RAV''', True),


('''
CONST
    Char id := 'a' ;
    String id := "test"
NOC
VAR 
    String id , id , id := "TEST"
RAV''', True),

('''
CONST
    Char id , id := 'a'
NOC''', False),


('''
CNST
    Char id , id := 'a'
NOC''', False),

('''
CONST
    Char id := 'a' ;
    String id := "test"
NOC
    String id , id , id := "TEST"
RAV''', False),


('''
CONST
    Char id := 'a' ;
    String id := "test"
VAR 
    String id , id , id := "TEST"
RAV''', False),


('''
CONST 
    Strong id := "test" ; 
    Ant id := '123' ; 
    Flat id := 1.23 ;
    Bool id := 1.24 ;
    Chr id := 'a'
NOC''', False),

('', False)
]

for test_id, test_data in enumerate(tests):
    test, expected_result = test_data
    tokens = test.split()
    set_tokens(tokens)
    if declarations() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {declarations()}')