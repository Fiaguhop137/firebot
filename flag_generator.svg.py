import threading
HEIGHT=360
WIDTH=int(HEIGHT * 4 / 3)
code,last_code="",""
def terminal_input():
    global code
    while True:
        try:
            text=input("Paste or type your code here: ").strip().lower()
            code="".join(c for c in text if c in "0123456789abcdef")
        except EOFError:
            break
def make_svg(code):
    colors=len(code)//6
    if colors==0:
        return
    with open("flag.svg","w") as f:
        f.write(f'<svg xmlns="http://www.w3.org/2000/svg" 'f'width="{WIDTH}" height="{HEIGHT}">\n')
        for i in range(colors):
            y1=i*HEIGHT//colors
            y2=(i+1)*HEIGHT//colors
            r=int(code[i*6:i*6+2],16)
            g=int(code[i*6+2:i*6+4],16)
            b=int(code[i*6+4:i*6+6],16)
            f.write(f'<rect x="0" y="{y1}" 'f'width="{WIDTH}" height="{y2-y1}" 'f'fill="#{r:02x}{g:02x}{b:02x}"/>\n')
        f.write("</svg>\n")
threading.Thread(target=terminal_input, daemon=True).start()
while True:
    if code!=last_code:
        make_svg(code)
        last_code=code