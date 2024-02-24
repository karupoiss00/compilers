from expression import expression
from lexer.temp_token_provider import set_tokens
from lexer.token_provider import clear_next_token


tests = [
    ('''- 50.6 or 49''', True),
    ('''not id or 47 = 47.0''', True),
    ('''id = 5 + 6''', True),
    ('''id = ( 5 * 5 div 5 ) >= 5''', True),
    ('''id = 9 or not ( id * 10 )''', True),
    ('''id - 6''', True),
    ('''id''', True),
    ('''9.5''', True),
    ('''id = ( 5 * 6''', False),
    ('''+ id''', False),
    ('''div 484''', False),
    ('''5.''', False),
    ('''5.0''', True),
    ('''0''', True),
    ("id =", False),
    ('''- ( id + 12.5 * - 5 * - ( - id * - id + - id ) )''', True)
]

for test_id, test_data in enumerate(tests):
    clear_next_token()
    test, expected_result = test_data
    tokens = test.split()
    set_tokens(tokens)
    if expression() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {expression()}')