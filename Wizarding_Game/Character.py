import pygame
import random
import time
import os

class Bonhomme():
    def __init__(self, screen, background, load, colorkey=(0,0,0), coordonnees=(100,100), side='neutral', color=(0,0,0), switchx=1, switchy=1):
        self.screen = screen
        self.background = background
        self.background_color = (88,88,88)
        self.position = self.x, self.y = coordonnees
        self.color = color
        self.switchx = switchx
        self.switchy = switchy
        self.load = [load, load+'_Right.png','_Right.png', 'Right']
        self.colorkey = colorkey
        self.dx, self.dy = 10, 10
        self.text = pygame.font.SysFont('mono', 60, bold=True)
        self.color_wall = (20,0,50)
        self.lifebar = Lifebar(self.screen, self.position, self.color_wall, self.load, self.dx, self.dy)
        self.timer = 0
        self.alive = True
        self.colision = False
        self.side = side
        self.lock = False
        self.spells = Spells(self.screen, self.background_color, self.side, self.x, self.y)
    # For NPC, moves characters from left to right
    # (On his own)
    def draw(self):
        self.motion()
        self.image()

    # Alows characters to be moved with keypad
    def draw_motion(self, way, maze):
        self.motion_keys(way)
        self.image()
        self.spells.position = self.spells.x, self.spells.y = self.x, self.y
        self.spells.orientation = self.load[3]
        self.spells.display()
        self.lifebar.position = self.lifebar.x, self.lifebar.y = self.position
        self.lifebar.path_character = self.load
        self.lifebar.colision = self.colision
        self.lifebar.run_life()
        if self.lifebar.percentage <= 10 and self.colision:
            if self.alive:
                self.lifebar.percentage = 0
                self.death()
            elif not(self.alive) and self.timer < 150:
                self.timer+=1
            elif not(self.alive) and self.timer == 150:
                self.respawn()
                self.timer = 0
        result = self.blocks(maze)
        if result == None:
            result = True
        return result

    # Charges an image (as character for example)
    def image(self):
        monsieur = pygame.image.load(self.load[1])
        monsieur.set_colorkey(self.colorkey)
        self.screen.blit(monsieur, (self.position))

    # Defines motions made with keys events
    def motion_keys(self, way):
        if self.alive:
            if way == 'left':
                if self.x-self.dx >= 0:
                    pixels = [(self.x-self.dx,self.y),(self.x-self.dx,self.y+29), (self.x-self.dx,self.y+58), (self.x-self.dx,self.y+87), (self.x-self.dx,self.y+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.x -= self.dx
                        self.colision = False
                    elif wall:
                        self.colision = True
                if not(self.spells.lock):
                    self.load[3] = 'Left'
                    self.load[2] = '_Left.png'
                    self.load[1] = self.load[0]+self.load[2]
                way = None
            elif way == 'right':
                if self.x+self.dx <= self.screen.get_size()[0]-108:
                    pixels = [(self.x+self.dx+88,self.y), (self.x+self.dx+88,self.y+29),(self.x+self.dx+88,self.y+58), (self.x+self.dx+88,self.y+87), (self.x+self.dx+88,self.y+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.x += self.dx
                        self.colision = False
                    elif wall:
                        self.colision = True
                if not(self.spells.lock):
                    self.load[3] = 'Right'
                    self.load[2] = '_Right.png'
                    self.load[1] = self.load[0]+self.load[2]
                way = None
            elif way == 'up':
                if self.y-self.dy >= 0:
                    pixels = [(self.x,self.y-self.dy), (self.x+44,self.y-self.dy), (self.x+88,self.y-self.dy)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.y -= self.dy
                        self.colision = False
                    elif wall:
                        self.colision = True
                way = None
            elif way == 'down':
                if self.y+self.dy <= self.screen.get_size()[1]-116:
                    pixels = [(self.x,self.y+self.dy+116), (self.x+44,self.y+self.dy+116), (self.x+88,self.y+self.dy+116)]
                    wall = False
                    for pixel in pixels:
                        if self.screen.get_at(pixel) == self.color_wall:
                            wall = True
                    if not(wall):
                        self.y += self.dy
                        self.colision = False
                    elif wall:
                        self.colision = True
                way = None
    def blocks(self, maze):
        # Next level block
        if maze.background.get_at((self.x+44,self.y+87)) == (255,50,50):
            if maze.start[1]+1 < maze.max_level:
                maze.start[1] +=1
                maze.start[0] = maze.levels[maze.start[1]]
            else:
                maze.start[1] = 0
                maze.start[0] = maze.levels[0]
            maze.start_position = maze.x, maze.y = self.x, self.y = maze.addlevel(maze.start[0])[5]
        # Random block
        elif maze.background.get_at((self.x+44,self.y+87)) == (0,0,200):
            maze.start[1] = random.randint(0,maze.max_level-1)
            maze.start[0] = maze.levels[maze.start[1]]
            maze.start_position = maze.x, maze.y = self.x, self.y = maze.addlevel(maze.start[0])[5]
            self.screen.blit(self.background, (0,0))
        # End block
        elif maze.background.get_at((self.x+44,self.y+87)) == (100,100,100):
            maze.background.fill((0,0,0))
            text = "GG le sang, t'es sorti."
            self.text.size(text)
            surface = self.text.render(text, True, (255,255,254))
            self.screen.blit(maze.background, (0,0))
            self.screen.blit(surface, (self.screen.get_size()[0]/4, 2*self.screen.get_size()[1]/5))
            return False
        elif maze.background.get_at((self.x+44,self.y+87)) == (255,50,255):
            if maze.start[1]-1 >= 0:
                maze.start[1] -=1
                maze.start[0] = maze.levels[maze.start[1]]
            else:
                maze.start[1] = 0
                maze.start[0] = maze.levels[0]
            maze.start_position = maze.x, maze.y = self.x, self.y = maze.addlevel(maze.start[0])[5]
            self.screen.blit(self.background, (0,0))

        self.position = (self.x, self.y)

    # Defines motions made from left to right
    def motion(self):
        choice = random.randint(0,1)
        if choice == 0:
            # Variations on x-axys
            if self.x >= 0-10 and self.x <= self.screen.get_size()[0]-111:
                self.x += self.switchx
            elif self.x < 0-10:
                self.x = 0-10
                self.switchx = 1
                self.x += self.switchx
                self.load[1] = self.load[0]+'_Right.png'
            elif self.x > self.screen.get_size()[0]-111:
                self.x = self.screen.get_size()[0]-111
                self.switchx = -1
                self.x += self.switchx
                self.load[1] = self.load[0]+'_Left.png'
        if choice == 1:
            # Variation on y-axys
            if self.y >= 287 and self.y <= self.screen.get_size()[1]-120:
                self.y += self.switchy
            elif self.y < 287:
                self.y = 287
                self.switchy = 1
                self.y += self.switchy
            elif self.y > self.screen.get_size()[1]-120:
                self.y = self.screen.get_size()[1]-120
                self.switchy = -1
                self.y += self.switchy
        self.position = (self.x, self.y)

    def death(self):
        if self.load[2] == '_Right.png':
            self.position = self.x, self.y = self.x-30, self.y
            self.load[2] = '_Right_Dead.png'
            self.load[1] = self.load[0]+self.load[2]
        elif self.load[2] == '_Left.png':
            self.position = self.x, self.y = self.x+20, self.y
            self.load[2] = '_Left_Dead.png'
            self.load[1] = self.load[0]+self.load[2]
        self.alive = False

    def respawn(self):
        self.alive = True
        if self.load[2] == '_Left_Dead.png':
            self.load[3] = 'Left'
            self.load[2] == '_Left.png'
            self.load[1] = self.load[0]+self.load[2]
            self.lifebar.percentage = 110
            self.motion_keys('right')
        elif self.load[2] == '_Right_Dead.png':
            self.load[3] = 'Right'
            self.load[2] == '_Right.png'
            self.load[1] = self.load[0]+self.load[2]
            self.lifebar.percentage = 110
            self.motion_keys('left')

        def lock(self):
            pass

class Lifebar(Bonhomme):
    def __init__(self, screen, position, color_wall, path_character, dx, dy):
        self.screen = screen
        self.position = self.x, self.y = position
        self.color_wall = color_wall
        self.path = ["Wizarding_Game\\Image\\120x120\\Lifebar\\100.png", "Wizarding_Game\\Image\\120x120\\Lifebar\\"]
        self.image = pygame.image.load(self.path[0])
        self.percentage = 100
        self.position_life = self.x_life, self.y_life = 0,0
        self.damage = 0
        self.path_character = path_character
        self.dx, self.dy = dx, dy
        self.colision = False
        self.compteur = 1

    def set_position_life(self):
        if (self.x-5 > self.screen.get_size()[0] or self.x-5 < 0) or (self.y-20 > self.screen.get_size()[1] or self.y-20 < 0):
            self.path[0] = self.path[1]+"alpha.png"
            self.position_life = self.x_life, self.y_life = 0, 0
        elif self.screen.get_at((self.x-5, self.y-20)) == self.color_wall or self.screen.get_at((self.x+98, self.y-20)) == self.color_wall:
            self.path[0] = self.path[1]+"alpha.png"
            self.position_life = self.x_life, self.y_life = 0, 0
        elif self.screen.get_at((self.x-5, self.y-10)) == self.color_wall or self.screen.get_at((self.x+98, self.y-10)) == self.color_wall:
            self.path[0] = self.path[1]+"alpha.png"
            self.position_life = self.x_life, self.y_life = 0, 0
        elif self.screen.get_at((self.x-5, self.y-20)) != self.color_wall and self.screen.get_at((self.x+98, self.y-20)) != self.color_wall:
            if self.percentage > 100:
                self.path[0] = self.path[1]+"100.png"
            else:
                self.path[0] = self.path[1]+str(self.percentage)+".png"
            self.position_life = self.x_life, self.y_life = self.x-5, self.y-20
            self.compteur = 0
        if self.colision and self.compteur == 0:
            self.damage = 1
            self.compteur = 1
        if self.damage == 1  and self.compteur == 0:
            if self.percentage > 0:
                self.percentage -= 10
            self.path[0] = self.path[1]+"alpha.png"
            self.damage = 0

    def draw_life(self):
        self.image = pygame.image.load(self.path[0])
        self.image.set_colorkey((0,0,0))
        self.image.convert_alpha()
        self.screen.blit(self.image, self.position_life)

    def run_life(self):
        self.set_position_life()
        self.draw_life()

class Spells(Bonhomme):
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
        # cleanup is a needed surface to clean up after attack
        # 21, 7 = Dimensions of the attack
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
        self.lock_spells = False

        self.path()


    def offensive(self):
        offensive_spell = None
        if self.side == 'darkness':
            offensive_spell = 'Avada_Kedravra'
        elif self.side == 'light':
            offensive_spell = 'Expelliarmus'
        elif self.side == 'neutral':
            offensive_spell = 'Confringo'
        return offensive_spell

    def defensive(self):
        defensive_spell = None
        if self.side == 'darkness':
            defensive_spell = 'Spero_Patronum'
        elif self.side == 'light':
            defensive_spell = 'Protego'
        elif self.side == 'neutral':
            defensive_spell = 'Shieldero'
        return defensive_spell

    def stunning(self):
        stunning_spell = None
        if self.side == 'darkness':
            stunning_spell = 'Crucio'
        elif self.side == 'light':
            stunning_spell = 'Stupefy'
        elif self.side == 'neutral':
            stunning_spell = 'Petrificus_Totalus'
        return stunning_spell

    def disappartition(self):
        disappartition_spell = None
        if self.side == 'darkness':
            disappartition_spell = 'Dark_Trail'
        elif self.side == 'light':
            disappartition_spell = 'Light_Trail'
        elif self.side == 'neutral':
            disappartition_spell = 'Disappartition'
        return disappartition_spell

    def light(self):
        light_spell = 'Lumos'
        return light_spell

    def metamorphosis(self):
        metamorphosis_spell = None
        if self.side == 'darkness':
            metamorphosis_spell = 'Serpent_Sortia'
        elif self.side == 'light':
            metamorphosis_spell = 'Phoenix_Sortia'
        elif self.side == 'neutral':
            metamorphosis_spell = 'Wolf_Sortia'
        return metamorphosis_spell

    # Update and set the dictionnary containing every path needed for
    # the animation of each spell
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

    def which_spell(self, number):
        keys = list(self.spells.keys())
        return self.spells[keys[number-1]]

    def set_animation(self):
        # Charges every images required for animation, depending on the orientation of the character
        if self.lock_spells == False:
            animation = []
            if self.orientation == 'Left':
                self.position_spell = self.x_spell, self.y_spell = self.x-71, self.y+42
                self.position_attack = self.x_spell-13, self.y_spell+15 # self.x_spell -21(length of the attack) + 8(empty area of the Seventh image), self.y_spell +15(wand's top position)
                for image in self.path_spell['Left']:
                    try:
                        animation.append(pygame.image.load(os.path.join(image)))
                    except:
                        print("Error, can't find the file '"+image+"' \nPlease, make sure you wrote the right path.")
            elif self.orientation == 'Right':
                self.position_spell = self.x_spell, self.y_spell = self.x+71, self.y+42
                self.position_attack = self.x_spell+78, self.y_spell+15 # self.x_spell +88(length of the character) - 8 or 10 (empty area of the Seventh image), self.y_spell +15(wand's top position)
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
            for image in self.path_spell['Both']:
                try:
                    animation_both.append(pygame.image.load(os.path.join(image)))
                except:
                    raise UserWarning("Error, can't find the file '"+image+"' \nPlease, make sure you wrote the right path.")
            for image in range (len(animation_both)):
               animation_both[image].set_colorkey(self.color_key)
               animation_both[image] = animation_both[image].convert_alpha()

            return animation, animation_both
    # Display the animation
    def display(self):
        milliseconds = self.clock.tick(60)  # Milliseconds passed since last frame
        seconds = milliseconds / 1000.0 # Seconds passed since last frame (float)
        self.cycletime += seconds
        if not(self.animation) or self.index_animation <= len(self.animation)-6:
            if self.orientation == 'Left':
                self.position_spell = self.x_spell, self.y_spell = self.x-71, self.y+42
                self.position_attack = self.x_spell-13, self.y_spell+15
            elif self.orientation == 'Right':
                self.position_spell = self.x_spell, self.y_spell = self.x+71, self.y+42
                self.position_attack = self.x_spell+78, self.y_spell+15 # self.x_spell +88(length of the character) - 8 or 10 (empty area of the Seventh image), self.y_spell +15(wand's top position)
        # Beginning of the animation on the wand
        if self.running and self.index_animation < len(self.animation):
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
                        #self.screen.blit(self.cleanup, (self.position_attack[0]+42, self.position_attack[1])) # Displays image with the dimensions of the attack but with the color of the BG
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
        if self.animation_progress == 'done': # Time of the animation (majorized)
            self.index_animation = 0
            self.animation_progress = 0
            self.running = False
            self.lock = False
            self.lock_spells = False
