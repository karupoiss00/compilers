from practice.stend_language.lexer.temp_token_provider import set_tokens
from practice.stend_language.lexer.token_provider import pop_token

def write_statement() -> bool:
    """<WRITE STATEMENT> -> <WRITELINE> | <WRITE>"""
    return writeline() or write()

def writeline() -> bool:
    """<WRITELINE> -> WriteLine(<IDENTIFIER>)"""
    return pop_token() == "WRITELINE"

def write() -> bool:
    """<WRITE> -> Write(<IDENTIFIER>)"""
    return pop_token() == "WRITE"

tests = [
    (['WRITELINE'], True),
    (['WRITE'], True),
    (['WRITELINE', 'WRITE'], True),
    (['WRITE', 'WRITELINE'], True),
    (['WRITELINE', 'WRITELINE'], False),
    (['WRITE', 'WRITE'], False),
    (['WRITELINE', 'WRITE', 'WRITELINE'], False),
]

for test_id, test_data in enumerate(tests):
    tokens, expected_result = test_data
    set_tokens(tokens)
    if write_statement() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {write_statement()}')