import pygame
import random
import time
import os

# Class which create characters and NPCs.
#
# screen : surface, the main screen
# background : surface, background
# position : tuple, coordinates of the top-left pixel of the character
# x : int, position[0], y : int, position[1]
# load : list, [0]: main path of the character's image used to update the image,
#              [1]: path used to load the image, composed with [0] + [2]
#              [2]: suffix of the image,
#              [3]: orientation of the character
# colorkey : tuple, color key of the background of the image
# dx : int, amount of pixels travelled on the x_axis when the character moves (like a speed)
# dy : int, amount of pixels travelled on the y_axis when the character moves (like a speed)
# text : Font, font of all text
# color_wall : tuple, color of the walls
# lifebar : Lifebar, livebar of the character
# timer : int, timer used for the respawn
# alive : boolean, indicate if the character is dead or alive
# side : str, allegiance of the character
# spells : Spells, list of the spells of the character
# hitbox : tuple, rectangle of the hitbox of the character
# ways : list, list of the different moving ways possible (used for NPC)
# way : str, current moving way of the character
# timer_NPC : int, timer used for the moves of NPCs
# distance : int, distance (in pixel) of a NPC's move
# waitime : int, time between two moves of a NPC

class Character(pygame.sprite.Sprite):
    """
    Constructor.

    :param screen: screen of the game
    :type screen: surface

    :param background: background of the screen
    :type background: surface

    :param load: path of the image of the character
    :type load: str

    :param colorkey: color key of the image's background (default (0,0,0))
    :type colorkey: tuple

    :param coordinates: coordinate of the top-left pixel of the character (default (100,100))
    :type coordinates: tuple

    :param side: allegiance of the character (between [light, darkness, neutral], default neutral)
    :type side: str
    """
    def __init__(self, screen, background, load, colorkey=(0,0,0), coordinates=(100,100), side='neutral'):
        self.screen = screen
        self.background = background
        self.background_color = (20,20,20)
        self.position = self.x, self.y = coordinates
        self.load = [load, load+'_Right.png','_Right.png', 'Right']
        self.colorkey = colorkey
        self.dx, self.dy = 10, 10
        self.text = pygame.font.SysFont('mono', 60, bold=True)
        self.color_wall = (20,0,50)
        self.lifebar = Lifebar(self.screen, self.position, self.color_wall, self.dx, self.dy)
        self.timer = 0
        self.alive = True
        self.side = side
        self.spells = Spells(self.screen, self.background_color, self.side, self.x, self.y)
        self.hitbox = (self.x, self.y, 88, 116)
        self.ways = ['left', 'right', 'up', 'down']
        self.way = None
        self.timer_NPC = 0
        self.distance = 120
        self.waitime = 0

    """
    Function that handles the moves of NPCs
    The NPC moves a distance and wait
    for a time both generated randomly
    """
    def draw_NPC(self):
        # Generates a random way
        if self.timer_NPC == 0:
            self.way = self.ways[random.randint(0,3)]
            self.distance = random.randint(80,200)
        # Moves the NPC in the way generated
        self.motion_NPC(self.way)
        # Display the NPC
        self.display()
        # Update the hitbox position
        self.hitbox = (self.x, self.y, 88, 116)
        # Update the position
        self.spells.position = self.spells.x, self.spells.y = self.x, self.y
        # Update the orientation
        self.spells.orientation = self.load[3]
        # Display the spell if one is cast (very unlikely)
        self.spells.display()
        # Update lifebar position and display it
        self.lifebar.position = self.lifebar.x, self.lifebar.y = self.position
        self.lifebar.path_character = self.load
        self.lifebar.run_life()
        # Load the animation if the character is hit
        if self.load[1] == self.load[0]+'_Hit.png':
            self.load[1] = self.load[0]+self.load[2]
        # Respawn the NPC if he is dead and if the timer is up
        if not(self.alive) and self.timer < 150:
            self.timer+=1
        elif not(self.alive) and self.timer == 150:
            self.respawn()
            self.timer = 0
        self.timer_NPC += 1
        # Stop the character when he moved the distance generated
        if self.timer_NPC == self.distance:
            self.way = None
            self.waitime = random.randint(200,400)
        # Wait before moving again
        if self.timer_NPC == self.distance+self.waitime:
            self.timer_NPC = 0

    """
    Function that display the characterand allows player to move his/her character.

    :param way: Way toward the player wants to move, generated with keyboard event
    :type way: str

    :param maze: Maze object required to check if the player gets out of the Maze
    :type maze: Maze
    """
    def draw_motion(self, way, maze):
        # Moves the character
        self.motion_keys(way)
        # Display the character
        self.display()
        # Update the hitbox position
        self.hitbox = (self.x, self.y, 88, 116)
        # Update the position
        self.spells.position = self.spells.x, self.spells.y = self.x, self.y
        # Update the orientation
        self.spells.orientation = self.load[3]
        # Display the spell if one is cast
        self.spells.display()
        # Update lifebar position and display it
        self.lifebar.position = self.lifebar.x, self.lifebar.y = self.position
        self.lifebar.path_character = self.load
        self.lifebar.run_life()
        # Load the animation if the character is hit
        if self.load[1] == self.load[0]+'_Hit.png':
            self.load[1] = self.load[0]+self.load[2]
        # Respawn the NPC if he is dead and if the timer is up
        if not(self.alive) and self.timer < 150:
            self.timer+=1
        elif not(self.alive) and self.timer == 150:
            self.respawn()
            self.timer = 0
        # Return false if the character gets out of the Maze
        result = self.blocks(maze)
        if result == None:
            result = True
        return result

    """
    Function that loads character's image
    """
    def display(self):
        image = pygame.image.load(self.load[1])
        image.set_colorkey(self.colorkey)
        image.convert_alpha()
        self.screen.blit(image, (self.position))

    """
    Function that moves the character toward the way generated with keyboard event
    For each way, the fonction does the same things, according the way.

    :param way: way chosed by the player
    :type way: str
    """
    def motion_keys(self, way):
        # If the character is alive
        if self.alive:
            if way == 'left':
                # Check if the character won't get out of the screen if it moves left
                if self.x-self.dx >= 0:
                    # List of pixels : the top-left one, the middle-left one and the bottom-left one (all shifted by self.dx on the left)
                    pixels = [(self.x-self.dx,self.y),(self.x-self.dx,self.y+29), (self.x-self.dx,self.y+58), (self.x-self.dx,self.y+87), (self.x-self.dx,self.y+116)]
                    wall = False
                    # If one of these pixels has the color of a wall, it means the character will hit a wall
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    # If the character doesn't it a wall, it can be moved
                    if not(wall):
                        self.x -= self.dx
                # If the character is casting a spell, it cannot turn over.
                # Otherwise, it oriented itself toward the way
                if not(self.spells.lock):
                    self.load[3] = 'Left'
                    self.load[2] = '_Left.png'
                    self.load[1] = self.load[0]+self.load[2]
                # Set way to None to make the character moves only one time by event
                way = None
            elif way == 'right':
                # Check if the character won't get out of the screen if it moves right, and ...
                if self.x+self.dx <= self.screen.get_size()[0]-108:
                    pixels = [(self.x+self.dx+88,self.y), (self.x+self.dx+88,self.y+29),(self.x+self.dx+88,self.y+58), (self.x+self.dx+88,self.y+87), (self.x+self.dx+88,self.y+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.x += self.dx
                if not(self.spells.lock):
                    self.load[3] = 'Right'
                    self.load[2] = '_Right.png'
                    self.load[1] = self.load[0]+self.load[2]
                way = None
                # Check if the character won't get out of the screen if it moves up, and ...
            elif way == 'up':
                if self.y-self.dy >= 0:
                    pixels = [(self.x,self.y-self.dy), (self.x+44,self.y-self.dy), (self.x+88,self.y-self.dy)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.y -= self.dy
                way = None
                # Check if the character won't get out of the screen if it moves down, and ...
            elif way == 'down':
                if self.y+self.dy <= self.screen.get_size()[1]-116:
                    pixels = [(self.x,self.y+self.dy+116), (self.x+44,self.y+self.dy+116), (self.x+88,self.y+self.dy+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.y += self.dy
                way = None

    """
    Function that changes the Maze's levels in function of the blocks
    on which the character walks.

    :param maze: Maze object required to display the levels
    :type maze: Maze
    """
    def blocks(self, maze):
        # If the character walks on a next level block (red one)
        if maze.background.get_at((self.x+44,self.y+87)) == (255,50,50):
            # Check if the current level is not the last one and, if so, blits the next one
            if maze.start[1]+1 < maze.max_level:
                maze.start[1] +=1
                maze.start[0] = maze.levels[maze.start[1]]
            # If it is the last, blits back the first level
            else:
                maze.start[1] = 0
                maze.start[0] = maze.levels[0]
            maze.start_position = maze.x, maze.y = self.x, self.y = maze.addlevel(maze.start[0])[5]
        # If the character walks on a random block (blue one)
        elif maze.background.get_at((self.x+44,self.y+87)) == (0,0,200):
            # Blits a random level
            maze.start[1] = random.randint(0,maze.max_level-1)
            maze.start[0] = maze.levels[maze.start[1]]
            maze.start_position = maze.x, maze.y = self.x, self.y = maze.addlevel(maze.start[0])[5]
            self.screen.blit(self.background, (0,0))
        # If the character walks on a end block (grey one)
        elif maze.background.get_at((self.x+44,self.y+87)) == (100,100,100):
            # Display "Congrats Screen"
            maze.background.fill((0,0,0))
            text = "GG le sang, t'es sorti."
            self.text.size(text)
            surface = self.text.render(text, True, (255,255,254))
            self.screen.blit(maze.background, (0,0))
            self.screen.blit(surface, (self.screen.get_size()[0]/4, 2*self.screen.get_size()[1]/5))
            # Return False to close the game window
            return False
        # If the character walks on a previous level block (magenta one)
        elif maze.background.get_at((self.x+44,self.y+87)) == (255,50,255):
            # Check if the current level is not the first one and, if so, blits the next one
            if maze.start[1]-1 >= 0:
                maze.start[1] -=1
                maze.start[0] = maze.levels[maze.start[1]]
            # If it is the First, set the character back to the start position
            else:
                maze.start[1] = 0
                maze.start[0] = maze.levels[0]
            maze.start_position = maze.x, maze.y = self.x, self.y = maze.addlevel(maze.start[0])[5]
            self.screen.blit(self.background, (0,0))
        # Upgrade the position of the characterway
        self.position = (self.x, self.y)

    """
    Function that moves the NPCs. Same function as the "draw_motion" function
    except that it moves only one pixel by one pixel instead of ten by ten.

    :param way: way in which the NPC has to move
    :type way: str
    """
    def motion_NPC(self, way):
        if self.alive:
            if self.way == 'left':
                if self.x-1 >= 0:
                    pixels = [(self.x-1,self.y),(self.x-1,self.y+29), (self.x-1,self.y+58), (self.x-1,self.y+87), (self.x-1,self.y+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.x -= 1
                if not(self.spells.lock):
                    self.load[3] = 'Left'
                    self.load[2] = '_Left.png'
                    self.load[1] = self.load[0]+self.load[2]
            elif self.way == 'right':
                if self.x+1 <= self.screen.get_size()[0]-108:
                    pixels = [(self.x+1+88,self.y), (self.x+1+88,self.y+29),(self.x+1+88,self.y+58), (self.x+1+88,self.y+87), (self.x+1+88,self.y+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.x += 1
                if not(self.spells.lock):
                    self.load[3] = 'Right'
                    self.load[2] = '_Right.png'
                    self.load[1] = self.load[0]+self.load[2]
            elif self.way == 'up':
                if self.y-1 >= 0:
                    pixels = [(self.x,self.y-1), (self.x+44,self.y-1), (self.x+88,self.y-1)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.y -= 1
            elif self.way == 'down':
                if self.y+1 < self.screen.get_size()[1]-116:
                    pixels = [(self.x,self.y+1+116), (self.x+44,self.y+1+116), (self.x+88,self.y+1+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.y += 1

    """
    Function that his called when the lifepoint goes to 0. Display
    the death image of the character.
    """
    def death(self):
        # Blit death image of the character depending on its orientation
        if self.load[2] == '_Right.png':
            self.position = self.x, self.y = self.x-30, self.y
            self.load[2] = '_Right_Dead.png'
            self.load[1] = self.load[0]+self.load[2]
        elif self.load[2] == '_Left.png':
            self.position = self.x, self.y = self.x+20, self.y
            self.load[2] = '_Left_Dead.png'
            self.load[1] = self.load[0]+self.load[2]
        self.alive = False

    """
    Function which follows the "death" function and set back, after a short
    time (~ 2 seconds), its 'normal' image depending on its orientation
    """
    def respawn(self):
        self.alive = True
        if self.load[2] == '_Left_Dead.png':
            self.load[3] = 'Left'
            self.load[2] == '_Left.png'
            self.load[1] = self.load[0]+self.load[2]
            self.lifebar.percentage = 100
            self.motion_keys('left')
        elif self.load[2] == '_Right_Dead.png':
            self.load[3] = 'Right'
            self.load[2] == '_Right.png'
            self.load[1] = self.load[0]+self.load[2]
            self.lifebar.percentage = 100
            self.motion_keys('right')

    """
    Function that display the 'hit' animation of the character when he is
    hit by something (a spell for now)
    """
    def get_hit(self):
        if not(self.spells.protected) and self.alive:
            self.load[1] = self.load[0]+'_Hit.png'
            if self.lifebar.percentage > 10:
                self.lifebar.percentage -= 10
            elif self.lifebar.percentage <= 10:
                if self.alive:
                    self.lifebar.percentage = 0
                    self.death()

# Class which create and display the lifebar of the character object
#
# screen : surface, the main screen
# position : tuple, coordinates of the top-left pixel of the character (not the lifebar)
# x : int, position[0], y : int, position[1]
# color_wall : tuple, color of the walls
# path : list, [0]: path used to load the image, composed with [1] and a suffix which match with the current lifepoints
#              [1]: main path of the lifebar's image used to update the image
# image : surface, current image of the lifebar
# percentage : int, percentage of lifepoints
# position_life : tuple, actual coordinates of the lifebar
# dx : int, amount of pixels travelled on the x_axis when the character moves (like a speed),
# dy : int, amount of pixels travelled on the y_axis when the character moves (like a speed)

class Lifebar(Character):
    """
    Constructor.

    :param screen: screen given by the character (the main screen in fact)
    :type screen: surface

    :param position: coordinates of the top-left pixel of the character
    :type position: tuple

    :param color_wall: color of the wall on the screen
    :type color_wall: tuple

    :param dx: dx given by the character
    :type dx: int

    :param dy: dy given by the character
    :type dy: int
    """
    def __init__(self, screen, position, color_wall, dx, dy):
        self.screen = screen
        self.position = self.x, self.y = position
        self.color_wall = color_wall
        self.path = [os.path.join("Wizarding_Game\\Image\\120x120\\Lifebar\\100.png"), os.path.join("Wizarding_Game\\Image\\120x120\\Lifebar\\")]
        self.image = pygame.image.load(self.path[0])
        self.percentage = 100
        self.position_life = self.x_life, self.y_life = 0,0
        self.dx, self.dy = dx, dy

    """
    Function that updates the position of the lifebar when the character moves and
    display it. If the lifebar hit a wall or get out the screen, it blits the 'alpha'
    image, which is a fully transparent image, to prevent the lifebar to be inside a
    wall or outside the screen coordinates
    """
    def set_position_life(self):
        # Check if the lifebar will still be inside the screen surface
        if (0 > self.x-5 > self.screen.get_size()[0]) or (0 > self.y-20 > self.screen.get_size()[1]):
            self.path[0] = self.path[1]+"alpha.png"
            self.position_life = self.x_life, self.y_life = 0, 0
        # Check if the lifebar will not hit a wall from the top
        elif self.screen.get_at((self.x-5, self.y-20)) == self.color_wall or self.screen.get_at((self.x+98, self.y-20)) == self.color_wall:
            self.path[0] = self.path[1]+"alpha.png"
            self.position_life = self.x_life, self.y_life = 0, 0
        # Check if the lifebar will not hit a wall from the bottom
        elif self.screen.get_at((self.x-5, self.y-10)) == self.color_wall or self.screen.get_at((self.x+98, self.y-10)) == self.color_wall:
            self.path[0] = self.path[1]+"alpha.png"
            self.position_life = self.x_life, self.y_life = 0, 0
        # If everything is fine, blits the lifebar 10 pixel over the character (it is a 102 x 10 image)
        elif self.screen.get_at((self.x-5, self.y-20)) != self.color_wall and self.screen.get_at((self.x+98, self.y-20)) != self.color_wall:
                self.path[0] = self.path[1]+str(self.percentage)+".png"
        self.position_life = self.x_life, self.y_life = self.x-5, self.y-20

    """
    Function that displays the image loaded in the previous function at
    the position of the lifebar
    """
    def display(self):
        self.image = pygame.image.load(self.path[0])
        self.image.set_colorkey((0,0,0))
        self.image.convert_alpha()
        self.screen.blit(self.image, self.position_life)

    """
    Function that runs the two previous functions
    """
    def run_life(self):
        self.set_position_life()
        self.display()



class Spells(Character):
    """
    Constructor.

    :param :
    :type :

    :param :
    :type :

    :param :
    :type :

    :param :
    :type :

    :param :
    :type :
    """
    def __init__(self, screen, background_color, side, x, y):
        self.screen = screen
        self.background = pygame.Surface((self.screen.get_size())).convert()
        self.background_color = background_color
        self.background.fill(self.background_color)
        self.side = side
        self.spells = {self.offensive():{'Left':[], 'Right':[], 'Both':[]}, self.defensive():{'Left':[], 'Right':[], 'Both':[]}, self.stunning():{'Left':[], 'Right':[], 'Both':[]}, self.disappartition():{'Left':[], 'Right':[], 'Both':[]}, self.light():{'Left':[], 'Right':[], 'Both':[]}, self.metamorphosis():{'Left':[], 'Right':[], 'Both':[]}}
        self.position = self.x, self.y = x, y
        self.position_spell = self.x_spell, self.y_spell = None, None
        self.orientation = None
        self.color_key = (63,72,204)
        self.animation, self.animation_both = None, None
        self.cleanup = pygame.Surface((21,7)).convert()
        self.cleanup.fill(self.background_color)
        self.index_animation = 0
        self.animation_progress = 0
        self.position_attack = None
        self.path_spell = None
        self.running = False
        self.clock = pygame.time.Clock()
        self.cycletime = 0
        self.interval = 0.05
        self.lock = False
        self.lock_spells = [False,False,False,False,False,False]
        self.number = None
        self.eraser = pygame.Surface((78,101)).convert()
        self.eraser.fill(self.background_color)
        self.protected = False
        self.hit_someone = False

        self.path()

    """
    """
    def offensive(self):
        offensive_spell = None
        if self.side == 'darkness':
            offensive_spell = 'Avada_Kedavra'
        elif self.side == 'light':
            offensive_spell = 'Expelliarmus'
        elif self.side == 'neutral':
            offensive_spell = 'Confringo'
        return offensive_spell

    """
    """
    def defensive(self):
        defensive_spell = None
        if self.side == 'darkness':
            defensive_spell = 'Spero_Patronum'
        elif self.side == 'light':
            defensive_spell = 'Protego'
        elif self.side == 'neutral':
            defensive_spell = 'Shieldero'
        return defensive_spell

    """
    """
    def stunning(self):
        stunning_spell = None
        if self.side == 'darkness':
            stunning_spell = 'Crucio'
        elif self.side == 'light':
            stunning_spell = 'Stupefy'
        elif self.side == 'neutral':
            stunning_spell = 'Petrificus_Totalus'
        return stunning_spell

    """
    """
    def disappartition(self):
        disappartition_spell = None
        if self.side == 'darkness':
            disappartition_spell = 'Dark_Trail'
        elif self.side == 'light':
            disappartition_spell = 'Light_Trail'
        elif self.side == 'neutral':
            disappartition_spell = 'Disappartition'
        return disappartition_spell

    """
    """
    def light(self):
        light_spell = 'Lumos'
        return light_spell

    """
    """
    def metamorphosis(self):
        metamorphosis_spell = None
        if self.side == 'darkness':
            metamorphosis_spell = 'Serpent_Sortia'
        elif self.side == 'light':
            metamorphosis_spell = 'Phoenix_Sortia'
        elif self.side == 'neutral':
            metamorphosis_spell = 'Wolf_Sortia'
        return metamorphosis_spell

    """
    Update and set the dictionnary containing every path needed for
    the animation of each spell
    """
    def path(self):
        # Name of every image needed for the animation, different between left and right.
        animation = ["First","Second","Third","Fourth","Fifth","Sixth","Seventh","Fifth","Fourth","Third","Second","First"]
        # Name of every image needed for the animation, identical in both ways
        both = ["Beginning_End", "Traveling", "Alpha"]
        for spell in self.spells:
            for image in animation:
                self.spells[spell]['Left'].append(os.path.join("Wizarding_Game","Image","120x120","Spells",spell,image+"_Left.png"))
                self.spells[spell]['Right'].append(os.path.join("Wizarding_Game","Image","120x120","Spells",spell,image+"_Right.png"))
            for image in both:
                self.spells[spell]['Both'].append(os.path.join("Wizarding_Game","Image","120x120","Spells",spell,image+".png"))

    """
    """
    def which_spell(self):
        keys = list(self.spells.keys())
        return self.spells[keys[self.number-1]]

    """
    """
    def set_animation(self):
        # Charges every images required for animation, depending on the orientation of the character
        animation = []
        if self.orientation == 'Left':
            if self.number == 1 or self.number == 3:
                self.position_spell = self.x_spell, self.y_spell = self.x-72, self.y+42
                self.position_attack = self.x_spell-13, self.y_spell+15 # self.x_spell -21(length of the attack) + 8(empty area of the Seventh image), self.y_spell +15(wand's top position)
            elif self.number == 2:
                self.position_spell = self.x_spell, self.y_spell = self.x-72, self.y+6
            for image in self.path_spell['Left']:
                try:
                    animation.append(pygame.image.load(os.path.join(image)))
                except:
                    print("Error, can't find the file '"+image+"' \nPlease, make sure you wrote the right path.")
        elif self.orientation == 'Right':
            if self.number == 1 or self.number == 3:
                self.position_spell = self.x_spell, self.y_spell = self.x+72, self.y+42
                self.position_attack = self.x_spell+78, self.y_spell+15 # self.x_spell +88(length of the character) - 8 or 10 (empty area of the Seventh image), self.y_spell +15(wand's top position)
            elif self.number == 2:
                self.position_spell = self.x_spell, self.y_spell = self.x+82, self.y+6
            for image in self.path_spell['Right']:
                try:
                    animation.append(pygame.image.load(os.path.join(image)))
                except:
                    raise UserWarning("Error, can't find the file '"+image+"' \nPlease, make sure you wrote the right path.")
        for image in range (len(animation)):
           animation[image].set_colorkey(self.color_key)
           animation[image] = animation[image].convert_alpha()

        # Charges every images required for animation, which will be usefull for both orientation
        animation_both = []
        if self.number == 1 or self.number == 3:
            for image in self.path_spell['Both']:
                try:
                    animation_both.append(pygame.image.load(os.path.join(image)))
                except:
                    raise UserWarning("Error, can't find the file '"+image+"' \nPlease, make sure you wrote the right path.")
            for image in range (len(animation_both)):
               animation_both[image].set_colorkey(self.color_key)
               animation_both[image] = animation_both[image].convert_alpha()
        elif self.number == 2:
            try:
                animation_both.append(pygame.image.load(os.path.join(self.path_spell['Both'][-1])))
            except:
                raise UserWarning("Error, can't find the file '"+self.path_spell['Both'][-1]+"' \nPlease, make sure you wrote the right path.")
            animation_both[0].set_colorkey(self.color_key)
            animation_both[0] = animation_both[0].convert_alpha()

        return animation, animation_both

    """
    Display the animation
    """
    def display(self):
        milliseconds = self.clock.tick(60)  # Milliseconds passed since last frame
        seconds = milliseconds / 1000.0 # Seconds passed since last frame (float)
        self.cycletime += seconds
        #
        # 1st spell
        #
        if self.number == 1 and self.lock_spells[1] == False and self.lock_spells[2] == False and self.lock_spells[3] == False and self.lock_spells[4] == False and self.lock_spells[5] == False:
            if self.animation and self.index_animation <= len(self.animation)-6:
                if self.orientation == 'Left':
                    self.position_attack = self.x_spell-13, self.y_spell+15
                elif self.orientation == 'Right':
                    self.position_attack = self.x_spell+78, self.y_spell+15 # self.x_spell +88(length of the character) - 8 or 10 (empty area of the Seventh image), self.y_spell +15(wand's top position)
            # Beginning of the animation on the wand
            if self.running and self.index_animation < len(self.animation):
                    if self.orientation == 'Left':
                        self.position_spell = self.x_spell, self.y_spell = self.x-72, self.y+42
                    elif self.orientation == 'Right':
                        self.position_spell = self.x_spell, self.y_spell = self.x+72, self.y+42
                    self.lock = True
                    mypicture = self.animation[self.index_animation]
                    self.screen.blit(mypicture, self.position_spell)# -71 +42 par rapport au personnage
            # Beginning of the traveling part
            if self.running and self.index_animation > len(self.animation)-6:
                # First frame
                if self.orientation == 'Left':
                    if self.animation_progress == 0:
                        self.animation_progress += 1 # Juste utile pour la premiere apparition de l'attaque
                        if self.position_attack[0]-42 > 0: # 2 times the length of the attack image (for remanence)
                            self.screen.blit(self.animation_both[0], self.position_attack) # Displays the "Beginning_End" image
                            self.position_attack = (self.position_attack[0]-21, self.position_attack[1]) # Upgrading position_attack
                    # Other frame
                    elif self.animation_progress > 0:
                        if self.position_attack[0]-42 >= 0:
                            self.screen.blit(self.animation_both[1], self.position_attack) # Displays the "Traveling" image
                            self.position_attack = (self.position_attack[0]-21, self.position_attack[1])
                        elif self.position_attack[0]-21 > 0: # If it goes through this, it means it is the last frame of the animation
                            self.screen.blit(self.animation_both[0], self.position_attack)
                            self.screen.blit(self.cleanup, (self.position_attack[0]+42, self.position_attack[1]))
                            self.screen.blit(self.cleanup, (self.position_attack[0]+21, self.position_attack[1]))
                            self.position_attack = (self.position_attack[0]-21, self.position_attack[1])
                        # Last frame
                        else:
                            self.screen.blit(self.animation_both[2], (0,0)) # Displays the "Alpha" image. End of animation
                            self.screen.blit(self.cleanup, (self.position_attack[0]+21, self.position_attack[1]))
                            self.animation_progress = 'done'
                elif self.orientation == 'Right':
                    if self.animation_progress == 0:
                        self.animation_progress += 1 # Juste utile pour la premiere apparition de l'attaque
                        if self.position_attack[0]+42 < self.screen.get_size()[0]: # 2 times the length of the attack image (for remanence)
                            self.screen.blit(self.animation_both[0], self.position_attack) # Displays the "Beginning_End" image
                            self.position_attack = (self.position_attack[0]+21, self.position_attack[1]) # Upgrading position_attack
                    # Other frame
                    elif self.animation_progress > 0 :
                        if self.position_attack[0]+42 < self.screen.get_size()[0]:
                            self.screen.blit(self.animation_both[1], self.position_attack) # Displays the "Traveling" image
                            self.screen.blit(self.cleanup, (self.position_attack[0]-42, self.position_attack[1])) # Displays image with the dimensions of the attack but with the color of the BG
                            self.position_attack = (self.position_attack[0]+21, self.position_attack[1])
                        elif self.position_attack[0]+21 < self.screen.get_size()[0]: # If it goes through this, it means it is the last frame of the animation
                            self.screen.blit(self.animation_both[0], self.position_attack)
                            self.screen.blit(self.cleanup, (self.position_attack[0]-42, self.position_attack[1]))
                            self.screen.blit(self.cleanup, (self.position_attack[0]-21, self.position_attack[1]))
                            self.position_attack = (self.position_attack[0]+21, self.position_attack[1])
                        # Last frame
                        elif self.position_attack[0]+21 >= self.screen.get_size()[0]:
                            self.screen.blit(self.animation_both[2], (0,0)) # Displays the "Alpha" image. End of animation
                            self.screen.blit(self.cleanup, (self.position_attack[0]-21, self.position_attack[1]))
                            self.animation_progress = 'done'
            if self.running and self.cycletime > self.interval:
                self.index_animation += 1
                self.cycletime = 0
            # Reset
            if self.animation_progress == 'done' or self.hit_someone == True:
                self.index_animation = 0
                self.animation_progress = 0
                self.running = False
                self.lock = False
                self.lock_spells[0] = False
                self.hit_someone = False
        #
        # 2nd spell
        #
        elif self.number == 2 and self.lock_spells[0] == False and self.lock_spells[2] == False and self.lock_spells[3] == False and self.lock_spells[4] == False and self.lock_spells[5] == False:
            if self.running and self.index_animation < len(self.animation):
                if self.orientation == 'Left':
                    self.position_spell = self.x_spell, self.y_spell = self.x-72, self.y+6
                elif self.orientation == 'Right':
                    self.position_spell = self.x_spell, self.y_spell = self.x+82, self.y+6
                if self.index_animation == 3:
                    self.protected = True
                if self.index_animation < len(self.animation):
                    self.screen.blit(self.animation_both[0],(0,0))
                    self.lock = True
                    mypicture = self.animation[self.index_animation]
                    self.screen.blit(mypicture, self.position_spell)
                    if self.running and self.cycletime > self.interval:
                        if self.index_animation != 6:
                            self.index_animation += 1
                        elif self.index_animation == 6:
                            self.animation_progress +=1
                            if self.animation_progress == 10:
                                self.animation_progress = 0
                                self.index_animation += 1
                        self.cycletime = 0

            if self.index_animation == len(self.animation)-1:
                self.index_animation = 0
                self.animation_progress = 0
                self.running = False
                self.lock = False
                self.lock_spells[1] = False
                self.protected = False
        #
        # 3rd spell
        #
        elif self.number == 3 and self.lock_spells[0] == False and self.lock_spells[1] == False and self.lock_spells[3] == False and self.lock_spells[4] == False and self.lock_spells[5] == False:
            if self.animation and self.index_animation < len(self.animation)-2:
                if self.orientation == 'Left':
                    self.position_attack = self.x_spell-30, self.y_spell+6
                elif self.orientation == 'Right':
                    self.position_attack = self.x_spell+30, self.y_spell+6 # self.x_spell +88(length of the character) - 8 or 10 (empty area of the Seventh image), self.y_spell +15(wand's top position)
            # Beginning of the animation on the wand
            if self.running and self.index_animation < len(self.animation):
                    if self.orientation == 'Left':
                        self.position_spell = self.x_spell, self.y_spell = self.x-72, self.y+42
                    elif self.orientation == 'Right':
                        self.position_spell = self.x_spell, self.y_spell = self.x+72, self.y+42
                    self.lock = True
                    mypicture = self.animation[self.index_animation]
                    self.screen.blit(mypicture, self.position_spell)# -71 +42 par rapport au personnage
            # Beginning of the traveling part
            if self.running and self.index_animation >= len(self.animation)-2:
                # First frame
                if self.orientation == 'Left':
                    if self.position_attack[0]-23 >= 0:
                        self.screen.blit(self.animation_both[1], self.position_attack) # Display Traveling
                        self.screen.blit(self.cleanup, (self.position_attack[0]+23, self.position_attack[1]))
                        self.position_attack = (self.position_attack[0]-23, self.position_attack[1])
                    elif self.position_attack[0]-23 < 0:
                        self.screen.blit(self.animation_both[2], (0,0)) # Displays the "Alpha" image. End of animation
                        self.screen.blit(self.cleanup, (self.position_attack[0]+23, self.position_attack[1]))
                        self.animation_progress = 'done'
                elif self.orientation == 'Right':
                    if self.position_attack[0]+23 < self.screen.get_size()[0]:
                        self.screen.blit(self.animation_both[1], self.position_attack) # Display Traveling
                        self.screen.blit(self.cleanup, (self.position_attack[0]-23, self.position_attack[1]))
                        self.position_attack = (self.position_attack[0]+23, self.position_attack[1])
                    elif self.position_attack[0]+23 >= self.screen.get_size()[0]:
                        self.screen.blit(self.animation_both[2], (0,0)) # Displays the "Alpha" image. End of animation
                        self.screen.blit(self.cleanup, (self.position_attack[0]-23, self.position_attack[1]))
                        self.animation_progress = 'done'
            if self.running and self.cycletime > self.interval:
                self.index_animation += 1
                self.cycletime = 0
            # Reset
            if self.animation_progress == 'done' or self.hit_someone == True:
                self.index_animation = 0
                self.animation_progress = 0
                self.running = False
                self.lock = False
                self.lock_spells[2] = False
                self.hit_someone = False
