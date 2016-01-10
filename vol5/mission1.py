input_lines = input()
print("".join(c for i, c in enumerate(input_lines) if i % 2 == 0))
