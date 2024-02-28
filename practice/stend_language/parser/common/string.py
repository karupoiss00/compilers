import re
from lexer.token_provider import match_token, read_token
from lexer.lexer import STRING

def string() -> bool:
    return match_token(STRING)