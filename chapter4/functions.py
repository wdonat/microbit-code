from microbit import *
 
compass.calibrate()

def iterate_thru():
    display.show(Image.ALL_ARROWS)
    display.clear()
    display.scroll("Press A")
    while not button_a.is_pressed(): # see text
        continue
    display.show(Image.ARROW_W) # see text
    sleep(1000)
    display.scroll("Press B")
    while not button_b.is_pressed(): # see text
        continue
    display.show(Image.ARROW_E) # see text
    sleep(1000)
    display.clear()
    x = str(accelerometer.get_x())
    y = str(accelerometer.get_y())
    z = str(accelerometer.get_z())
    a = x + " " + y + " " + z # see text
    display.show(a)
    sleep(1000)
    display.clear()
    display.scroll(str(compass.heading()))
    sleep(1000)
    if accelerometer.is_gesture("face up"):
        display.show(Image.HAPPY)
    return

while True:
    display.clear()
    if button_a.is_pressed():
        iterate_thru()
