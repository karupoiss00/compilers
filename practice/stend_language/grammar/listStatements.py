from expression import expression
from identifier import identifier
from lexer.token_provider import pop_token, read_token

# LIST STATEMENTS #

def list_statements() -> bool:
    """<LIST STATEMENTS> -> <STATEMENT><LIST STATEMENTS>|<STATEMENT>"""
    try:
        return statement() and list_statements() or statement()
    except Exception:
        return False

# RULES #

def statement() -> bool:
    """<STATEMENT> -> <EMPTY STATEMENT> | <ASSIGNMENT STATEMENT> | <IF STATEMENT>"""
    return empty_statement() or assignment_statement() or if_statement()

def empty_statement() -> bool:
    """<EMPTY STATEMENT> -> ;"""
    return read_token() == ';'

def assignment_statement() -> bool:
    """<ASSIGNMENT STATEMENT> -> <IDENTIFIER> := <EXPRESSION>"""
    return identifier() and pop_token() == ":=" and expression()

def if_statement() -> bool:
    """<IF STATEMENT> -> IF <EXPRESSION> THEN <STATEMENT><OPTIONAL ELSE> FI"""
    return (
        pop_token() == 'IF'
        and expression()
        and pop_token() == 'THEN'
        and statement()
        and optional_else()
        and pop_token() == 'FI'
    )

def optional_else() -> bool:
    """<OPTIONAL ELSE> -> e | ELSE <STATEMENT>"""
    return read_token() == 'ELSE' and pop_token() and statement() or True


