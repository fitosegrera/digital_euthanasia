import sys
from Tkinter import * #lib for GUI creation
import Image
import ImageDraw

app = Tk()

im = Image.open("images/skull.png")
transparent_area = (50,80,100,200)

mask=Image.new('L', im.size, color=255)
draw=ImageDraw.Draw(mask) 
draw.rectangle(transparent_area, fill=0)
im.putalpha(mask)
#im.show()
photo = PhotoImage(im)
label = Label(image = photo)
label.im = photo # keep a reference!
label.pack()
#.save('images/output.png')

app.mainloop()