from django.shortcuts import render
from django.http import HttpResponse
from django.template import loader, Context
from . import libcore


# Create your views here.
def index(request):
    game = libcore.CorewarGame()
    game.champions.append("../../resources/test_champ1.cor")
    game.champions.append("../../resources/test_champ2.cor")
    game.prepare()
    hello = "this is var hello"
    for i in range(300):
        game.update()
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
    template = loader.get_template('visu/index.html')
    context = {
            "logs" : game.logs,
            "hello" : "HELLO!",
            "screen": screen 
            } 
    return HttpResponse(template.render(context, request))

