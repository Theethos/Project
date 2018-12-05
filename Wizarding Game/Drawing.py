import pygame
import random

class Bonhomme():
    def __init__(self, screen, background, load, coordonnees=(100,100), color=(0,0,0), switchx=1, switchy=1):
        self.screen = screen
        self.background = background
        self.position = self.x, self.y = coordonnees
        self.color = color
        self.switchx = switchx
        self.switchy = switchy
        self.load = load

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

    def draw(self):
        self.motion()
        # # Draw the human squeleton
        # self.draw_squeleton()
        # # Draw hair, depending on character's sexe
        # self.draw_hair()
        self.image()
    def draw_motion(self, way):
        self.motion_keys(way)
        self.image()

    def image(self):
        monsieur = pygame.image.load(self.load)
        monsieur.set_colorkey((0,0,0))
        self.screen.blit(monsieur, (self.position))

    def motion_keys(self, way):
        if way == 'left':
            if self.x >= 0:
                self.x += -1
            elif self.x < 0:
                self.x = 0
            way = None
        if way == 'right':
            if self.x <= self.screen.get_size()[0]:
                self.x += 1
            elif self.x > self.screen.get_size()[0]:
                self.x = self.screen.get_size()[0]
            way = None
        if way == 'up':
            if self.y >= 350:
                self.y += -1
            elif self.y < 350:
                self.y = 350
            way = None
        if way == 'down':
            if self.y <= self.screen.get_size()[1]-60:
                self.y += 1
            elif self.y > self.screen.get_size()[1]-60:
                self.y = self.screen.get_size()[1]-60
            way = None
        self.position = (self.x, self.y)
    def motion(self):
        choice = random.randint(0,1)
        if choice == 0:
            # Variations on x-axys
            if self.x >= 0 and self.x <= self.screen.get_size()[0]:
                self.x += self.switchx
            elif self.x < 0:
                self.x = 0
                self.switchx = 1
                self.x += self.switchx
            elif self.x > self.screen.get_size()[0]:
                self.x = self.screen.get_size()[0]
                self.switchx = -1
                self.x += self.switchx
        if choice == 1:
            # Variation on y-axys
            if self.y >= 350 and self.y <= self.screen.get_size()[1]-60:
                self.y += self.switchy
            elif self.y < 350:
                self.y = 350
                self.switchy = 1
                self.y += self.switchy
            elif self.y > self.screen.get_size()[1]-60:
                self.y = self.screen.get_size()[1]-60
                self.switchy = -1
                self.y += self.switchy
        self.position = (self.x, self.y)
