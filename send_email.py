import smtplib

def alert():
    sendEmail("The following automatic message was sent from HeartBeat. \n We noticed that your friend appears to be in trouble. Please reach out to them, show them that you care.")

def sad():
   sendEmail("The following automatic message was sent from HeartBeat. \n It appears that your friend is feeling sad, we're sure a call or visit from you would help!")

def sendEmail(text):
    fromaddr = 'helpme@gmail.com'
    toaddrs  = 'sentimentalprinceton@gmail.com'


    # Credentials (if needed)
    username = 'sentimentalprinceton@gmail.com'
    password = 'hack123hack'


    TO = ["sentimentalprinceton@gmail.com"] # must be a list

    SUBJECT = "A friend needs your help! "

    # Prepare actual message

    from email.mime.text import MIMEText
    msg = MIMEText(text)
    msg['From'] = fromaddr
    msg['To'] = toaddrs
    msg['Subject'] = SUBJECT


    # The actual mail send
    server = smtplib.SMTP('smtp.gmail.com:587')
    server.starttls()
    server.login(username,password)
    server.sendmail(fromaddr, toaddrs, msg.as_string())
    server.quit()

