from lexer.token_provider import match_token, read_token
from lexer.token_type import TokenType

def char() -> bool:
    return match_token(TokenType.CHAR)