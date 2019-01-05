import pygame
import decimal
import time
import os


class Maze():
    def __init__(self, screen):
        self.image = pygame.transform.rotozoom(pygame.image.load(os.path.join("Wizarding_Game","Image","120x120","Environnement","Walls","Wall.png")),0 ,0.5)
        self.levels = self.maze_levels()
        self.screen = screen
        self.text = pygame.font.SysFont('mono', 60, bold=True)
        self.transition = [pygame.Surface((self.screen.get_size())).convert(), None]
        self.transition[0].fill((0,0,0))
        self.start = [self.levels[0], 0, self.transition]
        self.max_level = len(self.levels)
        self.background = pygame.Surface((self.screen.get_size())).convert()
        self.background_color = (20,20,20)
        self.background.fill(self.background_color)
        self.background_copy = self.background.copy()
        self.start_position = self.x, self.y = self.addlevel(self.start[0])[5]
        self.walls = self.addlevel(self.start[0])[6]
        self.height = self.addlevel(self.start[0])[1]
        self.length = self.addlevel(self.start[0])[0]
        self.compteur = 0


    def run_(self, transition):
        self.addlevel(self.start[0])

    def maze_levels(self):
        # -------------------- Maze ----------------
        # s...startposition of ball
        # n...next level
        # p...previous level
        # r...random level
        # e...end (game won)
        # x...wall
        # w...wall -
        # v...wall |  __
        # t...wall   |
        # +... wall +
        # u... wall _|  __
        # y... wall      |

        # diviser: 1600 : 1,2,4,5,8,10,16,20,25,32,40,50,64,80,100,160,200,320,400,800,1600
        #           900 : 1,2,3,4,5,6,9,10,12,15,18,20,25,30,36,45,50,60,75,90,100,150,180,225,300,450,900
        #          1920 : 1,2,3,4,5,6,8,10,12,15,16,20,24,30,32,40,48,60,64,80,96,120,128,160,192,240,320,384,480,640,960,1920
        #          1080 : 1,2,3,4,5,6,8,9,10,12,15,18,20,24,27,30,36,40,45,54,60,72,90,108,120,135,180,216,270,360,540,1080
        #          1280 : 1,2,4,5,8,10,16,20,32,40,64,80,128,160,256,320,640,1280
        #           720 : 1,2,3,4,5,6,8,9,10,12,15,16,18,20,24,30,36,40,45,48,60,72,80,90,120,144,180,240,360,720
        # bridge = 24x20
        bridge = ["xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "x.......................................s......................................x",
                  "x..............................................................................x",
                  "x..............................................................................x",
                  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx....xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"]


        # startlevel = 24 x 15
        startlevel = ["xxxxx..xxxxxxxxxxxxxxxxx",
                      "xs.......v............rx",
                      "x........v............rx",
                      "xwww...twu....wwy......x",
                      "x......v........v......x",
                      "x......v........v......x",
                      "x...www+www.....v......x",
                      "x......v........v......x",
                      "x......v.......w+ww..wwx",
                      "xwwww..v........v......x",
                      "x......v........v......x",
                      "x......v...twwwwu...wwwx",
                      "x..........v...........x",
                      "xpp........v...........x",
                      "xxxxxxxxxxxxxxxxxxxxnnxx"]
        # middlelevel = 16 x 15
        middlelevel =  ["xxxxxxxxxxxxxxxx",
                        "xs.............x",
                        "x.........v....x",
                        "x.........v....x",
                        "x......x..v....x",
                        "x.....x...v....x",
                        "x..p.wxwwwu....x",
                        "x.....x........x",
                        "x.v....x.......x",
                        "x.v...x........x",
                        "x.v....v.......x",
                        "x.awwwwu...n...x",
                        "x..............x",
                        "x..............x",
                        "xxxxxxxxxxxxxxxx"]
        # smilelevel: 32 x 18
        winlevel = ["xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
                    "xs.............................x",
                    "x..............................x",
                    "x..............................x",
                    "x............xxx....xxx........x",
                    "x...........xx.xx..xx.xx.......x",
                    "x............xxx....xxx........x",
                    "x..............................x",
                    "x................x.............x",
                    "x................x.............x",
                    "x..............................x",
                    "x..............................x",
                    "x................r.............x",
                    "x............xxxxxxxxx.........x",
                    "x..............................x",
                    "x..............................x",
                    "x..............................x",
                    "xxxxxppxxxxxxxxxxxnnxxxxxxxxxeex"]
        return [bridge, startlevel, middlelevel, winlevel]


    def createblock(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(color)
        tmpblock.convert()
        return tmpblock

    def createhalfblock(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(self.background_color)
        pygame.draw.polygon(tmpblock, color, ((0,height/4),(length,height/4),(length,3*height/4),(0,3*height/4)))
        tmpblock.convert()
        return tmpblock

    def createhalfblockstraight(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(self.background_color)
        pygame.draw.polygon(tmpblock, color, ((length/4,0),(length/4,height),(3*length/4,height),(3*length/4,0)))
        tmpblock.convert()
        return tmpblock

    def createcornerleft(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(self.background_color)
        pygame.draw.polygon(tmpblock, color, ((length/4,height/4),(length/4,height),(3*length/4,height),(3*length/4,(3*height+4)/4),(length,3*height/4), (length,height/4)))
        tmpblock.convert()
        return tmpblock

    def createcornerright_reverse(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(self.background_color)
        pygame.draw.polygon(tmpblock, color, ((length/4,0),(length/4,3*height/4),(length,3*height/4),(length,height/4),(3*length/4,height/4), (3*length/4,0)))
        tmpblock.convert()
        return tmpblock

    def createcornerleft_reverse(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(self.background_color)
        pygame.draw.polygon(tmpblock, color, ((length/4,0),(length/4,height/4),(0,height/4),(0,3*height/4),(3*length/4,3*height/4), (3*length/4,0)))
        tmpblock.convert()
        return tmpblock

    def createcornerright(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(self.background_color)
        pygame.draw.polygon(tmpblock, color, ((3*length/4,height/4),(3*length/4,height),(length/4,height),(length/4,(3*height+4)/4),(0,3*height/4), (0,height/4)))
        tmpblock.convert()
        return tmpblock

    def createcross(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(color)
        pygame.draw.rect(tmpblock, self.background_color, (0, 0, length/4, height/4))
        pygame.draw.rect(tmpblock, self.background_color, ((3*length+4)/4, 0, length/4, height/4))
        pygame.draw.rect(tmpblock, self.background_color, ((3*length+4)/4, (3*height+4)/4, length/4, height/4))
        pygame.draw.rect(tmpblock, self.background_color, (0, (3*height+4)/4, length/4, height/4))
        tmpblock.convert()
        return tmpblock

    def createcross_bottom(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(color)
        pygame.draw.rect(tmpblock, self.background_color, ((3*length+4)/4, (3*height+4)/4, length/4, height/4))
        pygame.draw.rect(tmpblock, self.background_color, (0, (3*height+4)/4, length/4, height/4))
        tmpblock.convert()
        return tmpblock

    def addlevel(self, level):
        """this function read the layout of the level dictionary
           and blit it to the screen.
           recalculate and return variables like block, height etc.
           usage:

           length, height, block, goal, ballx, bally, background = addlevel(newlevel)
        """

        lines = len(level)
        columns = len(level[0])

        screenrect = self.screen.get_rect()
        length = screenrect.width/columns
        height = screenrect.height/lines
        #wallblock = self.createblock(length, height,(20,0,50))
        #wallblock = self.images["Wall"]
        halfblock = self.createhalfblock(length, height,(20,0,50))
        halfblockstraight = self.createhalfblockstraight(length, height,(20,0,50))
        cornerleft = self.createcornerleft(length, height, (20,0,50))
        cornerright = self.createcornerright(length,height, (20,0,50))
        cross = self.createcross(length, height, (20,0,50))
        cross_bottom = self.createcross_bottom(length, height, (20,0,50))
        cornerleft_reverse = self.createcornerleft_reverse(length, height, (20,0,50))
        cornerright_reverse = self.createcornerright_reverse(length,height, (20,0,50))
        nextblock = self.createblock(length, height,(255,50,50))
        prevblock = self.createblock(length, height,(255,50,255))
        endblock  = self.createblock(length, height,(100,100,100))
        randomblock = self.createblock(length, height,(0,0,200))

        self.background = self.background_copy.copy()

        walls = dict()
        for y in range(lines):
            for x in range(columns):
                if level[y][x] == "x": # wall
                    walls[(int(x*length),int(y*height))] = True
                    self.background.blit(self.image, (length * x, height * y))
                elif level[y][x] == "w": # next level
                    self.background.blit(halfblock, (length * x, height * y))
                elif level[y][x] == "t": # next level
                    self.background.blit(cornerleft, (length * x, height * y))
                elif level[y][x] == "+": # next level
                    self.background.blit(cross, (length * x, height * y))
                elif level[y][x] == "a": # next level
                    self.background.blit(cornerright_reverse, (length * x, height * y))
                elif level[y][x] == "-": # next level
                    self.background.blit(cross_bottom, (length * x, height * y))
                elif level[y][x] == "y": # next level
                    self.background.blit(cornerright, (length * x, height * y))
                elif level[y][x] == "v": # next level
                    self.background.blit(halfblockstraight, (length * x, height * y))
                elif level[y][x] == "u": # next level
                    self.background.blit(cornerleft_reverse, (length * x, height * y))
                elif level[y][x] == "n": # next level
                    self.background.blit(nextblock, (length * x, height * y))
                elif level[y][x] == "p": # previous level
                    self.background.blit(prevblock, (length * x, height * y))
                elif level[y][x] == "r": # random level
                    self.background.blit(randomblock, (length*x, height * y))
                elif level[y][x] == "e": # end block
                    self.background.blit(endblock,  (length * x, height * y))
                elif level[y][x] == "s": #start
                    self.x = int(length * x)
                    self.y = int(height * y)
                    self.start_position = (self.x, self.y)
        self.screen.blit(self.background, (0,0))
        return length, height, lines, columns, self.background, self.start_position, walls



if __name__ == "__main__" :
    pass
