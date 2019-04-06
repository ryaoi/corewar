from flask import Flask, render_template
import libcore
from flask_wtf.csrf import CsrfProtect
import json
import string, random, os, time
from datetime import datetime

csrf = CsrfProtect()
app = Flask(__name__)
csrf.init_app(app)

sessions = []

class SessionData:
    def __init__(self, game, game_id):
        self.game = game
        self.game_id = game_id
        self.atime = time.time()
#csrf able

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

#@app.route("/prepare/<player1>/<player2>/<game_id>")
def prepare(game_info):#upload players with json
    info = json.leads(game_info)
    game = libcore.CorewarGame()
    game_id = create_game_id()
    sd = SessionData(game, game_id)
    sessions.append(sd)
    for i in range(4):
        name = "p" + str(i)
        if info[name]:
            fo = open(game_id[50] +"p" + str(i) + ".cor", "w")
            fo.write(info["p1"])
            fo.close()
            game.champions.append("players/" + game_id[50] +"p" + str(i)+ ".cor")
    try:
        game.prepare()
    except:
        return ""
    return game_id 


def create_game_id():
    ret = ""
    for i in range(200):
        ret = ret + random.choice(string.ascii_letters)
    return ret

##@app.route("/update/<game_id>")
def update(play_info):
    game = None
    info = json.leads(play_info)
    game_id = info["game_id"]
    now = time.time()
    for x in sessions:
        if x.game_id == game_id:
            game = x.game
            x.atime = now
        if now - x.atime > datetime.timedelta(minutes=10):
            sessions.pop(x)
    if game == None:
        return
    cycle = int(info["cycle"])
    for i in range(cycle):
        game.update()
    mem_dump = game.mem_dump().hex()
    logs_nbr = info["active_logs"]
    active_logs = []
    while i in logs_nbr:
        active_logs = active_logs + game.logs[int(i)]
    active_logs.sort(key=lambda x: x[1])
    for x in game.logs:
        x.clear()
    context = {
            "mem": mem,
            "log": active_logs
            }
    delete_untracked_games()
    return json.dumps(context)


def end_game(game_info):
    info = json.leads(game_info)
    game_id = info["game_id"]
    for x in sessions:
        if x.game_id == game_id:
            sessions.pop(x)
            break;
    try:
        os.remove(game_id[50] +"p1" + ".cor")
        os.remove(game_id[50] +"p2" + ".cor")
        os.remove(game_id[50] +"p3" + ".cor")
        os.remove(game_id[50] +"p4" + ".cor")
    except:
        return 

