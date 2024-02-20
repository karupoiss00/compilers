from expression import expression
from identifier import identifier
from token_provider import pop_token, read_token
from type import type_

def while_statement() -> bool:
	"""<WHILE STATEMENT> -> WHILE <EXPRESSION> do <LIST STATEMENTS> el"""
	return (
        read_token() == "WHILE"
        and pop_token()
        and expression()
        and read_token() == "DO"
        and pop_token()
        and statement()
        and pop_token() == "EL"
    )