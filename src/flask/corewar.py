from flask import Flask, render_template
import libcore
app = Flask(__name__)


sessions = []

class SessionData:
    def __init__(self, game, game_id):
        self.game = game
        self.game_id = game_id

@app.route("/")
def index():
    return render_template("test.html", variable="this is var")

@app.route("/play/<game_id>")
def play(game_id):
    game = None
    for x in sessions:
        if x.game_id == game_id:
            game = x.game
            break;
    if game == None:
        return render_template("error.html", m="no game found")
    for x in game.logs:
        x.clear()
    mem_dump = game.mem_dump().hex()
    return render_template("play.html", logs=logs, mem=mem_dump)

@app.route("/prepare/<player1>/<player2>/<game_id>")
def prepare(player1, player2, game_id):
    game = libcore.CorewarGame()
    sd = SessionData(game, game_id)
    game.champions.append(player1)
    game.champions.append(player2)
    try:
        game.prepare()
    except:
        return render_template("error.html", m="error in champions")
    return redirect("/play", game) 

@app.route("/update/<game_id>")
def update(game_id):
    game = None
    for x in sessions:
        if x.game_id == game_id:
            game = x.game
            break;
    if game == None:
        return render_template("error.html", m="no game found")
    for x in game.logs:
        x.clear()
    game.update()
    mem_dump = game.mem_dump().hex()
    active_logs = game.logs[0] + game.logs[1]
    active_logs.sort(key=lambda x: x[1])
    return '<div id="logs">{}</div>'.format(logs) + '<div id="mem">{}</div>'.format(mem)
