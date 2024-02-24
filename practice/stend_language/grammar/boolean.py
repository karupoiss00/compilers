from lexer.token_provider import read_token

def boolean() -> bool:
    token = read_token()
    return token == "true" or token == "false"