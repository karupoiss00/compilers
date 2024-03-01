from lexer.token_type import TokenType
from lexer.token_provider import pop_token, match_token


def lbrace() -> bool:
    if match_token(TokenType.LBRACE):
        pop_token()
        return True
    return False


def rbrace() -> bool:
    if match_token(TokenType.RBRACE):
        pop_token()
        return True
    return False
