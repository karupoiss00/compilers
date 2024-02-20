from grammar.writeStatement import write_statement
from lexer.temp_token_provider import set_tokens

tests = [
    ("WRITELINE ( id )", True),
    ("WRITE ( id )", True),
    ("WRITELINE", False),
    ("WRITE", False),
]

for test_id, test_data in enumerate(tests):
    test, expected_result = test_data
    tokens = test.split()
    set_tokens(tokens)
    if write_statement() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {write_statement()}')
