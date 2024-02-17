from lexer.token_provider import pop_token


def identifier() -> bool:
    ''' <IDENTIFIER> -> id '''
    # TODO: Определить лексему id
    return pop_token() == 'id'