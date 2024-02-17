from lexer.temp_token_provider import get_token as get_token_from_temp_token_provider


def get_token() -> str:
    return get_token_from_temp_token_provider()
