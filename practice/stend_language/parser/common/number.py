from lexer.token_provider import match_token
from lexer.token_type import TokenType


def number() -> bool:
    # <NUMBER> -> int value | float value
    return match_token(TokenType.NUMBER) or match_token(TokenType.FLOAT)
