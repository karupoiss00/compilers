from lexer.token_provider import pop_token, print_match_error, match_token
from lexer.token_type import TokenType
from parser.declarations.declarations import declarations
from parser.list_statements.list_statements import list_statements
from parser.common.brace import lbrace, rbrace


def program() -> bool:
    result = start() and declarations() and lbrace() and list_statements() and rbrace() and finish()
    if not result:
        print_match_error()
    return result


def start() -> bool:
    if match_token(TokenType.START):
        pop_token()
        return True
    return False


def finish() -> bool:
    if match_token(TokenType.FINISH):
        pop_token()
        return True
    return False
