import re
from lexer.token_provider import read_token

def string() -> bool:
    token = read_token()
    return re.match("^\"[a-zA-Z0-9_\-]+\"$", token) != None