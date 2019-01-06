import pygame
from pygame.locals import *
import math
import Maze
import Character
import time
import Menu
import ctypes
import os


class App:
    # Creation of App object
    def __init__(self):
        self._running = True
        self.screen = None
        self.background = None
        # Adapt the pygame widow to the monitor
        # user32 = ctypes.windll.user32
        # user32.SetProcessDPIAware()
        self.size = self.weight, self.height = None, None
        #self.size = self.weight, self.height = user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)
        self.background = None
        self.FPS = 60
        self.text = [None, self.FPS]
        self.print_FPS = True
        # One key for each character
        self.key = {1:None, 2:None}
        self.interval = None
        self.background_color = (20,20,20)
        self.character = [[None],[None]]
        self.animation_timer = [0,0]
        self.position_character = [None, None, None, None]
        self.menu = Menu.Game_Start_Menu()
        self.pause_menu = None
        self.pause = False
        self.pause_background = None
        self.font = None

    # Initialisation of App object
    def on_init(self):
        pygame.init()
        self.background = pygame.transform.rotozoom(pygame.image.load(os.path.join("Wizarding_Game","Image","120x120","Tiles","1rst_Map.png")),0, 1)
        self.size = self.weight, self.height = self.background.get_size()
        self.screen = pygame.display.set_mode((self.size),  (pygame.FULLSCREEN))
        self.screen.set_colorkey((63,72,204))
        self._running = True
        self.text[0] = pygame.font.SysFont('mono', 12, bold=True)
        self.pause_menu = Menu.Game_Pause_Menu(self.screen, self.background)

    # Event
    def on_event(self, event):
        if event.type == pygame.QUIT:
            # If user close the widow
            self._running = False
        elif event.type == pygame.KEYDOWN:
            # If user press ESC
            if event.key == pygame.K_ESCAPE:
                self.pause = True
            elif event.key == pygame.K_F2:
                self._running = False
            elif event.key == pygame.K_F1:
                if self.print_FPS:
                    self.print_FPS = False
                else:
                    self.print_FPS = True
            # 1rst Character
            elif event.key == pygame.K_1:
                if self.character[0].alive and self.character[0].spells.lock_spells[0] == False and self.character[0].spells.lock_spells[1] == False and self.character[0].spells.lock_spells[2] == False and self.character[0].spells.lock_spells[3] == False and self.character[0].spells.lock_spells[4] == False and self.character[0].spells.lock_spells[5] == False:
                    self.character[0].spells.running = True
                    self.character[0].spells.number = 1
                    self.character[0].spells.path_spell = self.character[0].spells.which_spell()
                    if self.character[0].spells.lock_spells[0] == False:
                        self.character[0].spells.animation, self.character[0].spells.animation_both = self.character[0].spells.set_animation()
                        self.character[0].spells.lock_spells[0] = True
            elif event.key == pygame.K_2:
                if self.character[0].alive and self.character[0].spells.lock_spells[0] == False and self.character[0].spells.lock_spells[1] == False and self.character[0].spells.lock_spells[2] == False and self.character[0].spells.lock_spells[3] == False and self.character[0].spells.lock_spells[4] == False and self.character[0].spells.lock_spells[5] == False:
                    self.character[0].spells.running = True
                    self.character[0].spells.number = 2
                    self.character[0].spells.path_spell = self.character[0].spells.which_spell()
                    if self.character[0].spells.lock_spells[1] == False:
                        self.character[0].spells.animation, self.character[0].spells.animation_both = self.character[0].spells.set_animation()
                        self.character[0].spells.lock_spells[1] = True
            elif event.key == pygame.K_3:
                if self.character[0].alive and self.character[0].spells.lock_spells[0] == False and self.character[0].spells.lock_spells[1] == False and self.character[0].spells.lock_spells[2] == False and self.character[0].spells.lock_spells[3] == False and self.character[0].spells.lock_spells[4] == False and self.character[0].spells.lock_spells[5] == False:
                    self.character[0].spells.running = True
                    self.character[0].spells.number = 3
                    self.character[0].spells.path_spell = self.character[0].spells.which_spell()
                    if self.character[0].spells.lock_spells[2] == False:
                        self.character[0].spells.animation, self.character[0].spells.animation_both = self.character[0].spells.set_animation()
                        self.character[0].spells.lock_spells[2] = True
            # 2nd Character
            elif event.key == pygame.K_KP1:
                if self.menu.mode == 'multiplayer':
                    if self.character[1].alive and self.character[1].spells.lock_spells[0] == False and self.character[1].spells.lock_spells[1] == False and self.character[1].spells.lock_spells[2] == False and self.character[1].spells.lock_spells[3] == False and self.character[1].spells.lock_spells[4] == False and self.character[1].spells.lock_spells[5] == False:
                        self.character[1].spells.running = True
                        self.character[1].spells.number = 1
                        self.character[1].spells.path_spell = self.character[1].spells.which_spell()
                        if self.character[1].spells.lock_spells[0] == False:
                            self.character[1].spells.animation, self.character[1].spells.animation_both = self.character[1].spells.set_animation()
                            self.character[1].spells.lock_spells[0] = True
            elif event.key == pygame.K_KP2:
                if self.menu.mode == 'multiplayer':
                    if self.character[1].alive and self.character[1].spells.lock_spells[0] == False and self.character[1].spells.lock_spells[1] == False and self.character[1].spells.lock_spells[2] == False and self.character[1].spells.lock_spells[3] == False and self.character[1].spells.lock_spells[4] == False and self.character[1].spells.lock_spells[5] == False:
                        self.character[1].spells.running = True
                        self.character[1].spells.number = 2
                        self.character[1].spells.path_spell = self.character[1].spells.which_spell()
                        if self.character[1].spells.lock_spells[1] == False:
                            self.character[1].spells.animation, self.character[1].spells.animation_both = self.character[1].spells.set_animation()
                            self.character[1].spells.lock_spells[1] = True
            elif event.key == pygame.K_KP3:
                if self.menu.mode == 'multiplayer':
                    if self.character[1].alive and self.character[1].spells.lock_spells[0] == False and self.character[1].spells.lock_spells[1] == False and self.character[1].spells.lock_spells[2] == False and self.character[1].spells.lock_spells[3] == False and self.character[1].spells.lock_spells[4] == False and self.character[1].spells.lock_spells[5] == False:
                        self.character[1].spells.running = True
                        self.character[1].spells.number = 3
                        self.character[1].spells.path_spell = self.character[1].spells.which_spell()
                        if self.character[1].spells.lock_spells[2] == False:
                            self.character[1].spells.animation, self.character[1].spells.animation_both = self.character[1].spells.set_animation()
                            self.character[1].spells.lock_spells[2] = True
            elif event.key == pygame.K_4:
                pass
            elif event.key == pygame.K_KP4:
                pass
            elif event.key == pygame.K_5:
                pass
            elif event.key == pygame.K_KP5:
                pass
            elif event.key == pygame.K_6:
                pass
            elif event.key == pygame.K_KP6:
                pass
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

    #
    def print_FPS_(self, clock_fps):
        if self.print_FPS:
            self.text[1] = "FPS : {}".format(clock_fps)
            self.text[0].size(self.text[1])
            surface = self.text[0].render(self.text[1], True, (0,255,0))
            self.screen.blit(surface, (0, 0))

    # Closing
    def on_cleanup(self):
        pygame.quit()

    # Execution
    def on_execute(self):
        # Menu
        self.menu.run_start()
        if not(self.menu.quit):
            if self.on_init() == False:
                self._running = False

            # Initialisation of variables
            self.pause_menu.language = self.menu.language
            clock = pygame.time.Clock()
            self.FPS = 60 # FPS max
            playtime = 0 # Time playedd
            cycletime = [0,0] # Cycle for animation
            self.interval = 0.5 # Interval for displaying animations
            Maze_ = Maze.Maze(self.screen) # Maze object

            # Character objects
            if self.menu.mode == 'singleplayer':
                self.character[0] =  Character.Character(self.screen, self.background, os.path.join("Wizarding_Game","Image","120x120","Characters","Albus_Dumbledore"), (63,72,204), Maze_.start_position, "light")
                self.character[1] =  Character.Character(self.screen, self.background, os.path.join("Wizarding_Game","Image","120x120","Characters","Harry_Potter"), (63,72,204), (int(self.weight*0.313), int(self.height*0.278)), "neutral")
                self.character.append(Character.Character(self.screen, self.background, os.path.join("Wizarding_Game","Image","120x120","Characters","Voldemort"), (63,72,204), (int(self.weight*0.260), int(self.height*0.556)), "darkness"))
            elif self.menu.mode == 'multiplayer':
                self.character[0] =  Character.Character(self.screen, self.background, os.path.join("Wizarding_Game","Image","120x120","Characters","Jules","Albus_Dumbledore"), (63,72,204), Maze_.start_position, "neutral")
                self.character[1] =  Character.Character(self.screen, self.background, os.path.join("Wizarding_Game","Image","120x120","Characters","Harry_Potter"), (63,72,204),  Maze_.start_position, "light")
                self.character.append(Character.Character(self.screen, self.background, os.path.join("Wizarding_Game","Image","120x120","Characters","Ronald_Weasley"), (63,72,204),  (int(self.weight*0.208), int(self.height*0.056)), "neutral"))
                self.character.append(Character.Character(self.screen, self.background, os.path.join("Wizarding_Game","Image","120x120","Characters","Hermione_Granger"), (63,72,204),  (int(self.weight*0.260), int(self.height*0.556)), "darkness"))

            # Main loop
            while (self._running) and not(self.menu.quit) and not(self.pause_menu.quit):
                if not(self.pause):
                    # Milliseconds passed since last frame
                    milliseconds = clock.tick(self.FPS)
                    # Seconds passed since last frame (float)
                    seconds = milliseconds / 1000.0
                    playtime += seconds
                    cycletime[0] += seconds
                    cycletime[1] += seconds
                    # Managing events
                    for event in pygame.event.get():
                        self.on_event(event)
                    # Display FPS
                    pygame.display.set_caption("Wizarding Game"" : limit FPS to {}"
                                       " (now: {:.2f})".format(self.FPS,clock.get_fps()))
                    self.print_FPS_(int(clock.get_fps()))
                    self.screen.blit(self.background, (0,0))

                    self.screen.blit(pygame.transform.rotozoom(pygame.image.load(os.path.join("Wizarding_Game","Image","120x120","Sprites","Sprite_Harry_Potter_Animation1.png")), 0, 1), (250,250))

                    # Center of loop
                    # stop allows to close the pygame window when the maze is complete (only way I found to make it work)
                    if self.menu.mode == 'singleplayer':
                        self.character[2].draw_NPC()
                        self.character[1].draw_NPC()
                        self.character[0].draw_motion(self.key[1], Maze_)
                    elif self.menu.mode == 'multiplayer':
                        self.character[3].draw_NPC()
                        self.character[2].draw_NPC()
                        self.character[1].draw_motion(self.key[2], Maze_)
                        self.character[0].draw_motion(self.key[1], Maze_)

                    # Managing damage with spells
                    for character in self.character:
                        if character.spells.running and (character.spells.number == 1 or character.spells.number == 3) and character.spells.index_animation > len(character.spells.animation)-6:
                            for other_character in self.character:
                                if character != other_character:
                                    if character.spells.position_attack[0]+character.spells.shift[str(character.spells.number)]['Length_Attack'][0] > other_character.hitbox[0] and character.spells.position_attack[0] < other_character.hitbox[0]+other_character.image_size[0] and character.spells.position_attack[1] > other_character.hitbox[1] and character.spells.position_attack[1]+character.spells.shift[str(character.spells.number)]['Length_Attack'][1] < other_character.hitbox[1]+other_character.image_size[1]:
                                        character.spells.hit_someone = True
                                        other_character.get_hit()

                    self.pause_menu.background = self.screen.copy()
                    if self.pause_menu.escape:
                        self.pause_menu.escape = False

                elif self.pause:
                    self.pause = self.pause_menu.run_pause()

                pygame.display.update()
                #Maze_.run_(stop)

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
