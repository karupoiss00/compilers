from parser.common.number import number
from parser.common.identifier import identifier
from parser.common.string import string
from parser.common.boolean import boolean
from parser.common.char import char
from lexer.token_provider import pop_token, match_token
from lexer.lexer import *
from lexer.token_type import TokenType


def expression() -> bool:
    # <EXPRESSION> -> <SIMPLE EXPRESSION><RELATION><EXPRESSION> | <SIMPLE EXPRESSION>
    if simple_expression():
        if relation():
            pop_token()
            return expression()
        return True
    return False


def relation() -> bool:
    # <RELATION> -> = | <> | < | > | <= | >=
    return (
        match_token(TokenType.EQUAL)
        or match_token(TokenType.NOT_EQUAL)
        or match_token(TokenType.LESS_THAN)
        or match_token(TokenType.GREATER_THAN)
        or match_token(TokenType.LESS_OR_EQUAL_THAN)
        or match_token(TokenType.GREATER_OR_EQUAL_THAN)
    )


def simple_expression() -> bool:
    # <SIMPLE EXPRESSION> -> <TERM><PLUS><SIMPLE EXPRESSION> | <TERM>
    if term():
        if addition():
            pop_token()
            return simple_expression()
        return True
    return False


def addition() -> bool:
    # <PLUS> -> + | or | -
    return (
        match_token(TokenType.PLUS)
        or match_token(TokenType.MINUS)
        or match_token(TokenType.OR)
    )


def term() -> bool:
    # <TERM> -> <FACTOR><MULTIPLY><TERM> | <FACTOR>
    if factor():
        if multiply():
            pop_token()
            return term()
        return True
    return False


def multiply() -> bool:
    # <MULTIPLY> -> * | / | div | mod | and
    return (
        match_token(TokenType.STAR)
        or match_token(TokenType.SLASH)
        or match_token(TokenType.DIV)
        or match_token(TokenType.MOD)
        or match_token(TokenType.AND)
    )


def factor() -> bool:
    # <FACTOR> -> -<FACTOR> 
    # | <NUMBER> 
    # | <IDENTIFIER> 
    # | (<SIMPLE EXPRESSION>) 
    # | not <FACTOR>
    if number():
        pop_token()
        return True
    if string():
        pop_token()
        return True
    if boolean():
        pop_token()
        return True
    if char():
        pop_token()
        return True
    if match_token(TokenType.LPAREN):
        pop_token()
        return simple_expression() and match_token(TokenType.RPAREN) and pop_token()
    if match_token(TokenType.MINUS) or match_token(TokenType.NOT):
        pop_token()
        return factor()
    if identifier():
        pop_token()
        return True
    return False
