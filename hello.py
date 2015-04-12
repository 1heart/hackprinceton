import os, arduino, time, datetime, Queue
from flask import Flask, render_template, jsonify, request

import get_messages, email

from sets import Set


app = Flask(__name__)

app.debug = True




@app.route('/')
def hello():
	global lst_of_messages
	get_current_time()
	return render_template('index.html')




lst_of_messages = []
sent_objects = set()
current_time = 0

def get_current_time():
	global current_time
	current_time = time.mktime((datetime.datetime.now()).timetuple())

def sort_lst(lst):
	return sorted(lst, key = lambda x: x.time_object)

def refresh(lst_of_messages):
	tweet_messages = get_messages.twitter_get("valar1234")
	lst_of_messages += [message_object for message_object in tweet_messages if message_object not in lst_of_messages]
	email_messages = get_messages.gmail_get("sentimentalprinceton@gmail.com", "hack123hack", "[Gmail]/Sent Mail")
	lst_of_messages += [message_object for message_object in email_messages if message_object not in lst_of_messages]
	lst_of_messages = sort_lst(lst_of_messages)

	sort_lst()

refresh()

@app.route('/')
def hello():
	# return str(lst_of_messages)
	return render_template('index.html')



@app.route('/get_data')
def data():
	global lst_of_messages
	lst_of_messages = refresh(lst_of_messages)
	push_to_arduino()
	return jsonify(result=[item.serialize() for item in lst_of_messages])



def keywordCheck():
	keywords = Set(["suicide", "hopelessness", "cyanide", "self-harm", "kill-myself"  ]); #alert keywords
	keywords2 = Set(['sad', 'depressed', 'depression', 'heartbroken','mournful','pessimistic','somber','down','cheerless','dejected','truobled','unhappy','pain']) #sad keywords

	for message in messages:
	    for word in message.message.split(' '):
	        if word.lower() in keywords: email.alert()
	        if word.lower() in keywords2: email.sad()

keywordCheck();

def push_to_arduino():
	global lst_of_messages
	global current_time
	global sent_objects
	for item in lst_of_messages:
		if item not in sent_objects:
			print(item.sentiment)
			try:
				arduino.send_to_arduino(item.sentiment)
				sent_objects.add(item)

			except:
				pass
	# sentiments = [obj.sentiment for obj in lst_of_messages]
	# for sentiment in sentiments:
	# 	print(sentiment)
	# 	arduino.send_to_arduino(sentiment)
	# 	time.sleep(4)


if __name__ == "__main__":
	app.run()
