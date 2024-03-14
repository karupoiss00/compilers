from lexer.token_provider import match_token
from lexer.token_type import TokenType


def boolean() -> bool:
    return match_token(TokenType.TRUE) or match_token(TokenType.FALSE)
