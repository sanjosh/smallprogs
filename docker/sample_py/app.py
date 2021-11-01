
from flask import Flask

app = Flask(__name__)

@app.route("/")
def hello():
    return "hello"

if __name__ == '__main__':
    create_app().run(host='0.0.0.0', port=5000, debug=True)

