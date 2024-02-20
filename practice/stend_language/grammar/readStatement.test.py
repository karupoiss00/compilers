from grammar.readStatement import read_statement
from lexer.temp_token_provider import set_tokens

tests = [
    ("READLINE ( id )", True),
    ("READ ( id )", True),
    ("READLINE", False),
    ("READ", False),
]

for test_id, test_data in enumerate(tests):
    test, expected_result = test_data
    tokens = test.split()
    set_tokens(tokens)
    if read_statement() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {read_statement()}')
