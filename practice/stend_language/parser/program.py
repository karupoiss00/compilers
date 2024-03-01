from lexer.token_provider import pop_token
from lexer.token_type import TokenType
from parser.declarations.declarations import declarations
from parser.list_statements import list_statements
from common.brace import lbrace, rbrace

def program() -> bool:
    return start() and declarations() and lbrace() and list_statements() and rbrace() and finish()


def start() -> bool:
    return pop_token() == TokenType.START


def finish() -> bool:
    return pop_token() == TokenType.FINISH