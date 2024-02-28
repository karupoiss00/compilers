from lexer.token_provider import match_token
from lexer.lexer import IDENTIFIER


def identifier() -> bool:
    ''' <IDENTIFIER> -> id '''
    # TODO: Определить лексему id
    return match_token(IDENTIFIER)