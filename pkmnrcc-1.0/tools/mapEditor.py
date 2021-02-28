#!/usr/bin/python3.6
import subprocess
import sys
import pyglet
from pyglet.gl import *
from pyglet.window import mouse
from pyglet.image.codecs.png import PNGImageDecoder
from PIL import Image

###############################################################################
## Return width and height of screen resolution
###############################################################################
def get_screen_res():
    cmd = ['xrandr']
    cmd2 = ['grep', '*']
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    p2 = subprocess.Popen(cmd2, stdin=p.stdout, stdout=subprocess.PIPE)
    p.stdout.close()
    resolution_string, junk = p2.communicate()
    resolution = resolution_string.split()[0]
    resolution = resolution.decode("utf-8")
    width, height = resolution.split('x')
    return width,height

###############################################################################
## Constants and global variables
###############################################################################
TILE_SIZE = 32
FILE_TO_SAVE = './saved'
SAVED = False # at q pressure check if 'w' is been pressed, means the map has been saved
if sys.argv and len(sys.argv) > 1:
    FILE_TO_SAVE = sys.argv[1]

isAccessible = True
CHECKBOX_CHECKED_IMAGE = pyglet.image.load('../assets/images/small-checkbox-checked.png')
CHECKBOX_UNCHECKED_IMAGE = pyglet.image.load('../assets/images/small-checkbox.png')
TILE_IMAGE = pyglet.image.load('../assets/images/tiles.png')
HR_IMAGE = pyglet.image.load('../assets/images/hr.png')
W = 24;
H = 25;
selected_tile_x = 0
selected_tile_y = 0

###############################################################################
## Define the 2D array that stores each tile coordinate
###############################################################################
class Point2D:
    x = 0
    y = 0

class Point1D:
    x = 0

Matrix = [[Point2D() for x in range(H)] for y in range(W)]
MatrixAccessibility = [[Point1D() for x in range(H)] for y in range(W)]

###############################################################################
## Populate the 2D arrays with empty tile values and default accessibility
###############################################################################
for i in range(W):
    for j in range(H - 1):
        Matrix[i][j].x = -1
        Matrix[i][j].y = -1
        MatrixAccessibility[i][j].x = 0

###############################################################################
## Renders the main program window
###############################################################################
window = pyglet.window.Window(caption='Tilemap Editor', width=768, height=896)
window.set_icon(pyglet.image.load('../assets/images/iconEditor.png'))
width, height = get_screen_res()
window.set_location(int((int(width) - 768)/2),int((int(height) - 896)/2))
cursor = window.get_system_mouse_cursor(window.CURSOR_HAND)
window.set_mouse_cursor(cursor)
pyglet.gl.glClearColor(0.1, 0.1, 0.1, 1)

###############################################################################
## Display the tiles that can be clicked to change the current selected tile
###############################################################################
def draw_tile_map_selector():
    HR_IMAGE.blit(0, 0)
    TILE_IMAGE.blit(0, 0)
    selected_tile_part = TILE_IMAGE.get_region(
        x=selected_tile_x * TILE_SIZE,
        y=selected_tile_y * TILE_SIZE,
        width=TILE_SIZE,
        height=TILE_SIZE
    )
    selected_tile_part.blit(365, 37)
    if isAccessible:
        CHECKBOX_UNCHECKED_IMAGE.blit(340, 93)
    else:
        CHECKBOX_CHECKED_IMAGE.blit(340, 93)

###############################################################################
## Draw UI labels and text
###############################################################################
def draw_ui_label():
    label_isAccessible = pyglet.text.Label(
        'isNotAccessible',
        font_name='Hermit',
        font_size=8,
        x=354,
        y=93,
        anchor_x='left',
        anchor_y='bottom'
    )
    label_title = pyglet.text.Label(
        'TILEMAP EDITOR',
        font_name='Hermit',
        font_size=10,
        x=460,
        y=85,
        anchor_x='left',
        anchor_y='bottom'
    )
    label_1 = pyglet.text.Label(
        '1. click one of the tiles to select',
        font_name='Hermit',
        font_size=10,
        x=460,
        y=60,
        anchor_x='left',
        anchor_y='bottom'
    )
    label_2 = pyglet.text.Label(
        '2. use the mouse to draw on the map',
        font_name='Hermit',
        font_size=10,
        x=460,
        y=45,
        anchor_x='left',
        anchor_y='bottom'
    )
    label_3 = pyglet.text.Label(
        '3. press "w" to write the map file',
        font_name='Hermit',
        font_size=10,
        x=460,
        y=30,
        anchor_x='left',
        anchor_y='bottom'
    )
    label_4 = pyglet.text.Label(
        '4. press "q" to quit the editor',
        font_name='Hermit',
        font_size=10,
        x=460,
        y=15,
        anchor_x='left',
        anchor_y='bottom'
    )
    label_title.draw()
    label_1.draw()
    label_2.draw()
    label_3.draw()
    label_4.draw()
    label_isAccessible.draw()

###############################################################################
## Saves the currently selected tile in the 2D array
###############################################################################
def save_tile_in_array(x, y):
    global selected_tile_x
    global selected_tile_y
    if x >= 0 and x <= 320 and y >= 0 and y < 96:
        if y >= 0 and y < TILE_SIZE:
            selected_tile_x = x // TILE_SIZE
            selected_tile_y = 0
        if y >= TILE_SIZE and y < 64:
            selected_tile_x = x // TILE_SIZE
            selected_tile_y = 1
        if y >= 64 and y < 96:
            selected_tile_x = x // TILE_SIZE
            selected_tile_y = 2
    if x >= 0 and x <= 768 and y >= 128 and y <= 896:
        target_x = x // TILE_SIZE
        target_y = (896 - y) // TILE_SIZE
        p_2d = Point2D()
        p_2d.x = selected_tile_x
        p_2d.y = selected_tile_y
        if target_x >= 0 and target_x < W and target_y >= 0 and target_y < H-1:
            #print(f'target_x = {target_x} , target_y = {target_y}')
            Matrix[target_x][target_y] = p_2d
        valAccessibility = 1
        if isAccessible:
            valAccessibility = 0
        if target_x >= 0 and target_x < W and target_y >= 0 and target_y < H-1:
            #print(f'target_x = {target_x} , target_y = {target_y}')
            MatrixAccessibility[target_x][target_y].x = valAccessibility

###############################################################################
## Loop the array and draw each selected tile in the screen
###############################################################################
def draw_array_of_selected_tiles():
    for i in range(W):
        for j in range(H - 1):
            target_tile_x = Matrix[i][j].x
            target_tile_y = Matrix[i][j].y
            target_pixel_x = i * TILE_SIZE
            target_pixel_y = 896 - j * TILE_SIZE
            if target_tile_x != -1 and target_tile_y != -1:
                current_tile_part = TILE_IMAGE.get_region(
                    x=target_tile_x * TILE_SIZE,
                    y=target_tile_y * TILE_SIZE,
                    width=TILE_SIZE,
                    height=TILE_SIZE
                )
                current_tile_part.blit(target_pixel_x, target_pixel_y - 32)

###############################################################################
## Save the selected tiles in a file
###############################################################################
def save_array_to_file():
    image_sheet = Image.new("RGBA", (32*24, 32*24))
    for j in range(H - 1):
        for i in range(W):
            x_value_to_save = Matrix[i][j].x
            y_value_to_save = Matrix[i][j].y
            if x_value_to_save == -1:
                x_value_to_save = 0
            if y_value_to_save == -1:
                y_value_to_save = 0
            reg = TILE_IMAGE.get_region( x_value_to_save * 32, y_value_to_save * 32, 32, 32)
            rawimage = reg.get_image_data() 
            format = 'RGBA'
            pitch = rawimage.width * len(format)
            pixels = rawimage.get_data(format, pitch)
            reg_Image = Image.frombuffer("RGBA", (32, 32), pixels, 'raw', 'RGBA', 0, 1)
            reg_Image = reg_Image.rotate(180)
            image_sheet.paste(reg_Image, ( int(i * 32), int(j * 32))) 
    image_sheet.save(FILE_TO_SAVE + ".png")

    with open(FILE_TO_SAVE + '.map', 'w') as file:
        for j in range(H - 1):
            for i in range(W):
                valAccessibility = MatrixAccessibility[i][j].x
                file.write(str(valAccessibility) + str('  '))
            file.write('\n')
    
    global SAVED
    SAVED = True


###############################################################################
## Event listener on key press
###############################################################################
@window.event
def on_key_press(symbol, modifiers):
    if symbol == 119:
        save_array_to_file()
    if symbol == 113:
        global SAVED
        if SAVED == True:
            exit()
        else:
            exit(1)

###############################################################################
## Event listener on mouse press
###############################################################################
@window.event
def on_mouse_press(x, y, buttons, modifiers):
    if (x >= 0 and x <= 768 and y >= 128 and y <= 896) or (x >= 0 and x <= 320 and y >= 0 and y <= 96):
        save_tile_in_array(x, y)
    global isAccessible
    if x >= 340 and x <= 352 and y >= 93 and y <= 105:
        isAccessible = not isAccessible

###############################################################################
## Event listener on mouse drag
###############################################################################
@window.event
def on_mouse_drag(x, y, dx, dy, buttons, modifiers):
    if x >= 0 and x <= 768 and y >= 128 and y <= 896:
        #print(f'x={x} , y={y}')
        save_tile_in_array(x, y)

###############################################################################
## Render loop
###############################################################################
@window.event
def on_draw():
    window.clear()
    draw_tile_map_selector()
    draw_array_of_selected_tiles()
    draw_ui_label()

###############################################################################
## Triggers graphics app execution
###############################################################################
pyglet.app.run()
