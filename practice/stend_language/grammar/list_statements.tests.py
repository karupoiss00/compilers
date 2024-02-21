from list_statements import list_statements
from lexer.temp_token_provider import set_tokens
from lexer.token_provider import clear_next_token

statement_tests = [
    ('; \0', True), #1
    ('id := 5 \0', True), #2
    ('IF id > 0 THEN id := 10 ELSE id := 0 FI \0', True), #3
    ('IF id > 0 THEN id := 10 ELSE id := 0 \0', False),  #4 Missing 'FI'
    ('VAR id := 5 RAV \0', False),  #5 Not a valid statement
    ('''
    FOR
        id := 5 TO 10 DO id := 1
    ROF \0''', True), #6
    ('''
    FOR
        i := 5 to 10 k=k+1
    ROF \0''', False), #7
    ('''
    FOR
        i := 5 to 10 do
    ROF \0''', False), #8
    ('''
    FOR
        i = 5 to 10 do k=k+1
    ROF \0''', False), #9
    ('''
    FOR
        i = 5 to 10 do k=k+1 \0
    ''', False), #10
    (' \0', False), #11
    ('''
    IF id > 0 
    THEN 
        id := 10 
    ELSE 
        id := 0 
    FI ;
    id := 1 ;
    ; \0
    ''', True), #3
]

for test_id, test_data in enumerate(statement_tests):
    clear_next_token()
    test, expected_result = test_data
    tokens = test.split()
    set_tokens(tokens)
    if list_statements() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {list_statements()}')