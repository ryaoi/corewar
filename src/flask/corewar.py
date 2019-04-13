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

server_dir = "/tmp/corewar_server_" + create_game_id(7)
os.mkdir(server_dir)

class SessionData:
    def __init__(self, game, game_id):
        self.game = game
        self.game_id = game_id
        self.atime = time.time()
        self.players = []
        self.saved_players = []

def check_outdated():
    outdated = time.time() - 300000
    for x in sessions:
        if x.atime < outdated:
            game_id = x.game_id
            sessions.pop(sessions.index(x))
            for i in x.saved_plaers:
                os.remove(i)
    print("outdated deleted.\n");

scheduler = BackgroundScheduler()
scheduler.add_job(func=check_outdated, trigger="interval", seconds=300)
scheduler.start()

@app.route("/AJAX/game_start", methods=['POST'])
def prepare():
    sd = SessionData(libcore.CorewarGame(), create_game_id(200))
    os.mkdir(server_dir + "/"  + sd.game_id[:20]);
    file_list = request.files
    if not request.files:
        return "cannot get a list of files.", 400
    for i in range(4):
        f = file_list.get("file" + str(i))
        if not f:
            break
            sd.players.append(f.filename)
        f.save(server_dir + "/" + sd.game_id[:20] + "/p" + str(i) + ".cor")
        sd.game.champions.append(server_dir + "/" + sd.game_id[:20] + "/p" + str(i) + ".cor")
        sd.saved_players = sd.game.champions
        sessions.append(sd)
    try:
        sd.game.prepare()
    except:
        for x in sd.saved_players:
            os.remove(x)
        return "cannot start corewar game.", 500
    return sd.game_id

@app.route("/AJAX/update", methods=['POST'])
def update():
    timeout = time.time() + 500
    game = None
    try:
        info = json.loads(request.data)
        game_id = info["game_id"]
        for x in sessions:
            if x.game_id == game_id:
                game = x.game
                x.atime = time.time()
        if game == None:
            return "no game found with the game_id.", 400
    except:
        return "cannot find game with the game_id.", 400
    try:
        cycles = info["cycles"]
        if cycles > 500:
            return "maximum cycle allowed : 500", 400
        for i in range(cycles):
            if time.time() >= timeout:
                return "time out.", 400
            game.update()
    except:
        return "cannot update corewar game.", 400
    mem_dump = game.mem_dump().hex()
    try:
        logs_nbr = info["active_logs"]
        active_logs = []
        for l in logs_nbr:
            active_logs.append(game.logs[l])
    except:
        return "cannot get logs.", 400
    context = {
            "mem": mem_dump,
            "log": active_logs
    }
    dump = json.dumps(context)
    for x in game.logs:
        x.clear()
    return dump

@app.route("/AJAX/logout", methods=['POST'])
def end_game():
    try:
        game_id= json.loads(request.data)["game_id"]
    except:
        return "invalid game_id", 400
    for x in sessions:
        if x.game_id == game_id:
            for i in x.saved_players:
                os.remove(i);
            sessions.pop(sessions.index(x))
            break;
    return ""


if __name__ == '__main__':
    app.run(debug=True)

atexit.register(lambda: scheduler.shutdown())
