import re

f = open('OgrePrerequisites.h')
lines = f.read()

pat = re.compile('class \w+;')
r = pat.search(lines)
out = ''
while r != None:
    c = r.group()
    c = c.split()[-1]
    c = c[:-1]
    out += "'" + c + "',\n"
    lines = lines.replace(r.group(), '')
    r = pat.search(lines)

print out
