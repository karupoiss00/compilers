from practice.stend_language.lexer.temp_token_provider import set_tokens
from practice.stend_language.lexer.token_provider import pop_token

def read_statement() -> bool:
    """<READ STATEMENT> -> <READLINE> | <READ>"""
    return readline() or read()

def readline() -> bool:
    """<READLINE> -> ReadLine(<IDENTIFIER>)"""
    return pop_token() == "READLINE"

def read() -> bool:
    """<READ> -> Read(<IDENTIFIER>)"""
    return pop_token() == "READ"

tests = [
    (['READLINE'], True),
    (['READ'], True),
    (['READLINE', 'READ'], True),
    (['READ', 'READLINE'], True),
    (['READLINE', 'READLINE'], False),
    (['READ', 'READ'], False),
    (['READLINE', 'READ', 'READLINE'], False),
]

for test_id, test_data in enumerate(tests):
    tokens, expected_result = test_data
    set_tokens(tokens)
    if read_statement() == expected_result:
        print(f'{test_id + 1}:\tOK')
    else:
        print(f'{test_id + 1}:\tFAIL')
        print(f'\tExpected: {expected_result}')
        print(f'\tGot: {read_statement()}')
