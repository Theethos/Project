
class Character():
	def __init__(self, pseudo=None, race=None, origin=None, level=1, side=None, statute='Children'):
		self.name = pseudo # /type string
		self.race = race # [Human, Giant, Centaur, Goblin, Troll, Elf, Ghost] /class Race
		self.origin = origin # [Muggle, Half-blood, Wizard] /type string
		self.level = level # 1 -> 50 /type int
		self.side = side # [Darkness, Brightness] ? /type string
		self.statute = statute # [Children, Teenager, Adult] /class Statute

	def Creation(self):
		# Initialisation
		print("Choisissez ")

class Race():
	def __init__(self, spells=None, class_=None, features=None, ):
		self.spells = spells # type List
		self._class = class_ # [Support, Tank, Dps] /type string
		self.features = features #type List
		self.appearance = None
