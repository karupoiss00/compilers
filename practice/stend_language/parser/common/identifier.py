from lexer.token_provider import  read_token
from lexer.lexer import IDENTIFIER

def identifier() -> bool:
    ''' <IDENTIFIER> -> id '''
    return read_token().id == IDENTIFIER