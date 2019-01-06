import os
import pygame
import time
import ctypes
import os

# Class that creates the start menu and manages the options and
# the differents menus
#
# size : tuple, size of the screen depending on the monitor used
# weight: int, size[0], height: int, size[1]
# screen : surface, the screen of the menu
# background : surface, background of the screen, , with the image depending on the screen's size
# FPS : int, desired dsiplayed frames per second
# quit : boolean, True is the user click on "quit" button
# _running : boolean, True while the user does not click on "play" button
# print_FPS : boolean, True if the user press F1 and wants to display the FPS rate
# menu : str, set the menu that has to be displayed (main menu, options, ...)
# language : str, language of the texts
# counter : str, counter to avoid multi-clicks
# font : dict, all the font needed for the different texts, with the size depending on the screen's size
# color : dict, all the color needed for the different texts
# dimensions : dict of dict, size of the buttons rectangle depending on the number of them in the menu
# position : dict of dict, position of the text and the button depending on the dimmensions of the screen


class Game_Start_Menu():
    """
    Constructor.
    """
    def __init__(self):
        pygame.init()
        # user32 = ctypes.windll.user32
        # user32.SetProcessDPIAware()
        self.size = self.weight, self.height = 1280, 720
        #self.size = self.weight, self.height = 1920, 1080 #user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)
        self.screen = pygame.display.set_mode((self.size))#, (pygame.FULLSCREEN))
        self.background = pygame.image.load(os.path.join("Wizarding_Game","Image","start_menu","Background_"+str(self.weight)+"_"+str(self.height)+".png"))
        self.FPS = 60
        self.quit = False
        self._running = True
        self.print_FPS = False
        self.menu = 'menu'
        self.language = 'english'
        self.counter = 0
        self.mode = None
        self.font =\
        {'Title':pygame.font.Font(os.path.join("Wizarding_Game","Image","start_menu","Police","harryp__.ttf"), min(int(self.height/5.4),int(self.weight/9.6))),
        'Menu':pygame.font.Font(os.path.join("Wizarding_Game","Image","start_menu","Police","PixieFont.ttf"),  min(int(self.height/18), int(self.weight/32))),
        'Option':pygame.font.Font(os.path.join("Wizarding_Game","Image","start_menu","Police","PixieFont.ttf"), min(int(self.height/21.6), int(self.weight/38.4)))}
        self.color =\
         {'Title':(255,215,0),
         'Shadow':(0,0,0),
         'Even_Button':(120,120,120),
         'Odd_Button':(157,143,114),
         'Light_Odd_Button':(177,163,124),
         'Light_Even_Button':(140,140,140)
         }
        self.dimensions =\
         {"Buttons":{
         '3':(int(self.weight*0.157),int(self.height*0.139)),
         '5':(int(self.weight*0.157),int(self.height*0.111)),
         '5_exit':(int(self.weight*0.157),int(self.height*0.083))}
         }
        self.positions =\
         {'Button':{"Menu":{'Play':(int(self.weight*0.401),int(self.height*0.361)),
                            'Jouer':(int(self.weight*0.385),int(self.height*0.361)),
                            'Options':(int(self.weight*0.375),int(self.height*0.519)),
                            'Quit':(int(self.weight*0.401),int(self.height*0.722)),
                            'Quitter':(int(self.weight*0.375),int(self.height*0.722))
                           },
                    "Play":{'Single':(int(self.weight*0.380),int(self.height*0.333)),
                            'Player_S':(int(self.weight*0.380),int(self.height*0.379)),
                            'Solo':(int(self.weight*0.401),int(self.height*0.354)),
                            'Multi':(int(self.weight*0.391),int(self.height*0.491)),
                            'Player_M':(int(self.weight*0.380),int(self.height*0.537)),
                            'Joueur':(int(self.weight*0.380),int(self.height*0.546)),
                            'Exit':(int(self.weight*0.401),int(self.height*0.722)),
                            'Retour':(int(self.weight*0.380), int(self.height*0.722))
                           },
                    "Option":{'Language':(int(self.weight*0.375), int(self.height*0.343)),
                              'Langue':(int(self.weight*0.390), int(self.height*0.343)),
                              'Video':(int(self.weight*0.396), int(self.height*0.481)),
                              'Sound':(int(self.weight*0.401), int(self.height*0.611)),
                              'Son':(int(self.weight*0.417), int(self.height*0.611)),
                              'Key':(int(self.weight*0.411), int(self.height*0.713)),
                              'Bindings':(int(self.weight*0.375), int(self.height*0.761)),
                              'Controles':(int(self.weight*0.375), int(self.height*0.741)),
                              'Exit':(int(self.weight*0.401), int(self.height*0.898)),
                              'Retour':(int(self.weight*0.391), int(self.height*0.898))
                              },
                    "Language":{'English':(int(self.weight*0.380), int(self.height*0.361)),
                                'Francais':(int(self.weight*0.375), int(self.height*0.519)),
                                'Exit':(int(self.weight*0.401), int(self.height*0.731)),
                                'Retour':(int(self.weight*0.380), int(self.height*0.731))
                               },
                    "Video":{'Full':(int(self.weight*0.390), int(self.height*0.324)),
                             'Screen':(int(self.weight*0.390), int(self.height*0.381)),
                             'Plein':(int(self.weight*0.390), int(self.height*0.324)),
                             'Ecran':(int(self.weight*0.390), int(self.height*0.381)),
                             'Window':(int(self.weight*0.375), int(self.height*0.519)),
                             'Fenetre':(int(self.weight*0.375), int(self.height*0.519)),
                             'Exit':(int(self.weight*0.401), int(self.height*0.731)),
                             'Retour':(int(self.weight*0.380), int(self.height*0.731))
                            },
                    "Sound":None,
                    "Key Bindings":None
                    },
         "Title":{'Title':(int(self.weight*0.239),int(self.height*0.111)),
                  'Menu':{"Become_a":(int(self.weight*0.547),int(self.height*0.278)),
                          "Wizard":(int(self.weight*0.555),int(self.height*0.324)),
                          "Sorcier":(int(self.weight*0.573),int(self.height*0.324))
                          }
                 },
         "Shadow":{'Title':int(self.weight*0.005),
                   'Menu':int(self.weight*0.003),
                   'Button_x':int(self.weight*0.010),
                   'Button_y':int(self.height*0.009)
                  },
         "Shape":{'3_buttons':{"1rst":(int(self.weight*0.354),int(self.height*0.315)),
                               "2nd":(int(self.weight*0.354),int(self.height*0.472)),
                               "3rd":(int(self.weight*0.354),int(self.height*0.685))
                              },
                  '5_buttons':{"1rst":(int(self.weight*0.354),int(self.height*0.315)),
                               "2nd":(int(self.weight*0.354),int(self.height*0.444)),
                               "3rd":(int(self.weight*0.354),int(self.height*0.574)),
                               "4th":(int(self.weight*0.354),int(self.height*0.704)),
                               "5th":(int(self.weight*0.354),int(self.height*0.880))
                              }
                 }
         }

    """
    Function that manages the events
    """
    def on_event(self, event):
        # If user close the widow
        if event.type == pygame.QUIT:
            self._running = False
        if event.type == pygame.KEYDOWN:
            # If user press ESC
            if event.key == pygame.K_ESCAPE:
                if self.menu == 'option':
                    self.screen.blit(self.background, (0,0))
                    self.menu = 'menu'
                if self.menu == 'language' or self.menu == 'video':
                    self.screen.blit(self.background, (0,0))
                    self.menu = 'option'
            # If user press F1
            elif event.key == pygame.K_F1:
                if self.print_FPS:
                    self.print_FPS = False
                    surface = pygame.image.load(os.path.join("Wizarding_Game","Image","start_menu","FPS_corner.png")).convert()
                    self.screen.blit(surface, (0,0))
                else:
                    self.print_FPS = True
            # If user press F2
            elif event.key == pygame.K_F2:
                pass

    """
    Function that displays the start menu
    """
    def run_start(self):
        clock = pygame.time.Clock()
        # Refresh the screen
        self.screen.blit(self.background, (0,0))
        # Main loop
        while self._running:
            # Clock for 60 fps
            clock.tick(self.FPS)
            # Event mannaging
            for event in pygame.event.get():
                self.on_event(event)

            # Display FPS
            if self.print_FPS:
                text = [pygame.font.SysFont('mono', 12, bold=True)]
                text.append("FPS : {}".format(int(clock.get_fps())))
                fps = text[0].render(text[1], True, (0,255,0))
                surface = pygame.image.load(os.path.join("Wizarding_Game","Image","start_menu","FPS_corner.png")).convert()
                self.screen.blit(surface, (0,0))
                self.screen.blit(fps, (0,0))

            # Display buttons
            self.button()
            # Display texts
            self.text()

            # Flip the screen
            pygame.display.flip()
        # Quit pygame
        pygame.quit()

    """
    Function that creates buttons depending on menu
    """
    def button(self):
        # Main menu
        if self.menu == 'menu':
            previous_menu = self.menu
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the different
            # menu switches because otherwise, it clicks instantly
            # on "Quit" when we click on "Exit"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # Play button
            # Shadow of the button for a "3D" visual effect
            Play = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['1rst'][0] and self.positions["Shape"]["3_buttons"]['1rst'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['1rst'][1]:
                # Displays the button with a lighter color
                Play = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Play"
                if click[0]:
                    # Break the main loop
                    self.menu = "play"
                    self.counter = 0
            else:
                # Else display it with its normal color
                Play = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # Options button
            # Same ...
            Options = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['2nd'][0] and self.positions["Shape"]["3_buttons"]['2nd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['2nd'][1]:
                Options = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Option"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Options = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # Quit button
            Quit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['3rd'][0] and self.positions["Shape"]["3_buttons"]['3rd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['3rd'][1]:
                Quit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Quit"
                if click[0]:
                    # Break the main loop ad quit pygame
                    self.quit = True
                    self._running = False
                    self.counter = 0
            else:
                Quit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # If the menu changes (user clicked on "option" for example)
            if self.menu != previous_menu:
                # It refreshes the screen
                self.screen.blit(self.background, (0,0))

        # Play menu
        elif self.menu == 'play':
            previous_menu = self.menu
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the different
            # menu switches because otherwise, it clicks instantly
            # on "Singleplayer" when we click on "Play"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # Singleplayer button
            # Shadow of the button for a "3D" visual effect
            Single_player = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['1rst'][0] and self.positions["Shape"]["3_buttons"]['1rst'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['1rst'][1]:
                # Displays the button with a lighter color
                Single_player = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Single player"
                if click[0]:
                    # Break the main loop
                    self._running = False
                    self.mode = "singleplayer"
                    self.counter = 0
            else:
                # Else display it with its normal color
                Single_player = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # Multi player button
            # Same ...
            Multi_player = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['2nd'][0] and self.positions["Shape"]["3_buttons"]['2nd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['2nd'][1]:
                Multi_player = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Option"
                if click[0]:
                    self._running = False
                    self.mode = "multiplayer"
                    self.counter = 0
            else:
                Multi_player = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # Exit button
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['3rd'][0] and self.positions["Shape"]["3_buttons"]['3rd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['3rd'][1]:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Quit"
                if click[0]:
                    # Break the main loop ad quit pygame
                    self.menu = "menu"
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # If the menu changes (user clicked on "option" for example)
            if self.menu != previous_menu:
                # It refreshes the screen
                self.screen.blit(self.background, (0,0))

        # Options menu
        elif self.menu == 'option':
            previous_menu = self.menu
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the different
            # menu switches because otherwise, it clicks instantly
            # on "Exit" and "Quit" when we click on "Exit"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # Language button
            Language = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['1rst'][0] and self.positions["Shape"]["5_buttons"]['1rst'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['1rst'][1]:
                Language = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["5_buttons"]['1rst'][0],self.positions["Shape"]["5_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Language"
                if click[0]:
                    self.menu = "language"
                    self.counter = 0
            else:
                Language = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["5_buttons"]['1rst'][0],self.positions["Shape"]["5_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Video button
            Video = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['2nd'][0] and self.positions["Shape"]["5_buttons"]['2nd'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['2nd'][1]:
                Video = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["5_buttons"]['2nd'][0],self.positions["Shape"]["5_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Video"
                if click[0]:
                    self.menu = "video"
                    self.counter = 0
            else:
                Video = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["5_buttons"]['2nd'][0],self.positions["Shape"]["5_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Sound button
            Sound = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['3rd'][0] and self.positions["Shape"]["5_buttons"]['3rd'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['3rd'][1]:
                Sound = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["5_buttons"]['3rd'][0],self.positions["Shape"]["5_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Sound"
                if click[0]:
                    pass
            else:
                Sound = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["5_buttons"]['3rd'][0],self.positions["Shape"]["5_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Key Bindings button
            KeyBindings = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['4th'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['4th'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['4th'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['4th'][0] and self.positions["Shape"]["5_buttons"]['4th'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['4th'][1]:
                KeyBindings = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["5_buttons"]['4th'][0],self.positions["Shape"]["5_buttons"]['4th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Key Bindings"
                if click[0]:
                    pass
            else:
                KeyBindings = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["5_buttons"]['4th'][0],self.positions["Shape"]["5_buttons"]['4th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Exit button (to main menu)
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['5th'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['5th'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5_exit'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['5th'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['5th'][0] and self.positions["Shape"]["5_buttons"]['5th'][1]+self.dimensions["Buttons"]['5_exit'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['5th'][1]:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["5_buttons"]['5th'][0],self.positions["Shape"]["5_buttons"]['5th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5_exit'][1]))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'menu'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["5_buttons"]['5th'][0],self.positions["Shape"]["5_buttons"]['5th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5_exit'][1]))
            # If the menu changes (user clicked on "language" for example)
            if self.menu != previous_menu:
                # It refreshesthe screen
                self.screen.blit(self.background, (0,0))

        # Language menu
        elif self.menu == 'language':
            previous_menu = self.menu
            previous_language = self.language
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the switch
            # of menu because otherwise, it clicks instantly
            # on "English" when we click on "Language"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # English button
            English = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['1rst'][0] and self.positions["Shape"]["3_buttons"]['1rst'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['1rst'][1]:
                English = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "English"
                if click[0]:
                    self.language = 'english'
            else:
                English = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # French button
            Francais = pygame.draw.rect(self.screen, self.color['Shadow'],  (self.positions["Shape"]["3_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['2nd'][0] and self.positions["Shape"]["3_buttons"]['2nd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['2nd'][1]:
                Francais = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Français"
                if click[0]:
                    self.language = 'francais'
            else:
                Francais = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # Exit button
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['3rd'][0] and self.positions["Shape"]["3_buttons"]['3rd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['3rd'][1]:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # If the menu changes (user clicked on "Exit" for example)
            if self.menu != previous_menu or self.language != previous_language:
                # It refreshes the screen
                self.screen.blit(self.background, (0,0))

        # Video menu
        elif self.menu == 'video':
            previous_menu = self.menu
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the switch
            # of menu because otherwise, it clicks instantly
            # on "Window" when we click on "Video"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # English button
            FullScreen = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['1rst'][0] and self.positions["Shape"]["3_buttons"]['1rst'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['1rst'][1]:
                FullScreen = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Full screen"
                if click[0]:
                    self.screen = pygame.display.set_mode((1920,1080), (pygame.FULLSCREEN))
                    self.screen.blit(self.background, (0,0))
            else:
                FullScreen = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # French button
            Window = pygame.draw.rect(self.screen, self.color['Shadow'],  (self.positions["Shape"]["3_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['2nd'][0] and self.positions["Shape"]["3_buttons"]['2nd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['2nd'][1]:
                Window = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Window"
                if click[0]:
                    self.screen = pygame.display.set_mode((1920,1080), (pygame.RESIZABLE))
                    self.screen.blit(self.background, (0,0))
            else:
                Window = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # Exit button
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['3rd'][0] and self.positions["Shape"]["3_buttons"]['3rd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['3rd'][1]:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # If the menu changes (user cliked on "Exit" for example )
            if self.menu != previous_menu:
                # It refreshes the screen
                self.screen.blit(self.background, (0,0))

    """
    Function that write all the text on the start menu screen.
    Write every title text 2 times to make a shadow.
    Write buttons text.
    Every text depends on the language chose by the user
    """
    def text(self):
        if self.language == 'english':
            # Title
            # Displays "Wizarding Game" and "Become a Wizard"
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizarding_Game, (self.positions["Title"]['Title'][0]+self.positions["Shadow"]['Title'], self.positions["Title"]['Title'][1]))
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizarding_Game, self.positions["Title"]['Title'])
            Become_a = self.font['Menu'].render("Become a", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Become_a, (self.positions['Title']["Menu"]['Become_a'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Become_a'][1]))
            Become_a = self.font['Menu'].render("Become a", True, self.color['Title']).convert_alpha()
            self.screen.blit(Become_a, self.positions['Title']["Menu"]['Become_a'])
            Wizard = self.font['Menu'].render("Wizard", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizard, (self.positions['Title']["Menu"]['Wizard'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Wizard'][1]))
            Wizard = self.font['Menu'].render("Wizard", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizard, self.positions['Title']["Menu"]['Wizard'])


            # Buttons text
            # Menu's buttons
            if self.menu == 'menu':
                Play = self.font['Menu'].render("Play", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Play, self.positions["Button"]["Menu"]["Play"])
                Options = self.font['Menu'].render("Options", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Options, self.positions["Button"]["Menu"]["Options"])
                Quit = self.font['Menu'].render("Quit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Quit, self.positions["Button"]["Menu"]["Quit"])

            # Play's buttons
            elif self.menu == 'play':
                Single = self.font['Menu'].render("Single", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Single, self.positions["Button"]['Play']['Single'])
                Player = self.font['Menu'].render("Player", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Player, self.positions["Button"]['Play']['Player_S'])
                Multi = self.font['Menu'].render("Multi", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Multi, self.positions["Button"]['Play']['Multi'])
                self.screen.blit(Player, self.positions["Button"]['Play']['Player_M'])
                Exit = self.font['Menu'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, self.positions["Button"]['Play']['Exit'])

            # Options's buttons
            elif self.menu == 'option':
                Language = self.font['Option'].render("Language", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Language, self.positions["Button"]['Option']['Language'])
                Video = self.font['Option'].render("Video", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Video, self.positions["Button"]['Option']['Video'])
                Sound = self.font['Option'].render("Sound", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Sound, self.positions["Button"]['Option']['Sound'])
                Key = self.font['Option'].render("Key", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Key, self.positions["Button"]['Option']['Key'])
                Bindings = self.font['Option'].render("Bindings", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Bindings, self.positions["Button"]['Option']['Bindings'])
                Exit = self.font['Option'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, self.positions["Button"]['Option']['Exit'])

            # Language's buttons
            elif self.menu == 'language':
                English = self.font['Menu'].render("English", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(English, self.positions["Button"]['Language']['English'])
                Francais = self.font['Menu'].render("Francais", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Francais, self.positions["Button"]['Language']['Francais'])
                Exit = self.font['Menu'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, self.positions["Button"]['Language']['Exit'])

            # Video's buttons
            elif self.menu == 'video':
                Full = self.font['Menu'].render("Full", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Full, self.positions["Button"]['Video']['Full'])
                Screen = self.font['Menu'].render("Screen", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Screen, self.positions["Button"]['Video']['Screen'])
                Window = self.font['Menu'].render("Window", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Window, self.positions["Button"]['Video']['Window'])
                Exit = self.font['Menu'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, self.positions["Button"]['Video']['Exit'])

        elif self.language == 'francais':
            # Title
            # Displays "Wizarding Game" and "Devient un Sorcier"
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizarding_Game, (self.positions["Title"]['Title'][0]+self.positions["Shadow"]['Title'], self.positions["Title"]['Title'][1]))
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizarding_Game, self.positions["Title"]['Title'])
            Devient_un = self.font['Menu'].render("Devient un", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Devient_un,  (self.positions['Title']["Menu"]['Become_a'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Become_a'][1]))
            Devient_un = self.font['Menu'].render("Devient un", True, self.color['Title']).convert_alpha()
            self.screen.blit(Devient_un, self.positions['Title']["Menu"]['Become_a'])
            Sorcier = self.font['Menu'].render("Sorcier", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Sorcier, (self.positions['Title']["Menu"]['Sorcier'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Sorcier'][1]))
            Sorcier = self.font['Menu'].render("Sorcier", True, self.color['Title']).convert_alpha()
            self.screen.blit(Sorcier, self.positions['Title']["Menu"]['Sorcier'])

            # Button
            # Menu's buttons
            if self.menu == 'menu':
                Jouer = self.font['Menu'].render("Jouer", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Jouer, self.positions["Button"]['Menu']["Jouer"])
                Options = self.font['Menu'].render("Options", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Options, self.positions["Button"]['Menu']["Options"])
                Quitter = self.font['Menu'].render("Quitter", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Quitter, self.positions["Button"]["Menu"]["Quitter"])

            # Play's buttons
            elif self.menu == 'play':
                Solo = self.font['Menu'].render("Solo", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Solo, self.positions["Button"]['Play']['Solo'])
                Multi = self.font['Menu'].render("Multi", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Multi, self.positions["Button"]['Play']['Multi'])
                Joueur = self.font['Menu'].render("Joueur", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Joueur, self.positions["Button"]['Play']['Joueur'])
                Retour = self.font['Menu'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, self.positions["Button"]['Play']['Retour'])

            # Option's buttons
            elif self.menu == 'option':
                Langue = self.font['Option'].render("Langue", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Langue, self.positions["Button"]['Option']['Langue'])
                Video = self.font['Option'].render("Video", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Video, self.positions["Button"]['Option']['Video'])
                Son = self.font['Option'].render("Son", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Son, self.positions["Button"]['Option']['Son'])
                Controles = self.font['Option'].render("Controles", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Controles, self.positions["Button"]['Option']['Controles'])
                Retour = self.font['Option'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, self.positions["Button"]['Option']['Retour'])

            # Language's buttons
            elif self.menu == 'language':
                English = self.font['Menu'].render("English", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(English, self.positions["Button"]['Language']['English'])
                Francais = self.font['Menu'].render("Francais", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Francais, self.positions["Button"]['Language']['Francais'])
                Retour = self.font['Menu'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, self.positions["Button"]['Language']['Retour'])

            # Video's buttons
            elif self.menu == 'video':
                Plein = self.font['Menu'].render("Plein", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Plein, self.positions["Button"]['Video']['Plein'])
                Ecran = self.font['Menu'].render("Ecran", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Ecran, self.positions["Button"]['Video']['Ecran'])
                Fenetre = self.font['Menu'].render("Fenetre", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Fenetre, self.positions["Button"]['Video']['Fenetre'])
                Retour = self.font['Menu'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, self.positions["Button"]['Video']['Retour'])


# Class that manage the pause menu (when the player press 'escape').
# Basically the same as the start menu except that the background is the
# the previous frame of the game.
# It return False to the game when the player want to resume the game
# (Resume button or escape)
#
# screen : surface, the main screen
# background : surface, background of the screen (last frame of the game)
# FPS : int, desired dsiplayed frames per second
# quit : boolean, True is the user click on "quit" button
# _running : boolean, True while the user does not click on "play" button
# print_FPS : boolean, True if the user press F1 and wants to display the FPS rate
# menu : str, set the menu that has to be displayed (main menu, options, ...)
# language : str, language of the texts
# counter : str, counter to avoid multi-clicks
# escape : boolean, True if the user press escape when he is on the main menu, resumes the game
# font : dict, all the font needed for the different texts, with the size depending on the screen's size
# color : dict, all the color needed for the different texts
# dimensions : dict of dict, size of the buttons rectangle depending on the number of them in the menu
# position : dict of dict, position of the text and the button depending on the dimmensions of the screen

class Game_Pause_Menu():
    """
    Constructor.

    :param screen: the main screen
    :type screen: surface

    :param background: the background of the screen
    :type background: surface
    """
    def __init__(self, screen=None, background=None):
        pygame.init()
        self.screen = screen
        self.background = background
        self.weight, self.height = self.screen.get_size()
        self.FPS = 60
        self.quit = False
        self._running = True
        self.print_FPS = False
        self.menu = 'menu'
        self.language = 'francais'
        self.counter = 0
        self.escape = False
        self.font =\
        {'Title':pygame.font.Font(os.path.join("Wizarding_Game","Image","start_menu","Police","harryp__.ttf"), min(int(self.height/5.4),int(self.weight/9.6))),
        'Menu':pygame.font.Font(os.path.join("Wizarding_Game","Image","start_menu","Police","PixieFont.ttf"), min(int(self.height/18), int(self.weight/32))),
        'Option':pygame.font.Font(os.path.join("Wizarding_Game","Image","start_menu","Police","PixieFont.ttf"), min(int(self.height/21.6), int(self.weight/38.4)))}
        self.color =\
         {'Title':(255,215,0),
         'Shadow':(0,0,0),
         'Even_Button':(120,120,120),
         'Odd_Button':(157,143,114),
         'Light_Odd_Button':(177,163,124),
         'Light_Even_Button':(140,140,140)
         }
        self.dimensions =\
         {"Buttons":{
         '3':(int(self.weight*0.157),int(self.height*0.139)),
         '5':(int(self.weight*0.157),int(self.height*0.111)),
         '5_exit':(int(self.weight*0.157),int(self.height*0.083))}
         }
        self.positions =\
         {"Button":{'Menu':{"Resume":(int(self.weight*0.370),int(self.height*0.361)),
                            "Reprendre":(int(self.weight*0.354),int(self.height*0.361)),
                            "Options":(int(self.weight*0.375),int(self.height*0.519)),
                            "Quit":(int(self.weight*0.401),int(self.height*0.722)),
                            "Quitter":(int(self.weight*0.375),int(self.height*0.722))
                           },
                    "Option":{'Language':(int(self.weight*0.375), int(self.height*0.343)),
                               'Langue':(int(self.weight*0.390), int(self.height*0.343)),
                               'Video':(int(self.weight*0.396), int(self.height*0.481)),
                               'Sound':(int(self.weight*0.401), int(self.height*0.611)),
                               'Son':(int(self.weight*0.417), int(self.height*0.611)),
                               'Key':(int(self.weight*0.411), int(self.height*0.713)),
                               'Bindings':(int(self.weight*0.375), int(self.height*0.761)),
                               'Controles':(int(self.weight*0.375), int(self.height*0.741)),
                               'Exit':(int(self.weight*0.401), int(self.height*0.898)),
                               'Retour':(int(self.weight*0.391), int(self.height*0.898))
                              },
                    "Language":{'English':(int(self.weight*0.380), int(self.height*0.361)),
                                'Francais':(int(self.weight*0.375), int(self.height*0.519)),
                                'Exit':(int(self.weight*0.401), int(self.height*0.731)),
                                'Retour':(int(self.weight*0.380), int(self.height*0.731))
                               },
                    "Video":{'Full':(int(self.weight*0.390), int(self.height*0.324)),
                             'Screen':(int(self.weight*0.390), int(self.height*0.381)),
                             'Plein':(int(self.weight*0.390), int(self.height*0.324)),
                             'Ecran':(int(self.weight*0.390), int(self.height*0.381)),
                             'Window':(int(self.weight*0.375), int(self.height*0.519)),
                             'Fenetre':(int(self.weight*0.375), int(self.height*0.519)),
                             'Exit':(int(self.weight*0.401), int(self.height*0.731)),
                             'Retour':(int(self.weight*0.380), int(self.height*0.731))
                            },
                    "Sound":None,
                    "Key Bindings":None
                    },
         "Title":{'Title':(int(self.weight*0.239),int(self.height*0.111)),
                  'Menu':{"Become_a":(int(self.weight*0.547),int(self.height*0.278)),
                          "Wizard":(int(self.weight*0.555),int(self.height*0.324)),
                          "Sorcier":(int(self.weight*0.573),int(self.height*0.324))
                          }
                 },
         "Shadow":{'Title':int(self.weight*0.005),
                   'Menu':int(self.weight*0.003),
                   'Button_x':int(self.weight*0.010),
                   'Button_y':int(self.height*0.009)
                  },
         "Shape":{'3_buttons':{"1rst":(int(self.weight*0.354),int(self.height*0.315)),
                               "2nd":(int(self.weight*0.354),int(self.height*0.472)),
                               "3rd":(int(self.weight*0.354),int(self.height*0.685))
                              },
                  '5_buttons':{"1rst":(int(self.weight*0.354),int(self.height*0.315)),
                               "2nd":(int(self.weight*0.354),int(self.height*0.444)),
                               "3rd":(int(self.weight*0.354),int(self.height*0.574)),
                               "4th":(int(self.weight*0.354),int(self.height*0.704)),
                               "5th":(int(self.weight*0.354),int(self.height*0.880))
                              }
                 }
         }

    """
    Function that manage the event
    """
    def on_event(self, event):
        # If user close the widow
        if event.type == pygame.QUIT:
            self._running = False
        if event.type == pygame.KEYDOWN:
            # If user press ESC
            if event.key == pygame.K_ESCAPE:
                if self.menu == 'menu':
                    self.escape = True
                if self.menu == 'option':
                    self.screen.blit(self.background, (0,0))
                    self.menu = 'menu'
                if self.menu == 'language' or self.menu == 'video':
                    self.screen.blit(self.background, (0,0))
                    self.menu = 'option'
    """
    Function that display the pause menu
    """
    def run_pause(self):
        # If user pressed escape
        if self.escape:
            return False
        clock = pygame.time.Clock()
        # Refreshes the screen
        self.screen.blit(self.background, (0,0))
        # Clock for 60 fps
        clock.tick(self.FPS)
        # Event mannaging
        for event in pygame.event.get():
            self.on_event(event)
        # Display FPS
        if self.print_FPS:
            text = [pygame.font.SysFont('mono', 12, bold=True)]
            text.append("FPS : {}".format(int(clock.get_fps())))
            fps = text[0].render(text[1], True, (0,255,0))
            surface = pygame.image.load(os.path.join("Wizarding_Game","Image","start_menu","FPS_corner.png")).convert()
            self.screen.blit(surface, (0,0))
            self.screen.blit(fps, (0,0))

        # result is returned to the game loop
        # Displays buttons
        result = self.button()
        # Displays texts
        self.text()
        if result == None:
            result = True
        return result

    """
    From here, it is exactly the same as the start menu, except
    that "play" button becomes "resume" button
    """
    def button(self):
        # Pause menu
        if self.menu == 'menu':
            previous_menu = self.menu
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the different
            # menu switches because otherwise, it clicks instantly
            # on "Quit" when we click on "Exit"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # Play button
            # Shadow of the button for a "3D" visual effect
            Resume = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['1rst'][0] and self.positions["Shape"]["3_buttons"]['1rst'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['1rst'][1]:
                # Displays the button with a lighter color
                Resume = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Resume"
                if click[0]:
                    # Break the main loop
                    self.escape = True
                    self.counter = 0
            else:
                # Else display it with its normal color
                Resume = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # Options button
            # Same ...
            Options = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['2nd'][0] and self.positions["Shape"]["3_buttons"]['2nd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['2nd'][1]:
                Options = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Option"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Options = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # Quit button
            Quit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['3rd'][0] and self.positions["Shape"]["3_buttons"]['3rd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['3rd'][1]:
                Quit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User clicks on "Quit"
                if click[0]:
                    # Break the main loop ad quit pygame
                    self.quit = True
                    self._running = False
                    self.counter = 0
            else:
                Quit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # If the menu changes (user clicked on "option" for example)
            if self.menu != previous_menu:
                # It refreshes the screen
                self.screen.blit(self.background, (0,0))

        # Options menu
        elif self.menu == 'option':
            previous_menu = self.menu
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the different
            # menu switches because otherwise, it clicks instantly
            # on "Exit" and "Quit" when we click on "Exit"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # Language button
            Language = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['1rst'][0] and self.positions["Shape"]["5_buttons"]['1rst'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['1rst'][1]:
                Language = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["5_buttons"]['1rst'][0],self.positions["Shape"]["5_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Language"
                if click[0]:
                    self.menu = "language"
                    self.counter = 0
            else:
                Language = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["5_buttons"]['1rst'][0],self.positions["Shape"]["5_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Video button
            Video = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['2nd'][0] and self.positions["Shape"]["5_buttons"]['2nd'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['2nd'][1]:
                Video = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["5_buttons"]['2nd'][0],self.positions["Shape"]["5_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Video"
                if click[0]:
                    self.menu = "video"
                    self.counter = 0
            else:
                Video = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["5_buttons"]['2nd'][0],self.positions["Shape"]["5_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Sound button
            Sound = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['3rd'][0] and self.positions["Shape"]["5_buttons"]['3rd'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['3rd'][1]:
                Sound = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["5_buttons"]['3rd'][0],self.positions["Shape"]["5_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Sound"
                if click[0]:
                    pass
            else:
                Sound = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["5_buttons"]['3rd'][0],self.positions["Shape"]["5_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Key Bindings button
            KeyBindings = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['4th'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['4th'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['4th'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['4th'][0] and self.positions["Shape"]["5_buttons"]['4th'][1]+self.dimensions["Buttons"]['5'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['4th'][1]:
                KeyBindings = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["5_buttons"]['4th'][0],self.positions["Shape"]["5_buttons"]['4th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))
                # User click on "Key Bindings"
                if click[0]:
                    pass
            else:
                KeyBindings = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["5_buttons"]['4th'][0],self.positions["Shape"]["5_buttons"]['4th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5'][1]))

            # Exit button (to main menu)
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['5th'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['5th'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5_exit'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["5_buttons"]['5th'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["5_buttons"]['5th'][0] and self.positions["Shape"]["5_buttons"]['5th'][1]+self.dimensions["Buttons"]['5_exit'][1] > mouse[1] > self.positions["Shape"]["5_buttons"]['5th'][1]:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["5_buttons"]['5th'][0],self.positions["Shape"]["5_buttons"]['5th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5_exit'][1]))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'menu'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["5_buttons"]['5th'][0],self.positions["Shape"]["5_buttons"]['5th'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['5_exit'][1]))
            # If the menu changes (user clicked on "language" for example)
            if self.menu != previous_menu:
                # It refreshesthe screen
                self.screen.blit(self.background, (0,0))

        # Language menu
        elif self.menu == 'language':
            previous_menu = self.menu
            previous_language = self.language
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the switch
            # of menu because otherwise, it clicks instantly
            # on "English" when we click on "Language"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # English button
            English = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['1rst'][0] and self.positions["Shape"]["3_buttons"]['1rst'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['1rst'][1]:
                English = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "English"
                if click[0]:
                    self.language = 'english'
            else:
                English = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # French button
            Francais = pygame.draw.rect(self.screen, self.color['Shadow'],  (self.positions["Shape"]["3_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['2nd'][0] and self.positions["Shape"]["3_buttons"]['2nd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['2nd'][1]:
                Francais = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Français"
                if click[0]:
                    self.language = 'francais'
            else:
                Francais = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # Exit button
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['3rd'][0] and self.positions["Shape"]["3_buttons"]['3rd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['3rd'][1]:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # If the menu changes (user clicked on "Exit" for example)
            if self.menu != previous_menu or self.language != previous_language:
                # It refreshes the screen
                self.screen.blit(self.background, (0,0))

        # Video menu
        elif self.menu == 'video':
            previous_menu = self.menu
            # Gets the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the switch
            # of menu because otherwise, it clicks instantly
            # on "Window" when we click on "Video"
            if self.counter < 10:
                click = [0,0,0]
                self.counter += 1
            # English button
            FullScreen = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["5_buttons"]['1rst'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["5_buttons"]['1rst'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['1rst'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['1rst'][0] and self.positions["Shape"]["3_buttons"]['1rst'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['1rst'][1]:
                FullScreen = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Full screen"
                if click[0]:
                    self.screen = pygame.display.set_mode((1920,1080), (pygame.FULLSCREEN))
                    self.screen.blit(self.background, (0,0))
            else:
                FullScreen = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['1rst'][0],self.positions["Shape"]["3_buttons"]['1rst'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # French button
            Window = pygame.draw.rect(self.screen, self.color['Shadow'],  (self.positions["Shape"]["3_buttons"]['2nd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['2nd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['2nd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['2nd'][0] and self.positions["Shape"]["3_buttons"]['2nd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['2nd'][1]:
                Window = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Window"
                if click[0]:
                    self.screen = pygame.display.set_mode((1920,1080), (pygame.RESIZABLE))
                    self.screen.blit(self.background, (0,0))
            else:
                Window = pygame.draw.rect(self.screen, self.color['Even_Button'], (self.positions["Shape"]["3_buttons"]['2nd'][0],self.positions["Shape"]["3_buttons"]['2nd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # Exit button
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (self.positions["Shape"]["3_buttons"]['3rd'][0]+self.positions["Shadow"]["Button_x"],self.positions["Shape"]["3_buttons"]['3rd'][1]+self.positions["Shadow"]["Button_y"],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
            # If the mouse is inside the button
            if self.positions["Shape"]["3_buttons"]['3rd'][0]+self.dimensions["Buttons"]['3'][0] > mouse[0] > self.positions["Shape"]["3_buttons"]['3rd'][0] and self.positions["Shape"]["3_buttons"]['3rd'][1]+self.dimensions["Buttons"]['3'][1] > mouse[1] > self.positions["Shape"]["3_buttons"]['3rd'][1]:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (self.positions["Shape"]["3_buttons"]['3rd'][0],self.positions["Shape"]["3_buttons"]['3rd'][1],self.dimensions["Buttons"]['3'][0],self.dimensions["Buttons"]['3'][1]))

            # If the menu changes (user cliked on "Exit" for example )
            if self.menu != previous_menu:
                # It refreshes the screen
                self.screen.blit(self.background, (0,0))


    """
    Function that write all the text on the start menu screen.
    Write every title text 2 times to make a shadow.
    Write buttons text.
    Every text depends on the language chose by the user
    """
    def text(self):
        if self.language == 'english':
            # Title
            # Displays "Wizarding Game" and "Become a Wizard"
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizarding_Game, (self.positions["Title"]['Title'][0]+self.positions["Shadow"]['Title'], self.positions["Title"]['Title'][1]))
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizarding_Game, self.positions["Title"]['Title'])
            Become_a = self.font['Menu'].render("Become a", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Become_a, (self.positions['Title']["Menu"]['Become_a'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Become_a'][1]))
            Become_a = self.font['Menu'].render("Become a", True, self.color['Title']).convert_alpha()
            self.screen.blit(Become_a, self.positions['Title']["Menu"]['Become_a'])
            Wizard = self.font['Menu'].render("Wizard", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizard, (self.positions['Title']["Menu"]['Wizard'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Wizard'][1]))
            Wizard = self.font['Menu'].render("Wizard", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizard, self.positions['Title']["Menu"]['Wizard'])


            # Buttons text
            # Menu's buttons
            if self.menu == 'menu':
                Resume = self.font['Menu'].render("Resume", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Resume, self.positions["Button"]["Menu"]["Resume"])
                Options = self.font['Menu'].render("Options", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Options, self.positions["Button"]["Menu"]["Options"])
                Quit = self.font['Menu'].render("Quit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Quit, self.positions["Button"]["Menu"]["Quit"])
            # Options's buttons
            elif self.menu == 'option':
                Language = self.font['Option'].render("Language", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Language, self.positions["Button"]['Option']['Language'])
                Video = self.font['Option'].render("Video", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Video, self.positions["Button"]['Option']['Video'])
                Sound = self.font['Option'].render("Sound", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Sound, self.positions["Button"]['Option']['Sound'])
                Key = self.font['Option'].render("Key", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Key, self.positions["Button"]['Option']['Key'])
                Bindings = self.font['Option'].render("Bindings", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Bindings, self.positions["Button"]['Option']['Bindings'])
                Exit = self.font['Option'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, self.positions["Button"]['Option']['Exit'])
            # Language's buttons
            elif self.menu == 'language':
                English = self.font['Menu'].render("English", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(English, self.positions["Button"]['Language']['English'])
                Francais = self.font['Menu'].render("Francais", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Francais, self.positions["Button"]['Language']['Francais'])
                Exit = self.font['Menu'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, self.positions["Button"]['Language']['Exit'])
            # Video's buttons
            elif self.menu == 'video':
                Full = self.font['Menu'].render("Full", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Full, self.positions["Button"]['Video']['Full'])
                Screen = self.font['Menu'].render("Screen", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Screen, self.positions["Button"]['Video']['Screen'])
                Window = self.font['Menu'].render("Window", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Window, self.positions["Button"]['Video']['Window'])
                Exit = self.font['Menu'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, self.positions["Button"]['Video']['Exit'])

        elif self.language == 'francais':
            # Title
            # Displays "Wizarding Game" and "Devient un Sorcier"
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizarding_Game, (self.positions["Title"]['Title'][0]+self.positions["Shadow"]['Title'], self.positions["Title"]['Title'][1]))
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizarding_Game, self.positions["Title"]['Title'])
            Devient_un = self.font['Menu'].render("Devient un", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Devient_un,  (self.positions['Title']["Menu"]['Become_a'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Become_a'][1]))
            Devient_un = self.font['Menu'].render("Devient un", True, self.color['Title']).convert_alpha()
            self.screen.blit(Devient_un, self.positions['Title']["Menu"]['Become_a'])
            Sorcier = self.font['Menu'].render("Sorcier", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Sorcier, (self.positions['Title']["Menu"]['Sorcier'][0]+self.positions["Shadow"]['Menu'], self.positions['Title']["Menu"]['Sorcier'][1]))
            Sorcier = self.font['Menu'].render("Sorcier", True, self.color['Title']).convert_alpha()
            self.screen.blit(Sorcier, self.positions['Title']["Menu"]['Sorcier'])

            # Button
            # Menu's buttons
            if self.menu == 'menu':
                Reprendre = self.font['Menu'].render("Reprendre", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Reprendre, self.positions["Button"]['Menu']["Reprendre"])
                Options = self.font['Menu'].render("Options", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Options, self.positions["Button"]['Menu']["Options"])
                Quitter = self.font['Menu'].render("Quitter", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Quitter, self.positions["Button"]["Menu"]["Quitter"])

            # Option's buttons
            elif self.menu == 'option':
                Langue = self.font['Option'].render("Langue", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Langue, self.positions["Button"]['Option']['Langue'])
                Video = self.font['Option'].render("Video", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Video, self.positions["Button"]['Option']['Video'])
                Son = self.font['Option'].render("Son", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Son, self.positions["Button"]['Option']['Son'])
                Controles = self.font['Option'].render("Controles", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Controles, self.positions["Button"]['Option']['Controles'])
                Retour = self.font['Option'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, self.positions["Button"]['Option']['Retour'])
            # Language's buttons
            elif self.menu == 'language':
                English = self.font['Menu'].render("English", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(English, self.positions["Button"]['Language']['English'])
                Francais = self.font['Menu'].render("Francais", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Francais, self.positions["Button"]['Language']['Francais'])
                Retour = self.font['Menu'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, self.positions["Button"]['Language']['Retour'])
            # Video's buttons
            elif self.menu == 'video':
                Plein = self.font['Menu'].render("Plein", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Plein, self.positions["Button"]['Video']['Plein'])
                Ecran = self.font['Menu'].render("Ecran", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Ecran, self.positions["Button"]['Video']['Ecran'])
                Fenetre = self.font['Menu'].render("Fenetre", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Fenetre, self.positions["Button"]['Video']['Fenetre'])
                Retour = self.font['Menu'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, self.positions["Button"]['Video']['Retour'])
