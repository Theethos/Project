import pygame
from pygame.locals import *
import math
import Maze
import Character
import time
import Spells

class App:
    # Creation of App object
    def __init__(self):
        self._running = True
        self.screen = None
        self.size = self.weight, self.height = 1920, 1080
        self.background = None
        self.FPS = 60
        self.text = [None, self.FPS]
        self.print_FPS = True
        # One key for each character
        self.key = {1:None, 2:None}
        self.interval = None
        self.background_color = (88,88,88)
        self.spells = [{'Character_Spell':None, 'Running': False},{'Character_Spell':None, 'Running': False}]
        self.character= [[None],[None]]
        self.animation_timer = [0,0]

    # Initialisation of App object
    def on_init(self):
        pygame.init()
        self.screen = pygame.display.set_mode(self.size, (pygame.FULLSCREEN))
        self.background = pygame.Surface((self.size)).convert()
        self.background.fill(self.background_color)
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
            elif event.key == pygame.K_F1:
                if self.print_FPS:
                    self.print_FPS = False
                else:
                    self.print_FPS = True
            elif event.key == pygame.K_1:
                self.character[0].spells.running = True
                self.character[0].spells.path_spell = self.character[0].spells.which_spell(1)
                if self.character[0].spells.lock_spells == False:
                    self.character[0].spells.animation, self.character[0].spells.animation_both = self.character[0].spells.set_animation()
                    self.character[0].spells.lock_spells = True
            elif event.key == pygame.K_KP1:
                self.character[1].spells.running = True
                self.character[1].spells.path_spell = self.character[1].spells.which_spell(1)
                if self.character[1].spells.lock_spells == False:
                    self.character[1].spells.animation, self.character[1].spells.animation_both = self.character[1].spells.set_animation()
                    self.character[1].spells.lock_spells = True
            elif event.key == pygame.K_2:
                self.spells[0].path_spell = self.which_spell(2)
                self.animation, self.animation_both = self.set_animation(path)
            elif event.key == pygame.K_3:
                self.spells[0].path_spell = self.which_spell(3)
                self.animation, self.animation_both = self.set_animation(path)
            elif event.key == pygame.K_4:
                self.spells[0].path_spell = self.which_spell(4)
                self.animation, self.animation_both = self.set_animation(path)
            elif event.key == pygame.K_5:
                self.spells[0].path_spell = self.which_spell(5)
                self.animation, self.animation_both = self.set_animation(path)
            elif event.key == pygame.K_6:
                self.spells[0].path_spell = self.which_spell(6)
                self.animation, self.animation_both = self.set_animation(path)
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
    def on_loop(self, clock_fps):
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
        playtime = 0 # Time playedd
        cycletime = [0,0] # Cycle for animation
        self.interval = 0.5 # Interval for displaying animations
        Maze_ = Maze.Maze(self.screen) # Maze object
        # Bonhomme objects
        self.character =  Character.Bonhomme(self.screen, self.background,'Wizarding_Game\\Image\\120x120\\Harry_Potter_Quidditch', (63,72,204), Maze_.start_position, "light"), Character.Bonhomme(self.screen, self.background, 'Wizarding_Game\\Image\\120x120\\Harry_Potter', (63,72,204), Maze_.start_position, "neutral")
        #self.spells[0]['Character_Spell'] = Character.Spells(self.screen, self.FPS, self.background_color, self.character[0])
        #self.spells[1]['Character_Spell'] = Character.Spells(self.screen, self.FPS, self.background_color, self.character[1])

        # Main loop
        while( self._running ):
            milliseconds = clock.tick(self.FPS)  # Milliseconds passed since last frame
            seconds = milliseconds / 1000.0 # Seconds passed since last frame (float)
            playtime += seconds
            cycletime[0] += seconds
            cycletime[1] += seconds
            # Managing events
            for event in pygame.event.get():
                self.on_event(event)
            # Display FPS
            pygame.display.set_caption("Wizarding Game"" : limit FPS to {}"
                               " (now: {:.2f})".format(self.FPS,clock.get_fps()))
            self.on_loop(int(clock.get_fps()))
            # Center of loop
            # stop allows to close the pygame window when the maze is complete (only way I found to make it work)
            stop = self.character[0].draw_motion(self.key[2], Maze_)
            stop = self.character[1].draw_motion(self.key[1], Maze_)
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