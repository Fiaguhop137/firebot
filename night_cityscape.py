import random
import pygame
WIDTH,HEIGHT=600,600
FPS=24
pygame.init()
screen=pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Night Cityscape")
clock=pygame.time.Clock()
def make_city():
    surface=pygame.Surface((WIDTH,HEIGHT))
    surface.fill(pygame.Color("#0a0f46"))
    y=HEIGHT
    for i in range(30):
        j=0
        for j in range(i*20):
            x=random.randrange(WIDTH)
            pygame.draw.circle(surface,pygame.Color("#ffffff"),(x,y),random.randint(0,2))
            y-=1
        y+=j
    x=0
    return surface
city=make_city()
running=True
while running:
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            running=False
    screen.blit(city,(0,0))
    pygame.display.flip()
    clock.tick(FPS)
pygame.quit()