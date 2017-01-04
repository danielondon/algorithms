"""
You have to replace all spaces in a string for %20 !
"""

def replace_spaces(str):
    return '$20'.join(str.split())

print(replace_spaces('h a l l o'))
