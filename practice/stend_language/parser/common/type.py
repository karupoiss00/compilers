from lexer.token_provider import pop_token
from lexer.token_type import TokenType

def type_() -> bool:
    """<TYPE> -> String | Int | Float | Boolean | Char"""
    return pop_token().id in [
        TokenType.STRING_TYPE, 
        TokenType.INT_TYPE, 
        TokenType.FLOAT_TYPE, 
        TokenType.BOOLEAN_TYPE, 
        TokenType.CHAR_TYPE
    ]
