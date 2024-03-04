import sys

sys.path.append('../..'); sys.path.append('..'); sys.path.append('.')
from lexer.token_provider import clear_next_token, read_token;
from declarations_ll1 import declarations
from lexer.lexer import *

tests = [

('''
VAR 
    String id := 123
RAV''', True),

('''
CONST 
    String id := 123 ; 
    Int id := 123 ; 
    Float id := 123 ;
    Boolean id := 123 ;
    Char id := 123
NOC 
VAR 
    String id := 123
RAV''', True),


('''
CONST 
    String id := 123 ; 
    Int id := 123 ; 
    Float id := 123 ;
    Boolean id := 123 ;
    Char id := 123
NOC 
VAR 
    String id := 123 ;
    String id := 123 ;
    String id, id, id := 123
RAV''', True),


('''
CONST 
    String id := 123 ; 
    Int id := 123 ; 
    Float id := 123 ;
    Boolean id := 123 ;
    Char id := 123
NOC 
VAR 

RAV''', False),


('''
VAR 
    String id
RAV''', True),


('''
VAR 
    String id 10
RAV''', False),


('''
VAR 
    String id := 10 ;
RAV''', False),


('''
VAR 
    String id := 10
''', False),


('''
CONST
    String id := 10
RAV''', False),


('''
VAR 
    String id :=
RAV''', False),


('''
VAR 
    String id ;
RAV''', False),


('''
VAR 
    String id ; :=
RAV''', False),

('''
VAR 
    String
RAV''', False),


('''
VAR 

RAV''', False),



('''
CONST
    Char id := 123 ;
    String id := 123
NOC
VAR 
    String idA , idB , idC := 123
RAV''', True),

('''
CONST
    Char id , id := 123
NOC''', False),


('''
CNST
    Char id , id := 123
NOC''', False),

('''
CONST
    Char id := 123 ;
    String id := 123
NOC
    String id , id , id := 123
RAV''', False),


('''
CONST
    Char id := 123 ;
    String id := 123
VAR 
    String id , id , id := 123
RAV''', False),


('''
CONST 
    Strong id := 123 ; 
    Ant id := 123 ; 
    Flat id := 123 ;
    Bool id := 123 ;
    Chr id := 123
NOC''', False),

('', False)
]

for test_id, test_data in enumerate(tests):
    test, should_be_valid = test_data

    tokenize(test)
    clear_next_token()
    try:
        if declarations() == should_be_valid:
            print(f'{test_id + 1}:\tOK')
            continue
    except NoNextTokenException:
        pass
    print(f'{test_id + 1}:\tFAIL')


