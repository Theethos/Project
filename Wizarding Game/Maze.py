import pygame
import decimal

class Maze():
    def __init__(self, screen):
        self.levels = self.maze_levels()
        self.start = self.levels[0]
        self.screen = screen
        self.background = pygame.Surface((self.screen.get_size())).convert()
        self.background.fill((255,255,255))
        self.background_copy = self.background.copy()
        self.start_position = self.x, self.y = self.addlevel(self.start)[5]
        self.walls = self.addlevel(self.start)[6]
        self.height = self.addlevel(self.start)[1]
        self.length = self.addlevel(self.start)[0]
    def run_(self):
        self.addlevel(self.start)
    def maze_levels(self):
        # -------------------- Maze ----------------
        # s...startposition of ball
        # n...next level
        # p...previous level
        # r...random level
        # e...end (game won)
        # x...wall

        # startlevel = 25 x 15
        startlevel = ["xxxxx..xxxxxxxxxxxxxxxxxx",
                      "xs.......v...............",
                      "x.......................x",
                      "xwww..........www.......x",
                      "x......v........v.......x",
                      "x......v........v.......x",
                      "x...wwwwwww.............x",
                      "x......v................x",
                      "x......v........wwwwwwwwx",
                      "xwwww..v................x",
                      "x......v................x",
                      "x......v...wwww.....wwwwx",
                      "x..........v............x",
                      "x..........v............x",
                      "xxxxxxxxxxxxxxxxxxxxxnnxx"]
        # middlelevel = 16 x 15
        middlelevel =  ["xxxxxxxxxxxxxxxx",
                        "xs.............x",
                        "x.........x....x",
                        "x.........x....x",
                        "x......x..x....x",
                        "x.....x...x....x",
                        "x..p.xxxxxx....x",
                        "x.....x........x",
                        "x.x....x.......x",
                        "x.x...x........x",
                        "x.x....x.......x",
                        "x.xxxxxxx..n...x",
                        "x......x.......x",
                        "x.....x........x",
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
                    "x................x.............x",
                    "x..............................x",
                    "x................r.............x",
                    "x............xx....xxx.........x",
                    "x.............xxxxxxx..........x",
                    "x..............................x",
                    "x..............................x",
                    "xxxxxxpxxxxxxxxxxxnxxxxxxxxxxxex"]
        return [startlevel, middlelevel, winlevel]


    def createblock(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill(color)
        tmpblock.convert()
        return tmpblock

    def createhalfblock(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill((255,255,255))
        pygame.draw.polygon(tmpblock, color, ((0,height/4),(length,height/4),(length,3*height/4),(0,3*height/4)))
        tmpblock.convert()
        return tmpblock

    def createhalfblockstraight(self, length, height, color):
        tmpblock = pygame.Surface((length, height))
        tmpblock.fill((255,255,255))
        pygame.draw.polygon(tmpblock, color, ((length/4,0),(length/4,height),(3*length/4,height),(3*length/4,0)))
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

        wallblock = self.createblock(length, height,(20,0,50))
        halfblock = self.createhalfblock(length, height,(20,0,50))
        halfblockstraight = self.createhalfblockstraight(length, height,(20,0,50))
        nextblock = self.createblock(length, height,(255,50,50))
        prevblock = self.createblock(length, height,(255,50,255))
        endblock  = self.createblock(length, height,(100,100,100))
        randomblock = self.createblock(length, height,(0,0,200))

        self.background = self.background_copy.copy()

        walls = dict()
        for y in range(lines):
            for x in range(columns):
                # pygame.draw.rect(self.background,(0,0,0),(length * x, height * y, length, height), 3)
                if level[y][x] == "x": # wall
                    walls[(int(x*length),int(y*height))] = True
                    self.background.blit(wallblock, (length * x, height * y))
                elif level[y][x] == "w": # next level
                    self.background.blit(halfblock, (length * x, height * y))
                elif level[y][x] == "v": # next level
                    self.background.blit(halfblockstraight, (length * x, height * y))
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
    a = 12.6
    c = int(a)
    b = decimal.Decimal(str(round(a)))
    b = round(a)
    print(b,c,type(a))
