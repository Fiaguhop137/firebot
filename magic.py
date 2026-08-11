import random
def user_input(prompt,valid_options=None):
    user_is_stupid=True
    while user_is_stupid:
        try:
            response=input(f"{prompt} ({", ".join(valid_options[:-1])}, or {valid_options[-1]}) ").strip()
            if valid_options and response not in valid_options:
                print(f"Invalid input. Please choose {", ".join(valid_options[:-1])}, or {valid_options[-1]}.")
                continue
            user_is_stupid=False
            return response
        except Exception as e:
            print(f"Invalid input. Please try again. ({e})")
class stats:
    def __init__(self,attack,speed,defense,health):
        self.attack=attack
        self.speed=speed
        self.defense=defense
        self.health=health
class powers:
    def __init__(self,basic,alignnment,cosmic):
        self.basic=basic
        self.alignnment=alignnment
        self.cosmic=cosmic
class player:
    def __init__(self):
        self.name=user_input("What would you like to name your character?")
        rand=user_input("Would you like to randomize your character's stats and powers?",["yes","no"]).lower()
        if rand=="yes":
            basic=random.choice(["fire","metal","wood","earth","water"]*2+["avatar"])
            alignment=random.choice(["light","dark"]*4+["neutral"])
            cosmic=random.choice(["space","time"]*5+["reality"])
        else:
            basic=user_input("What would you like your character's basic power to be?",["fire","metal","wood","earth","water"]).lower()
            alignment=user_input("What would you like your character's alignment to be?",["light","dark"]).lower()
            cosmic=user_input("What would you like your character's cosmic power to be?",["space","time"]).lower()
        self.stats=stats(10,20,10,50)
        self.powers=powers(basic,alignment,cosmic)
        self.pets=[]    
print("Welcome to the game! You are a player in a world of magic and adventure. You will be able to choose your character's stats and powers, and then embark on a journey to defeat the evil forces that threaten the land.")
player=player()
