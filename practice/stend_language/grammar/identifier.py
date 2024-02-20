from lexer.token_provider import  read_token


def identifier() -> bool:
    ''' <IDENTIFIER> -> id '''
    # TODO: Определить лексему id
    return read_token() == 'id'