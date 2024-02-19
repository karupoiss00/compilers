from listStatements import list_statements
from lexer.temp_token_provider import set_tokens

statement_tests = [
    (';', True),
    ('x := 5;', True),
    ('IF x > 0 THEN y := 10; ELSE y := 0; FI', True),
    ('IF x > 0 THEN y := 10; ELSE y := 0;', False),  # Missing 'FI'
    ('VAR x := 5 RAV', False),  # Not a valid statement
    ('', False),  # Empty input
]

for test_id, test_data in enumerate(statement_tests):
    test, expected_result = test_data
    tokens = test.split()
    set_tokens(tokens)
    if list_statements() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {list_statements()}')