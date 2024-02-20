from number import number
from identifier import identifier
from lexer.token_provider import pop_token, read_token

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
        return read_token() in ["=", "<>", "<", ">", "<=", ">="]
    except Exception:
        return False

def simple_expression() -> bool:
    # <SIMPLE EXPRESSION> -> <TERM><PLUS><SIMPLE EXPRESSION> | <TERM>
    try:
        if term():
            if plus():
                pop_token()
                return simple_expression()
            return True
        return False
    except Exception:
        return False

def plus() -> bool:
    # <PLUS> -> + | or
    try:
        return read_token() in ["+", "or"]
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
    # <MULTIPLY> -> * | / | div | mod
    try:
        return read_token() in ["*", "/", "div", "mod"]
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
        if read_token() == "(":
            pop_token()
            return simple_expression() and pop_token() == ")"
        if read_token() == "-" or read_token() == "not":
            pop_token()
            return factor()
        if identifier():
            pop_token()
            return True
        return False
    except Exception:
        return False