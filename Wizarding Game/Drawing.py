import pygame
import random

class Bonhomme():
    def __init__(self, screen, background, load, colorkey=(0,0,0), coordonnees=(100,100), color=(0,0,0), switchx=1, switchy=1):
        self.screen = screen
        self.background = background
        self.position = self.x, self.y = coordonnees
        self.color = color
        self.switchx = switchx
        self.switchy = switchy
        self.load = [load, load+'_Right.png']
        self.colorkey = colorkey
        self.dx, self.dy = 3, 3
    """Test"""
    def draw_squeleton(self):
        # Head
        pygame.draw.circle(self.screen, self.color, (self.x,self.y-20), 20, 0)
        # Body ~Trait
        pygame.draw.line(self.screen, self.color, (self.x,self.y), (self.x,self.y+40),8)
        # Body ~Ventre
        pygame.draw.ellipse(self.screen, self.color, (self.x-9,self.y,20,40), 0)
        # Left arm
        pygame.draw.line(self.screen, self.color, (self.x,self.y+20), (self.x-30,self.y),8)
        # Right arm
        pygame.draw.line(self.screen, self.color, (self.x,self.y+20), (self.x+30,self.y),8)
        # Left leg
        pygame.draw.line(self.screen, self.color, (self.x,self.y+40), (self.x-20,self.y+60),8)
        # Right leg
        pygame.draw.line(self.screen, self.color, (self.x,self.y+40), (self.x+20,self.y+60),8)

    def draw_test(self):
        pygame.draw.circle(self.screen, self.color, (self.position), 20, 4)
    def draw_hair(self):
        # Girl's hair:
        listPoint = ((self.x-20,self.y-45), (self.x, self.y-50), (self.x+20,self.y-45), (self.x+30,self.y-25), (self.x-30,self.y-25))
        pygame.draw.polygon(self.screen, (255,255,0), listPoint)
    """Until Here"""
    # For NPC, moves characters from left to right
    # (On his own)
    def draw(self):
        self.motion()
        self.image()

    # Alows characters to be moved with keypad
    def draw_motion(self, way, level, length, height):
        self.motion_keys(way, level, length, height)
        self.image()

    # Charges an image (as character for example)
    def image(self):
        monsieur = pygame.image.load(self.load[1])
        monsieur.set_colorkey(self.colorkey)
        self.screen.blit(monsieur, (self.position))

    # Defines motions made with keys events
    def motion_keys(self, way, level, length, height):
        if way == 'left':
            if self.x-self.dx >= 0:
                pixels = [(self.x-self.dx,self.y), (self.x-self.dx,self.y+58), (self.x-self.dx,self.y+116)]
                wall = False
                for pixel in pixels:
                    if self.screen.get_at(pixel) == (20,0,50):
                        wall = True
            # pygame.draw.circle(self.screen, (255,0,0), pixels[0], 1)
            # pygame.draw.circle(self.screen, (255,0,0), pixels[1], 1)
            # pygame.draw.circle(self.screen, (255,0,0), pixels[2], 1)
                if not(wall):
                    self.x -= self.dx
            self.load[1] = self.load[0]+'_Left.png'
            way = None
        if way == 'right':
            if self.x+self.dx <= self.screen.get_size()[0]-108:
                pixels = [(self.x+self.dx+88,self.y), (self.x+self.dx+88,self.y+58), (self.x+self.dx+88,self.y+116)]
                wall = False
                for pixel in pixels:
                    if self.screen.get_at(pixel) == (20,0,50):
                        wall = True
            # pygame.draw.circle(self.screen, (255,0,0), pixels[0], 1)
            # pygame.draw.circle(self.screen, (255,0,0), pixels[1], 1)
            # pygame.draw.circle(self.screen, (255,0,0), pixels[2], 1)
                if not(wall):
                    self.x += self.dx
            self.load[1] = self.load[0]+'_Right.png'
            way = None
        if way == 'up':
            if self.y-self.dy >= 0:
                pixels = [(self.x,self.y-self.dy), (self.x+88,self.y-self.dy)]
                wall = False
                for pixel in pixels:
                    if self.screen.get_at(pixel) == (20,0,50):
                        wall = True
            # pygame.draw.circle(self.screen, (255,0,0), pixels[0], 1)
            # pygame.draw.circle(self.screen, (255,0,0), pixels[1], 1)
                if not(wall):
                    self.y -= self.dy
            way = None
        if way == 'down':
            if self.y+self.dy <= self.screen.get_size()[1]-116:
                pixels = [(self.x,self.y+self.dy+116), (self.x+88,self.y+self.dy+116)]
                wall = False
                for pixel in pixels:
                    if self.screen.get_at(pixel) == (20,0,50):
                        wall = True
            # pygame.draw.circle(self.screen, (255,0,0), pixels[0], 1)
            # pygame.draw.circle(self.screen, (255,0,0), pixels[1], 1)
                if not(wall):
                    self.y += self.dy
            way = None
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
