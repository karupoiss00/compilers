from typing import Optional
from lexer.lexer import get_token, tokenize, Token, NoNextTokenException, LEXEMS
from lexer.token_type import TokenType

next_token: Optional[Token] = None
last_match_tokens: Optional[list[str]] = None

def generate_tokens(text: str):
    global last_match_tokens
    global next_token
    last_match_tokens = None
    next_token = None
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


def match_token(token_id: TokenType) -> bool:
    global last_match_tokens
    try:
        result = read_token().id == token_id

        if not result:
            expected_token = next(x for x in LEXEMS if x[2] == token_id)
            last_match_tokens = [read_token().name, expected_token[0]]
        return result
    except NoNextTokenException:
        return False


def print_match_error():
    if last_match_tokens is None:
        return
    if last_match_tokens[0] != last_match_tokens[1]:
        print(f'Expected {last_match_tokens[1]}, got {last_match_tokens[0]}')


def clear_next_token():
    global next_token
    next_token = None
