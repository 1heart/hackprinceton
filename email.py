import smtplib

def alert():
    sendEmail("The following automatic message was sent from HeartBeat. \n We noticed that your friend appears to be in trouble. Please reach out to them, show them that you care.")

def sad():
   sendEmail("The following automatic message was sent from HeartBeat. \n It appears that your friend is feeling sad, we''re sure a call or visit from you would help!")

def sendEmail(message):
    fromaddr = 'helpme@gmail.com'
    toaddrs  = 'sentimentalprinceton@gmail.com'


    # Credentials (if needed)
    username = 'sentimentalprinceton@gmail.com'
    password = 'hack123hack'

    # The actual mail send
    server = smtplib.SMTP('smtp.gmail.com:587')
    server.starttls()
    server.login(username,password)
    server.sendmail(fromaddr, toaddrs, message)
    server.quit()

