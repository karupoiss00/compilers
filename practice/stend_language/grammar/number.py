import re
from  lexer.token_provider import read_token

def number() -> bool:
    # <NUMBER> -> int value | float value
    token = read_token()
    return re.match("^\d+(\.\d+)?$", token)