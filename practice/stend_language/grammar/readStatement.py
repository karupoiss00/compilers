from practice.stend_language.lexer.token_provider import pop_token, read_token

def read_statement() -> bool:
    """<READ STATEMENT> -> <READLINE> | <READ>"""
    return readline() or read()

def readline() -> bool:
    """<READLINE> -> ReadLine(<IDENTIFIER>)"""
    return pop_token() == "READLINE"

def read() -> bool:
    """<READ> -> Read(<IDENTIFIER>)"""
    return pop_token() == "READ"
