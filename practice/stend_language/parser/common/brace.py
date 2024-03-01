from lexer.token_type import TokenType
from lexer.token_provider import pop_token


def lbrace() -> bool:
    return pop_token() == TokenType.LBRACE

def rbrace() -> bool:
    return pop_token() == TokenType.RBRACE