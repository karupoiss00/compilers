from lexer.token_provider import pop_token
from lexer.lexer import STRING_TYPE, INT_TYPE, FLOAT_TYPE, BOOLEAN_TYPE, CHAR_TYPE

def type_() -> bool:
    """<TYPE> -> String | Int | Float | Boolean | Char"""
    return pop_token() in [STRING_TYPE, INT_TYPE, FLOAT_TYPE, BOOLEAN_TYPE, CHAR_TYPE]
