from lexer.token_provider import generate_tokens
from parser.program import program

tests = [
    ('''
START 
CONST 
    String id := 123 ; 
    Int id := 123 ; 
    Float id := 1.23 ;
    Boolean id := 1.24 ;
    Char id := 123
NOC
VAR
    Int id := 123 
RAV 
{ 
    READ ( id ) ;
    FOR id := 5 TO 10 
    DO 
        id := 1 ;
        IF id > 0 THEN 
            id := 10 
        ELSE 
            id := 0 
        FI
    ROF ; 
    id := 1 ; 
    ; ;
    IF id > 0 
    THEN 
        id := 10 ;
        FOR id := 5 TO 10 
        DO 
            id := 1 ;
            IF id > 0 THEN 
                id := 10 
            ELSE 
                id := 0 
            FI
        ROF 
    ELSE 
        id := 0 ; 
        FOR id := 5 TO 10 
        DO 
            id := 1 ;
            IF id > 0 THEN 
                id := 10 
            ELSE 
                id := 0 
            FI
        ROF; 
        WHILE id < 5
        DO
            id := id + 1 ;
            READLINE ( id ) ;
            WHILE id < 5
            DO
                id := id + 1
            EL
        EL
    FI;
    
    WRITELINE ( id + 1 );
    WRITE ( id + 2 )
} 
FINISH
''', True),

    ('''
START } FINISH
''', False),

    ('''
START { FINISH
''', False),

    ('''
START { }
''', False),

    ('''
{ } FINISH
''', False),
]

for test_id, test_data in enumerate(tests):
    test, expected_result = test_data
    tokens = generate_tokens(test)

    res = program()

    if res == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {res}')