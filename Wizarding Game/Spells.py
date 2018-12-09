class Spells():
    def __init__(self, side='neutral'):
        self.side = side
        self.spells = [self.Offensive(), self.Defensive(), self.Stunning(), self.Disappartition(), self.Light(), self.Metamorphosis()]

    def Offensive(self):
        offensive_spell = None
        if self.side = 'darkness':
            offensive_spell = 'Avada Kedravra'
        elif self.side = 'light':
            offensive_spell = 'Expelliarmus'
        else self.side = 'neutral'
            offensive_spell = 'Incarcerous'
        return offensive_spell

    def Defensive(self):
        defensive_spell = None
        if self.side = 'darkness':
            defensive_spell = 'Spero Patronum'
        elif self.side = 'light':
            defensive_spell = 'Protego'
        else self.side = 'neutral'
            defensive_spell = 'Shieldero'
        return defensive_spell

    def Stunning(self):
        stunning_spell = None
        if self.side = 'darkness':
            stunning_spell = 'Crucio'
        elif self.side = 'light':
            stunning_spell = 'Stupefy'
        else self.side = 'neutral'
            stunning_spell = 'Petrificus Totalus'
        return stunning_spell

    def Disappartition(self):
        disappartition_spell = 'Disappartition'
        return disappartition_spell

    def Light(self):
        light_spell = 'Lumos'
        return light_spell

    def Metamorphosis(self):
        metamorphosis_spell = None
        if self.side = 'darkness':
            metamorphosis_spell = 'Serpent Sortia'
        elif self.side = 'light':
            metamorphosis_spell = 'Phoenix Sortia'
        elif self.side = 'neutral':
            metamorphosis_spell = 'Wolf Sortia'

    def run(self):








if __name__ == "__main__" :
    pass
