from lexer.token_provider import match_token
from lexer.lexer import CHAR


def char() -> bool:
    return match_token(CHAR)
