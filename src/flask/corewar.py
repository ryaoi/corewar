from flask import Flask, render_template
import libcore
from flask_wtf.csrf import CsrfProtect
import json, string, random, os, time
from datetime import datetime
from flask import request

app = Flask(__name__)

sessions = []

class SessionData:
    def __init__(self, game, game_id):
        self.game = game
        self.game_id = game_id
        self.atime = time.time()
        self.p1 = ""
        self.p2 = ""
        self.p3 = ""
        self.p4 = ""

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/game_start", methods=['POST'])
def prepare():
    game = libcore.CorewarGame()
    game_id = create_game_id()
    sd = SessionData(game, game_id)
    file_list = request.files
    if not file_list:
       return "cannot get a list of files", 400
    i = 1
    while i < 5:
        f = file_list.get("file" + str(i))
        if not f:
            break;
        if i == 0:
            sd.p1 = f.filename
        elif i == 1:
            sd.p2 = f.filename
        elif i == 2:
            sd.p3 = f.filename
        elif i == 3:
            sd.p4 = f.filename
        f.save("players/" + game_id[:100] +"p" + str(i)+ ".cor")
        game.champions.append("players/" + game_id[:100] +"p" + str(i)+ ".cor")
        i += 1
    sessions.append(sd)
    try:
        game.prepare()
    except:
        a = 1
        while a < i:
            os.remove("players/" + game_id[:100] +"p" +str(a) + ".cor")
        return "cannot start game", 400
    return game_id

def create_game_id():
    ret = ""
    for i in range(200):
        ret = ret + random.choice(string.ascii_letters)
    return ret

@app.route("/AJAX/update/", methods=['POST'])
def update():
    signal.signal(signal.SIGALRM, raise_timeout)
    signal.alarm(60000)
    try:
        game = None
        info = json.loads(play_info)
        game_id = info["game_id"]
        now = time.time()
        for x in sessions:
            if x.game_id == game_id:
                game = x.game
                x.atime = now
       # if now - x.atime > timedelta(minutes=10):
       #     sessions.pop(x)
        if game == None:
            return "no game found with the game_id", 400
        cycle = int(info["cycle"])
        if cycle > 500:
            return "maximum cycle allowd : 500", 400
        for i in range(cycle):
            game.update()
        mem_dump = game.mem_dump().hex()
        logs_nbr = info["active_logs"]
        active_logs = []
        i = 0
        while i < len(logs_nbr):
            active_logs = active_logs + game.logs[int(logs_nbr[i])]
            i += 1
        active_logs.sort(key=lambda x: x[1])
        for x in game.logs:
            x.clear()
        context = {
                "mem": mem_dump,
                "log": active_logs
                }
        return json.dumps(context)
    except:
        return "timeout.", 400

@app.route("/AJAX/logout/", methods=['POST'])
def end_game():
    game_info = request.data
    info = json.loads(game_info)
    game_id = info["game_id"]
    for x in sessions:
        if x.game_id == game_id:
            sessions.pop(sessions.index(x))
            break;
    try:
        os.remove("players/" + game_id[:100] +"p1" + ".cor")
        os.remove("players/" + game_id[:100] +"p2" + ".cor")
        os.remove("players/" + game_id[:100] +"p3" + ".cor")
        os.remove("players/" + game_id[:100] +"p4" + ".cor")
    except:
        return ""
    return ""


if __name__ == '__main__':
    app.run(debug=True)
