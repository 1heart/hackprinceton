import os
from flask import Flask

import get_messages

app = Flask(__name__)

@app.route('/')
def hello():
    # return get_messages.twitter_get("elonmusk")
	# return str(get_messages.gmail_get("sentimentalprinceton@gmail.com", "hack123hack", "[Gmail]/Sent Mail"))
	return "Hello world."