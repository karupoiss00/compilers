class NoNextTokenException(Exception):
    pass

tokens = []

position = 0

def get_token() -> str:
    global position
    if position < len(tokens):
        token = tokens[position]
        position += 1
        return token
    else:
        raise NoNextTokenException

def set_tokens(tokens_list: list) -> None:
    global position
    global tokens
    position = 0
    tokens = tokens_list