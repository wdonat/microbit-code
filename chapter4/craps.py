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
    for i in range(0, 2):
        display.show(dice[0])
        sleep(1000)
        display.clear()
        display.show(dice[1])
        sleep(1000)

while True:
 
    display.show(Image.YES)
    if accelerometer.was_gesture("shake") and button_a.is_pressed():
        display.clear()
        sleep(500)
        roll = roll_seven()
        show_roll(roll)
 
    elif accelerometer.was_gesture("shake") and button_b.is_pressed():
        display.clear()
        sleep(500)
        roll = roll_eight()
        show_roll(roll)
 
    elif accelerometer.was_gesture("shake"):
        display.clear()
        sleep(500)
        roll = roll_dice()
        show_roll(roll)
 
    sleep(1000)
