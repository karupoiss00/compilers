from lexer.token_provider import match_token
from lexer.lexer import TRUE, FALSE


def boolean() -> bool:
    return match_token(TRUE) or match_token(FALSE)
