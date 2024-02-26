import re
from lexer.token_provider import read_token
from lexer.lexer import FLOAT, NUMBER

def number() -> bool:
    # <NUMBER> -> int value | float value
    return read_token() == FLOAT or read_token() == NUMBER