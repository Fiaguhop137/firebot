import pygame,threading
pygame.init()
HEIGHT=840
WIDTH=HEIGHT*4/3
screen=pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Flag generator (beta)")
clock=pygame.time.Clock()
code=""
def terminal_input():
    global code
    while True:
        try:
            text=input("Paste or type your code here: ").strip().lower()
            code="".join([c for c in text if c in "0123456789abcdef"])
        except:break
def main():
    global code
    threading.Thread(target=terminal_input,daemon=True).start()
    running,fps=True,1
    while running:
        pygame.event.pump()
        for event in pygame.event.get():
            if event.type==pygame.QUIT:
                running=False
        screen.fill((0,0,0))
        stripe_count=len(code)
        if stripe_count>=6:
            for i in range(int(stripe_count/6)):
                r=int(code[i*6:i*6+2],16)
                g=int(code[i*6+2:i*6+4],16)
                b=int(code[i*6+4:i*6+6],16)
                h=int((HEIGHT*6)/stripe_count)
                pygame.draw.rect(screen,(r,g,b),(0,i*h,WIDTH,h))
        pygame.display.flip()
        clock.tick(fps)
main()
pygame.quit()
