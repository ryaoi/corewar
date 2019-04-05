from django import template

register = template.Library()

@register.filter('next_cycle')
def next_cycle(value):
    return int(value) + 1


@register.filter('delete_cycle_num')
def delete_cycle_num(value):
    return int(value) -20

@register.filter('get_address')
def get_address(value):
    return ("%#6.4x" % (value * 64))

