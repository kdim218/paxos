from flask import Flask
from flask import request
from flask import jsonify
import hashlib

# Use a dictionary to hold a mapping from hash digests to an original message.
# If we were to extend this microservice, we would prefer to use a DB over
# memory.
messageDict = {} 

app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():
    return "Hi. This is a simple solution to Paxos' coding challenge #1."

@app.route('/messages', methods = ['POST'])
def postJsonHandler():
    # If we receive a 'message' in the POST's json, then
    # save the SHA256 hash digest in our dictionary for future
    # reference.

    content = request.get_json()
    if 'message' in content:
        currHash = hashlib.sha256()
        currHash.update(content['message'].encode('utf-8'))
        messageDict[currHash.hexdigest()] = content['message']

        return jsonify(digest=currHash.hexdigest());
    else:
        return "Missing a 'message'."

@app.route('/messages/<inHash>', methods = ['GET'])
def getHash(inHash):
    # Return the previously saved message if it exists, otherwise
    # return a 404 """

    if inHash not in messageDict:
        return 'Message not found.', 404
    else:
        return jsonify(message=messageDict[inHash])
