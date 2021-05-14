#!/usr/bin/env python3
import json
import threading
import logging
import sys

try:
  from SimpleHTTPServer import SimpleHTTPRequestHandler
  from BaseHTTPServer import HTTPServer
except Exception:
  try:
    from http.server import SimpleHTTPRequestHandler
    from http.server import HTTPServer
  except Exception:
    pass


logging.basicConfig()
log = logging.getLogger("web")
log.setLevel(logging.INFO)


class WebHandler (SimpleHTTPRequestHandler):
  def log_message (self, format, *args):
    log.debug(format, *args)

  def do_GET (self):
    if self.path == "/data.txt":
      self.handle_data()
    elif self.path.endswith(".html") or self.path == "/":
      #super(WebHandler,self).do_GET()
      SimpleHTTPRequestHandler.do_GET(self)
    else:
      self.send_error(404)


  def do_OPTIONS (self):
    self.send_response(204)
    self.send_header("Access-Control-Allow-Origin", "*")
    self.send_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS")
    self.send_header("Access-Control-Allow-Headers", "Content-Type")
    self.send_header("Access-Control-Allow-Max-Age", 86400)
    self.end_headers()


  def handle_data (self):
    data = outgoing_data#.encode("utf8")

    #data = json.dumps(data).encode("utf8")

    self.send_response(200)
    self.send_header("Content-Type", "text/plain") #"application/json")
    self.send_header("Content-Length", len(data))
    self.send_header("Access-Control-Allow-Origin", "*")
    self.send_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS")
    self.send_header("Access-Control-Allow-Headers", "Content-Type")
    self.send_header("Access-Control-Allow-Max-Age", 86400)
    self.end_headers()
    self.wfile.write(data)

    import os
    os._exit(0)

    return True



def start ():
  try:
    server = HTTPServer((web_addr, web_port), WebHandler)
  except OSError as e:
    if e.errno == errno.EADDRINUSE:
      log.error("The webserver could not be started because the listening "
                "port\nis already in use.  Try executing the command again.")
      return False
    raise

  log.info("Waiting for web interface...")
  server.serve_forever()





web_addr = ''
web_port = 65432



# lul; this code is awful.
o = []

J = -1
T = 0
P = 0

def record_trace (j, t, p):
  global J,T,P

  if T < t: # Idling
    o.append([J, t - T, P])
  else:
    pass
  T = t
  J = j
  P = p


def build_data ():
  jobs = []
  sizes = []
  priorities = []
  cur = None
  last = (None,None)
  T = 0
  while o:
    j,t,p = o.pop(0)
    T += t
    if last != (j,p) or not o:
      #print(j,t,p)
      sizes.append(T)
      jobs.append(j)
      priorities.append(p)
      T = 0
    last = (j,p)

  maxprio = max(priorities)

  out = dict(
    Jobs=jobs,
    Sizes=sizes,
    Prios=[maxprio-p for p in priorities],
    )
    #job_stats=jobstats,
    #avg_response=responseSum / float(len(jobstats)),
    #avg_turnaround=turnaroundSum / float(len(jobstats)) )

  return out


if __name__ == '__main__':
  import sys, json

  data = sys.stdin.read().strip().split("\n")
  for d in data:
    d = d.strip().split("#", 1)[0].strip()
    if not d: continue

    t,j,p = d.split()
    t,j,p = float(t),int(j),int(p)
    record_trace(j, t, p)

  if J != -1 and o[-1][0] != J:
    log.warning("Can't tell how long last job was")

  out = build_data()

  global outgoing_data
  outgoing_data = json.dumps(out).encode("utf8")

  start()
