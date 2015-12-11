def suffix_array(str):
    return sorted(range(len(str)), key=lambda i: str[i:])
