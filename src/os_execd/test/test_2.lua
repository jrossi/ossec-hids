
local M = {} 


function M.add(user, addr) 
    if not M.state[user] then 
      M.state[user] = { addr }
    else 
      M.state[user][#M.state[user]+1] = addr 
    end
end

function M.del(user, addr)
    M.state[user] = nil 
end

function M.tick(time)
    print("tick")
end

function M.init()
    print "state setup"
    M.state = {}
end

function M.startup()
    print "startup"
end

function M.shutdown()
    print "startup"
end

ar.register_add(M.add)
ar.register_delete(M.del)
ar.register_init(M.init)
ar.register_startup(M.startup)
ar.register_shutdown(M.shutdown)

