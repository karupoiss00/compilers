from lexer.token_type import TokenType
from lexer.token_provider import pop_token


def brace(isLeft: bool = True) -> bool:
    return pop_token() == TokenType.LBRACE if isLeft else pop_token() == TokenType.RBRACE