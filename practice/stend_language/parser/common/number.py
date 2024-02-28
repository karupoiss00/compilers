import re
from lexer.token_provider import match_token
from lexer.lexer import FLOAT, NUMBER

def number() -> bool:
    # <NUMBER> -> int value | float value
    return match_token(FLOAT) or match_token(NUMBER)