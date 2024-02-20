from for_statement import for_statement
from lexer.temp_token_provider import set_tokens

for_tests = [
('''
FOR 
    i := 5 to 10 do k:=k+1 
ROF''', True),

('''
FOR 
    i := 5 to 10 k=k+1 
ROF''', False),

('''
FOR 
    i := 5 to 10 do
ROF''', False),

('''
FOR 
    i = 5 to 10 do k=k+1 
ROF''', False),

('''
FOR 
    i = 5 to 10 do k=k+1 
''', False),


('', False)
]

for test_id, test_data in enumerate(for_tests):
    test, expected_result = test_data
    tokens = test.split()
    set_tokens(tokens)
    if for_statement() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {for_statement()}')
