import pygame
from pygame.locals import *
import math
import Loop
import Drawing


class App:
    # Creation of App object
    def __init__(self):
        self._running = True
        self._display_surf = None
        self.size = self.weight, self.height = 1000, 625
        self.background = None
        self.FPS = 0
        self.key = None
    # Initialisation of App object
    def on_init(self):
        pygame.init()
        self._display_surf = pygame.display.set_mode(self.size, pygame.DOUBLEBUF)
        self.background = pygame.Surface((self.size)).convert()
        self.background_()
        self._running = True

    # Event
    def on_event(self, event):
        if event.type == pygame.QUIT:
            #Si on ferme la fenetre
            self._running = False
        elif event.type == pygame.KEYDOWN:
            #Si on presse Echap
            if event.key == pygame.K_ESCAPE:
                self._running = False
            elif event.key == pygame.K_1:
                self.FPS = 10
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
                self.key ='up'
            elif event.key == pygame.K_DOWN:
                self.key ='down'
            elif event.key == pygame.K_LEFT:
                self.key ='left'
            elif event.key == pygame.K_RIGHT:
                self.key ='right'
        else:
            self.key = 'none'
    # Main loop (where things happen ;) )
    def on_loop(self):
        pass

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

        clock = pygame.time.Clock()
        self.FPS = 60 # FPS max
        playtime = 0
        Harry = Drawing.Bonhomme(self._display_surf, self.background, 'Image\Harry.png', (50,340))
        Hermione = Drawing.Bonhomme(self._display_surf, self.background, 'Image\Hermione.png', (700,340))
        # Frame
        while( self._running ):
            milliseconds = clock.tick(self.FPS)  # Milliseconds passed since last frame
            seconds = milliseconds / 1000.0 # Seconds passed since last frame (float)
            playtime += seconds
            for event in pygame.event.get():
                self.on_event(event)
            # Display FPS
            pygame.display.set_caption("Wizarding Game"" : limit FPS to {}"
                               " (now: {:.2f})".format(self.FPS,clock.get_fps()))
            self.on_loop()

            self._display_surf.blit(self.background, (0,0))
            Harry.draw()
            Hermione.draw_motion(self.key)
            pygame.display.flip()

            self.on_render()

        # Time played
        if playtime < 61:
            print("You played : "+str(int(playtime))+" second(s)")
        else:
            print("You played : "+str(int(playtime)//60)+" minute(s) "+str(int(playtime)%60)+" second(s)")
        # Cleaning
        self.on_cleanup()

    def background_(self):
        #Ciel
        pygame.draw.rect(self.background, (125,125,255), (0,0,self.weight, 400), 0)
        #Herbe
        pygame.draw.rect(self.background, (0,255,0), (0,400,self.weight,self.height), 0)
        #Soleil
        pygame.draw.circle(self.background, (255,255,0), (875, 75), 40, 0)

# Loading
if __name__ == "__main__" :
    theApp = App()
    theApp.on_execute()
