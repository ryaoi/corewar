from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.template import loader, Context
from . import libcore
from visu.models import logs, memory

class SessionData:
    def __init__(game, game_id):
        game = game;
        game_id = game_id;

def index(request):
    template = loader.get_template('visu/index.html')
    context = {
            } 
    return HttpResponse(template.render(context, request))

def play(request):
    template = loader.get_template('visu/play.html')
    for x in game.logs:
        x.clear()
    mem_dump = game.mem_dump().hex()
    i = 0
    mem = ""
    while (i < 64):
        mem = mem + mem_dump[i* 128:i * 128 + 128]
        mem = mem + "\n"
        i += 1
    active_logs = game.logs[0] + game.logs[1]
    active_logs.sort(key=lambda x: x[1])
    context = {
            "logs" : active_logs,
            "mem" : mem,
            "mem_dump": mem_dump,
            "cycle": "1",
            "range" : range(64)
            } 
    return HttpResponse(template.render(context, request))

def show_cycle(request, cycle):
    template = loader.get_template('visu/show.html')
    context = {
            "cycle" : cycle,
            }
    return HttpResponse(template.render(context, request))


def prepare(request):
    game = libcore.CorewarGame()
    game_id = "safh glaja" #TODO generate here or client side
    sd = SessionData(game, game_id)
    game.champions.append("../../resources/test_champ1.cor")
    game.champions.append("../../resources/test_champ2.cor")
    game.prepare()
    return redirect('play') #TODO give  gamae_id

def update(request):
    for x in game.logs:
        x.clear()
    game.update()
    #cycle += 1
    mem_dump = game.mem_dump().hex()
    i = 0
    mem = ""
    while (i < 64):
        mem = mem + mem_dump[i* 128:i * 128 + 128]
        mem = mem + "\n"
        i += 1
    active_logs = game.logs[0] + game.logs[1]
    active_logs.sort(key=lambda x: x[1])
    return (active_logs)
