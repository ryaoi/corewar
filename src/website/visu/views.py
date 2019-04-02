from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.template import loader, Context
from . import libcore
from visu.models import logs, memory

# Create your views here.

def play_game(cycle):
    game = libcore.CorewarGame()
    game.champions.append("../../resources/test_champ1.cor")
    game.champions.append("../../resources/test_champ2.cor")
    game.prepare()
    for b in range(10):
        game.update()
        active_logs = game.logs[0] + game.logs[1]
        active_logs.sort(key=lambda x: x[1])
        messages = [x[0] for x in active_logs]
        nl = logs()
        nl.save()
        nl.log1 = messages
        nl.save()
        mem = game.mem_dump()
        screen = ""
        i = 0
        for x in mem:
            if i % 64 == 0:
                screen = screen + "\n"
            else:
                screen += format(x, '02X')
            i = i + 1
        screen += '\n'
        nm = memory(screen=screen)
        nm.save()

def index(request):
    template = loader.get_template('visu/index.html')
    context = {
            } 
    return HttpResponse(template.render(context, request))

def play_cycle(request, cycle):
    template = loader.get_template('visu/play.html')
    context = {
            "logs" : logs.objects.get(id=str(cycle)).log1,
            "hello" : "click for play the cycle",
            "screen": memory.objects.get(id=str(cycle)).screen, 
            "cycle": cycle
            } 
    return HttpResponse(template.render(context, request))

def play(request):
    play_game(10)
    return redirect('play_cycle', cycle='1')
