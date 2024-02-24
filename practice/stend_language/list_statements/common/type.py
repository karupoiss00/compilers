from lexer.token_provider import pop_token


def type_() -> bool:
    """<TYPE> -> String | Int | Float | Boolean | Char"""
    return pop_token() in ["String", "Int", "Float", "Boolean", "Char"]
