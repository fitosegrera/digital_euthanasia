import smtplib  
  
fromaddr = 'fitosegrera@gmail.com' #gmail account that from where the email is sent 
toaddrs  = 'segrr140@newschool.edu' #email that will recieve 
msg = 'my first test "SENDING AN EMAIL WITH PYTHON!!!!"' #message 
  
  
# Credentials (if needed)  
username = 'fitosegrera'  
password = 'Fito1015'  
  
# The actual mail send  
server = smtplib.SMTP('smtp.gmail.com:587')  
server.starttls()  
server.login(username,password)  
server.sendmail(fromaddr, toaddrs, msg)  
server.quit() 