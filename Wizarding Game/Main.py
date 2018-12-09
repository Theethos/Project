import pygame
from pygame.locals import *
import math
import Maze
import Drawing
import time


class App:
    # Creation of App object
    def __init__(self):
        self._running = True
        self.screen = None
        self.size = self.weight, self.height = 1600, 900
        self.background = None
        self.FPS = 60
        self.text = [None, self.FPS]
        self.print_FPS = True
        # One key for each character
        self.key = {1:None, 2:None}

    # Initialisation of App object
    def on_init(self):
        pygame.init()
        self.screen = pygame.display.set_mode(self.size, (pygame.FULLSCREEN))
        self.background = pygame.Surface((self.size)).convert()
        self._running = True
        self.text[0] = pygame.font.SysFont('mono', 12, bold=True)

    # Event
    def on_event(self, event):
        if event.type == pygame.QUIT:
            # If user close the widow
            self._running = False
        elif event.type == pygame.KEYDOWN:
            # If user press ESC
            if event.key == pygame.K_ESCAPE:
                self._running = False
            elif event.key == pygame.K_1:
                if self.print_FPS:
                    self.print_FPS = False
                else:
                    self.print_FPS = True
            elif event.key == pygame.K_2:
                self.FPS = 20
            elif event.key == pygame.K_3:
                self.FPS = 30
            elif event.key == pygame.K_4:
                self.FPS = 40
            elif event.key == pygame.K_5:
                self.FPS = 50
            elif event.key == pygame.K_6:
                self.FPS = 60
            elif event.key == pygame.K_7:
                self.FPS = 70
            elif event.key == pygame.K_8:
                self.FPS = 80
            elif event.key == pygame.K_9:
                self.FPS = 90
            elif event.key == pygame.K_0:
                self.FPS = 1000
            elif event.key == pygame.K_UP:
                self.key[1] = 'up'
            elif event.key == pygame.K_DOWN:
                self.key[1] = 'down'
            elif event.key == pygame.K_LEFT:
                self.key[1] = 'left'
            elif event.key == pygame.K_RIGHT:
                self.key[1] = 'right'
            elif event.key == pygame.K_w:
                self.key[2] = 'up'
            elif event.key == pygame.K_s:
                self.key[2] = 'down'
            elif event.key == pygame.K_a:
                self.key[2] = 'left'
            elif event.key == pygame.K_d:
                self.key[2] = 'right'

        else:
            self.key = {1:'none', 2:'none'}
    # Loop (where things are supposed happen ;) )
    def on_loop(self, clock_fps, character):
        if self.print_FPS:
            self.text[1] = "FPS : {}".format(clock_fps)
            self.text[0].size(self.text[1])
            surface = self.text[0].render(self.text[1], True, (0,255,0))
            self.screen.blit(surface, (0, 0))
    # Render
    def on_render(self):
        pass

    # Closing
    def on_cleanup(self):
        pygame.quit()

    # Execution
    def on_execute(self):
        if self.on_init() == False:
            self._running = False

        # Initialisation of variables
        clock = pygame.time.Clock()
        self.FPS = 60 # FPS max
        playtime = 0 # Time played
        Maze_ = Maze.Maze(self.screen) # Maze object
        # Bonhomme objects
        Harry_Potter_Quidditch = Drawing.Bonhomme(self.screen, self.background,'Wizarding Game\\Image\\120x120\\Harry_Potter_Quidditch', (63,72,204), Maze_.start_position)
        Harry_Potter = Drawing.Bonhomme(self.screen, self.background, 'Wizarding Game\\Image\\120x120\\Harry_Potter', (63,72,204), Maze_.start_position)


        # Main loop
        while( self._running ):
            milliseconds = clock.tick(self.FPS)  # Milliseconds passed since last frame
            seconds = milliseconds / 1000.0 # Seconds passed since last frame (float)
            playtime += seconds
            # Managing events
            for event in pygame.event.get():
                self.on_event(event)
            # Display FPS
            pygame.display.set_caption("Wizarding Game"" : limit FPS to {}"
                               " (now: {:.2f})".format(self.FPS,clock.get_fps()))
            self.on_loop(int(clock.get_fps()), Harry_Potter)
            # Center of loop
            # stop allows to close the pygame window when the maze is complete (only way I found to make it work)
            #stop = Harry_Potter_Quidditch.draw_motion(self.key[2], Maze_)
            stop = Harry_Potter.draw_motion(self.key[1], Maze_)
            pygame.display.flip()
            Maze_.run_(stop)
            # Render (nor usefull now)
            self.on_render()
            # Close the pygame window when the maze is complete
            # Freeze the screen for 2 seconds to allow the reading of the ending screen
            if not(stop):
                time.sleep(2)
                break
        # Time played
        if playtime < 61:
            print("You played : "+str(int(playtime))+" second(s)")
        else:
            print("You played : "+str(int(playtime)//60)+" minute(s) "+str(int(playtime)%60)+" second(s)")
        # Cleaning
        self.on_cleanup()

    def background_(self):
        pass

# Loading
if __name__ == "__main__" :
    theApp = App()
    theApp.on_execute()
