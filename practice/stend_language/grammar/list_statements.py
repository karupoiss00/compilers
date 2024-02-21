from expression import expression
from identifier import identifier
from number import number
from lexer.token_provider import pop_token, read_token
from lexer.temp_token_provider import NoNextTokenException

# LIST STATEMENTS #

def list_statements() -> bool:
    """<LIST STATEMENTS> -> <STATEMENT>;<LIST STATEMENTS>|<STATEMENT>"""
    try:
        if (statement()):
            if (read_token() == ';'):
                pop_token()
                return list_statements()
            return True
        return False
    except NoNextTokenException:
        print('out of tokens')
        return False
# RULES #

def statement() -> bool:
    """<STATEMENT> -> <EMPTY STATEMENT> | <ASSIGNMENT STATEMENT> | <IF STATEMENT>"""
    return (
        empty_statement()
        or assignment_statement()
        or for_statement()
        or while_statement()
        or if_statement()
    )

def empty_statement() -> bool:
    """<EMPTY STATEMENT> -> ;"""
    if (read_token() == ';'):
        pop_token()
        return True
    return False

def assignment_statement() -> bool:
    """<ASSIGNMENT STATEMENT> -> <IDENTIFIER> := <EXPRESSION>"""
    return identifier() and pop_token() and pop_token() == ":=" and expression()

def if_statement() -> bool:
    """<IF STATEMENT> -> IF <EXPRESSION> THEN <STATEMENT><OPTIONAL ELSE> FI"""
    return (
        read_token() == 'IF'
        and pop_token()
        and expression()
        and pop_token() == 'THEN'
        and list_statements()
        and optional_else()
        and pop_token() == 'FI'
    )

def optional_else() -> bool:
    """<OPTIONAL ELSE> -> e | ELSE <STATEMENT>"""
    if read_token() == 'ELSE':
        pop_token()
        return list_statements()
    return True

def for_statement() -> bool:
    """<FOR STATEMENT> -> for <IDENTIFIER> := <NUMBER> to <NUMBER> do <EXPRESSION> rof"""

    return (
            read_token() == "FOR"
            and pop_token()
            and identifier()
            and pop_token()
            and pop_token() == ":="
            and number()
            and pop_token()
            and pop_token() == "TO"
            and number()
            and pop_token()
            and pop_token() == "DO"
            and list_statements()
            and pop_token() == "ROF"
    )

def while_statement() -> bool:
    """<WHILE STATEMENT> -> WHILE <EXPRESSION> do <LIST STATEMENTS> el"""

    return (
        read_token() == "WHILE"
        and pop_token()
        and expression()
        and read_token() == "DO"
        and pop_token()
        and list_statements()
        and pop_token() == "EL"
    )



