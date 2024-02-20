from lexer.token_provider import pop_token
from grammar.declarations import declarations
from grammar.list_statements import list_statements

def program() -> bool:
    return start() and declarations() and pop_token() == '{' and list_statements() and pop_token() == '}' and finish()


def start() -> bool:
    return pop_token() == 'START'


def finish() -> bool:
    return pop_token() == 'FINISH'