import threading
import time
HEIGHT=360
WIDTH=int(HEIGHT*4/3)
code,last_code="",""
def terminal_input():
    global code
    while True:
        try:
            text=input("Paste or type your code here: ").strip().lower()
            code="".join(c for c in text if c in "0123456789abcdef")
        except EOFError:
            break
def compress_colors(colors):
    if not colors:return[]
    compressed,current,count=[],colors[0],1
    for color in colors[1:]:
        if color==current:
            count+=1
        else:
            compressed.append((current, count))
            current=color
            count=1
    compressed.append((current, count))
    return compressed
def make_svg(code):
    colors=[]
    for i in range(0,len(code),6):
        if i+6>len(code):break
        colors.append((int(code[i:i+2], 16),int(code[i+2:i+4], 16),int(code[i+4:i+6], 16)))
    if not colors:return
    colors=compress_colors(colors)
    total_stripes=sum(count for _,count in colors)
    with open("flag.svg","w") as f:
        f.write(f'''<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" height="{HEIGHT}"><!-- Generated using Fiaguhop137's flag generator -->''')        
        y=0
        for(r,g,b),count in colors:
            height=count*HEIGHT//total_stripes
            f.write(f'<rect x="0" y="{y}" 'f'width="{WIDTH}" height="{height}" 'f'fill="#{r:02x}{g:02x}{b:02x}"/>\n')
            y+=height
        f.write("</svg>\n")
threading.Thread(target=terminal_input, daemon=True).start()
while True:
    if code!=last_code:
        make_svg(code)
        last_code=code
    time.sleep(1)