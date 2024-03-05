from lexer.token_provider import match_token
from lexer.token_type import TokenType


def identifier() -> bool:
    ''' <IDENTIFIER> -> id '''
    return match_token(TokenType.IDENTIFIER)