"""
	This contains the functions that get the last post/tweet/email.
"""

# Indico sentiment analysis

import indicoio

api_key = "ad828e5b5cde7780b7181ac8f6ad4f36"

indicoio.config.api_key = api_key

def sentiment_get(text):
	return indicoio.sentiment(text)


# Twitter

import twitter

ckey = 'Jf9C7YptmIKD7fAOg3P5yi16d'
csecret = 'MH7AEMVXSCffgCzflGOSE6lAeshi4axxh9nDfFXRn1A59fAHNh'
atoken = '2886962559-s0XUNE5a81Zy2Xb5wD5bCKw4Ab791KKxVK87LW6'
asecret = '6BH1JYDSrQjGke6FpkRpg7iHzrRmA4qljhuhr2kK3E3MG'

auth = twitter.OAuth(atoken, asecret, ckey, csecret)
t = twitter.Twitter(auth=auth)


def twitter_get(username):
	user = t.statuses.user_timeline(screen_name=username, count=1)
	return user[0]['text']



# Gmail


import sys, imaplib, getpass, email, email.header, datetime


def gmail_get(username, password, folder):
	"""
	Returns a list of messages.
	"""
	M = imaplib.IMAP4_SSL('imap.gmail.com')
	try:
	    rv, data = M.login(username, password)
	except imaplib.IMAP4.error:
		print("Login failed.")

	rv, mailboxes = M.list()

	rv, data = M.select(folder)
	if rv == 'OK':
	    # print "Processing mailbox...\n"
	    result = process_mailbox(M)
	    M.close()
	    return result
	else:
	    print "ERROR: Unable to open mailbox ", rv

	M.logout()

def process_mailbox(M):
    """
    Processes a mailbox and returns the list of messages.
    """

    rv, data = M.search(None, "ALL")
    if rv != 'OK':
        print "No messages found!"
        return

    list_of_messages = []

    for num in data[0].split():
        rv, data = M.fetch(num, '(RFC822)')
        if rv != 'OK':
            print "ERROR getting message", num
            return

        msg = email.message_from_string(data[0][1])
        #print msg

        if msg.get_content_maintype() == 'multipart': #If message is multi part we only want the text version of the body, this walks the message and gets the body.
            for part in msg.walk():
                if part.get_content_type() == "text/plain":
                    body = part.get_payload(decode=True)
                else:
                            continue


        decode = email.header.decode_header(msg['Subject'])[0]
        subject = unicode(decode[0])
        # print 'Message %s: %s' % (num, subject)
        list_of_messages.append(body)
    
    return list_of_messages
