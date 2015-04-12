import os
from flask import Flask

import get_messages

app = Flask(__name__)


lst_of_messages = []

def sort_lst():
	global lst_of_messages
	lst_of_messages = sorted(lst_of_messages, key = lambda x: x.time_object)

def refresh():
	global lst_of_messages
	tweet_messages = get_messages.twitter_get("elonmusk")
	lst_of_messages += [message_object for message_object in tweet_messages if message_object not in lst_of_messages]
	email_messages = get_messages.gmail_get("sentimentalprinceton@gmail.com", "hack123hack", "[Gmail]/Sent Mail")
	lst_of_messages += [message_object for message_object in email_messages if message_object not in lst_of_messages]

	sort_lst()



refresh()

@app.route('/')
def hello():
    return str([msg.message for msg in lst_of_messages])