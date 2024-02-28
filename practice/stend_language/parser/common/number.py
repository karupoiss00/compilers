from lexer.token_provider import match_token
from lexer.lexer import NUMBER, FLOAT


def number() -> bool:
    # <NUMBER> -> int value | float value
    return match_token(NUMBER) or match_token(FLOAT)
