import random
def user_input(prompt,valid_options=None):
    user_is_stupid=True
    while user_is_stupid:
        try:
            response=input(f"{prompt} ({', '.join(valid_options[:-1])} or {valid_options[-1]}) ").strip() if valid_options else input(f"{prompt} ").strip()
            if valid_options and response not in valid_options:
                print(f"Invalid input. Please choose {', '.join(valid_options[:-1])} or {valid_options[-1]}.")
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
    def __init__(self,basic,alignment,cosmic):
        self.basic=basic
        self.alignment=alignment
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
            cosmic=user_input("What would you like your character's cosmic power to be?",["space","time","reality"]).lower()
        self.stats=stats(10,20,10,50)
        self.powers=powers(basic,alignment,cosmic)
        self.pets=[]  
        self.rare_traits=((self.powers.basic=="avatar")+(self.powers.alignment=="neutral")+(self.powers.cosmic=="reality"))
print("Welcome to the game! You are a player in a world of magic and adventure. You will be able to choose your character's stats and powers, and then embark on a journey to defeat the evil forces that threaten the land.")
player=player()
print(f"""{player.name} has been created with the following stats: 
Attack: {player.stats.attack} 
Speed: {player.stats.speed} 
Defense: {player.stats.defense} 
Health: {player.stats.health} 
{'You are an Avatar!' if player.powers.basic=='avatar' else f'Your Basic Power: {player.powers.basic}'} 
{'You are neutral!' if player.powers.alignment=='neutral' else f'Your Alignment: {player.powers.alignment}'} 
{'You are a reality-bender!' if player.powers.cosmic=='reality' else f'Your Cosmic Power: {player.powers.cosmic}'}""")
if player.rare_traits==1:
    if player.powers.basic=='avatar':print("As an Avatar, you have the ability to control all elements and have access to powerful abilities. Use your powers wisely to defeat your enemies and protect the land ")
    if player.powers.alignment=='neutral':print("As a neutral character, you have the ability to balance the forces of light and dark and see the objective. Use your powers wisely to maintain harmony in the land ")
    if player.powers.cosmic=='reality':print("As a reality-bending character, you have the ability to manipulate space and time and have access to powerful abilities. Use your powers wisely to achieve your goals and explore the universe ")
elif player.rare_traits==2:
    if player.powers.basic=='avatar':
        if player.powers.alignment=='neutral':print("As a neutral Avatar, you have the ability to control all elements and balance the forces of light and dark. Use your powers wisely to restore harmony in the land and defeat your enemies ")
        if player.powers.cosmic=='reality':print("As a reality-bending Avatar, you have the ability to manipulate space and time and have access to all the elements. Use your powers wisely to journey through the universe and defeat your enemies ")
    else:
        # If they have 2 rare traits, but not the Avatar power, we can assume they have the other two rare traits
        print("As a neutral reality-bending character, you have the ability to manipulate space and time and balance the forces of light and dark. Use your powers wisely to restore harmony to the land and achieve your goals ")
elif player.rare_traits==3:
    print("Legend has it that one in a thousand people are neutral reality-bending Avatars, and you are one of them! You have the ability to control all elements, manipulate space and time, and balance the forces of light and dark. Use your powers wisely to restore harmony to the land and achieve your goals ")
