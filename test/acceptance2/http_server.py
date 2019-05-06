from flask import Flask
from flask import request

app = Flask(__name__)

@app.route('/', methods=['POST'])
def main():
    print(request.get_json())
    return "ok"