import pygame
import random
import time


class Bonhomme():
    def __init__(self, screen, background, load, colorkey=(0,0,0), coordonnees=(100,100), color=(0,0,0), switchx=1, switchy=1):
        self.screen = screen
        self.background = background
        self.position = self.x, self.y = coordonnees
        self.color = color
        self.switchx = switchx
        self.switchy = switchy
        self.load = [load, load+'_Right.png','_Right.png']
        self.colorkey = colorkey
        self.dx, self.dy = 10, 10
        self.text = pygame.font.SysFont('mono', 60, bold=True)
        self.color_wall = (20,0,50)
        self.lifebar = Lifebar(self.screen, self.position, self.color_wall, self.load)
        self.timer = 0
        self.alive = True
    # For NPC, moves characters from left to right
    # (On his own)
    def draw(self):
        self.motion()
        self.image()

    # Alows characters to be moved with keypad
    def draw_motion(self, way, maze):
        if self.lifebar.percentage == 0:
            if self.alive:
                self.death()
            elif not(self.alive) and self.timer < 150:
                self.timer+=1
            elif not(self.alive) and self.timer == 150:
                self.respawn(maze)
                self.timer = 0
        self.motion_keys(way, maze)
        self.image()
        self.lifebar.position = self.lifebar.x, self.lifebar.y = self.position
        self.lifebar.path_character = self.load
        self.lifebar.run_life()
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
    def motion_keys(self, way, maze):
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
            self.position = self.x, self.y = self.x-20, self.y
            self.load[2] = '_Right_Dead.png'
            self.load[1] = self.load[0]+self.load[2]
        elif self.load[2] == '_Left.png':
            self.position = self.x, self.y = self.x+20, self.y
            self.load[2] = '_Left_Dead.png'
            self.load[1] = self.load[0]+self.load[2]
        self.alive = False
    def respawn(self, maze):
        self.alive = True
        if self.load[2] == '_Left_Dead.png':
            self.load[2] == '_Left.png'
            self.load[1] = self.load[0]+self.load[2]
            self.lifebar.percentage = 100
            self.motion_keys('right', maze)
        elif self.load[2] == '_Right_Dead.png':
            self.load[2] == '_Right.png'
            self.load[1] = self.load[0]+self.load[2]
            self.lifebar.percentage = 100
            self.motion_keys('left', maze)

class Lifebar(Bonhomme):
    def __init__(self, screen, position, color_wall, path_character):
        self.screen = screen
        self.position = self.x, self.y = position
        self.color_wall = color_wall
        self.path = ["Wizarding Game\\Image\\120x120\\Lifebar\\100.png", "Wizarding Game\\Image\\120x120\\Lifebar\\"]
        self.image = pygame.image.load(self.path[0])
        self.percentage = 100
        self.position_life = self.x_life, self.y_life = 0,0
        self.damage = 0
        self.path_character = path_character

    def set_position_life(self):
        if (self.x-5 > self.screen.get_size()[0] or self.x-5 < 0) or (self.y-20 > self.screen.get_size()[1] or self.y-20 < 0):
            self.path[0] = self.path[1]+"alpha.png"
            self.position_life = self.x_life, self.y_life = 0, 0
            self.damage = 1
        elif self.screen.get_at((self.x-5, self.y-20)) != self.color_wall and self.screen.get_at((self.x+98, self.y-20)) != self.color_wall:
            self.path[0] = self.path[1]+str(self.percentage)+".png"
            self.position_life = self.x_life, self.y_life = self.x-5, self.y-20
            self.damage = 1
        else:
            if self.damage == 1:
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
