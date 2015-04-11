import indicoio, twitter


api_key = "ad828e5b5cde7780b7181ac8f6ad4f36"

indicoio.config.api_key = api_key

# print(indicoio.sentiment('not bad !'))

ckey = 'Jf9C7YptmIKD7fAOg3P5yi16d'
csecret = 'MH7AEMVXSCffgCzflGOSE6lAeshi4axxh9nDfFXRn1A59fAHNh'
atoken = '2886962559-s0XUNE5a81Zy2Xb5wD5bCKw4Ab791KKxVK87LW6'
asecret = '6BH1JYDSrQjGke6FpkRpg7iHzrRmA4qljhuhr2kK3E3MG'

auth = twitter.OAuth(atoken, asecret, ckey, csecret)
t = twitter.Twitter(auth=auth)

user = t.statuses.user_timeline(screen_name="elonmusk", count=5)

total_sentiment = 0.0
count = 0
for tweet in user:
	text = tweet['text']
	sentiment = indicoio.sentiment(text)
	print text, sentiment
	total_sentiment += sentiment
	count+=1

print "Average sentiment on last 5 tweets is", total_sentiment/count