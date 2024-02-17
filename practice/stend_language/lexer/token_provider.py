from typing import Optional
from lexer.lexer import get_token

next_token: Optional[str] = None


def pop_token() -> str:
    global next_token
    if next_token:
        token = next_token
        next_token = None
        return token

    return get_token()


def read_token() -> str:
    global next_token
    if next_token is None:
        next_token = get_token()
    return next_token
