from flask import Flask, render_template, request
import libcore
from flask_wtf.csrf import CsrfProtect
import json, string, random, os, time
from datetime import datetime
import time
import atexit
from apscheduler.schedulers.background import BackgroundScheduler



app = Flask(__name__)

sessions = []


def create_game_id(size):
    ret = ""
    for i in range(size):
        ret = ret + random.choice(string.ascii_letters)
    return ret


server_id =  create_game_id(7)
os.mkdir("/tmp/corewar_server_" + server_id)


class SessionData:
    def __init__(self, game, game_id):
        self.game = game
        self.game_id = game_id
        self.atime = time.time()
        self.p1 = ""
        self.p2 = ""
        self.p3 = ""
        self.p4 = ""

def check_outdated():
    outdated = time.time() - 5 * 60 * 1000
    for x in sessions:
        if x.atime < outdated:
            game_id = x.game_id
            sessions.pop(sessions.index(x))
            try:
                gamedirname = '/' + game_id[:20] + '/'
                for i in range(1 , 4):
                    os.remove("/tmp/corewar_server_" + server_id + gamedirname + "p" + str(i)+ ".cor")
            except:
                continue;



scheduler = BackgroundScheduler()
scheduler.add_job(func=check_outdated, trigger="interval", seconds=300)
scheduler.start()


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/AJAX/game_start", methods=['POST'])
def prepare():
    game = libcore.CorewarGame()
    game_id = create_game_id(200)
    sd = SessionData(game, game_id)
    gamedirname = '/' + game_id[:20] + '/'
    try:
        os.mkdir("/tmp/corewar_server_" + server_id + "/"  + game_id[:20]);
    except:
        return "cannot make a game dir.", 400
    file_list = request.files
    if not file_list:
        return "cannot get a list of files", 400
    i = 0
    while i < 4:
        f = file_list.get("file" + str(i))
        if f == None:
            print("failed at " + str(i))
            break;
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
        f.save("/tmp/corewar_server_" + server_id + gamedirname  + "p" + str(i + 1)+ ".cor")
        game.champions.append("/tmp/corewar_server_" + server_id + gamedirname + "p" + str(i + 1)+ ".cor")
        i += 1
    sessions.append(sd)
    try:
        game.prepare()
    except:
        a = 1
        while a < i:
            os.remove("/tmp/corewar_server_" + server_id + gamedirname + "p" + str(i)+ ".cor")
        return "cannot start game", 400
    return game_id

#tell alex to change the game start request to /AJAX/game_start
@app.route("/AJAX/update", methods=['POST'])
def update():
    game = None
    play_info = request.data
    info = json.loads(play_info)
    game_id = info["game_id"]
    now = time.time()
    for x in sessions:
        if x.game_id == game_id:
            game = x.game
            x.atime = now
    if game == None:
        return "no game found with the game_id", 400
    cycle = int(info["cycles"])
    if cycle > 500:
        return "maximum cycle allowed : 500", 400
    for i in range(cycle):
        game.update()
    mem_dump = game.mem_dump().hex()
    logs_nbr = info["active_logs"]
    active_logs = []
    for l in logs_nbr:
        active_logs.append(game.logs[l])
    for x in game.logs:
        x.clear()
    context = {
            "mem": mem_dump,
            "log": active_logs
            }
    return json.dumps(context)

@app.route("/AJAX/logout", methods=['POST'])
def end_game():
    game_info = request.data
    info = json.loads(game_info)
    game_id = info["game_id"]
    for x in sessions:
        if x.game_id == game_id:
            sessions.pop(sessions.index(x))
            break;
    try:
        gamedirname = '/' + game_id[:20] + '/'
        for i in range(1 , 4):
            os.remove("/tmp/corewar_server_" + server_id + gamedirname + "p" + str(i)+ ".cor")
    except:
        return ""
    return ""


if __name__ == '__main__':
    app.run(debug=True)

atexit.register(lambda: scheduler.shutdown())
