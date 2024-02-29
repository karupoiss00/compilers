from parser.expression.expression import expression
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
    """TODO поддержать в [ <LIST STATEMENT> ]"""
    return (
        empty_statement()
        or assignment_statement()
        or for_statement()
        or while_statement()
        or if_statement()
        or write_statement()
        or read_statement()
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
    """<FOR STATEMENT> -> for <IDENTIFIER> := <NUMBER> to <NUMBER> do <LIST STATEMENTS> rof"""

    return (
            match_token(FOR)
            and pop_token()
            and identifier()
            and pop_token()
            and pop_token(ASSIGN)
            and number()
            and pop_token()
            and pop_token(TO)
            and number()
            and pop_token()
            and pop_token(DO)
            and list_statements()
            and pop_token(ROF)
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

def read_statement() -> bool:
    """<READ STATEMENT> -> <READLINE> | <READ>"""
    return readline() or read()

def readline() -> bool:
    """<READLINE> -> ReadLine(<IDENTIFIER>)"""
    try:
        return read_token() == "READLINE" and pop_token() and pop_token() == "(" and identifier() and pop_token() and pop_token() == ")"
    except Exception:
        return False

def read() -> bool:
    """<READ> -> Read(<IDENTIFIER>)"""
    try:
        return read_token() == "READ" and pop_token() and pop_token() == "(" and identifier() and pop_token() and pop_token() == ")"
    except Exception:
        return False

def write_statement() -> bool:
    """<WRITE STATEMENT> -> <WRITELINE> | <WRITE>"""
    return writeline() or write()

def writeline() -> bool:
    """<WRITELINE> -> WriteLine(<IDENTIFIER>)"""
    try:
        return read_token() == "WRITELINE" and pop_token() and pop_token() == "(" and expression() and pop_token() == ")"
    except Exception:
        return False

def write() -> bool:
    """<WRITE> -> Write(<IDENTIFIER>)"""
    try:
        return read_token() == "WRITE" and pop_token() and pop_token() == "(" and expression() and pop_token() == ")"
    except Exception:
        return False
