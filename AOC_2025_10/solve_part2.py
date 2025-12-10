#!/usr/bin/env python3

#Generated with Copilot since i do not plan to implement my own solver :)

from z3 import *
import re

def parse_indicator(s):
    """Parse indicator like [#....#...] into a bitmask"""
    s = s[1:-1]  # Remove brackets
    result = 0
    for i, ch in enumerate(s):
        if ch == '#':
            result |= (1 << i)
    return result

def parse_button(s):
    """Parse button like (1,2,3) into a bitmask"""
    s = s[1:-1]  # Remove parentheses
    if not s:  # Empty button
        return 0
    indices = [int(x) for x in s.split(',')]
    result = 0
    for idx in indices:
        result |= (1 << idx)
    return result

def parse_joltage(s):
    """Parse joltage like {10,11,5} into a list"""
    s = s[1:-1]  # Remove braces
    return [int(x) for x in s.split(',')]

def parse_line(line):
    """Parse a line like: [#..#] (1,2) (3,4) {10,20,30}"""
    parts = line.strip().split()
    
    indicator = parse_indicator(parts[0])
    
    # All parts except first and last are buttons
    buttons = []
    for i in range(1, len(parts) - 1):
        buttons.append(parse_button(parts[i]))
    
    joltage = parse_joltage(parts[-1])
    
    return indicator, buttons, joltage

def solve_machine_z3(buttons, joltage):
    """
    Solve for minimum button presses using Z3.
    
    For each button i, we have a variable x[i] representing how many times it's pressed.
    For each joltage j, the sum of presses of buttons affecting j must equal joltage[j].
    Minimize sum(x).
    """
    n_buttons = len(buttons)
    n_joltages = len(joltage)
    
    # Create Z3 optimizer
    opt = Optimize()
    
    # Create integer variables for button presses (must be non-negative)
    x = [Int(f'x_{i}') for i in range(n_buttons)]
    
    # Constraint: all button presses must be non-negative
    for i in range(n_buttons):
        opt.add(x[i] >= 0)
    
    # Constraint: for each joltage slot, sum of affecting button presses equals target
    for j in range(n_joltages):
        # Find which buttons affect this joltage
        affecting = []
        for i in range(n_buttons):
            if buttons[i] & (1 << j):  # Button i affects joltage j
                affecting.append(x[i])
        
        if affecting:
            opt.add(Sum(affecting) == joltage[j])
    
    # Objective: minimize total button presses
    total_presses = Sum(x)
    opt.minimize(total_presses)
    
    # Solve
    if opt.check() == sat:
        model = opt.model()
        result = sum(model[x[i]].as_long() for i in range(n_buttons))
        return result
    else:
        print("No solution found!")
        return 0

def main():
    with open('input', 'r') as f:
        lines = f.readlines()
    
    total = 0
    for idx, line in enumerate(lines):
        if not line.strip():
            continue
        
        indicator, buttons, joltage = parse_line(line)
        
        print(f"Machine #{idx}")
        result = solve_machine_z3(buttons, joltage)
        print(f"  Result: {result}")
        total += result
    
    print(f"\nPart 2: {total}")

if __name__ == "__main__":
    main()
