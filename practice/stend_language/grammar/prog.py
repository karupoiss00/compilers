from lexer.token_provider import pop_token


def prog() -> bool:
    return start() and declarations() and pop_token() == '{' and list_stms() and pop_token() == '}' and finish()


def start() -> bool:
    return pop_token() == 'START'


def finish() -> bool:
    return pop_token() == 'FINISH'
