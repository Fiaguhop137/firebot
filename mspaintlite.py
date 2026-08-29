import turtle
screen=turtle.Screen()
screen.title("unforutnatley we ran out of budgte for the real ms paint so i made this garbge instead")
screen.bgcolor("white")
turtle=turtle.Turtle()
turtle.color("black")
turtle.speed(0)
turtle.hideturtle()
turtle.penup()
def mouse_down(event):turtle.pendown()
def mouse_up(event):turtle.penup()
def track_motion(event):
    #i hate how 0,0 is in th emiddel instead of top left cuz its so weird and my brain hurts
    x=event.x-screen.window_width()/2
    y=screen.window_height()/2-event.y
    #hashtag turtle is so annoying why did you pick this thing anyway
    turtle.goto(x,y)
canvas=screen.getcanvas()
canvas.bind('<Motion>',track_motion)
canvas.bind('<Button-1>',mouse_down)
canvas.bind('<ButtonRelease-1>',mouse_up)
screen.mainloop()