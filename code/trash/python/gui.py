import sys
from Tkinter import *
from PIL import Image, ImageOps

app = Tk()
email = StringVar()


im = Image.open("images/skull.png")
mask = Image.open("images/mask.png")
#comp = Image.composite(im, mask)
output = ImageOps.fit(im, mask.size, centering=(0.5, 0.5))
#comp.putalpha(mask)
output.putalpha(mask)

comp.show()


#mask = Label(image = skullImage1, borderwidth = '0').grid(row = 0, column = 0)
#output.show()


#app.geometry('300x100+500+500') #create the GUI window the +500+500 refers to the positioning of the window on the PC screen

app.title("digital_euthanasia_beta1.0") #window title
appLabel1 = Label(app, text = '///////////////////////////////////////////////////////////////////', fg = 'white', bg = 'black').grid(row = 0, column = 0) #necessary to write the text in position of the GRID "sticky = E" stands for East and align the text to the right
appLabel2 = Label(app, text = '///// This is a beta version of the software /////', fg = 'white', bg = 'black').grid(row = 1, column = 0)
appLabel3 = Label(app, text = '///////////////////////////////////////////////////////////////////', fg = 'white', bg = 'black').grid(row = 2, column = 0) #necessary to write the text in position of the GRID "E" stands for East and align the text to the right
appLabel4 = Label(app, text = 'e-mail address of the patient', fg = 'white', bg = 'black').grid(row = 4, column = 0) #necessary to write the text in position of the GRID
#appLabel.place(x = 255, y = 255) #necessary to write the text in a specific x y coordinate

#Function that sends the message once the button is pressed
def sendMessage():
	emailSend = email.get()
	appLabel1 = Label(app, text = "Message sent to: " + emailSend, fg = 'white', bg = 'black').grid(row = 7, column = 0)
	return

entryText = Entry(app, textvariable = email).grid(row = 5, column = 0)#the name of the variable HAS to be 'textvariable'
appButton = Button(app, text = "OK", command = sendMessage).grid(row = 6, column = 0) #the "command = " points the button to the function with the name of the variable
app.mainloop()