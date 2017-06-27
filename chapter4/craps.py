from microbit import *

import random
random.seed()

def roll_dice():
    a = random.randint(1, 6)
    b = random.randint(1, 6)
    numbers = [str(a), str(b)]
    return numbers
    
def roll_seven():
    a = 4
    b = 3
    numbers = [str(a), str(b)]
    return numbers
    
def roll_eight():
    a = 5
    b = 3
    numbers = [str(a), str(b)]
    return numbers
    
def show_roll(dice):
    for i in range(0, len(dice)):
        display.clear()
        display.show(dice[i])
        sleep(1000)
    display.show(Image.YES)
    
display.show(Image.YES)

while True:
    if not accelerometer.was_gesture("shake"):
        continue
    if button_a.is_pressed():
        roll = roll_seven()
        show_roll(roll)
        continue
    if button_b.is_pressed():
        roll = roll_eight()
        show_roll(roll)
        continue
    roll = roll_dice()
    show_roll(roll)
    
