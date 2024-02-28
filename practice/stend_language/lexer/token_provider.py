from typing import Optional
from lexer.lexer import get_token, tokenize, Token

next_token: Optional[Token] = None

def generate_tokens(text: str):
    tokenize(text)


def pop_token() -> Token:
    global next_token
    if next_token:
        token = next_token
        next_token = None
        return token

    return get_token()


def read_token() -> Token:
    global next_token
    if next_token is None:
        next_token = get_token()
    return next_token


def match_token(token_id: int) -> bool:
    return read_token().id == token_id


def clear_next_token():
    global next_token
    next_token = None