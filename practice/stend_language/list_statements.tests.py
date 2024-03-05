from parser.list_statements.list_statements import list_statements
from lexer.token_provider import clear_next_token, generate_tokens

statement_tests = [
    (';', True), #1
    ('id := 5', True), #2
    ('IF id > 0 THEN id := 10 ELSE id := 0 FI ', True), #3
    ('IF id > 0 THEN id := 10 ELSE id := 0 ', False),  #4 Missing 'FI'
    ('VAR id := 5 RAV ', False),  #5 Not a valid statement
    ('''
    FOR
        id := 5 TO 10 DO id := 1
    ROF ''', True), #6
    ('''
    FOR
        i := 5 to 10 k=k+1
    ROF ''', False), #7
    ('''
    FOR
        i := 5 to 10 do
    ROF ''', False), #8
    ('''
    FOR
        i = 5 to 10 do k=k+1
    ROF ''', False), #9
    ('''
    FOR
        i = 5 to 10 do k=k+1 
    ''', False), #10
    (' ', False), #11
    ('''
    IF id > 0 
    THEN 
        id := 10 
    ELSE 
        id := 0 
    FI ;
    id := 1 ;
    ; ;
    WHILE id < 5 
    DO
        id := id + 1
    EL
    ''', True), #12
    ('''
    WHILE id < 5
    DO
        id := id + 1
    EL

    ''', True), #13
    ('''
    WRITE ( id + 1 )
    
    ''', True), #14
    ('''
    WRITELINE ( id + 1 )
    
    ''', True), #15
    ('''
    READ ( id )
    
    ''', True), #16
    ('''
    READLINE ( id )
    
    ''', True), #17
    ('''
    READLINE ( id + 1 )
    
    ''', False), #18
    ('''
       WHILE id < 5
       DO
           [ id := id + 1 ]
       EL
       
   ''', True), # 9
]

for test_id, test_data in enumerate(statement_tests):
    clear_next_token()
    test, expected_result = test_data
    generate_tokens(test)
    if list_statements() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {list_statements()}')