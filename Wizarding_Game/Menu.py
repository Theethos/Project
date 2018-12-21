import os
import pygame
import time

class Game_Start_Menu():

    def __init__(self):
        pygame.init()
        self.size = self.weight, self.height = 1920, 1080
        self.screen = pygame.display.set_mode(self.size, (pygame.FULLSCREEN))
        #self.size = self.weight, self.height = 1600, 900
        self.background = pygame.image.load("Wizarding_Game\\Image\\start_menu\\Hogwarts.png")
        self.FPS = 60
        self.quit = False
        self._running = True
        self.print_FPS = False
        self.menu = 'menu'
        self.language = 'english'
        self.counter = 0
        self.font =\
        {'Title':pygame.font.Font('Wizarding_Game\\Image\\start_menu\\Police\\harryp__.ttf', 200),
        'Menu':pygame.font.Font('Wizarding_Game\\Image\\start_menu\\Police\\PixieFont.ttf', 60),
        'Option':pygame.font.Font('Wizarding_Game\\Image\\start_menu\\Police\\PixieFont.ttf', 50)}
        self.color =\
         {'Title':(255,215,0),
         'Shadow':(0,0,0),
         'Even_Button':(120,120,120),
         'Odd_Button':(157,143,114),
         'Light_Odd_Button':(177,163,124),
         'Light_Even_Button':(140,140,140)}


    """
    Manage the event
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
            elif event.key == pygame.K_F1:
                if self.print_FPS:
                    self.print_FPS = False
                    surface = pygame.image.load("Wizarding_Game\\Image\\start_menu\\FPS_corner.png").convert()
                    self.screen.blit(surface, (0,0))
                else:
                    self.print_FPS = True
            elif event.key == pygame.K_F2:
                pass

    """
    Function that display the start menu
    """
    def run_start(self):
        clock = pygame.time.Clock()
        # Loop for the start menu
        self.screen.blit(self.background, (0,0))
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
                surface = pygame.image.load("Wizarding_Game\\Image\\start_menu\\FPS_corner.png").convert()
                self.screen.blit(surface, (0,0))
                self.screen.blit(fps, (0,0))


            self.button()
            self.text()


            pygame.display.flip()
        # Quit pygame
        pygame.quit()

    """
    Function that display the pause menu
    """
    def run_pause(self):
        clock = pygame.time.Clock()
        # Loop for the start menu
        self.screen.blit(self.background, (0,0))
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
                surface = pygame.image.load("Wizarding_Game\\Image\\start_menu\\FPS_corner.png").convert()
                self.screen.blit(surface, (0,0))
                self.screen.blit(fps, (0,0))


            self.button()
            self.text()


            pygame.display.flip()
        # Quit pygame
        pygame.quit()

    """
    Create buttons depending on menu
    """
    def button(self):
        # Main menu
        if self.menu == 'menu':
            previous_menu = self.menu
            # Get the mouse position and if it clicks
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # Play button
            # Shadow of the button
            Play = pygame.draw.rect(self.screen, self.color['Shadow'], (700,350,300,150))
            # If the mouse is inside the button
            if 680+300 > mouse[0] > 680 and 340+150 > mouse[1] > 340:
                # Print it with a lighter color
                Play = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,340,300,150))
                # User click on "Play"
                if click[0]:
                    self._running = False
            else:
                # Else display it normaly
                Play = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,340,300,150))
            # Options button
            # Same ...
            Options = pygame.draw.rect(self.screen, self.color['Shadow'], (700,520,300,150))
            if 680+300 > mouse[0] > 680 and 510+150 > mouse[1] > 510:
                Options = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (680,510,300,150))
                # User click on "Option"
                if click[0]:
                    self.menu = 'option'
            else:
                Options = pygame.draw.rect(self.screen, self.color['Even_Button'], (680,510,300,150))
            # Quit button
            Quit = pygame.draw.rect(self.screen, self.color['Shadow'], (700,750,300,150))
            if 680+300 > mouse[0] > 680 and 680+150 > mouse[1] > 680:
                Quit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,740,300,150))
                # User click on "Quit"
                if click[0]:
                    self.quit = True
                    self._running = False
            else:
                Quit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,740,300,150))
            # If the menu changes
            if self.menu != previous_menu:
                self.screen.blit(self.background, (0,0))

        # Options menu
        if self.menu == 'option':
            previous_menu = self.menu
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the switch
            # of menu because otherwise, it clicks instantly
            # on "Video" when we click on "Option"
            if self.counter < 5:
                click = [0,0,0]
                self.counter += 1
            Language = pygame.draw.rect(self.screen, self.color['Shadow'], (700,350,300,120))
            if 680+300 > mouse[0] > 680 and 340+120 > mouse[1] > 340:
                Language = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,340,300,120))
                # User click on "Language"
                if click[0]:
                    self.menu = "language"
                    self.counter = 0

            else:
                Language = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,340,300,120))
            Video = pygame.draw.rect(self.screen, self.color['Shadow'], (700,490,300,120))
            if 680+300 > mouse[0] > 680 and 480+120 > mouse[1] > 480:
                Video = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (680,480,300,120))
                # User click on "Video"
                if click[0]:
                    self.menu = "video"
                    self.counter = 0
            else:
                Video = pygame.draw.rect(self.screen, self.color['Even_Button'], (680,480,300,120))
            Sound = pygame.draw.rect(self.screen, self.color['Shadow'], (700,630,300,120))
            if 680+300 > mouse[0] > 680 and 620+120 > mouse[1] > 620:
                Sound = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,620,300,120))
                # User click on "Sound"
                if click[0]:
                    pass
            else:
                Sound = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,620,300,120))
            KeyBindings = pygame.draw.rect(self.screen, self.color['Shadow'], (700,770,300,120))
            if 680+300 > mouse[0] > 680 and 760+120 > mouse[1] > 760:
                KeyBindings = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (680,760,300,120))
                # User click on "Key Bindings"
                if click[0]:
                    pass
            else:
                KeyBindings = pygame.draw.rect(self.screen, self.color['Even_Button'], (680,760,300,120))
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (700,960,300,90))
            if 680+300 > mouse[0] > 680 and 950+90 > mouse[1] > 950:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,950,300,90))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'menu'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,950,300,90))

            if self.menu != previous_menu:
                self.screen.blit(self.background, (0,0))

        # Language menu
        elif self.menu == 'language':
            previous_menu = self.menu
            previous_language = self.language
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the switch
            # of menu because otherwise, it clicks instantly
            # on "English" when we click on "Language"
            if self.counter < 5:
                click = [0,0,0]
                self.counter += 1
            # English button
            English = pygame.draw.rect(self.screen, self.color['Shadow'], (700,350,300,150))
            if 680+300 > mouse[0] > 680 and 340+150 > mouse[1] > 340:
                English = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,340,300,150))
                # User click on "English"
                if click[0]:
                    self.language = 'english'
            else:
                English = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,340,300,150))
            # French button
            Francais = pygame.draw.rect(self.screen, self.color['Shadow'],  (700,520,300,150))
            if 680+300 > mouse[0] > 680 and 510+150 > mouse[1] > 510:
                Francais = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (680,510,300,150))
                # User click on "Français"
                if click[0]:
                    self.language = 'francais'
            else:
                Francais = pygame.draw.rect(self.screen, self.color['Even_Button'], (680,510,300,150))
            # Exit button
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (700,750,300,150))
            if 680+300 > mouse[0] > 680 and 700+150 > mouse[1] > 700:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,740,300,150))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,740,300,150))

            # If the menu changes
            if self.menu != previous_menu or self.language != previous_language:
                self.screen.blit(self.background, (0,0))

        # Video menu
        elif self.menu == 'video':
            previous_menu = self.menu
            mouse = pygame.mouse.get_pos()
            click = pygame.mouse.get_pressed()
            # self.counter put a delay between the switch
            # of menu because otherwise, it clicks instantly
            # on "Window" when we click on "Video"
            if self.counter < 5:
                click = [0,0,0]
                self.counter += 1
            # English button
            FullScreen = pygame.draw.rect(self.screen, self.color['Shadow'], (700,350,300,150))
            if 680+300 > mouse[0] > 680 and 340+150 > mouse[1] > 340:
                FullScreen = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,340,300,150))
                # User click on "Full screen"
                if click[0]:
                    self.screen = pygame.display.set_mode((1920,1080), (pygame.FULLSCREEN))
                    self.screen.blit(self.background, (0,0))
            else:
                FullScreen = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,340,300,150))
            # French button
            Window = pygame.draw.rect(self.screen, self.color['Shadow'],  (700,520,300,150))
            if 680+300 > mouse[0] > 680 and 510+150 > mouse[1] > 510:
                Window = pygame.draw.rect(self.screen, self.color['Light_Even_Button'], (680,510,300,150))
                # User click on "Français"
                if click[0]:
                    self.screen = pygame.display.set_mode((1920,1080), (pygame.RESIZABLE))
                    self.screen.blit(self.background, (0,0))
            else:
                Window = pygame.draw.rect(self.screen, self.color['Even_Button'], (680,510,300,150))
            # Exit button
            Exit = pygame.draw.rect(self.screen, self.color['Shadow'], (700,750,300,150))
            if 680+300 > mouse[0] > 680 and 700+150 > mouse[1] > 700:
                Exit = pygame.draw.rect(self.screen, self.color['Light_Odd_Button'], (680,740,300,150))
                # User click on "Exit"
                if click[0]:
                    self.menu = 'option'
                    self.counter = 0
            else:
                Exit = pygame.draw.rect(self.screen, self.color['Odd_Button'], (680,740,300,150))

            # If the menu changes
            if self.menu != previous_menu:
                self.screen.blit(self.background, (0,0))

    """
    Write all the text on the menu screen
    Write every text 2 times to make a shadow
    Also write buttons text
    """
    def text(self):
        if self.language == 'english':
            # Title
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizarding_Game, (460,120))
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizarding_Game, (450,120))
            Become_a = self.font['Menu'].render("Become a", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Become_a, (1055,300))
            Become_a = self.font['Menu'].render("Become a", True, self.color['Title']).convert_alpha()
            self.screen.blit(Become_a, (1050,300))
            Wizard = self.font['Menu'].render("Wizard", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizard, (1070,350))
            Wizard = self.font['Menu'].render("Wizard", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizard, (1065,350))

            # Button
            if self.menu == 'menu':
                Play = self.font['Menu'].render("Play", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Play, (770,390))
                Options = self.font['Menu'].render("Options", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Options, (720,560))
                Quit = self.font['Menu'].render("Quit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Quit, (770,780))
            elif self.menu == 'option':
                Language = self.font['Option'].render("Language", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Language, (720,370))
                Video = self.font['Option'].render("Video", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Video, (760,520))
                Sound = self.font['Option'].render("Sound", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Sound, (770,660))
                Key = self.font['Option'].render("Key", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Key, (790,770))
                Bindings = self.font['Option'].render("Bindings", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Bindings, (720,770+Key.get_size()[1]))
                Exit = self.font['Option'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, (770,970))
            elif self.menu == 'language':
                English = self.font['Menu'].render("English", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(English, (730,390))
                Francais = self.font['Menu'].render("Francais", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Francais, (720,560))
                Exit = self.font['Menu'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, (770,790))
            elif self.menu == 'video':
                Full = self.font['Menu'].render("Full", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Full, (750,350))
                Screen = self.font['Menu'].render("Screen", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Screen, (750,350+Full.get_size()[1]))
                Window = self.font['Menu'].render("Window", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Window, (720,560))
                Exit = self.font['Menu'].render("Exit", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Exit, (770,790))

        elif self.language == 'francais':
            # Title
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Wizarding_Game, (460,120))
            Wizarding_Game = self.font['Title'].render("Wizarding Game", True, self.color['Title']).convert_alpha()
            self.screen.blit(Wizarding_Game, (450,120))
            Devient_un = self.font['Menu'].render("Devient un", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Devient_un, (1055,300))
            Devient_un = self.font['Menu'].render("Devient un", True, self.color['Title']).convert_alpha()
            self.screen.blit(Devient_un, (1050,300))
            Sorcier = self.font['Menu'].render("Sorcier", True, self.color['Shadow']).convert_alpha()
            self.screen.blit(Sorcier, (1110,350))
            Sorcier = self.font['Menu'].render("Sorcier", True, self.color['Title']).convert_alpha()
            self.screen.blit(Sorcier, (1100,350))

            # Button
            if self.menu == 'menu':
                Jouer = self.font['Menu'].render("Jouer", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Jouer, (750,390))
                Options = self.font['Menu'].render("Options", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Options, (720,560))
                Quitter = self.font['Menu'].render("Quitter", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Quitter, (730,780))
            elif self.menu == 'option':
                Langue = self.font['Option'].render("Langue", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Langue, (750,370))
                Video = self.font['Option'].render("Video", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Video, (760,520))
                Son = self.font['Option'].render("Son", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Son, (800,660))
                Controles = self.font['Option'].render("Controles", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Controles, (720,800))
                Retour = self.font['Option'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, (750,970))
            elif self.menu == 'language':
                English = self.font['Menu'].render("English", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(English, (730,390))
                Francais = self.font['Menu'].render("Francais", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Francais, (720,560))
                Retour = self.font['Menu'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, (730,790))
            elif self.menu == 'video':
                Plein = self.font['Menu'].render("Plein", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Plein, (750,350))
                Ecran = self.font['Menu'].render("Ecran", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Ecran, (750,350+Plein.get_size()[1]))
                Fenetre = self.font['Menu'].render("Fenetre", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Fenetre, (720,560))
                Retour = self.font['Menu'].render("Retour", True, self.color['Shadow']).convert_alpha()
                self.screen.blit(Retour, (730,790))

# Class that manage the pause menu (when the player press 'escape')
#


class Game_Pause_Menu():
    """
    Constructor.

    :param screen: the main screen
    :type screen: surface

    :param background: the background of the screen
    :type background: surface

    :param :
    :type :

    :param :
    :type :

    :param :
    :type :

    :param :
    :type :

    :param :
    :type :

    :param :
    :type :

    """
    def __init__(self, screen=None, background=None):
        self.screen = screen
        self.background = background
        self.menu = 'menu'

    def button(self):
        pass

    def text(self):
        pass

if __name__ == "__main__" :
    gameStartMenu = Game_Start_Menu()
    gameStartMenu.run()
