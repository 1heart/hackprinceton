import os
from flask import Flask, render_template, jsonify, request

import get_messages, email

from sets import Set


app = Flask(__name__)


lst_of_messages = []

def sort_lst():
	global lst_of_messages
	lst_of_messages = sorted(lst_of_messages, key = lambda x: x.time_object)

def refresh():
	global lst_of_messages
	tweet_messages = get_messages.twitter_get("valar1234")
	lst_of_messages += [message_object for message_object in tweet_messages if message_object not in lst_of_messages]
	email_messages = get_messages.gmail_get("sentimentalprinceton@gmail.com", "hack123hack", "[Gmail]/Sent Mail")
	lst_of_messages += [message_object for message_object in email_messages if message_object not in lst_of_messages]

	sort_lst()

refresh()

@app.route('/')
def hello():
	# return str(lst_of_messages)
	return render_template('index.html')

@app.route('/get_data')
def data():
	refresh()
	return jsonify(result=[item.serialize() for item in lst_of_messages])


def keywordCheck():
	keywords = Set(["suicide", "hopelessness", "cyanide", "self-harm", "kill-myself"  ]); #alert keywords
	keywords2 = Set(['sad', 'depressed', 'depression', 'heartbroken','mournful','pessimistic','somber','down','cheerless','dejected','truobled','unhappy','pain']) #sad keywords

	for message in messages:
	    for word in message.message.split(' '):
	        if word.lower() in keywords: email.alert()
	        if word.lower() in keywords2: email.sad()

keywordCheck();
