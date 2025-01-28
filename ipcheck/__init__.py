from flask import Flask

def __init__():
    app = Flask(__name__)
    from routes import main
    app.register_blueprint(main)
    return app