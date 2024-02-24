import re
from lexer.token_provider import read_token

def char() -> bool:
    token = read_token()
    return re.match("^'.'$", token) != None