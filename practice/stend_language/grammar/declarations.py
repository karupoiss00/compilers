from expression import expression
from identifier import identifier
from lexer.token_provider import pop_token, read_token
from type import type_

# DECLARATION #

def declarations() -> bool:
    """<DECLARATIONS> -> <LIST CONST><LIST VAR>|<LIST VAR>"""
    try:
        return list_const() and list_var() or list_var()
    except Exception:
        return False


# RULES #

def list_const() -> bool:
    """<LIST CONST> -> CONST <LIST SECTION CONST> NOC"""
    return (
        read_token() == "CONST"
        and pop_token()
        and list_section_const()
        and pop_token() == "NOC"
    )


def list_section_const() -> bool:
    """<LIST SECTION CONST> -> <SECTION CONST> | <SECTION CONST>;<LIST SECTION CONST>"""
    return section_const() and list_section_const_postfix()


def list_section_const_postfix() -> bool:
    """;<LIST SECTION CONST>"""
    return read_token() == ";" and pop_token() and list_section_const() or True


def section_const() -> bool:
    """<SECTION CONST> -> <TYPE> <IDENTIFIER> := <EXPRESSION>"""
    return type_() and identifier() and pop_token() == ":=" and expression()


def list_var() -> bool:
    """<LIST VAR> -> VAR <LIST SECTION VAR> RAV"""
    return pop_token() == "VAR" and list_section_var() and pop_token() == "RAV"


def list_section_var() -> bool:
    """<SECTION VAR> | <SECTION VAR>;<LIST SECTION VAR>"""

    return section_var() and list_section_var_postfix()


def list_section_var_postfix() -> bool:
    """;<LIST SECTION VAR>"""
    return read_token() == ";" and pop_token() and list_section_var() or True


def section_var() -> bool:
    """<SECTION VAR> -> <TYPE> <IDENTIFIER LIST> | <TYPE> <IDENTIFIER LIST> := <EXPRESSION>"""
    return type_() and identifier_list() and section_var_postfix()


def section_var_postfix() -> bool:
    """:= <EXPRESSION>"""
    return read_token() == ":=" and pop_token() and expression() or True


def identifier_list() -> bool:
    """<IDENTIFIER LIST> -> <IDENTIFIER> | <IDENTIFIER>, <IDENTIFIER LIST>"""
    return identifier() and identifier_list_postfix()


def identifier_list_postfix() -> bool:
    """,<IDENTIFIER LIST>"""
    return read_token() == "," and pop_token() and identifier_list() or True
