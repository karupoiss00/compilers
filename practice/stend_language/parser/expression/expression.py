from parser.common.number import number
from parser.common.identifier import identifier
from parser.common.string import string
from parser.common.boolean import boolean
from parser.common.char import char
from lexer.token_provider import pop_token, match_token
from lexer.lexer import MINUS, NOT, LPAREN, RPAREN, EQUAL, NOT_EQUAL, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL_THAN, GREATER_OR_EQUAL_THAN, PLUS, OR, STAR, SLASH, DIV, MOD, AND


def expression() -> bool:
    # <EXPRESSION> -> <SIMPLE EXPRESSION><RELATION><EXPRESSION> | <SIMPLE EXPRESSION>
    try:
        if simple_expression():
            if relation():
                pop_token()
                return expression()
            return True
        return False
    except Exception:
        return False


def relation() -> bool:
    # <RELATION> -> = | <> | < | > | <= | >=
    try:
        return match_token(EQUAL) or match_token(NOT_EQUAL) or match_token(LESS_THAN) or match_token(GREATER_THAN) or match_token(LESS_OR_EQUAL_THAN) or match_token(GREATER_OR_EQUAL_THAN)
    except Exception:
        return False


def simple_expression() -> bool:
    # <SIMPLE EXPRESSION> -> <TERM><PLUS><SIMPLE EXPRESSION> | <TERM>
    try:
        if term():
            if addition():
                pop_token()
                return simple_expression()
            return True
        return False
    except Exception:
        return False


def addition() -> bool:
    # <PLUS> -> + | or | -
    try:
        return match_token(PLUS) or match_token(MINUS) or match_token(OR)
    except Exception:
        return False


def term() -> bool:
    # <TERM> -> <FACTOR><MULTIPLY><TERM> | <FACTOR>
    try:
        if factor():
            if multiply():
                pop_token()
                return term()
            return True
        return False
    except Exception:
        return False


def multiply() -> bool:
    # <MULTIPLY> -> * | / | div | mod | and
    try:
        return match_token(STAR) or match_token(SLASH) or match_token(DIV) or match_token(MOD) or match_token(AND)
    except Exception:
        return False


def factor() -> bool:
    # <FACTOR> -> -<FACTOR> 
    # | <NUMBER> 
    # | <IDENTIFIER> 
    # | (<SIMPLE EXPRESSION>) 
    # | not <FACTOR>
    try:
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
        if match_token(LPAREN):
            pop_token()
            return simple_expression() and match_token(RPAREN) and pop_token()
        if match_token(MINUS) or match_token(NOT):
            pop_token()
            return factor()
        if identifier():
            pop_token()
            return True
        return False
    except Exception:
        return False
