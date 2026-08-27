##
## EPITECH PROJECT, 2023
## B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
## File description:
## string_xor
##

from itertools import cycle

def string_xor(str1: str, str2: str) -> bytes:
    """Xor two strings"""
    b1 = bytearray(str1.encode())
    b2 = bytearray(str2.encode())
    
    # XOR operation using bytearray
    result = bytearray(a ^ b for a, b in zip(b1, cycle(b2)))
    result = bytes(result)
    decoded_result = result.decode("utf-8")
    return decoded_result