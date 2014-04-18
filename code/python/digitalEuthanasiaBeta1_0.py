#/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#This Python code is the first stage of a critical software designed as part of a system that allows a user to
#commit DIGITAL EUTHANASIA. It is a work in progress...
#Author: fito_segrera
#For detailed info visit: fii.to 
#/////////////////////////////////////////////////////////////////////////////////////////////////////////////

import smtplib #imports lib for sending emails 
import sys
from Tkinter import * #lib for GUI creation
#from PIL import ImageTk, Image #lib for importing images

app = Tk() #create a Tkinter object

#Load images
#skullImage1 = PhotoImage(file = "images/skull.gif")
#img1 = Label(image = skullImage1, borderwidth = '0').grid(row = 0, column = 0)

#photo = ImageTk.PhotoImage(skullImage).grid(row = 7, column = 0)

fromaddr = 'fitosegrera@gmail.com' #gmail account that from where the email is sent 
msg = 'IT IS MY WILL TO COMMIT DIGITAL EUTHANASIA' #message 

# Credentials (if needed)  
username = 'fitosegrera'  
password = 'Fito1015'  

email = StringVar() #email that will recieve 
server = smtplib.SMTP('smtp.gmail.com:587')
#app.geometry('300x100+500+500') #create the GUI window the +500+500 refers to the positioning of the window on the PC screen
app.configure(background = "black")
app.title("digital_euthanasia_beta1.0") #window title
appLabel1 = Label(app, text = '///////////////////////////////////////////////////////////////////', fg = 'white', bg = 'black').grid(row = 1, column = 0) #necessary to write the text in position of the GRID "sticky = E" stands for East and align the text to the right
appLabel2 = Label(app, text = '///// This is a beta version of the software /////', fg = 'white', bg = 'black').grid(row = 2, column = 0)
appLabel3 = Label(app, text = '///////////////////////////////////////////////////////////////////', fg = 'white', bg = 'black').grid(row = 3, column = 0) #necessary to write the text in position of the GRID "E" stands for East and align the text to the right
appLabel4 = Label(app, text = 'e-mail address of the patient', fg = 'white', bg = 'black').grid(row = 4, column = 0) #necessary to write the text in position of the GRID
#appLabel.place(x = 255, y = 255) #necessary to write the text in a specific x y coordinate

#Function that sends the message once the button is pressed
def sendMessage():
	toaddrs = email.get() #email that will recieve 
	# The actual mail send    
	server.starttls() 
	server.login(username,password)  
	server.sendmail(fromaddr, toaddrs, msg)  
	server.quit()
	#End of email sending
	appLabel1 = Label(app, text = "Message sent to: " + toaddrs, fg = 'black', bg = 'yellow').grid(row = 7, column = 0)

entryText = Entry(app, textvariable = email, fg = 'black', bg = 'grey').grid(row = 5, column = 0)#the name of the variable HAS to be 'textvariable'
appButton = Button(app, text = "OK", command = sendMessage, fg = 'white', bg = 'black').grid(row = 6, column = 0) #the "command = " points the button to the function with the name of the variable

#////////////////////
#///// MENU BAR /////
#////////////////////
menuBar = Menu(app, fg = 'white', bg = 'black') #create a menu object
#///// File /////
fileMenu = Menu(menuBar, fg = 'white', bg = 'black') #create a filemenu button
fileMenu.add_command(label = "new") #add a comand called "new" to the file menu
fileMenu.add_command(label = "open") #add a comand called "open" to the file menu
fileMenu.add_command(label = "save as..") #add a comand called "save as.." to the file menu
fileMenu.add_command(label = "close") #add a comand called "close" to the file menu
menuBar.add_cascade(label = "File", menu = fileMenu)
#///// Help /////
helpMenu = Menu(menuBar, fg = 'white', bg = 'black') #create a helpMenu button
helpMenu.add_command(label = "documentation") #add a comand called "documentation" to the file menu
helpMenu.add_command(label = "about") #add a comand called "about" to the file menu
menuBar.add_cascade(label = "Help", menu = helpMenu)

app.config(menu = menuBar)

app.mainloop()