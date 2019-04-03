from django import template

register = template.Library()

@register.filter('next_cycle')
def next_cycle(value):
    return int(value) + 1
