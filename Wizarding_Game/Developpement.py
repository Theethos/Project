import pygame
import os

pygame.init()
screen = pygame.display.set_mode((1600,900), (pygame.FULLSCREEN))
background = pygame.Surface((1600,900)).convert()
screen.fill((20,20,20))
background.fill((20,20,20))

animation_left = []
animation_right = []
path = os.path.join("Wizarding_Game","Image","120x120","Spells","Shieldero")
# Taille = 78 x 31
images_left = ["First_Left.png","Second_Left.png","Third_Left.png","Fourth_Left.png","Fifth_Left.png","Sixth_Left.png","Seventh_Left.png","Fifth_Left.png","Fourth_Left.png","Third_Left.png","Second_Left.png","First_Left.png","Alpha.png"]
images_right = ["First_Right.png","Second_Right.png","Third_Right.png","Fourth_Right.png","Fifth_Right.png","Sixth_Right.png","Seventh_Right.png","Fifth_Right.png","Fourth_Right.png","Third_Right.png","Second_Right.png","First_Right.png","Alpha.png"]

for image in images_left:
    try:
        animation_left.append(pygame.image.load(os.path.join(path,image)))
    except:
        print("Erreur_1")

for image in images_right:
    try:
        animation_right.append(pygame.image.load(os.path.join(path,image)))
    except:
        print("Erreur_2", image)
for nbr in range(len(animation_left)):
   animation_left[nbr].set_colorkey((63,72,204))
   animation_left[nbr] = animation_left[nbr].convert_alpha()
   animation_right[nbr].set_colorkey((63,72,204))
   animation_right[nbr] = animation_right[nbr].convert_alpha()


clock = pygame.time.Clock()        #create pygame clock object
mainloop = True
FPS = 60                           # desired max. framerate in frames per second.
playtime = 0
cycletime = 0
monsieur_left = pygame.image.load(os.path.join("Wizarding_Game","Image","120x120","Harry_Potter_Left.png"))
monsieur_left.set_colorkey((63,72,204))
monsieur_left.convert_alpha()
monsieur_right = pygame.image.load(os.path.join("Wizarding_Game","Image","120x120","Harry_Potter_Right.png"))
monsieur_right.set_colorkey((63,72,204))
monsieur_right.convert_alpha()
interval = .1 # how long one single images should be displayed in seconds
picnr = 0
# attack = (987,315) # 1000 -21(taille de l'attaque) + 8(zone vide de l'animation Seventh), 300 +15(décalage vers la baguette) (1000,300) = pos de la boule vers la gauche
# image_attack = pygame.image.load(os.path.join(path,"Traveling.png"))
# image_attack.convert
# image_attack_debut_fin = pygame.image.load(os.path.join(path,"Beginning_End.png"))
# image_attack_debut_fin.set_colorkey((63,72,204))
# image_attack_debut_fin.convert_alpha()
compteur = 0
surface = pygame.Surface((21,7)).convert() # Taille de l'attaque
surface.fill((20,20,20))
eraser = pygame.Surface((78,101)).convert()
eraser.fill((20,20,20))
side = 'left'
while mainloop:
    animation_left = []
    animation_right = []
    for image in images_left:
        try:
            animation_left.append(pygame.image.load(os.path.join(path,image)))
        except:
            print("Erreur_3")

    for image in images_right:
        try:
            animation_right.append(pygame.image.load(os.path.join(path,image)))
        except:
            print("Erreur_4")
    for nbr in range(len(animation_left)):
       animation_left[nbr].set_colorkey((63,72,204))
       animation_left[nbr] = animation_left[nbr].convert_alpha()
       animation_right[nbr].set_colorkey((63,72,204))
       animation_right[nbr] = animation_right[nbr].convert_alpha()
    # image_attack = None
    # image_attack_debut_fin = None
    # image_attack = pygame.image.load(os.path.join(path,"Traveling.png"))
    # image_attack.convert
    # image_attack_debut_fin = pygame.image.load(os.path.join(path,"Beginning_End.png"))
    # image_attack_debut_fin.set_colorkey((63,72,204))
    # image_attack_debut_fin.convert_alpha()
    milliseconds = clock.tick(FPS)  # milliseconds passed since last frame
    seconds = milliseconds / 1000.0 # seconds passed since last frame (float)
    playtime += seconds
    cycletime += seconds
    if side == 'left':
        if cycletime > interval and picnr < 7:
            #screen.blit(eraser,(928,306))
            screen.blit(animation_right[-1],(0,0))
            mypicture = animation_left[picnr] ##
            screen.blit(monsieur_left, (1000,300))# +71, -42 par rapport a la boule
            screen.blit(mypicture, (928,306))# -71 +42 par rapport au personnage
            cycletime = 0
            if picnr != 6:
                picnr += 1
            elif picnr == 6:
                compteur +=1
                if compteur == 10:
                    compteur = 0
                    picnr += 1
        elif cycletime > interval and picnr < len(animation_left):
            screen.blit(eraser,(928,306))
            #screen.blit(animation_right[-1],(0,0))
            mypicture = animation_left[picnr] ##
            screen.blit(monsieur_left, (1000,300))# +71, -42 par rapport a la boule
            screen.blit(mypicture, (928,306))# -71 +42 par rapport au personnage
            cycletime = 0
            picnr += 1

        # if picnr >= len(animation_left)-6:
        #     if compteur == 0:
        #         if attack[0]-42 > 0: # 2 fois la taille de l'attaque
        #             screen.blit(image_attack_debut_fin, attack)
        #             attack = (attack[0]-21, attack[1]) # On incrémente d'une fois l'attaque (toujours 2 afficher pour effet de longueur)
        #     else:
        #         if attack[0]-42 > 0:
        #             screen.blit(image_attack, attack)
        #             screen.blit(surface, (attack[0]+42, attack[1]))
        #             attack = (attack[0]-21, attack[1])
        #         elif attack[0]-21 > 0: # Si 2 fois la taille ça sort c'est qu'on doit afficher une dernière fois
        #             screen.blit(image_attack_debut_fin, attack)
        #             screen.blit(surface, (attack[0]+42, attack[1]))
        #             screen.blit(surface, (attack[0]+21, attack[1]))
        #             attack = (attack[0]-21, attack[1])
        #         else:
        #             screen.blit(animation_left[-1], (0,0)) # Fin
        #             screen.blit(surface, (attack[0]+21, attack[1]))
            # compteur += 1 # Juste utile pour la premiere apparition de l'attaque
        elif picnr == len(animation_left) : # compteur > 60: # Pour le changement de sens
            picnr = 0
            compteur = 0
            cycletime = 0
            screen.fill((20,20,20))
            # attack = (449,315) #+78 (taille de l'animation Seventh) +15(decalage vers la baguette) par rapport a la boule vers la droite
            side = 'right'
    elif side == 'right':
        if cycletime > interval and picnr < 7:
            #screen.blit(eraser,(382,306))
            screen.blit(animation_right[-1],(0,0))
            mypicture = animation_right[picnr] ##
            screen.blit(monsieur_right, (300,300))# -71, +42 par rapport a la boule
            screen.blit(mypicture, (382,306))# +71, -42 par rapport au personnage
            cycletime = 0
            if picnr != 6:
                picnr += 1
            elif picnr == 6:
                compteur +=1
                if compteur == 10:
                    compteur = 0
                    picnr += 1
        elif cycletime > interval and picnr < len(animation_right) and picnr >= 7:
            screen.blit(eraser,(382,306))
            #screen.blit(animation_right[-1],(0,0))
            mypicture = animation_right[picnr] ##
            screen.blit(monsieur_right, (300,300))# -71, +42 par rapport a la boule
            screen.blit(mypicture, (382,306))# +71, -42 par rapport au personnage
            cycletime = 0
            picnr += 1
    #     if picnr >= len(animation_right)-6:
    #         if compteur == 0:
    #             if attack[0]+42 < screen.get_size()[0]: #Pareil qu'a gauche mais inversé
    #                 screen.blit(image_attack_debut_fin, attack)
    #                 attack = (attack[0]+21, attack[1])
    #         else:
    #             if attack[0]+42 < screen.get_size()[0]:
    #                 screen.blit(image_attack, attack)
    #                 screen.blit(surface, (attack[0]-42, attack[1]))
    #                 attack = (attack[0]+21, attack[1])
    #             elif attack[0]+21 < screen.get_size()[0]:
    #                 screen.blit(image_attack_debut_fin, attack)
    #                 screen.blit(surface, (attack[0]-42, attack[1]))
    #                 screen.blit(surface, (attack[0]-21, attack[1]))
    #                 attack = (attack[0]+21, attack[1])
    #             else:
    #                 screen.blit(animation_left[-1], (0,0))
    #                 screen.blit(surface, (attack[0]-21, attack[1]))
            # compteur += 1
        elif picnr == len(animation_left):
            picnr = 0
            compteur = 0
            cycletime = 0
            screen.fill((20,20,20))
            side = 'left'
            if path == ("Wizarding_Game\\Image\\120x120\\Spells\\Protego"):
                path = os.path.join("Wizarding_Game","Image","120x120","Spells","Spero_Patronum")
            elif path == ("Wizarding_Game\\Image\\120x120\\Spells\\Spero_Patronum"):
                path = os.path.join("Wizarding_Game","Image","120x120","Spells","Shieldero")
            elif path == ("Wizarding_Game\\Image\\120x120\\Spells\\Shieldero"):
                path = os.path.join("Wizarding_Game","Image","120x120","Spells","Protego")
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            mainloop = False # pygame window closed by user
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                mainloop = False # user pressed ESC

    pygame.display.set_caption("[FPS]: %.2f picture: %i" % (clock.get_fps(), picnr))
    #this would repaint the whole screen (secure, but slow)
    #screen.blit(background, (0,0))     #draw background on screen (overwriting all)

    pygame.display.flip()          # flip the screen 30 times a second
print("This 'game' was played for {:.2f} seconds".format(playtime))
