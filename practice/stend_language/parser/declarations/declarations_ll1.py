from lexer.token_provider import pop_token, read_token
from lexer.lexer import NoNextTokenException
from lexer.token_type import TokenType as T


ALL_TOKENS = T
ALL_TYPES = (T.STRING_TYPE, T.INT_TYPE, T.FLOAT_TYPE, T.BOOLEAN_TYPE, T.CHAR_TYPE)


table = {
    # (Номер, Токен, Направляющие, Указатель,                   Сдвиг?, Ошибка?,Стэк?,  Конец?)
    1:  ('declarations',                [T.CONST, T.VAR],   2,      False,  True,   False,  False),
    2:  ('list_const',                  [T.CONST],        4,      False,  False,  True,   False),
    3:  ('list_var',                    [T.VAR],          13,     False,  True,   False,  False),
    4:  ('T.CONST',                     [T.CONST],        5,      True,   True,   False,  False),
    5:  ('list_section_const',          [*ALL_TOKENS],  8,      False,  True,   True,   False),
    6:  ('list_section_const_postfix',  [T.SEMICOLON],    5,      True,   False,  False,  False),
    7:  ('T.NOC',                       [T.NOC],          None,   True,   True,   False,  False),
    8:  ('section_const',               [*ALL_TOKENS],  9,      False,  True,   False,  False),
    9:  ('type',                        [*ALL_TYPES],   10,     True,   True,   False,  False),
    10: ('identifier',                  [T.IDENTIFIER],   11,     True,   True,   False,  False),
    11: ('T.ASSIGN',                    [T.ASSIGN],       12,     True,   True,   False,  False),
    12: ('expression',                  [T.NUMBER],       None,   True,   True,   False,  False), # T.TODO: Jump to expression table
    13: ('T.VAR',                       [T.VAR],          14,     True,   True,   False,  False),
    14: ('list_section_var',            [*ALL_TOKENS],  17,     False,  True,   True,   False),
    15: ('list_section_var_postfix',    [T.SEMICOLON],    14,     True,   False,  False,  False),
    16: ('T.RAV',                       [T.RAV],          None,   True,   True,   False,  True),
    17: ('section_var',                 [*ALL_TOKENS],  18,     False,  True,   False,  False),
    18: ('type',                        [*ALL_TYPES],   19,     True,   True,   False,  False),
    19: ('identifier_list',             [*ALL_TOKENS],  24,     False,  True,   True,   False),
    20: ('T.ASSIGN',                    [T.ASSIGN],       23,     True,   False,  False,  False),
    21: ('T.RAV',                       [T.RAV],          None,   True,   True,   False,  True),
    22: ('section_var_postfix',         [*ALL_TOKENS],  20,     False,  True,   False,  False),
    23: ('expression',                  [T.NUMBER],       None,   True,   True,   False,  False), # T.TODO: Jump to expression table
    24: ('identifier',                  [T.IDENTIFIER],   25,     True,   True,   False,  False),
    25: ('identifier_list_postfix',     [T.COMMA],        19,     True,   False,  False,  False),
    26: ('identifier_list_postfix',     [*ALL_TOKENS],  None,   False,  True,   False,  False),
}


def declarations() -> bool:
    current = 1
    stack = []
    while True:
        try:
            state = table[current]
            if read_token().id not in state[1] and state[4]:
                return False
            if read_token().id not in state[1]:
                current += 1
                continue
            if state[5]:
                stack.append(current + 1)
            if read_token().id in state[1]:
                current = state[2]
            if state[6]:
                return True
            if state[2] == None:
                try:
                    current = stack.pop()
                except:
                    return False
            if state[3]:
                pop_token()
        except NoNextTokenException:
            return False
